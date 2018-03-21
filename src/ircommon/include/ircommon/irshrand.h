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
#ifndef _IRCOMMON_IRSHRAND_H_
#define _IRCOMMON_IRSHRAND_H_

#include <ircommon/irrandom.h>
#include <mutex>

namespace ircommon {
namespace threading {

/**
 * This class implements IRRandom that can be shared among multiple threads.
 *
 * <p>This implementation doest not implement an actual PRNG but act as a
 * Decorator that can provide exclusive access to the inner IRRandom instance,
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
	ircommon::IRRandom * _random;

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
	virtual ~IRSharedRandom();

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
