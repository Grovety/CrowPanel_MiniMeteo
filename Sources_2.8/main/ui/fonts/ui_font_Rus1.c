/*******************************************************************************
 * Size: 20 px
 * Bpp: 1
 * Opts: --bpp 1 --size 20 --font C:/Users/badjo/SquareLine/assets/Montserrat-SemiBold.ttf -o C:/Users/badjo/SquareLine/assets\ui_font_Rus1.c --format lvgl -r 0x20 --symbols мртс. --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_RUS1
#define UI_FONT_RUS1 1
#endif

#if UI_FONT_RUS1

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+002E "." */
    0xff, 0x80,

    /* U+043C "м" */
    0xf0, 0x1f, 0x81, 0xfe, 0x1f, 0xf0, 0xff, 0xcf,
    0xf6, 0x6f, 0x9e, 0x7c, 0xf3, 0xe3, 0x1f, 0x18,
    0xf8, 0x6,

    /* U+0440 "р" */
    0xef, 0x8f, 0xfc, 0xf0, 0xee, 0x7, 0xe0, 0x7e,
    0x7, 0xe0, 0x7f, 0x7, 0xf0, 0xef, 0xfc, 0xef,
    0x8e, 0x0, 0xe0, 0xe, 0x0, 0xe0, 0x0,

    /* U+0441 "с" */
    0x1f, 0x87, 0xf9, 0xe3, 0xf0, 0xe, 0x1, 0xc0,
    0x38, 0x7, 0x0, 0x70, 0xe7, 0xf8, 0x7e, 0x0,

    /* U+0442 "т" */
    0xff, 0xff, 0xf0, 0xe0, 0x38, 0xe, 0x3, 0x80,
    0xe0, 0x38, 0xe, 0x3, 0x80, 0xe0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 88, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 78, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 258, .box_w = 13, .box_h = 11, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 221, .box_w = 12, .box_h = 15, .ofs_x = 2, .ofs_y = -4},
    {.bitmap_index = 44, .adv_w = 186, .box_w = 11, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 164, .box_w = 10, .box_h = 11, .ofs_x = 1, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0xe, 0x41c, 0x420, 0x421, 0x422
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 1059, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 6, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 0, 0, 0, 1, 2, 3
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 0, 0, 2, 3
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    -3, 0, -6, 6, -3, -2, -16, -7,
    3
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 3,
    .right_class_cnt     = 3,
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
const lv_font_t ui_font_Rus1 = {
#else
lv_font_t ui_font_Rus1 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if UI_FONT_RUS1*/

