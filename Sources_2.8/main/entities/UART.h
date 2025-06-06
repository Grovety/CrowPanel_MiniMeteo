#pragma once
#include "entities/EnvironmentalSensorData.h"

#include "driver/uart.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include <json_parser.h>
#include <string>
#include <string.h>
#include "esp_system.h"
#include "esp_task_wdt.h"
#include <ctime>
#include "ui/ui.h"

#define EX_UART_NUM UART_NUM_1
#define EX_UART_TX  1
#define EX_UART_RX  2
#define BUF_SIZE    (1024)
#define RD_BUF_SIZE (BUF_SIZE)

extern volatile float latest_temperature = 0;
extern volatile float latest_humidity = 0;
extern volatile float latest_pressure = 0;
extern volatile float latest_IAQ = 0;
extern volatile float latest_CO2 = 0;
extern volatile float latest_VOC = 0;

void update_ui_task() {
    while (true) {      
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(10)); 
    }
}


class UART {
    static constexpr char TAG[] = "uart";
    QueueHandle_t queue;
    jparse_ctx_t jctx;

    static void task(void *pvParameters) {
        UART *uart = static_cast<UART *>(pvParameters);
        uart_event_t event;
        size_t buffered_size = 0;
        uint8_t *dtmp = (uint8_t *)malloc(RD_BUF_SIZE);
        struct EnvironmentalSensor::Data sensor;
        const std::string dev_name = "local";
        for (;;) {
            if (xQueueReceive(uart->queue, (void *)&event,
                              (TickType_t)portMAX_DELAY)) {
                ESP_LOGE(TAG, "event=%d, timeout=%d, size=%u", event.type,
                         event.timeout_flag, event.size);
                switch (event.type) {
                // Event of UART receiving data
                /*We'd better handler data event fast, there would be much more
                data events than other types of events. If we take too much time
                on data event, the queue might be full.*/
                case UART_DATA: {
                    uart_read_bytes(EX_UART_NUM, &dtmp[buffered_size],
                                    event.size, portMAX_DELAY);
                    buffered_size += event.size;
                    if (!event.timeout_flag)
                        break;
                    ESP_LOGE(TAG, "[UART DATA]: %d, %d", buffered_size,
                             event.timeout_flag ? 1 : 0);
                    ESP_LOG_BUFFER_HEXDUMP(TAG, dtmp, buffered_size,
                                           ESP_LOG_INFO);
                    int ret = json_parse_start(&uart->jctx,
                                               reinterpret_cast<char *>(dtmp),
                                               buffered_size);
                    buffered_size = 0;
                    if (ret != OS_SUCCESS) {
                        ESP_LOGE(TAG, "Parser failed: json structure (%d)",
                                 ret);
                        break;
                    }
                    if ((ret == OS_SUCCESS) &&
                        (json_obj_get_float(&uart->jctx, "temperature",
                                            &sensor.temperature) ==
                         OS_SUCCESS) &&
                        (json_obj_get_float(&uart->jctx, "humidity",
                                            &sensor.humidity) == OS_SUCCESS) &&
                        (json_obj_get_float(&uart->jctx, "pressure",
                                            &sensor.pressure) == OS_SUCCESS) &&
                        (json_obj_get_float(&uart->jctx, "co2", &sensor.co2) ==
                         OS_SUCCESS) &&
                        (json_obj_get_float(&uart->jctx, "voc", &sensor.voc) ==
                         OS_SUCCESS) &&
                        (json_obj_get_float(&uart->jctx, "iaq", &sensor.iaq) ==
                         OS_SUCCESS)) {

                        ESP_LOGE(TAG,"Launch ok");
                        EnvironmentalSensor::Flags flags;
                        flags.set_source(EnvironmentalSensor::Source::UART);
                        time_t time_val = time(NULL);
                        uint32_t t = (uint32_t)time_val;

                        latest_temperature=sensor.temperature;
                        latest_humidity=sensor.humidity;
                        latest_pressure=float(sensor.pressure) / 100;
                        latest_IAQ=sensor.iaq;
                        latest_CO2=sensor.co2;
                        latest_VOC=sensor.voc;
                    }
                    json_parse_end(&uart->jctx);
                    memset(dtmp, 0, RD_BUF_SIZE);
                    break;
                }
                default:
                    break;
                }
            }
        }
        free(dtmp);
        dtmp = NULL;
        vTaskDelete(NULL);
    }

  public:
    static UART &instance() {
        static UART instance;
        return instance;
    }

    void init() {
        uart_config_t uart_config = {
            .baud_rate = 115200,
            .data_bits = UART_DATA_8_BITS,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
            .source_clk = UART_SCLK_DEFAULT,
        };

        esp_task_wdt_config_t config = {
            .timeout_ms = 10000,  
        };
        esp_task_wdt_init(&config); 

        uart_driver_install(EX_UART_NUM, BUF_SIZE * 2, BUF_SIZE * 2, 20, &queue,
                            0);
        uart_param_config(EX_UART_NUM, &uart_config);
        uart_set_pin(EX_UART_NUM, EX_UART_TX, EX_UART_RX, UART_PIN_NO_CHANGE,
                     UART_PIN_NO_CHANGE);
        xTaskCreatePinnedToCore(task, "uart task", 3072, this, 12, NULL, 1);
    }
};
