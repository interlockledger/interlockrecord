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
/** @}*/ //addtogroup irerr_param

/** @}*/ //addtogroup irerr

#endif //__irecord_irdll_H__

