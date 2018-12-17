
#include "dye.h"

#if defined WIN32 || defined _WIN32 || defined _WIN64
#define DYE_WIN32
#elif defined __unix || defined __unix__ || defined __linux__ || defined __APPLE__ || defined __MACH__
#define DYE_POSIX
#else
#error unsupported platform
#endif

#ifdef DYE_WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <io.h>
#include <windows.h>
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
// DYE_WIN32
#elif defined DYE_POSIX
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#endif // DYE_POSIX

bool dye(dye_tty_t tty, dye_color_t fg, dye_color_t bg)
{
#if defined DYE_WIN32
  static WORD stdout_attrs = 0;
  static WORD stderr_attrs = 0;

  if (!_isatty(_fileno(tty)))
    return false;

  HANDLE tty_handle = (HANDLE) _get_osfhandle(_fileno(tty));
  CONSOLE_SCREEN_BUFFER_INFO tty_info = { 0 };

  if (!GetConsoleScreenBufferInfo(tty_handle, &tty_info))
    return false;

  WORD tty_attrs = tty_info.wAttributes;

  switch (_fileno(tty))
  {
    case STDOUT_FILENO:
    {
      if (!stdout_attrs)
        stdout_attrs = tty_attrs;

      if (fg != DYE_CURRENT)
      {
        tty_attrs &= ~(tty_attrs & 0x0F);
        tty_attrs |= (WORD) (fg == DYE_RESET ? stdout_attrs & 0x0F : fg);
      }

      if (bg != DYE_CURRENT)
      {
        tty_attrs &= ~(tty_attrs & 0xF0);
        tty_attrs |= (WORD) (bg == DYE_RESET ? stdout_attrs & 0xF0 : bg << 4);
      }

      break;
    }
    case STDERR_FILENO:
    {
      if (!stderr_attrs)
        stderr_attrs = tty_attrs;

      if (fg != DYE_CURRENT)
      {
        tty_attrs &= ~(tty_attrs & 0x0F);
        tty_attrs |= (WORD) (fg == DYE_RESET ? stderr_attrs & 0x0F : fg);
      }

      if (bg != DYE_CURRENT)
      {
        tty_attrs &= ~(tty_attrs & 0xF0);
        tty_attrs |= (WORD) (bg == DYE_RESET ? stderr_attrs & 0xF0 : bg << 4);
      }

      break;
    }
    default:
      return false;
  }

  return (bool) SetConsoleTextAttribute(tty_handle, tty_attrs);
// DYE_WIN32
#elif defined DYE_POSIX
  static dye_color_t stdout_fg = DYE_RESET;
  static dye_color_t stdout_bg = DYE_RESET;
  static dye_color_t stderr_fg = DYE_RESET;
  static dye_color_t stderr_bg = DYE_RESET;

  static const unsigned char ansi_fg_color[] =
  {
    0  /* Reset  */,
    30 /* Black  */,  34 /* NavyBlue */,  32 /* Green  */,  36 /* Cyan   */,
    31 /* Maroon */,  35 /* Purple   */,  33 /* Olive  */,  37 /* Silver */,
    90 /* Grey   */,  94 /* Blue     */,  92 /* Lime   */,  96 /* Teal   */,
    91 /* Red    */,  95 /* Magenta  */,  93 /* Yellow */,  97 /* White  */
  };

  static const unsigned char ansi_bg_color[] =
  {
    0   /* Reset  */,
    40  /* Black  */,  44  /* NavyBlue */,  42  /* Green  */,  46  /* Cyan   */,
    41  /* Maroon */,  45  /* Purple   */,  43  /* Olive  */,  47  /* Silver */,
    100 /* Grey   */,  104 /* Blue     */,  102 /* Lime   */,  106 /* Teal   */,
    101 /* Red    */,  105 /* Magenta  */,  103 /* Yellow */,  107 /* White  */
  };

  static const char* ansi_term[] =
  {
    "ansi",     "color",  "console",  "cygwin", "gnome",
    "konsole",  "kterm",  "linux",    "msys",   "putty",
    "rxvt",     "screen", "vt100",    "xterm",
    0 /* End */
  };

  if (!isatty(fileno(tty)))
    return false;

  const char* term = getenv("TERM");
  unsigned char is_ansi_term = 0;

  for (const char** t = &ansi_term[0]; *t && !is_ansi_term; ++t)
  {
    if (strncmp(term, *t, strlen(*t)) == 0)
      is_ansi_term = 1;
  }

  if (!is_ansi_term)
    return false;

  dye_color_t _fg = DYE_RESET;
  dye_color_t _bg = DYE_RESET;

  switch (fileno(tty))
  {
    case STDOUT_FILENO:
      stdout_fg = _fg = fg == DYE_CURRENT ? stdout_fg : fg;
      stdout_bg = _bg = bg == DYE_CURRENT ? stdout_bg : bg;
      break;
    case STDERR_FILENO:
      stderr_fg = _fg = fg == DYE_CURRENT ? stderr_fg : fg;
      stderr_bg = _bg = bg == DYE_CURRENT ? stderr_bg : bg;
      break;
    default:
      return false;
  }

  return fprintf(tty, "\x1B[0;%u;%um", ansi_fg_color[_fg + 1], ansi_bg_color[_bg + 1]) > 0;
#endif // DYE_POSIX
}

#undef DYE_WIN32
#undef DYE_POSIX
