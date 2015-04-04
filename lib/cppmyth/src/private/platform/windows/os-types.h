#pragma once
/*
 * This file is part of the libCEC(R) library.
 *
 * libCEC(R) is Copyright (C) 2011-2012 Pulse-Eight Limited.  All rights reserved.
 * libCEC(R) is an original work, containing original code.
 *
 * libCEC(R) is a trademark of Pulse-Eight Limited.
 *
 * This program is dual-licensed; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 *
 * Alternatively, you can license this library under a commercial license,
 * please contact Pulse-Eight Licensing for more information.
 *
 * For more information contact:
 * Pulse-Eight Licensing       <license@pulse-eight.com>
 *     http://www.pulse-eight.com/
 *     http://www.pulse-eight.net/
 */

#if !defined(__WINDOWS__)
#define __WINDOWS__
#endif

/* Enable LEAN_AND_MEAN support */
#define WIN32_LEAN_AND_MEAN

/* Don't define min() and max() to prevent a clash with std::min() and std::max */
#ifndef NOMINMAX
#define NOMINMAX
#endif

/* Disable warning C4005: '_WINSOCKAPI_' : macro redefinition */
#pragma warning(disable:4005)
#include <winsock2.h>
#pragma warning(default:4005)
#include <windows.h>
#include <wchar.h>
#include <time.h>
#include <sys/timeb.h>
#include <io.h>
#include <stdlib.h>
#include <errno.h>
#include <stddef.h>
#include <process.h>
#include <stdint.h>
#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif
#include "inttypes.h"

/* prevent inclusion of wingdi.h */
#define NOGDI

typedef SOCKET tcp_socket_t;
#define INVALID_SOCKET_VALUE        INVALID_SOCKET
typedef HANDLE serial_socket_t;
#define INVALID_SERIAL_SOCKET_VALUE INVALID_HANDLE_VALUE

/* Platform dependent path separator */
#ifndef PATH_SEPARATOR_CHAR
#define PATH_SEPARATOR_CHAR '\\'
#define PATH_SEPARATOR_STRING "\\"
#endif

/* Handling of 2-byte Windows wchar strings */
#define WcsLen wcslen
#define WcsToMbs wcstombs
typedef wchar_t Wchar_t; /* sizeof(wchar_t) = 2 bytes on Windows */

#ifndef _SSIZE_T_DEFINED
#ifdef  _WIN64
typedef __int64    ssize_t;
#else
typedef _W64 int   ssize_t;
#endif
#define _SSIZE_T_DEFINED
#endif

#define usleep(t) Sleep((DWORD)(t)/1000)
#define sleep(t)  Sleep((DWORD)(t)*1000)

/* Microsoft Visual C++ compilers */
#if defined(_MSC_VER)

struct timezone
{
  int	tz_minuteswest;
  int	tz_dsttime;
};

/* String to 64-bit int */
#if (_MSC_VER < 1800)
#define atoll(S) _atoi64(S)
#endif

/* Prevent deprecation warnings */
#define snprintf _snprintf
#define strnicmp _strnicmp

#endif /* _MSC_VER */

#define gettimeofday __gettimeofday
__inline int gettimeofday(struct timeval *pcur_time, struct timezone *tz)
{
  if (pcur_time == NULL)
  {
    SetLastError(EFAULT);
    return -1;
  }
  struct _timeb current;
  _ftime(&current);
  pcur_time->tv_sec = (long) current.time;
  pcur_time->tv_usec = current.millitm * 1000L;
  if (tz)
  {
    tz->tz_minuteswest = current.timezone;	/* minutes west of Greenwich  */
    tz->tz_dsttime = current.dstflag;	      /* type of dst correction  */
  }
  return 0;
}
