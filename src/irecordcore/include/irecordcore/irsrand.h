/*
 * Copyright (c) 2017-2018, Open Communications Security
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
