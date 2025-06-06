SET(SOURCES screens/ui_Screen1.c
    screens/ui_Screen2.c
    ui.c
    components/ui_comp_hook.c
    ui_helpers.c
    ui_events.c
    images/ui_img_iaq_bar_png.c
    images/ui_img_arrow_bar_png.c
    images/ui_img_arrow_png.c
    images/ui_img_co2_bar_png.c
    fonts/ui_font_CO2Font.c
    fonts/ui_font_Font1.c
    fonts/ui_font_Font2.c
    fonts/ui_font_Font3.c
    fonts/ui_font_Rus1.c)

add_library(ui ${SOURCES})
