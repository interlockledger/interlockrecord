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
#ifndef _IRECORDCORE_IRKEY_H_
#define _IRECORDCORE_IRKEY_H_

#include <cstdint>
#include <ircommon/irpmem.h>
#include <ircommon/irbuffer.h>

namespace irecordcore {
namespace crypto {

/**
 * Base class for all cryptographic keys.
 *
 * @since 2018.03.12
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRKey {
public:
	IRKey() = default;

	virtual ~IRKey() = default;

	virtual bool serialize(ircommon::IRBuffer & out) = 0;
};

/**
 * Base class for all secret keys.
 *
 * @since 2018.03.12
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRSecretKey: public IRKey {
public:
	IRSecretKey() = default;

	virtual ~IRSecretKey() = default;

	virtual std::uint64_t size() = 0;

	virtual std::uint64_t sizeInBytes() = 0;
};

/**
 * Base class for all software based secret keys. This implementation supports
 * in-memory encryption.
 *
 * @since 2018.03.12
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRSecretKeyImpl: public IRSecretKey {
private:
	ircommon::crypto::IRProtectedMemory _key;

	bool _protected;
public:
	IRSecretKeyImpl(const void * key, std::uint64_t keySize);

	virtual ~IRSecretKeyImpl();

	virtual std::uint64_t size();

	virtual std::uint64_t sizeInBytes();

	bool isProtected() const {
		return this->_protected;
	}

	void protect();

	void uprotect();

	/**
	 * Returns the raw key.
	 *
	 * @return The raw key value or nullptr if it is not available.
	 */
	const void * key() const {
		if (this->isProtected()) {
			return nullptr;
		} else {
			return this->_key.value();
		}
	}
};

} //namespace crypto
} //namespace irecordcore

#endif /* _IRECORDCORE_IRKEY_H_ */
