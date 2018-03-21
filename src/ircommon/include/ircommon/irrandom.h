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
#ifndef _IRCOMMON_IRRANDOM_H_
#define _IRCOMMON_IRRANDOM_H_

#include <cstdint>
#include <mutex>

namespace ircommon {

/**
 * This class implements the base class for all random generators.
 *
 * @since 2018.03.15
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRRandom {
public:
	IRRandom() = default;

	virtual ~IRRandom() = default;

	/**
	 * Sets the seed.
	 *
	 * @param[in] seed The seed value.
	 */
	virtual void setSeed(std::uint64_t seed) = 0;

	/**
	 * Sets the seed. Each implementation may
	 *
	 * @param[in] seed The seed value.
	 * @param[in] seedSize The seed size.
	 */
	virtual void setSeed(const void * seed, std::uint64_t seedSize) = 0;

	/**
	 * Returns the next random boolean. The default implementation extracts a
	 * 32 bit random value and returns the XOR of all of its bits. This should
	 * ensure that all bits are used to compute the actual value, removing the
	 * dependency of the randomness of a single bit.
	 *
	 * @return The next random boolean.
	 */
	virtual bool nextBoolean();

	/**
	 * Returns the next 8 bit value. The default implementation returns the
	 * least significant bits of IRRandom::next32().
	 *
	 * @return The next 8-bit value.
	 */
	virtual std::uint8_t next();

	/**
	 * Returns the next 16 bit value. The default implementation returns the
	 * least significant bits of IRRandom::next32().
	 *
	 * @return The next 16-bit value.
	 */
	virtual std::uint16_t next16();

	/**
	 * Returns the next 32 bit value. The default implementation extracts
	 * 4 bytes from the source using IRRandom::nextBytes() and interprets it
	 * as a big endian value.
	 *
	 * @return The next 32-bit value.
	 */
	virtual std::uint32_t next32();

	/**
	 * Returns the next 64 bit value. The default implementation combines 2
	 * IRRandom::next32() into a single 64-bit value.
	 *
	 * @return The next 64-bit value.
	 */
	virtual std::uint64_t next64();

	/**
	 * Returns the next float value between 0 (inclusive) and 1.0 (exclusive).
	 *
	 * It is computed by extracting 23 random bits using IRRandom::next32() and
	 * dividing this value by 2^23.
	 *
	 * @return The next float value.
	 */
	virtual float nextFloat();

	/**
	 * Returns the next double value between 0 (inclusive) and 1.0 (exclusive).
	 *
	 * It is computed by extracting 52 random bits using IRRandom::next64() and
	 * dividing this value by 2^52.
	 *
	 * @return The next float value.
	 */
	virtual double nextDouble();

	/**
	 * Returns the next bytes.
	 *
	 * @param[out] out The output buffer.
	 * @param[in] outSize The number of bytes to extract.
	 */
	virtual void nextBytes(void * out, std::uint64_t outSize) = 0;

	/**
	 * This helper method fills a byte array using the method
	 * IRRandom::next32(). It can be used to implement IRRandom::nextBytes().
	 *
	 * @param[in] random The random instance.
	 * @param[out] out The output buffer.
	 * @param[in] outSize The number of bytes to extract.
	 */
	static void nextBytesFrom32(IRRandom & random, void * out,
			std::uint64_t outSize);
};

/**
 * This class implements a variant of the XORShit+ proposed by Saito, M. and
 * Matsumoto, M. in 2014.
 *
 * @since 2018.03.15
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRXORShifRandom : public IRRandom {
protected:
	std::uint64_t _state[2];
public:
	/**
	 * Creates a new instance of this class.
	 *
	 * @note The initial seed will be set to the result of the function time()
	 * from the standard library.
	 */
	IRXORShifRandom();

	/**
	 * Disposes this instance and releases all associated resources.
	 */
	virtual ~IRXORShifRandom() = default;

	/**
	 * Sets the seed. In this implementation, only the fist first 64-bits of the
	 * state will be set to the seed value. The other value of the state will be
	 * set to the seed XORed by 0x6a09e667bb67ae85.
	 *
	 * <p>The value 0x6a09e667bb67ae85 is the concatenation of the the initial
	 * value for the states h0 and h1 of the SHA-256 algorithm.</p>
	 *
	 * <p>This initialization procedure will ensure that at least one bit of the
	 * state will not be zero.</p>
	 *
	 * @param[in] seed The seed value.
	 */
	virtual void setSeed(std::uint64_t seed);

	/**
	 * Sets the seed. The ideal seed will have exact 16 bytes. If the seedSize
	 * is smaller than 16, it will be padded with zeroes. If the state is larger
	 * than 16, the remaining bytes will be ignored.
	 *
	 * <p>It is important to notice that, if all bits of the seed are 0, this
	 * initialization procedure will set the value of the first 64-bits of the
	 * state to 1.</p>
	 *
	 * @param[in] seed The seed value.
	 * @param[in] seedSize The seed size.
	 */
	virtual void setSeed(const void * seed, std::uint64_t seedSize);

	/**
	 * Sets the seed.
	 *
	 * <p>It is important to notice that, if seed0 and seed1 are set to 0,
	 * seed0 will assume the value 1.</p>
	 *
	 * @param[in] seed0 The first 64-bits of the internal state.
	 * @param[in] seed1 The last 64-bits of the internal state.
	 */
	void setSeed(std::uint64_t seed0, std::uint64_t seed1);

	/**
	 * Returns the next value as specified by XORShit+.
	 *
	 * @return The next 64-bit integer generated by XORShit+.
	 */
	std::uint64_t nextValue();

	/**
	 * Returns the next 32 bit value.
	 *
	 * @return The next 32-bit value.
	 */
	virtual std::uint32_t next32();

	virtual void nextBytes(void * out, std::uint64_t outSize);
};

/**
 * This class implements IRRandom that can be shared among multiple threads.
 *
 * @since 2018.03.21
 * @author Fabio Jun Takada Chino (fchino at opencs.com.br)
 */
class IRSharedRandom : public IRRandom {
protected:
	IRRandom * random;

	std::mutex _mutex;
public:
	IRSharedRandom(IRRandom * random);

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

} // namespace ircommon

#endif /* _IRCOMMON_IRRANDOM_H_ */
