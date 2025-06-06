
file(GLOB_RECURSE SRC_UI ${CMAKE_SOURCE_DIR} "ui/*.c")

set(ENTITIES_DIR "${PROJECT_DIR}/main/entities")

idf_component_register(
    SRCS 
        "main.c"
        "./entities/aggregator_wrapper.cpp"
        "./setup/setup_gpio.c"
        "./setup/setup_spi.c"
        "./setup/setup_i2c.c"
        "./device/device_lcd.c"
        "./device/device_touch.c"
        "./device/FT6336U.c"
        "./soft_drv/soft_drv_lvgl_port.c"
        "./lv_ui/lv_ui.c"
        ${SRC_UI}
    INCLUDE_DIRS
        "."
        "./setup/include"
        "./device/include"
        "./soft_drv/include"
        "./lv_ui/include"
        "./ui"
        "entities"
    REQUIRES 
        spi_flash 
        esp_timer 
        lvgl 
        json_parser 
        esp-nimble-cpp
)

target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-missing-field-initializers)

idf_build_get_property(build_components BUILD_COMPONENTS)
foreach(COMPONENT ${build_components})
    if(COMPONENT MATCHES "lvgl" OR COMPONENT MATCHES "lvgl__lvgl")
        set(TARGET_COMPONENT ${COMPONENT})
        break()
    endif()
endforeach()

if(TARGET_COMPONENT STREQUAL "")
    message(FATAL_ERROR "Component 'lvgl' not found.")
else()
    idf_component_get_property(LVGL_LIB ${TARGET_COMPONENT} COMPONENT_LIB)
endif()

target_compile_options(${LVGL_LIB} PRIVATE "-Wno-format")
set(TARGET_COMPONENT "")
