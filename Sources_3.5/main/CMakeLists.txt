
set(ENTITIES_DIR "${PROJECT_DIR}/main/entities")

set(ENTITIES_SRC 
    "${ENTITIES_DIR}/my_nvs.c"
)

file(
    GLOB_RECURSE LIB_SRC
    "../lib/ui/*.c"
    "../lib/LovyanGFX-master/src/*.c"
    "../lib/LovyanGFX-master/src/*.cpp"
    "../lib/lvgl/src/*.cpp"
    "../lib/lvgl/src/*.c"
    "../lib/TAMC_GT911/*.cpp"
)

idf_component_register(
    SRCS
    ${LIB_SRC}
    "main.cpp"
    ${SRC_UI}
    ${ENTITIES_SRC}
    INCLUDE_DIRS 
    "." 
    "../lib/ui"
    "../lib/lvgl"
    "../lib/LovyanGFX-master/src"
    "../lib/TAMC_GT911"
    "entities"

    REQUIRES
    arduino-esp32
    spi_flash 
    esp_timer 
    json_parser 
    nvs_flash 
)