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
#ifndef _IRECORDCORE_ITRSA_H_
#define _IRECORDCORE_ITRSA_H_

#include <irecordcore/irasykey.h>
#include <ircommon/irbuffer.h>

namespace irecordcore {
namespace crypto {

class IRRSAPublicKey: public IRPublicKey {
public:
	IRRSAPublicKey(bool exportable);

	virtual ~IRRSAPublicKey() = default;

	bool setModulus(const void * v, std::uint64_t vSize) = 0;

	bool setPublicExponent(const void * v, std::uint64_t vSize) = 0;
};

class IRRSAPrivateKey: public IRPrivateKey {
public:
	IRRSAPrivateKey(bool exportable);

	virtual ~IRRSAPrivateKey() = default;

	bool setModulus(const void * v, std::uint64_t vSize) = 0;

	bool setPublicExponent(const void * v, std::uint64_t vSize) = 0;

	bool setPrivateExponent(const void * v, std::uint64_t vSize) = 0;

	bool setPrimeP(const void * v, std::uint64_t vSize) = 0;

	bool setPrimeQ(const void * v, std::uint64_t vSize) = 0;

	bool setPrimeExponentP(const void * v, std::uint64_t vSize) = 0;

	bool setPrimeExponentQ(const void * v, std::uint64_t vSize) = 0;

	bool setCrtCoefficient(const void * v, std::uint64_t vSize) = 0;
};

class IRRSAKeyFactory {
public:
	IRRSAPrivateKey * createKey() = 0;
};

} //namespace crypto
} //namespace irecordcore

#endif /* _IRECORDCORE_ITRSA_H_ */
