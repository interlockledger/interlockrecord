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
#ifndef __irecord_irerr_H__
#define __irecord_irerr_H__

// Please declare erros sorted by value in order to avoid accidental duplications

/**
 * @defgroup irerr Error codes
 */
/** @addtogroup irerr
 *  @{
 */

/**
 * Unknown error.
 */
#define IRE_UNKNOWN_ERROR -1

/**
 * Success of the operation.
 */
#define IRE_SUCCESS 0

/**
 * Invalid context.
 */
#define IRE_INVALID_CONTEXT 1 

/**
 * Invalid state. It happens when a given operation cannot be executed due to
 * an invalid state.
 */
#define IRE_INVALID_STATE 2

/**
 * The buffer is too short to hold the information.
 */
#define IRE_BUFFER_TOO_SHORT 3

/**
 * Function not implemented.
 */
#define IRE_NOT_IMPLEMENTED 4

/**
 * Library not initialized.
 */
#define IRE_NOT_INITIALIZED 5

/**
 * Invalid handle.
 */
#define IRE_INVALID_HANDLE 5

/**
 * Unsupported version.
 */
#define IRE_UNSUPPORTED_VERSION 6

/**
 * Unsupported algorithm.
 */
#define IRE_UNSUPPORTED_ALG 7

/**
 * Unsupported root template parameter.
 */
#define IRE_ROOT_TEMPL_UNSUPPORTED_PARAM 8

/**
 * Missing emergency key in root template parameter.
 */
#define IRE_ROOT_TEMPL_MISSING_EKEY 9

/**
 * Missing friendly name in root template parameter.
 */
#define IRE_ROOT_TEMPL_MISSING_FNAME 10

/**
 * Missing owner name in root template parameter.
 */
#define IRE_ROOT_TEMPL_MISSING_OWNER 11

/**
 * The block data is corrupted.
 */
#define IRE_BLOCK_CORRUPTED 12

/**
 * The given block is not a root record.
 */
#define IRE_BLOCK_NOT_ROOT 13

/**
 * The given block is not the parent.
 */
#define IRE_BLOCK_NOT_PARENT 14


//------------------------------------------------------------------------------
/**
 * @defgroup irerr_param Invalid parameter error codes.
 */
/** @addtogroup irerr_param
 *  @{
 */
/**
 * Base value for an invalid parameter.
 * @internal
 */
#define IRE_INVALID_PARAM_BASE 0x7FFFFFF0

/**
 * Maximum value for an invalid parameter error.
 * @internal
 */
#define IRE_INVALID_PARAM_MAX (IRE_INVALID_PARAM_BASE + 15)

/**
 * Generates the error code for the invalid parameter error.
 *
 * @param[in] x The parameter. Must be a value from 0 to 15.
 */
#define IRE_INVALID_PARAM_DEF(x) (IRE_INVALID_PARAM_BASE + (x))

/**
 * Verifies if a given error code is indeed a invalid parameter error.
 *
 * @param[in] x The error code.
 */
#define IRE_IS_INVALID_PARAM(x) \
	(((x) >= IRE_INVALID_PARAM_BASE) && ((x) <= IRE_INVALID_PARAM_MAX))

/**
 * Verifies if a given error code is indeed a invalid parameter error.
 *
 * @param[in] x The error code.
 */
#define IRE_GET_INVALID_PARAM(x) ((x) - IRE_INVALID_PARAM_BASE)

/**
 * Invalid parameter 0.
 */
#define IRE_INVALID_PARAM_00 IRE_INVALID_PARAM_DEF(0)

/**
 * Invalid parameter 1.
 */
#define IRE_INVALID_PARAM_01 IRE_INVALID_PARAM_DEF(1)

/**
 * Invalid parameter 2.
 */
#define IRE_INVALID_PARAM_02 IRE_INVALID_PARAM_DEF(2)

/**
 * Invalid parameter 3.
 */
#define IRE_INVALID_PARAM_03 IRE_INVALID_PARAM_DEF(3)

/**
 * Invalid parameter 4.
 */
#define IRE_INVALID_PARAM_04 IRE_INVALID_PARAM_DEF(4)

/**
 * Invalid parameter 5.
 */
#define IRE_INVALID_PARAM_05 IRE_INVALID_PARAM_DEF(5)

/**
 * Invalid parameter 6.
 */
#define IRE_INVALID_PARAM_06 IRE_INVALID_PARAM_DEF(6)

/**
 * Invalid parameter 7.
 */
#define IRE_INVALID_PARAM_07 IRE_INVALID_PARAM_DEF(7)

/**
 * Invalid parameter 8.
 */
#define IRE_INVALID_PARAM_08 IRE_INVALID_PARAM_DEF(8)

/**
 * Invalid parameter 9.
 */
#define IRE_INVALID_PARAM_09 IRE_INVALID_PARAM_DEF(9)

/**
 * Invalid parameter 10.
 */
#define IRE_INVALID_PARAM_10 IRE_INVALID_PARAM_DEF(10)

/**
 * Invalid parameter 11.
 */
#define IRE_INVALID_PARAM_11 IRE_INVALID_PARAM_DEF(11)

/**
 * Invalid parameter 12
 */
#define IRE_INVALID_PARAM_12 IRE_INVALID_PARAM_DEF(12)

/**
 * Invalid parameter 13.
 */
#define IRE_INVALID_PARAM_13 IRE_INVALID_PARAM_DEF(13)

/**
 * Invalid parameter 14.
 */
#define IRE_INVALID_PARAM_14 IRE_INVALID_PARAM_DEF(14)

/**
 * Invalid parameter 15.
 */
#define IRE_INVALID_PARAM_15 IRE_INVALID_PARAM_DEF(15)

/** @}*/ //addtogroup irerr_param

/** @}*/ //addtogroup irerr

#endif //__irecord_irdll_H__

