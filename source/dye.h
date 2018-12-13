
#pragma once

#ifndef LIBDYE_H
#define LIBDYE_H

#include <stdio.h>

#ifndef __cplusplus
#include <stdbool.h>
#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined 1
#define bool  int
#define true  1
#define false 0
#endif // !__bool_true_false_are_defined
#endif // !__cplusplus

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

enum dye_color
{
  DYE_CURRENT   = -2,
  DYE_RESET     = -1,
  DYE_BLACK     = 0,
  DYE_NAVYBLUE  = 1,
  DYE_GREEN     = 2,
  DYE_CYAN      = 3,
  DYE_MAROON    = 4,
  DYE_PURPLE    = 5,
  DYE_OLIVE     = 6,
  DYE_SILVER    = 7,
  DYE_GREY      = 8,
  DYE_GRAY      = 8,
  DYE_BLUE      = 9,
  DYE_LIME      = 10,
  DYE_TEAL      = 11,
  DYE_RED       = 12,
  DYE_MAGENTA   = 13,
  DYE_YELLOW    = 14,
  DYE_WHITE     = 15
};

typedef enum dye_color dye_color_t;
typedef FILE* dye_tty_t;

extern bool dye(dye_tty_t tty, dye_color_t fg, dye_color_t bg);

#define dyefg(tty, fg) dye((tty), (fg), DYE_CURRENT);
#define dyebg(tty, bg) dye((tty), DYE_CURRENT, (bg));

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !LIBDYE_H