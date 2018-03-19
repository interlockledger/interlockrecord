# Copyright (c) 2017-2018, Open Communications Security
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the <organization> nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL OPEN COMMUNICATIONS SECURITY BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
import numpy
#===============================================================================
# This script implements a python version of the XORShift algorithm
# Author: Fabio Jun Takada Chino (fchino at opencs.com.br)
# Since: 2018.03.18
#-------------------------------------------------------------------------------
class XORShiftPlus:
	def __init__(self):
		self._s0 = numpy.uint64(0)
		self._s1 = numpy.uint64(0)

	@property
	def state0(self):
		return self._s0

	@state0.setter
	def state0(self, value):
		self._s0 = numpy.uint64(value)

	@property
	def state1(self):
		return self._s1

	@state1.setter
	def state1(self, value):
		self._s1 = numpy.uint64(value)

	def next(self):
		x = numpy.uint64(self.state0)
		y = numpy.uint64(self.state1)
		self.state0 = y
		x = x ^ (x << numpy.uint64(23))
		self.state1 = x ^ y ^ (x >> numpy.uint64(17)) ^ (y >> numpy.uint64(26))
		return self.state1 + y;
	
	def next32(self):
		return (self.next() >> numpy.uint64(8)) & numpy.uint64(0xFFFFFFFF)


rand = XORShiftPlus()
rand.state0 = 1
rand.state1 = 1

print(rand.next())
print(rand.next())
print(rand.next())
print(rand.next())
print(rand.next32())
