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
#ifndef _IRECORDCORE_IRSRAND_H_
#define _IRECORDCORE_IRSRAND_H_

#include <ircommon/irrandom.h>
#include <botan/rng.h>
#include <memory>

namespace irecordcore {
namespace crypto {

/**
 * This class implements a secure IRRandom.
 *
 * @since 2018.03.20
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRSecureRandom : public ircommon::IRRandom {
protected:
	std::unique_ptr<Botan::RandomNumberGenerator> _random;

	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] rng The Botan::RandomNumberGenerator backend. This class will
	 * claim the ownership of this instance.
	 */
	IRSecureRandom(Botan::RandomNumberGenerator * rng);
public:
	/**
	 * Creates a new instance of this class.
	 */
	IRSecureRandom();

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRSecureRandom() = default;

	virtual void setSeed(std::uint64_t seed);

	virtual void setSeed(const void * seed, std::uint64_t seedSize);

	virtual void nextBytes(void * out, std::uint64_t outSize);
};

/**
 * This class implements a IRRandom that uses a Botan::RandomNumberGenerator
 * instance as its backend.
 *
 * @since 2018.03.20
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRBotanSecureRandom : public IRSecureRandom {
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] rng The Botan::RandomNumberGenerator backend. This class will
	 * claim the ownership of this instance.
	 */
	IRBotanSecureRandom(Botan::RandomNumberGenerator * rng):
			IRSecureRandom(rng) {}

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRBotanSecureRandom() = default;

	/**
	 * Grants direct access to the backend of this instance.
	 *
	 * @return The Botan::RandomNumberGenerator that is used as the backend of
	 * this instance.
	 */
	Botan::RandomNumberGenerator & backend(){
		return *(this->_random);
	}
};

} // namespace crypto
} // namespace irecordcore

#endif /* _IRECORDCORE_IRSRAND_H_ */
