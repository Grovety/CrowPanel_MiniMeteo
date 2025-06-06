#include "aggregator_wrapper.h"
#include "EnvironmentalSensorData.h"
#include "UART.h"
#include "ui/ui.h"
#include "esp_task_wdt.h"


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
    // Сдвигаем значения вправо
    for (int i = 10 - 1; i > 0; --i) {
        arr[i] = arr[i - 1];
    }

    // Сохраняем новое значение в начало
    arr[0] = value;

    // Вычисляем среднее остальных (без нового)
    float sum = 0.0f;
    for (int i = 1; i < 10; ++i) {
        sum += arr[i];
    }
    float avg = sum / (10 - 1);

    // Сравниваем новое значение со средним
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

void aggregator_create(void) {
    UART::instance().init();
    vTaskDelay(pdMS_TO_TICKS(5000));
    for(;;){
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
            lv_label_set_text(ui_PresConst, "\n mmHg");
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
        vTaskDelay(pdMS_TO_TICKS(60000));  // обновляем раз в секунду
    }
}