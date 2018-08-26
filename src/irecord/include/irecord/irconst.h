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

