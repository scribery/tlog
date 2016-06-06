/**
 * @file
 * @brief Miscellaneous functions.
 *
 * A collection of miscellaneous function, macros and data types not worthy of
 * their own module.
 */
/*
 * Copyright (C) 2015 Red Hat
 *
 * This file is part of tlog.
 *
 * Tlog is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Tlog is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with tlog; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _TLOG_MISC_H
#define _TLOG_MISC_H

#include <stdlib.h>
#include <stdint.h>
#include <tlog/grc.h>

/** Return number of elements in an array */
#define TLOG_ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

/** Return maximum of two numbers */
#define TLOG_MAX(_a, _b) ((_a) > (_b) ? (_a) : (_b))

/** Return minimum of two numbers */
#define TLOG_MIN(_a, _b) ((_a) < (_b) ? (_a) : (_b))

/** Return an offset of a type member */
#define TLOG_OFFSET_OF(_type, _member) ((size_t) &((_type *)0)->_member)

/**
 * Cast a member of a structure out to the containing structure.
 *
 * @param \_ptr     The pointer to the member.
 * @param \_type    The type of the container this is embedded in.
 * @param \_member  The name of the member within the type.
 *
 */
#define TLOG_CONTAINER_OF(_ptr, _type, _member) \
    ({                                                              \
        const typeof(((_type *)0)->_member) *_mptr = (_ptr);        \
        (_type *)((char *)_mptr - TLOG_OFFSET_OF(_type, _member));  \
    })

/**
 * Convert a nibble (4-bit number) to a hexadecimal digit.
 *
 * @param n     Nibble to convert.
 *
 * @return Hexadecimal digit.
 */
static inline uint8_t
tlog_nibble_digit(uint8_t n)
{
    return (n < 10) ? ('0' + n) : ('a' - 10 + n);
}

/**
 * Calculate number of decimal digits in a size_t number.
 *
 * @param n     The number to count digits for.
 *
 * @return Number of digits.
 */
static inline size_t
tlog_size_digits(size_t n)
{
    size_t d;
    for (d = 1; n > 9; d++, n /= 10);
    return d;
}

/**
 * Retrieve an absolute path to a file either in the build tree, if possible,
 * and if running from the build tree, or at the installed location.
 *
 * @param ppath             Location for the retrieved absolute path.
 * @param prog_path         Path to a program relative to which the build_rel_path
 *                          is specified, to use if running from the build tree.
 * @param build_rel_path    Build tree path relative to prog_path, to use if
 *                          running from the build tree.
 * @param inst_abs_path     Absolute installation path to use if not running
 *                          from the build tree, or if prog_path or
 *                          build_rel_path were not found.
 *
 * @return True if retrieval was successful, false if it failed and errno was
 *         set to indicate the error.
 */
extern tlog_grc tlog_build_or_inst_path(char          **ppath,
                                        const char     *prog_path,
                                        const char     *build_rel_path,
                                        const char     *inst_abs_path);

#endif /* _TLOG_MISC_H */
