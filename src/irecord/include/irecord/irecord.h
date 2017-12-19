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
#ifndef __irecord_irecord_H__
#define __irecord_irecord_H__

#include <irecord/irdll.h>

/**
 * @defgroup irecord_pub Public Functions
 */
/** @addtogroup irecord_pub
 *  @{
 */

/**
 * Type of the InterlockRecord context. It should always be threated as an
 * opaque value.
 */
typedef void * IRContext;

//==============================================================================
// Initialization/Deinitialization
//------------------------------------------------------------------------------
/**
 * @defgroup irecord_pub_init Initialization/Deinitialization
 */
/** @addtogroup irecord_pub_init
 *  @{
 */
/**
 * Creates a new IRContext. Each context will be kept
 *
 * @param[in] configFile Path to the configuration file.
 * @param[out] context The new context.
 * @return IRE_SUCCESS on success or other error code in case of failure.
 */
IR_EXPORT_ATTR int IR_EXPORT_CALL IRContextCreate(const char * configFile,
	IRContext * context);

/**
 * Disposes the IRContext created with IRContextCreate().
 *
 * @param[in] context The new context.
 * @return IRE_SUCCESS on success or other error code in case of failure.
 */
IR_EXPORT_ATTR int IR_EXPORT_CALL  IRContextDispose(IRContext context);
/** @}*/ //addtogroup irecord_pub_init

//==============================================================================
// Version information
//------------------------------------------------------------------------------
/**
 * @defgroup irecord_pub_version Version information
 */
/** @addtogroup irecord_pub_version
 *  @{
 */
/**
 * Get the version of the DLL as a string.
 *
 * @param[out] version
 * @param[out] versionSize
 * @return IRE_SUCCESS on success or other error code in case of failure.
 */
IR_EXPORT_ATTR int IR_EXPORT_CALL  IRGetVersion(char * version, int * versionSize);

/**
 * Get the version of the DLL as integers.
 *
 * @param[out] major Major of the version.
 * @param[out] minor Minor of the version.
 * @return IRE_SUCCESS on success or other error code in case of failure.
 */
IR_EXPORT_ATTR int IR_EXPORT_CALL IRGetVersionInt(int * major, int * minor);
/** @}*/ //addtogroup irecord_pub_version

/** @}*/ //addtogroup irecord_pub
#endif // __irecord_irecord_H__

