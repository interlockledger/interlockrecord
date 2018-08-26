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
#ifndef _IRECORDCORE_IRPBKDF2_H_
#define _IRECORDCORE_IRPBKDF2_H_

#include <ircommon/irutils.h>
#include <irecordcore/irkeygen.h>

namespace irecordcore {
namespace crypto {

/**
 * This class implements a key generator based on the PBKDF2 algorithm defined
 * by RFC2898.
 *
 * @since 2018.03.14
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRPBKDF2KeyGenerator: public IRSoftwareKeyGenerator {
private:
	/**
	 * The inner MAC.
	 */
	std::unique_ptr<IRMAC> _prf;
	/**
	 * Number of rounds of the block generation.
	 */
	unsigned int _rounds;
	/**
	 * The current salt.
	 */
	ircommon::IRBuffer _salt;
	/**
	 * Generates the block with the given index.
	 *
	 * @param[in] index The block index.
	 * @param[in,out] tmp The temporary buffer. It must have at least
	 * blockSize() bytes or 4 witchever
	 * @param[out] out The block output. It must have at least blockSize()
	 * bytes.
	 */
	void generateBlock(std::uint32_t index, std::uint8_t * tmp,
			std::uint8_t * out);

	/**
	 * Core of the key generation function.
	 *
	 * @param[out] key The output key.
	 * @param[in] keySize The size of the output key in bytes.
	 */
	bool generateRawCore(std::uint8_t * key, unsigned int keySize);
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRPBKDF2KeyGenerator(IRMAC * prf, unsigned int rounds = 1024);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRPBKDF2KeyGenerator() = default;

	/**
	 * Number of rounds of this algorithm.
	 *
	 * @return The number of rounds.
	 */
	unsigned int rounds() const {
		return this->_rounds;
	}

	/**
	 * Sets the number of rounds.
	 *
	 * @param[in] rounds The number of rounds.
	 */
	void setRounds(unsigned int rounds) {
		this->_rounds = rounds;
	}

	/**
	 * Size of the inner block.
	 *
	 * @return Size of the inner block in bytes.
	 */
	unsigned int blockSize() const {
		return this->_prf->sizeInBytes();
	}

	/**
	 * Sets the password.
	 *
	 * @param[in] password The password.
	 * @param[in] passwordSize The size of the password in bytes.
	 */
	void setPassword(const void * password, std::uint64_t passwordSize);

	/**
	 * Sets the salt.
	 *
	 * @param[in] salt The salt.
	 * @param[in] saltSize The salt size.
	 */
	void setSalt(const void * salt, std::uint64_t saltSize);

	virtual bool generateRaw(void * key, unsigned int keySize);
};

} // namespace crypto
} // namespace irecordcore

#endif /* _IRECORDCORE_IRPBKDF2_H_ */
