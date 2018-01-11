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
#include <irecord/irerr.h>
#include <stdint.h>

/**
 * @defgroup irecord_pub Public Functions
 */
/** @addtogroup irecord_pub
 *  @{
 */

//==============================================================================
// Data types
//------------------------------------------------------------------------------
/**
 * @defgroup irecord_pub_types Data types
 */
/** @addtogroup irecord_pub_types
 *  @{
 */
/**
 * Type of the InterlockRecord's context.
 */
typedef int IRContext;

/**
 * Type of the InterlockRecord's object ID.
 */
typedef int IRObjectID;

/** @} */ //irecord_pub_types

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
 * Initializes the library. It is used to prepare the library for the first use.
 *
 * <p>It must be called only once after the library is loaded and before the first
 * use of the library.</p>
 *
 * @return IRE_SUCCESS on success or other error code in case of failure.
 * @note This function is not thread safe.
 * @see IRDeinitialize()
 */
IR_EXPORT_ATTR int IR_EXPORT_CALL IRInitialize();

/**
 * Deinitializes the library. It releases all resources associated with it (all
 * internal objects will be destroyed).
 *
 * <p>It must be called before unload the library.</p>
 *
 * @return IRE_SUCCESS on success or other error code in case of failure.
 * @note This function is not thread safe.
 * @see IRInitialize()
 */
IR_EXPORT_ATTR int IR_EXPORT_CALL IRDeinitialize();
/** @}*/ //addtogroup irecord_pub_init
//==============================================================================
// Context Initialization/Dispose
//------------------------------------------------------------------------------
/**
* @defgroup irecord_pub_context Initialization/Dispose
*/
/** @addtogroup irecord_pub_context
*  @{
*/

/**
 * Creates a new IRContext. Each context will be kept
 *
 * @param[in] configFile Path to the configuration file.
 * @param[out] context The new context.
 * @return IRE_SUCCESS on success or other error code in case of failure.
 * @note This function is thread safe.
 */
IR_EXPORT_ATTR int IR_EXPORT_CALL IRContextCreate(const char * configFile, IRContext * context);

/**
 * Disposes the IRContext created with IRContextCreate().
 *
 * @param[in] context The new context.
 * @return IRE_SUCCESS on success or other error code in case of failure.
 * @note This function is thread safe.
 */
IR_EXPORT_ATTR int IR_EXPORT_CALL  IRContextDispose(IRContext context);
/** @}*/ //addtogroup irecord_pub_context

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
 * @param[out] version The buffer that will receive the version string.
 * @param[in,out] versionSize On input, the size of version in characters. On output, it
 * returns the number of characters used including the null terminator.
 * @return IRE_SUCCESS on success or other error code in case of failure.
 * @note The function will return the required size of the buffer if
 * version is NULL or the initial versionSize is smaller than the required size to
 * store the version string. In both cases, the returned error code will be IRE_BUFFER_TOO_SHORT.
 */
IR_EXPORT_ATTR int IR_EXPORT_CALL  IRGetVersion(int * versionSize, char * version);

/**
 * Get the version of the DLL as integers.
 *
 * @param[out] major Major of the version.
 * @param[out] minor Minor of the version.
 * @return IRE_SUCCESS on success or other error code in case of failure.
 */
IR_EXPORT_ATTR int IR_EXPORT_CALL IRGetVersionInt(int * major, int * minor);
/** @}*/ //addtogroup irecord_pub_version


//==============================================================================
// Emergency key
//------------------------------------------------------------------------------
/**
* @defgroup irecord_pub_emergency_key Emergency key
*/
/** @addtogroup irecord_pub_emergency_key
*  @{
*/

/**
* Creates an emergency key as an integer.
*
* @param[in] context The new context.
* @param[in] type The type of the emergency key.
* @param[in] size The size of the emergency key.
* @param[out] hkey The created emergency key.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IREmergencyKeyCreate(IRContext context, int type, int size, int * hKey);

/**
* Disposes an emergency key.
*
* @param[in] context The new context.
* @param[in] hkey The emergency key.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IREmergencyKeyDispose(IRContext context, int hKey);

/**
* Serializes an emergency key.
*
* @param[in] context The new context.
* @param[in] hkey The emergency key.
* @param[in/out] buffSize The buffer size of the serialized emergency key.
* @param[out] buff The emergency key serialized buffer.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IREmergencyKeySerialize(IRContext context, int hKey, int * buffSize, void * buff);

/**
* Loads an emergency key.
*
* @param[in] context The new context.
* @param[in] buffSize The buffer size of the emergency key.
* @param[in] buff The emergency key buffer.
* @param[out] hkey The loaded emergency key.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IREmergencyKeyLoad(IRContext context, int buffSize, void * buff, int * hKey);

/** @}*/ //addtogroup irecord_pub_emergency_key

