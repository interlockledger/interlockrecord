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
#ifndef __irecord_const_H__
#define __irecord_const_H__

/**
 * @defgroup irconst Constants
 */
/** @addtogroup irconst
 *  @{
 */

//==============================================================================
// Hash algorithms
//------------------------------------------------------------------------------
/**
 * @defgroup irconst Hash algorithms
 */
/** @addtogroup irconst_hash
 *  @{
 */
/**
 * Secure hash with 160 bits defined by FIPS PUB 180.
 * @note This algorithm should not be used unless the inner hardware does not
 * support more robust algorithms.
 */
#define IRH_SHA_1 0

/**
 * Secure hash with 256 bits defined by FIPS PUB 180-2.
 */
#define IRH_SHA_256 1

/**
 * Secure hash with 512 bits defined by FIPS PUB 180-2.
 */
#define IRH_SHA_512 2

/**
 * Secure hash with 256 bits defined by FIPS PUB 202.
 */
#define IRH_SHA3_256 3

/**
 * Secure hash with 512 bits defined by FIPS PUB 202.
 */
#define IRH_SHA3_512 4

/**
 * Secure hash with 256 bits defined by FIPS PUB 202.
 */
#define IRH_COPY 0xFFFF

/** @}*/ //addtogroup irconst_hash

//==============================================================================
// Hash algorithms
//------------------------------------------------------------------------------
/**
 * @defgroup irconst_sign Signing algorithms
 */
/** @addtogroup irconst_sign
 *  @{
 */

/**
 * Signing algorithm defined by PKCS #1.
 */
#define IRS_RSA_PSS 0 

/**
 * Signing algorithm defined by PKCS #1 1.5.
 */
#define IRS_RSA_PKCS_1_5 1

/**
 * Signing algorithm defined by NIST FIPS 186-4.
 */
#define IRS_DSA 2

/**
 * Signing algorithm created by ElGamal.
 */
#define IRS_ELGAMAL 3

/**
 * Signing algorithm using an elliptic curve defined in FIPS PUB 186-4.
 */
#define IRS_ECDSA 4

/**
 * Signing algorithm using Edwards-curves proposed by Daniel J. Bernstein, 
 * Niels Duif, Tanja Lange, Peter Schwabe, and Bo-Yin Yang. This constant
 */
#define IRS_EDDSA_ED25519 5

/** @}*/ //irconst_sign

/** @}*/ //irconst

#endif //__irecord_const_H__

