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
#ifndef _IRCOMMON_IRSHRAND_H_
#define _IRCOMMON_IRSHRAND_H_

#include <ircommon/irrandom.h>
#include <memory>
#include <mutex>

namespace ircommon {
namespace threading {

/**
 * This class implements IRRandom that can be shared among multiple threads.
 *
 * <p>This implementation doest not implement an actual PRNG but act as a
 * Decorator that ensures the exclusive access to the inner IRRandom instance,
 * thus making it thread-safe.</p>
 *
 * @since 2018.03.21
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRSharedRandom : public ircommon::IRRandom {
protected:
	/**
	 * Inner IRRandom instance.
	 */
	std::unique_ptr<ircommon::IRRandom> _random;

	/**
	 * The synchronization mutex.
	 */
	std::mutex _mutex;
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] random The inner random instance. This class will take
	 * ownership of this instance.
	 */
	IRSharedRandom(IRRandom * random);

	/**
	 * Dispose this instance and releases all associated resources.
	 */
	virtual ~IRSharedRandom() = default;

	virtual void setSeed(std::uint64_t seed);

	virtual void setSeed(const void * seed, std::uint64_t seedSize);

	virtual bool nextBoolean();

	virtual std::uint8_t next();

	virtual std::uint16_t next16();

	virtual std::uint32_t next32();

	virtual std::uint64_t next64();

	virtual float nextFloat();

	virtual double nextDouble();

	virtual void nextBytes(void * out, std::uint64_t outSize);
};

} //namespace threading
} //namespace ircommon

#endif /* _IRCOMMON_IRSHRAND_H_ */
