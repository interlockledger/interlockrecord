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
#ifndef _IRCOMMON_IRRANDOM_H_
#define _IRCOMMON_IRRANDOM_H_

#include <cstdint>

namespace ircommon {

/**
 * This class implements the base class for all random generators.
 *
 * <p>It is important to notice that instances of this class and its subclasses
 * should not be considered thread safe unless stated otherwise.</p>
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
	 * Creates a new instance of this class. It is a convenience method that
	 * creates the random value and sets the seed at the same time by calling
	 * IRXORShifRandom::setSeed(std::uint64_t).
	 *
	 * @param[in] seed The initial seed.
	 * @since 2018.04.05
	 */
	IRXORShifRandom(std::uint64_t seed);

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

} // namespace ircommon

#endif /* _IRCOMMON_IRRANDOM_H_ */
