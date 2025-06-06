#include <stdio.h>
#include "esp_log.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "ui.h"

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

void my_c_function() {
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
}