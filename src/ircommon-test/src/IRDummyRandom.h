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
#ifndef _IRDUMMYRANDOM_H_
#define _IRDUMMYRANDOM_H_

#include <memory>
#include <ircommon/irrandom.h>

using namespace ircommon;

/**
 * This class implements a dummy random number generator. It generates a
 * sequence of incrementing numbers starting with the current seed.
 */
class IRDummyRandom: public IRRandom {
private:
	std::uint64_t _seed;
public:
	IRDummyRandom(): _seed(0) {}

	virtual ~IRDummyRandom() = default;

	virtual void setSeed(std::uint64_t seed);

	virtual void setSeed(const void * seed, std::uint64_t seedSize);

	std::uint64_t seed() const {
		return this->_seed;
	}

	virtual void nextBytes(void * out, std::uint64_t outSize);
};

/**
 * This class implements a IRRandom Decorator that adds a delay in the execution
 * of all operations. It can be used to simulate race conditions during testing.
 */
class IRDelayedRandom : public ircommon::IRRandom {
protected:
	/**
	 * Inner IRRandom instance.
	 */
	std::unique_ptr<ircommon::IRRandom> _random;

	std::uint64_t _delay;

	void delay();
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @param[in] random The inner random instance. This class will take
	 * ownership of this instance.
	 * @param[in] delay Delay in ms.
	 */
	IRDelayedRandom(IRRandom * random, std::uint64_t delay);

	/**
	 * Dispose this instance and releases all associated resources.
	 */
	virtual ~IRDelayedRandom() = default;

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


#endif /* _IRDUMMYRANDOM_H_ */
