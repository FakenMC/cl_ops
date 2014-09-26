/*
 * This file is part of CL-Ops.
 *
 * CL-Ops is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * CL-Ops is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with CL-Ops. If not, see
 * <http://www.gnu.org/licenses/>.
 * */

/**
 * @file
 * @brief Common data structures and function headers for CL-Ops.
 *
 * @author Nuno Fachada
 */

#ifndef CLO_COMMON_H
#define CLO_COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <cf4ocl2.h>

/** Helper macros to convert int to string at compile time. */
/** @todo Use G_STRINGIFY instead*/
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

/** Default RNG seed. */
#define CLO_DEFAULT_SEED 0

/** Default OpenCL source path. */
#define CLO_DEFAULT_PATH ".." G_DIR_SEPARATOR_S "share" G_DIR_SEPARATOR_S "cl_ops" /// @todo This path should be configured in CMake

/** Resolves to error category identifying string. Required by glib error reporting system. */
#define CLO_ERROR clo_error_quark()

/**
 * @brief Obtains information about an algorithm by finding where this
 * information is located within a vector.
 *
 * @param info The requested information about an algorithm.
 * @param info_v The information vector containing info about algorithms.
 * @param arg_tag Tag identifying the requested algorithm.
 * */
#define CLO_ALG_GET(info, info_v, arg_tag) \
	for (int i___priv = 0; info_v[i___priv].tag; i___priv++) { \
		if (g_str_has_prefix(arg_tag, info_v[i___priv].tag)) { \
			info = info_v[i___priv]; \
			break; \
		} \
	}

/**
 * @brief Performs integer division returning the ceiling instead of
 * the floor if it is not an exact division.
 *
 * @param a Integer numerator.
 * @param b Integer denominator.
 * */
#define CLO_DIV_CEIL(a, b) ((a + b - 1) / b)

/**
 * @brief Calculates an adjusted global worksize equal or larger than
 * the given global worksize and is a multiple of the given local
 * worksize.
 *
 * @param gws Minimum global worksize.
 * @param lws Local worksize.
 * */
#define CLO_GWS_MULT(gws, lws) (lws * CLO_DIV_CEIL(gws, lws))

/**
 * @brief Program error codes.
 * */
/**
 * @brief Error codes.
 * */
enum clo_error_codes {
	CLO_SUCCESS = 0,        /**< Successful operation. */
	CLO_ERROR_OPENFILE = 1, /**< Error code thrown when it's not possible to open file. */
	CLO_ERROR_ARGS = 2,     /**< Error code thrown when passed arguments are invalid. */
	CLO_ERROR_DEVICE_NOT_FOUND = 3, /**< Error code thrown when no OpenCL device is found. */
	CLO_ERROR_STREAM_WRITE = 4,     /**< Error code thrown when an error occurs while writing to a stream. */
	CLO_ERROR_IMPL_NOT_FOUND = 5,   /**< An algorithm implementation was not found. */
	CLO_ERROR_UNKNOWN_TYPE = 6,   /**< Requested OpenCL type does not exist.  */
	CLO_ERROR_LIBRARY = 7          /**< An error ocurred in a third party library. */
};

/**
 * Enumeration of OpenCL types.
 * */
typedef enum {
	CLO_CHAR = 0,
	CLO_UCHAR = 1,
	CLO_SHORT = 2,
	CLO_USHORT = 3,
	CLO_INT = 4,
	CLO_UINT = 5,
	CLO_LONG = 6,
	CLO_ULONG = 7,
	CLO_HALF = 8,
	CLO_FLOAT = 9,
	CLO_DOUBLE = 10
} CloType;

/**
 * Information about an OpenCL type.
 * */
typedef struct clo_type_info CloTypeInfo;

/* Return OpenCL type name. */
const char* clo_type_get_name(CloType type, GError** err);

/* Return OpenCL type size in bytes. */
int clo_type_sizeof(CloType type, GError** err);

CloType clo_type_by_name(const char* name, GError** err);

/** @brief Returns the next larger power of 2 of the given value. */
unsigned int clo_nlpo2(register unsigned int x);

/** @brief Returns the number of one bits in the given value. */
unsigned int clo_ones32(register unsigned int x);

/** @brief Returns the trailing Zero Count (i.e. the log2 of a base 2 number). */
unsigned int clo_tzc(register int x);

/** @brief Returns the series (sum of sequence of 0 to) x. */
unsigned int clo_sum(unsigned int x);

/** @brief Implementation of GLib's GPrintFunc which does not print the
 * string given as a parameter. */
void clo_print_to_null(const gchar *string);

/** @brief Get full kernel path name.
 * @todo REMOVE
 * */
gchar* clo_kernelpath_get(gchar* kernel_filename, char* exec_name);

/** @brief Resolves to error category identifying string, in this case
 *  an error related to ocl-ops. */
GQuark clo_error_quark(void);


#endif
