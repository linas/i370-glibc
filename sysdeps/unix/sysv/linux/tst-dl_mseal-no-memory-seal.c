/* Basic tests for sealing.
   Copyright (C) 2024 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#include <gnu/lib-names.h>

/* This test checks the GNU_PROPERTY_NO_MEMORY_SEAL handling on multiple
   places:

   - On the binary itself.
   - On a LD_PRELOAD library.
   - On a depedency module (tst-dl_mseal-mod-no-memory-seal-2.so).
   - On a audit modules (tst-dl_mseal-no-memory-seal-auditmod.so).
   - On a dlopen dependency opened with RTLD_NODELET
     (tst-dl_mseal-dlopen-no-memory-seal-2.so).
*/

#define LIB_PRELOAD              "tst-dl_mseal-no-memory-seal-preload.so"
#define GLIBC_RTLD_SEAL          "1"

#define LIB_DLOPEN_DEFAULT       "tst-dl_mseal-dlopen-1.so"
#define LIB_DLOPEN_DEFAULT_DEP   "tst-dl_mseal-dlopen-1-1.so"
#define LIB_DLOPEN_NODELETE      "tst-dl_mseal-dlopen-no-memory-seal-2.so"
#define LIB_DLOPEN_NODELETE_DEP  "tst-dl_mseal-dlopen-no-memory-seal-2-1.so"

#define LIB_AUDIT                "tst-dl_mseal-no-memory-seal-auditmod.so"

/* Expected libraries that loader will seal.  */
static const char *expected_sealed_libs[] =
{
  "libc.so",
  "ld.so",
  "tst-dl_mseal-mod-no-memory-seal-1.so",
  LIB_DLOPEN_NODELETE_DEP,
  LIBGCC_S_SO,
};

/* Expected non sealed libraries.  */
static const char *expected_non_sealed_libs[] =
{
  "[vdso]",
  "tst-dl_mseal-no-memory-seal",
  LIB_PRELOAD,
  LIB_AUDIT,
  "tst-dl_mseal-mod-no-memory-seal-2.so",
  LIB_DLOPEN_DEFAULT,
  LIB_DLOPEN_DEFAULT_DEP,
  LIB_DLOPEN_NODELETE,
};

#include "tst-dl_mseal-skeleton.c"
