#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "setup_gpio.h"
#include "setup_spi.h"
#include "setup_i2c.h"
#include "device_lcd.h"
#include "device_touch.h"
#include "soft_drv_lvgl_port.h"
#include "lv_ui.h"
#include "ui/ui.h"
#include "entities/aggregator_wrapper.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "nvs.h"

static const char *TAG = "MAIN";
bool isC = true;
bool ismmHg = true;

bool load_bool(const char *key, bool default_value) {
    nvs_handle_t handle;
    esp_err_t err = nvs_open("storage", NVS_READONLY, &handle);
    if (err != ESP_OK) return default_value;

    int32_t val = 0;
    if (nvs_get_i32(handle, key, &val) == ESP_OK) {
        nvs_close(handle);
        ESP_LOGI(TAG, "Load ok");
        return val != 0;
    } else {
        nvs_close(handle);
        ESP_LOGE(TAG, "Load error");
        return default_value;
    }
}

void app_main(void)
{

    //Setting the pin of the bulb is output mode
    gpio_set_direction(18, GPIO_MODE_OUTPUT);
    //Small screen size necessary initialization pins------------------------------------------------------------
    gpio_set_direction(GPIO_NUM_38, GPIO_MODE_OUTPUT);
    // Set the GPIO pin level to high
    gpio_set_level(GPIO_NUM_38, 1);
//-----------------------------------------------------------------------------------


    setup_gpio_init();
    setup_spi_init();
    setup_i2c_init();
    device_lcd_init();
    device_touch_init();
    soft_drv_lvgl_port_init();
    ui_init();

    esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_LOGW(TAG, "NVS flash corrupted or version changed, erasing...");
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    ESP_ERROR_CHECK(ret);
    ESP_LOGI(TAG, "NVS initialized successfully");

    ismmHg=load_bool("ismmHg",true);
    isC=load_bool("isC",true);

    if(isC==false){
        lv_obj_add_state(ui_Switch3, LV_STATE_CHECKED); 
    }
    if(ismmHg==false){
        lv_obj_add_state(ui_Switch2, LV_STATE_CHECKED); 
    }


    aggregator_create();
}