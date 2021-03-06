/**************************************************************************
 * Copyright (C) 2019-2020  junlon2006
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 **************************************************************************
 *
 * Description : uni_stringhash.c
 * Author      : junlon2006@163.com
 * Date        : 2019.11.06
 *
 **************************************************************************/
#include "uni_stringhash.h"

unsigned int GetStringHashCode(const char *str) {
  unsigned int hashcode = 0;
  unsigned char c;
  unsigned int tmp;
  /* use c perf memory load, use shift perf * 31 */
  while ((c = *str++) != '\0') {
    hashcode += c;
    tmp = hashcode;
    hashcode <<= 5;
    hashcode -= tmp;
  }
  return hashcode;
}