//==============================================================================
// Root Record Template
//------------------------------------------------------------------------------
/**
* @defgroup irecord_pub_root_record_template Root Record Template
*/
/** @addtogroup irecord_pub_root_record_template
*  @{
*/

/**
* Creates a new Root Record Template.
*
* @param[in] context The new context.
* @param[out] hTemplate The root record template created.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRRootTemplateCreate(IRContext context, int * hTemplate);

/**
* Disposes a Root Record Template.
*
* @param[in] context The new context.
* @param[in] hTemplate The root record template to be disposed.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRRootTemplateDispose(IRContext context, int hTemplate);

/**
* Root Record Template Parameter.
*
* @param[in] context The new context.
* @param[in] hTemplate The root record template.
* @param[in] param The new root record template parameter.
* @param[in] value The root record template parameter value.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRRootTemplateParam(IRContext context, int hTemplate, int param, const char * value);

/**
* Root Record Template Integer Parameter.
*
* @param[in] context The new context.
* @param[in] hTemplate The root record template.
* @param[in] param The new root record template parameter.
* @param[in] value The root record template integer parameter value.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRRootTemplateParamInt(IRContext context, int hTemplate, int param, int64_t value);

/**
* Sets a Parent Root Record Template.
*
* @param[in] context The new context.
* @param[in] hTemplate The root record template.
* @param[in] parentRootRecord The parent root record.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRRootTemplateSetParent(IRContext context, int hTemplate, int parentRootRecord);

/**
* Sets an emergency key in a root record template.
*
* @param[in] context The new context.
* @param[in] hTemplate The root record template.
* @param[in] hKey The emergency key to be set.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRRootTemplateSetEmergencyKey(IRContext context, int hTemplate, int hKey);

/**
* Sets a new network to the root record template.
*
* @param[in] context The new context.
* @param[in] hTemplate The root record template.
* @param[in] networkID The network ID to be set.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRRootTemplateSetNetwork(IRContext context, int hTemplate, uint64_t networkID);


/** @}*/ //addtogroup irecord_pub_root_record_template

//==============================================================================
// State Handling
//------------------------------------------------------------------------------
/**
* @defgroup irecord_pub_state_handling State Handling
*/
/** @addtogroup irecord_pub_state_handling
*  @{
*/

/**
* Creates a new state.
*
* @param[in] context The new context.
* @param[out] hState The state created.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRInstanceStateCreate(IRContext context, int * hState);

/**
* Sets a new state parameter.
*
* @param[in] context The new context.
* @param[out] hState The state.
* @param[in] param The state parameter to be set.
* @param[in] value The state parameter value to be set
* @note  Parameters such as Hash type, Signature algorithm type among others
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRInstanceStateSetParam(IRContext context, int * hState, int param, uint64_t value);

/**
* Loads a state.
*
* @param[in] context The new context.
* @param[in] stateSize The size of the state.
* @param[in] state The bytes of the state.
* @param[out] hState The state loaded.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRInstanceStateLoad(IRContext context, int stateSize, const void * state, int * hState);

/**
* Serializes a state.
*
* @param[in] context The new context.
* @param[in] hState The state.
* @param[in/out] buffSize The buffer size of the serialized state.
* @param[out] buff The serialized state buffer.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRInstanceStateSerialize(IRContext context, int hState, int * buffSize, void * buff);

/**
* Diosposes a state.
*
* @param[in] context The new context.
* @param[in] hState The state to be disposed.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRInstanceStateDispose(IRContext context, int hState);

/** @}*/ //addtogroup irecord_pub_state_handling

//==============================================================================
// Block Handling
//------------------------------------------------------------------------------
/**
* @defgroup irecord_pub_block_handling Block Handling
*/
/** @addtogroup irecord_pub_block_handling
*  @{
*/

