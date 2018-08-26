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
#ifndef _IRECORDCORE_IRKEYGEN_H_
#define _IRECORDCORE_IRKEYGEN_H_

#include <memory>
#include <irecordcore/irkey.h>
#include <irecordcore/irmac.h>
#include <ircommon/irrandom.h>

namespace irecordcore {
namespace crypto {

/**
 * This is the base class for all key generators.
 *
 * @since 2018.03.14
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @note Instances of this class are not thread safe unless stated otherwise.
 */
class IRKeyGenerator {
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRKeyGenerator() = default;

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRKeyGenerator() = default;

	/**
	 * Returns the key size in bits.
	 *
	 * @return The key size.
	 */
	virtual unsigned int keySize() const = 0;

	/**
	 * Returns the key size in bytes.
	 *
	 * @return The key size.
	 */
	virtual bool setKeySize(unsigned int keySize) = 0;
};

/**
 * This is the base class for all Secret Key generators.
 *
 * @since 2018.03.14
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRSecretKeyGenerator : public IRKeyGenerator {
private:
	unsigned int _keySize;
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRSecretKeyGenerator();

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRSecretKeyGenerator() = default;

	virtual unsigned int keySize() const;

	virtual unsigned int keySizeInBytes() const;

	/**
	 * Sets the key size. This class restricts the key size to multiple of 8, so
	 * it will fail if keySize is not dividible by 8.
	 *
	 * @param[in] keySize in bits.
	 * @return true for success or false otherwise.
	 */
	virtual bool setKeySize(unsigned int keySize);

	/**
	 * Generates the raw key value.
	 *
	 * @param[out] key The buffer that will receive the key.
	 * @param[int] keySize The size of key in bytes.
	 * @return true for success or false otherwise.
	 * @note This method may not be supported by all subclasses of this class.
	 */
	virtual bool generateRaw(void * key, unsigned int keySize) = 0;

	/**
	 * Generates the key.
	 *
	 * @return The gerated key or NULL in case of error.
	 */
	virtual IRSecretKey * generate() = 0;
};

/**
 * This abstract class implements the software based secret key generator.
 *
 * @since 2018.03.14
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRSoftwareKeyGenerator : public IRSecretKeyGenerator {
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRSoftwareKeyGenerator() = default;

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRSoftwareKeyGenerator() = default;

	/**
	 * Generates the key. This method uses calls
	 * IRSoftwareKeyGenerator::generateRaw(void *, unsigned int) in order to
	 * generate the actual key.
	 *
	 * @return The gerated key or NULL in case of error.
	 * @note This method will fail if the key size is set to 0.
	 */
	virtual IRSecretKey * generate();
};

/**
 * This class implements a key generator based on a given random number
 * generator.
 *
 * @since 2018.03.14
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRRandomKeyGenerator : public IRSoftwareKeyGenerator {
private:
	std::shared_ptr<ircommon::IRRandom> _random;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] random The random generator. This class will take ownership
	 * of this instance.
	 */
	IRRandomKeyGenerator(ircommon::IRRandom * random);

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] random The random generator.
	 * @note Do not use this constructor unless it is possible to guarantee
	 * that the instance of random can be shared with other instances.
	 */
	IRRandomKeyGenerator(std::shared_ptr<ircommon::IRRandom> random);

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRRandomKeyGenerator() = default;

	/**
	 * Returns the inner random generator.
	 */
	ircommon::IRRandom & random(){
		return *(this->_random);
	}

	virtual bool generateRaw(void * key, unsigned int keySize);
};

} // namespace crypto
} // namespace irecordcore

#endif /* _IRECORDCORE_IRKEYGEN_H_ */
