
/**
 * @file    dye.h
 * @brief   Definitions of libdye functions, types and constants
 * @author  Aleksey Kuznetsov (kalexey89)
 */

#pragma once

#ifndef LIBDYE_H
#define LIBDYE_H

#include <stdio.h>

#ifndef __cplusplus
#include <stdbool.h>
#ifndef __bool_true_false_are_defined
/** @internal */
#define __bool_true_false_are_defined 1
#define bool  int
#define true  1
#define false 0
#endif // !__bool_true_false_are_defined
#endif // !__cplusplus

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/** Color list */
enum dye_color
{
  DYE_CURRENT   = -2, ///< Use current color
  DYE_RESET     = -1, ///< Reset to default color
  DYE_BLACK     = 0,  ///< Black
  DYE_NAVYBLUE  = 1,  ///< Navy Blue
  DYE_GREEN     = 2,  ///< Green
  DYE_CYAN      = 3,  ///< Cyan
  DYE_MAROON    = 4,  ///< Maroon
  DYE_PURPLE    = 5,  ///< Purple
  DYE_OLIVE     = 6,  ///< Olive
  DYE_SILVER    = 7,  ///< Silver
  DYE_GREY      = 8,  ///< Grey
  DYE_GRAY      = 8,  ///< Grey
  DYE_BLUE      = 9,  ///< Blue
  DYE_LIME      = 10, ///< Lime
  DYE_TEAL      = 11, ///< Teal
  DYE_RED       = 12, ///< Red
  DYE_MAGENTA   = 13, ///< Magenta
  DYE_YELLOW    = 14, ///< Yellow
  DYE_WHITE     = 15  ///< White
};

/** Output stream color id */
typedef enum dye_color dye_color_t;
/** Output stream handle */
typedef FILE* dye_tty_t;

/**
 * @brief Sets @c fg and @c bg colors respectively as foreground and background to the @c tty output stream
 * @param[in] tty Output stream
 * @param[in] fg  Foreground color
 * @param[in] bg  Background color
 * @return true if success, false othervise
 */
extern bool dye(dye_tty_t tty, dye_color_t fg, dye_color_t bg);

/**
 * @def dyefg(tty, fg)
 * @brief Sets @c fg as foreground color to the @c tty output stream
 * @param[in] tty Output stream
 * @param[in] fg  Foreground color
 * @return true if success, false othervise
 */
#define dyefg(tty, fg) dye((tty), (fg), DYE_CURRENT);

/**
 * @def dyebg(tty, bg)
 * @brief Sets @c bg as a background color to the @c tty output stream
 * @param[in] tty Output stream
 * @param[in] bg  Background color
 * @return true if success, false othervise
 */
#define dyebg(tty, bg) dye((tty), DYE_CURRENT, (bg));

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !LIBDYE_H
