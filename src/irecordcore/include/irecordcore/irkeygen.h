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
 */
class IRKeyGenerator {
public:
	IRKeyGenerator() = default;

	virtual ~IRKeyGenerator() = default;

	virtual unsigned int keySize() const = 0;

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
	IRSecretKeyGenerator();

	virtual ~IRSecretKeyGenerator() = default;

	virtual unsigned int keySize() const;

	virtual unsigned int keySizeInBytes() const;

	virtual bool setKeySize(unsigned int keySize);

	virtual bool generateRaw(void * key, int keySize) = 0;

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
	IRSoftwareKeyGenerator() = default;

	virtual ~IRSoftwareKeyGenerator() = default;

	virtual IRSecretKey * generate();
};

/**
 * This class implements a key generator based on the PBKDF2 algorithm defined
 * by RFC2898.
 *
 * @since 2018.03.14
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRRandomKeyGenerator : public IRSoftwareKeyGenerator {
private:
	std::shared_ptr<ircommon::IRRandom> _random;
public:
	IRRandomKeyGenerator(ircommon::IRRandom * random);

	IRRandomKeyGenerator(std::shared_ptr<ircommon::IRRandom> random);

	virtual ~IRRandomKeyGenerator() = default;

	virtual bool generateRaw(void * key, int keySize);
};

/**
 * This class implements a key generator based on the PBKDF2 algorithm defined
 * by RFC2898.
 *
 * @since 2018.03.14
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRPBKDF2KeyGenerator: public IRSoftwareKeyGenerator {
private:
	std::unique_ptr<IRMAC> _prf;

	unsigned int _rounds;

	ircommon::IRBuffer _salt;

	std::uint8_t * _tmp;

	void f(unsigned int rounds, std::uint8_t * out);
public:
	IRPBKDF2KeyGenerator(IRMAC * prf, unsigned int rounds);

	virtual ~IRPBKDF2KeyGenerator();

	unsigned int rounds() const {
		return this->_rounds;
	}

	void setRounds(unsigned int rounds) {
		this->_rounds = rounds;
	}

	void setPassword(const void * password, std::uint64_t passwordSize);

	void setSalt(const void * salt, std::uint64_t saltSize);

	virtual bool generateRaw(void * key, int keySize);
};

} // namespace crypto
} // namespace irecordcore

#endif /* _IRECORDCORE_IRKEYGEN_H_ */
