#include "Arduino.h"
#include "LovyanGFX_Driver.h"
#include <Wire.h>
#include <SPI.h>
#include "ui.h"
#include "lvgl.h"
#include "touch.h"

#include "EnvironmentalSensorData.h"
#include "UART.h"
#include "esp_task_wdt.h"
#include "my_nvs.h"
#include <Ticker.h>

Ticker myTimer;

float temperature_history[10] = {0};  
float humidity_history[10] = {0}; 
float pressure_history[10] = {0}; 

extern bool isC;
extern bool ismmHg;

int cnt=2;

void update_IAQ(float value){
    if (value >= 0 && value <= 50) lv_obj_set_y(ui_IAQArrow, 22); 
    else if (value <= 100)         lv_obj_set_y(ui_IAQArrow, 14); 
    else if (value <= 150)         lv_obj_set_y(ui_IAQArrow, 4); 
    else if (value <= 200)         lv_obj_set_y(ui_IAQArrow, -5); 
    else if (value <= 300)         lv_obj_set_y(ui_IAQArrow, -13); 
    else if (value <= 500)         lv_obj_set_y(ui_IAQArrow, -22); 
    else                           lv_obj_set_y(ui_IAQArrow, -22);
}

void update_CO2(float value){
    if (value >= 0 && value <= 350) lv_obj_set_y(ui_Co2Arrow, 22); 
    else if (value <= 450)          lv_obj_set_y(ui_Co2Arrow, 14); 
    else if (value <= 700)          lv_obj_set_y(ui_Co2Arrow, 4); 
    else if (value <= 1000)         lv_obj_set_y(ui_Co2Arrow, -5); 
    else if (value <= 2500)         lv_obj_set_y(ui_Co2Arrow, -13); 
    else if (value <= 5000)         lv_obj_set_y(ui_Co2Arrow, -22); 
    else                            lv_obj_set_y(ui_Co2Area, -22);
}

void update_VOC(float value){
    if (value >= 0 && value <= 60)  lv_obj_set_y(ui_VocArrow, 22); 
    else if (value <= 200)          lv_obj_set_y(ui_VocArrow, 14); 
    else if (value <= 600)          lv_obj_set_y(ui_VocArrow, 4); 
    else if (value <= 2000)         lv_obj_set_y(ui_VocArrow, -5); 
    else if (value <= 3000)         lv_obj_set_y(ui_VocArrow, -13); 
    else if (value <= 5000)         lv_obj_set_y(ui_VocArrow, -22); 
    else                            lv_obj_set_y(ui_VocArrow, -22);
}

void update_history(float value,lv_obj_t *img,float *arr ) {
    for (int i = 10 - 1; i > 0; --i) {
        arr[i] = arr[i - 1];
    }

    arr[0] = value;

    float sum = 0.0f;
    for (int i = 1; i < 10; ++i) {
        sum += arr[i];
    }
    float avg = sum / (10 - 1);

    if (value > avg + 0.1f) {
        lv_img_set_angle(img, 0);
    } else if (value < avg - 0.1f) {
        lv_img_set_angle(img, 900);
    } else {
        lv_img_set_angle(img, 410);
    }
}

void write(lv_obj_t *label, float value){
    char str[32];
    snprintf(str, sizeof(str), "%d", (int)value);
    lv_label_set_text(label, str);
}


void onTimer() {
        char str[32];
        if(isC){
            snprintf(str, sizeof(str), "%d°C", (int)latest_temperature);
        }
        else{
            latest_temperature=latest_temperature*1.8+32;
            snprintf(str, sizeof(str), "%d°F", (int)latest_temperature);
        }
        lv_label_set_text(ui_TempArea, str);
        update_history(latest_temperature,ui_TempArrow,temperature_history);

        char str3[32];
        snprintf(str3, sizeof(str3), "%d%%", (int)latest_humidity);
        lv_label_set_text(ui_HumArea, str3);
        update_history(latest_humidity,ui_HumArrow,humidity_history);

        char str2[32];
        if(ismmHg){
            latest_pressure=latest_pressure / 1.33322;
            snprintf(str2, sizeof(str2), "%d", (int)latest_pressure);
            lv_label_set_text(ui_PresConst, " mmHg");
        }
        else{
            snprintf(str2, sizeof(str2), "%d", (int)latest_pressure);
            lv_label_set_text(ui_PresConst, "\n      Pha");
        }
        lv_label_set_text(ui_PresArea, str2);
        update_history(latest_pressure,ui_PresArrow,pressure_history);
        if(cnt==2){
            write(ui_IAQArea,latest_IAQ);
            update_IAQ(latest_IAQ);

            write(ui_Co2Area,latest_CO2);
            update_CO2(latest_CO2);

            write(ui_VocArae,latest_VOC);
            update_VOC(latest_VOC);
            cnt=0;
        }

        cnt++;
        esp_task_wdt_reset(); 
}

LGFX gfx; // Ensure that the instance is displayed globally

/* LVGL configuration */
#define HOR_RES 320
#define VER_RES 480
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf_1[HOR_RES * 20];
static lv_color_t buf_2[HOR_RES * 20];

/* Displays refresh callbacks */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
    uint32_t w = area->x2 - area->x1 + 1;
    uint32_t h = area->y2 - area->y1 + 1;
    
    gfx.startWrite();
    gfx.setAddrWindow(area->x1, area->y1, w, h);
    gfx.pushPixels((uint16_t*)color_p, w * h, true);
    gfx.endWrite();
    
    lv_disp_flush_ready(disp);
}

/* Touch input processing */

uint16_t touchX, touchY;
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {
  data->state = LV_INDEV_STATE_REL;
  if ( gfx.getTouch( &touchX, &touchY ) ) {
    data->state = LV_INDEV_STATE_PR;
    data->point.x = touchX;
    data->point.y = touchY;

    Serial.print( "Data x " );
    Serial.println( data->point.x );
    Serial.print( "Data y " );
    Serial.println( data->point.y );
  }
}

void setup() {
    Serial.begin(115200);
    while(!Serial); 
    Serial.println("\n\nSystem starting...");

    pinMode(18, OUTPUT);

    pinMode(38, OUTPUT);
    digitalWrite(38, LOW); 

    gfx.begin();
    gfx.setRotation(2);
    gfx.setBrightness(128);
    digitalWrite(38, HIGH);

    Wire.begin(TOUCH_GT911_SDA, TOUCH_GT911_SCL);
    Serial.println("[I2C] Bus started");

    lv_init();
    lv_disp_draw_buf_init(&draw_buf, buf_1, buf_2, HOR_RES * 20);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = gfx.width();
    disp_drv.ver_res = gfx.height();
    disp_drv.flush_cb = my_disp_flush;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = my_touchpad_read;
    lv_indev_t * touch_indev = lv_indev_drv_register(&indev_drv);
    Serial.printf("[input] The touch device is registered(ID:%p)\n", touch_indev);

    uint8_t gt911_address = 0x14;
    touch_init(gt911_address);

    ui_init();

    my_c_function();

    Serial.println("[system] Initialization complete");
    UART::instance().init();
    vTaskDelay(pdMS_TO_TICKS(5000));
    onTimer();
    myTimer.attach(60, onTimer);
}

void loop() {
    lv_timer_handler();
    vTaskDelay(pdMS_TO_TICKS(10));  
}