/**
* Loads a block.
*
* @param[in] context The new context.
* @param[in] blockSize The block size to be loaded.
* @param[in] block The bytes of the block.
* @param[out] hBlock The block loaded.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRBlockLoad(IRContext context, int blockSize, const void * block, int * hBlock);

/**
* Serializes a block.
*
* @param[in] context The new context.
* @param[in] hBlock The block.
* @param[in/out] buffSize The buffer size of the serialized block.
* @param[out] buff The serialized block buffer.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRBlockSerialize(IRContext context, int hBlock, int * buffSize, void * buff);

/**
* Diosposes a block.
*
* @param[in] context The new context.
* @param[in] hBlock The block to be disposed.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRBlockDispose(IRContext context, int hBlock);

/** @}*/ //addtogroup irecord_pub_block_handling

//==============================================================================
// Root block
//------------------------------------------------------------------------------
/**
* @defgroup irecord_pub_root_block Root block
*/
/** @addtogroup irecord_pub_root_block
*  @{
*/

/**
* Creates a root block.
*
* @param[in] context The new context.
* @param[in] hTemplate The root record template.
* @param[in] hState The root block state.
* @param[out] hBlock The block loaded.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRRootBlockCreate(IRContext context, int hTemplate, int hState, int * hBlock);

/** @}*/ //addtogroup irecord_pub_root_block

//==============================================================================
// Data record
//------------------------------------------------------------------------------
/**
* @defgroup irecord_pub_data_record Data record
*/
/** @addtogroup irecord_pub_data_record
*  @{
*/

/**
* Adds a data block.
*
* @param[in] context The new context.
* @param[in] hState The root block state.
* @param[in] lockKey The lock key.
* @param[in] hParentBlock The parent block.
* @param[in] applicationId The ID of the Application.
* @param[in] payloadSize The payload size.
* @param[in] payload The payload of the data block.
* @param[out] hBlock The data block loaded.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRDataBlockAdd(IRContext context, int hState, int lockKey, int hParentBlock,
	uint64_t applicationId, int payloadSize, const void * payload, int * hBlock);


/** @}*/ //addtogroup irecord_pub_data_record


//==============================================================================
// Closing Record
//------------------------------------------------------------------------------
/**
* @defgroup irecord_pub_closing_record Closing record
*/
/** @addtogroup irecord_pub_closing_record
*  @{
*/

/**
* Closes a record.
*
* @param[in] context The new context.
* @param[in] hState The block state.
* @param[in] hParentBlock The parent block.
* @param[in] reason The reason of closing this block.
* @param[in] comments Comments about closing this block.
* @param[in] hSucessor The sucessor block.
* @param[out] hBlock The block closed.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRClose(IRContext context, int hState, int hParentBlock, int reason, const char * comments, int hSucessor, int * hBlock);

/**
* Emergency close.
*
* @param[in] context The new context.
* @param[in] hState The block state.
* @param[in] hParentBlock The parent block.
* @param[in] hEmerngencyKey The emergency key.
* @param[in] reason The reason of closing this block.
* @param[in] comments Comments about closing this block.
* @param[out] hBlock The block emergency closed.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IREmergencyClose(IRContext context, int hState, int hRootBlock, int hParentBlock, int hEmerngencyKey, int reason, const char * comments, int * hBlock);

/** @}*/ //addtogroup irecord_pub_closing_record

//==============================================================================
// Verification
//------------------------------------------------------------------------------
/**
* @defgroup irecord_pub_verification Verification
*/
/** @addtogroup irecord_pub_verification
*  @{
*/

/**
* Checks the root block.
*
* @param[in] context The new context.
* @param[in] hRootBlock The root block.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRCheckRoot(IRContext context, int hRootBlock);

/**
* Checks the parent block.
*
* @param[in] context The new context.
* @param[in] hBlock The actual block.
* @param[in] hParentBlock The parent block.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRCheckParent(IRContext context, int hBlock, int hParentBlock);

/**
* Checks the emergency closing block.
*
* @param[in] context The new context.
* @param[in] hBlock The actual block.
* @param[in] hRootBlock The root block.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRCheckEmergencyClosing(IRContext context, int hBlock, int hRootBlock);

/**
* Block Parameters
*
* @param[in] context The new context.
* @param[in] hBlock The actual block.
* @param[in] param The parameter.
* @param[out] value The parameter value.
* @return IRE_SUCCESS on success or other error code in case of failure.
*/
IR_EXPORT_ATTR int IR_EXPORT_CALL IRBlockParameter(IRContext context, int hBlock, int param, uint64_t * value);

/** @}*/ //addtogroup irecord_pub_verification

/** @}*/ //addtogroup irecord_pub
#endif // __irecord_irecord_H__

