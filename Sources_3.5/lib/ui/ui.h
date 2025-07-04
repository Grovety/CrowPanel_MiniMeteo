// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.1
// LVGL version: 8.3.11
// Project name: 3.5

#ifndef _3_5_UI_H
#define _3_5_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined __has_include
#if __has_include("lvgl.h")
#include "lvgl.h"
#elif __has_include("lvgl/lvgl.h")
#include "lvgl/lvgl.h"
#else
#include "lvgl.h"
#endif
#else
#include "lvgl.h"
#endif

#include "ui_helpers.h"
#include "ui_events.h"

// SCREEN: ui_Screen1
void ui_Screen1_screen_init(void);
void ui_event_Screen1(lv_event_t * e);
extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_VocCont;
extern lv_obj_t * ui_VocArae;
extern lv_obj_t * ui_VocConst;
extern lv_obj_t * ui_VocBar;
extern lv_obj_t * ui_VocMin;
extern lv_obj_t * ui_VocMax;
extern lv_obj_t * ui_VocArrow;
extern lv_obj_t * ui_PresCont;
extern lv_obj_t * ui_PresArea;
extern lv_obj_t * ui_PresConst;
extern lv_obj_t * ui_PresArrow;
extern lv_obj_t * ui_Co2Cont;
extern lv_obj_t * ui_Co2Area;
extern lv_obj_t * ui_Co2Const;
extern lv_obj_t * ui_Co2Bar;
extern lv_obj_t * ui_Co2Min;
extern lv_obj_t * ui_Co2Max;
extern lv_obj_t * ui_Co2Arrow;
extern lv_obj_t * ui_HumibilityCont;
extern lv_obj_t * ui_HumArea;
extern lv_obj_t * ui_HumArrow;
extern lv_obj_t * ui_TempCont;
extern lv_obj_t * ui_TempArea;
extern lv_obj_t * ui_TempArrow;
extern lv_obj_t * ui_IaqCont;
extern lv_obj_t * ui_IAQConst;
extern lv_obj_t * ui_IAQArea;
extern lv_obj_t * ui_IAQMax;
extern lv_obj_t * ui_IAQMin;
extern lv_obj_t * ui_IAQBar;
extern lv_obj_t * ui_IAQArrow;
// CUSTOM VARIABLES

// SCREEN: ui_Screen2
void ui_Screen2_screen_init(void);
void ui_event_Screen2(lv_event_t * e);
extern lv_obj_t * ui_Screen2;
void ui_event_Switch2(lv_event_t * e);
extern lv_obj_t * ui_Switch2;
void ui_event_Switch3(lv_event_t * e);
extern lv_obj_t * ui_Switch3;
extern lv_obj_t * ui_Label1;
extern lv_obj_t * ui_Label2;
extern lv_obj_t * ui_Label3;
extern lv_obj_t * ui_Label4;
// CUSTOM VARIABLES

// EVENTS

extern lv_obj_t * ui____initial_actions0;

// IMAGES AND IMAGE SETS
LV_IMG_DECLARE(ui_img_iaq_bar_png);    // assets/IAQ_Bar.png
LV_IMG_DECLARE(ui_img_arrow_bar_png);    // assets/Arrow_bar.png
LV_IMG_DECLARE(ui_img_arrow_png);    // assets/arrow.png
LV_IMG_DECLARE(ui_img_co2_bar_png);    // assets/CO2_Bar.png

// FONTS
LV_FONT_DECLARE(ui_font_CO2Font);
LV_FONT_DECLARE(ui_font_Font1);
LV_FONT_DECLARE(ui_font_Font2);
LV_FONT_DECLARE(ui_font_Font3);
LV_FONT_DECLARE(ui_font_Rus1);

// UI INIT
void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
