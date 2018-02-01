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
#ifndef IRECORDCORE_INCLUDE_IRECORDCORE_IRHASH_H_
#define IRECORDCORE_INCLUDE_IRECORDCORE_IRHASH_H_

#include <ircommon/irbuffer.h>
#include <irecordcore/ircrypto.h>
#include <cstdint>
#include <botan/sha160.h>
#include <botan/sha2_32.h>
#include <botan/sha2_64.h>

namespace irecordcore {
namespace crypto {

class IRHash {
private:
	IRHashAlg _type;
public:
	IRHash(IRHashAlg type):
			_type(type) {}

	virtual ~IRHash() = default;

	IRHashAlg type() const {
		return this->_type;
	}

	virtual void reset() = 0;

	virtual std::uint64_t size() const;

	virtual void update(const void * buff, std::uint64_t size) = 0;

	virtual bool finalize(void * out, std::uint64_t size) = 0;
};

class IRCopyHash  : public IRHash {
private:
	ircommon::IRBuffer _state;
public:
	IRCopyHash(IRHashAlg type):IRHash(IR_HASH_COPY),
			_state(0, true) {}

	virtual ~IRCopyHash() = default;

	virtual void reset();

	virtual std::uint64_t size() const;

	virtual void update(const void * buff, std::uint64_t size);

	virtual bool finalize(void * out, std::uint64_t size);
};

template <class BotanHashImpl, IRHashAlg Type>
class IRBotanHash : public IRHash {
private:
	BotanHashImpl _hash;
public:
	IRBotanHash(): IRHash(Type) {}

	virtual ~IRBotanHash() = default;

	virtual void reset() {
		this->_hash.clear();
	}

	virtual std::uint64_t size() const {
		return this->_hash.output_length();
	}

	virtual void update(const void * buff, std::uint64_t size) {
		this->_hash.update((const std::uint8_t *)buff, size);
	}

	virtual bool finalize(void * out, std::uint64_t size) {
		if (size < this->size()) {
			return false;
		}
		this->_hash.final((std::uint8_t *)out);
		return true;
	}
};

typedef IRBotanHash<Botan::SHA_160, IR_HASH_SHA1> IRSHA1Hash;

typedef IRBotanHash<Botan::SHA_256, IR_HASH_SHA256> IRSHA256Hash;

typedef IRBotanHash<Botan::SHA_512, IR_HASH_SHA256> IRSHA512Hash;

class IRHashFactory {
public:
	IRHash * create(std::uint16_t type);
};

} //namespace crypto
} //namespace irecordcore

#endif /* IRECORDCORE_INCLUDE_IRECORDCORE_IRHASH_H_ */
