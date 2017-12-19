/*
 * Copyright (c) 2017, Open Communications Security
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL OPEN COMMUNICATIONS SECURITY BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef __irecord_irdll_H__
#define __irecord_irdll_H__

/**
 * @defgroup irdll DLL definitions
 */
/** @addtogroup irdll
 *  @{
 */

/**
 * This macro defines the modifier for all DLL public functions. This must be
 * used as follows:
 *
 * @code{.c}
   IR_EXPORT_ATTR return_type IR_EXPORT_CALL functio_name(...);
 * @endcode
 *
 * This modifier is used to ensure that all funcions will be using the standard
 * C function declaration.
 */
#if defined(_MSC_VER)
	#define IR_EXPORT_CALL __cdecl
#else
	#define IR_EXPORT_CALL
#endif //__GNUC__

/**
 * This macro adds the declaration 'extern "C"' if this header is called from
 * a C++ code.
 */
#ifdef __cplusplus
	#define IR_EXPORT_EXTERN_C extern "C"
#else
	#define IR_EXPORT_EXTERN_C
#endif //__cplusplus

/**
 * This macro defines the attribute for all DLL public functions. This must be
 * used as follows:
 *
 * @code{.c}
   IR_EXPORT_ATTR return_type IR_EXPORT_CALL functio_name(...);
 * @endcode
 *
 * On all platforms, it instructs that this function is a C function instead of
 * a C++ function.
 *
 * Additionally, on GCC and CLang, it instructs that the function must have its
 * visibility as public because all other functions will default to private
 * visibility.
 */
#if defined(__GNUC__)
	#ifdef IR_EXPORTS
		#define IR_EXPORT_ATTR IR_EXPORT_EXTERN_C __attribute__((visibility("default")))
	#else
		#define IR_EXPORT_ATTR IR_EXPORT_EXTERN_C
	#endif //IR_EXPORTS
#elif defined(_MSC_VER)
	#define IR_EXPORT_ATTR
#else
	#define IR_EXPORT_ATTR
#endif //__GNUC__
/** @}*/ //addtogroup irdll

#endif //__irecord_irdll_H__

