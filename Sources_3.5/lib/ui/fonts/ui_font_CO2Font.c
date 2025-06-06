/*******************************************************************************
 * Size: 24 px
 * Bpp: 1
 * Opts: --bpp 1 --size 24 --font D:/3.5/assets/Montserrat-SemiBold.ttf -o D:/3.5/assets\ui_font_CO2Font.c --format lvgl --symbols ₂COVIAQ --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_CO2FONT
#define UI_FONT_CO2FONT 1
#endif

#if UI_FONT_CO2FONT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0041 "A" */
    0x1, 0xe0, 0x0, 0x78, 0x0, 0x3f, 0x0, 0xf,
    0xc0, 0x7, 0x78, 0x1, 0xce, 0x0, 0x73, 0x80,
    0x38, 0x70, 0xe, 0x1c, 0x7, 0x3, 0x81, 0xc0,
    0xe0, 0xff, 0xfc, 0x3f, 0xff, 0x1e, 0x1, 0xe7,
    0x0, 0x39, 0xc0, 0xe, 0xe0, 0x1, 0xc0,

    /* U+0043 "C" */
    0x3, 0xf8, 0xf, 0xfe, 0x3e, 0x1e, 0x38, 0x4,
    0x70, 0x0, 0xf0, 0x0, 0xe0, 0x0, 0xe0, 0x0,
    0xe0, 0x0, 0xe0, 0x0, 0xe0, 0x0, 0xf0, 0x0,
    0x70, 0x0, 0x38, 0x4, 0x3e, 0x1e, 0xf, 0xfe,
    0x3, 0xf8,

    /* U+0049 "I" */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0,

    /* U+004F "O" */
    0x3, 0xf0, 0x3, 0xff, 0x3, 0xe1, 0xf0, 0xe0,
    0x1c, 0x70, 0x3, 0xbc, 0x0, 0xee, 0x0, 0x1f,
    0x80, 0x7, 0xe0, 0x1, 0xf8, 0x0, 0x7e, 0x0,
    0x1f, 0xc0, 0xe, 0x70, 0x3, 0x8e, 0x1, 0xc3,
    0xe1, 0xf0, 0x3f, 0xf0, 0x3, 0xf0, 0x0,

    /* U+0051 "Q" */
    0x3, 0xf0, 0x1, 0xff, 0x80, 0xf8, 0x7c, 0x1c,
    0x3, 0x87, 0x0, 0x39, 0xe0, 0x7, 0x38, 0x0,
    0x77, 0x0, 0xe, 0xe0, 0x1, 0xdc, 0x0, 0x3b,
    0x80, 0x7, 0x38, 0x1, 0xc7, 0x80, 0x78, 0x78,
    0x1e, 0x7, 0xff, 0x80, 0x7f, 0xe0, 0x1, 0xf0,
    0x0, 0xf, 0x18, 0x0, 0xff, 0x80, 0x7, 0xc0,

    /* U+0056 "V" */
    0xe0, 0x3, 0x9c, 0x0, 0xe7, 0x0, 0x79, 0xe0,
    0x1c, 0x38, 0x7, 0xf, 0x3, 0x81, 0xc0, 0xe0,
    0x70, 0x70, 0xe, 0x1c, 0x3, 0x8f, 0x0, 0xf3,
    0x80, 0x1c, 0xe0, 0x7, 0xf0, 0x0, 0xfc, 0x0,
    0x3e, 0x0, 0x7, 0x80, 0x1, 0xe0, 0x0,

    /* U+2082 "₂" */
    0x7c, 0xff, 0xc3, 0x3, 0x6, 0xc, 0x18, 0x70,
    0xff, 0xff
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 288, .box_w = 18, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 279, .box_w = 16, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 122, .box_w = 3, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 323, .box_w = 18, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 323, .box_w = 19, .box_h = 20, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 167, .adv_w = 280, .box_w = 18, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 165, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x2, 0x8, 0xe, 0x10, 0x15, 0x2041
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 65, .range_length = 8258, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 7, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 1, 2, 3, 4, 4, 5, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 1, 2, 3, 2, 2, 4, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    7, -4, 0, -14, -6, -6, 0, -2,
    0, 0, 0, -2, -4, 0, 0, -8,
    -14, -8, -6, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 5,
    .right_class_cnt     = 4,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t ui_font_CO2Font = {
#else
lv_font_t ui_font_CO2Font = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 20,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_CO2FONT*/

