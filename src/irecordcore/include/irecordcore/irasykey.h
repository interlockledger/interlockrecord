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
#ifndef _IRECORDCORE_IRASYKEY_H_
#define _IRECORDCORE_IRASYKEY_H_

#include <irecordcore/irkey.h>
#include <irecordcore/ircrypto.h>

namespace irecordcore {
namespace crypto {

class IRAsymmetricKey: public IRKey {
private:
	IRSignAlg _algorithm;
public:
	IRAsymmetricKey(IRSignAlg alg, bool exportable);

	virtual ~IRAsymmetricKey() = default;

	IRSignAlg algorithm() const {
		return this->_algorithm;
	}

	/**
	 * Returns the key size in bits.
	 */
	std::uint64_t keySize() = 0;
};

class IRPublicKey: public IRAsymmetricKey {
public:
	IRPublicKey(IRSignAlg alg, bool exportable);

	virtual ~IRPublicKey() = default;
};

class IRPrivateKey: public IRAsymmetricKey {
public:
	IRPrivateKey(IRSignAlg alg, bool exportable);

	virtual ~IRPrivateKey() = default;

	virtual IRPublicKey & publicKey() const = 0;
};

} //namespace crypto
} //namespace irecordcore



#endif /* _IRECORDCORE_IRASYKEY_H_ */
