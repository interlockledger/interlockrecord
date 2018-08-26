/*
 * Copyright (c) 2017-2018 InterlockLedger Network
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
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

