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
#ifndef _IRCOMMON_IRPMEM_H_
#define _IRCOMMON_IRPMEM_H_

#include <cstdint>
#include <mutex>
#ifndef _WIN32
#include <ircommon/irarc4.h>
#endif //_WIN32

namespace ircommon {
namespace crypto {

/**
 * This class implements a protected memory segment. It is specially useful to
 * store in-memory secrets like keys and passwords.
 *
 * <p>It attemps to protect the data by keeping the information stored
 * inside it encrypted and/or obfuscated whenever possible. It will also
 * use other system specific techniques whenever available.</p>
 *
 * <p>The usage of this class is quite simple. Call lock() to make the buffer
 * available for reading and writing. When the data is no longer necessary
 * in its plain form, class unlock() to release it.</p>
 *
 * <p>This class may consume a substantial resources from the system.
 * Specially because it will try to prevent it from leaving the physical
 * memory whenever possible. Given that, it is recommended to limit the
 * usage of this class only for critical information such as passwords
 * and long term keys.</p> 
 *
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 * @since 2018.01.30
 * @note This class is thread safe.
 */
class IRProtectedMemory {
protected:
	std::uint8_t * _value;

	std::uint64_t _valueBufferSize;

	std::uint64_t _valueSize;
	
	std::mutex _mutex;

	bool protect();

	bool unprotect();
public:
	IRProtectedMemory(std::uint64_t size);

	virtual ~IRProtectedMemory();

	/**
	 * This method locks the data and unprotects it for
	 * reading and writing in plain.
	 *
	 * @return true for success or false otherwise. 
	 */
	virtual bool lock();

	/**
	 * This method protects the data in memory and releases 
	 * the lock.
	 *
	 * @return true for success or false otherwise. 
	 */
	virtual bool unlock();

	/**
	 * The size of the data.
	 *
	 * @return The size of the data in bytes.
	 */
	std::uint64_t size() const {
		return this->_valueSize;
	}

	/**
	 * Pointer to the internal data. It is available only when
	 * locked.
	 *
	 * @return
	 */
	std::uint8_t * value() const {
		return this->_value;
	}
};

} // namespace crypto
} // namespace ircommon

#endif /* _IRCOMMON_IRPMEM_H_ */
