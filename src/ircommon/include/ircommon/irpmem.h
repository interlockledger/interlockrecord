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

	#ifndef _WIN32
	IRARC4 * _arc4;
	#endif //_WIN32

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
