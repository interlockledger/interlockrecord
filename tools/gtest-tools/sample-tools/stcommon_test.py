#!/usr/bin/python
# -*- coding: utf-8 -*-
# Copyright (c) 2017-2018, FJTC
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
# 
# * Redistributions of source code must retain the above copyright notice, this
#   list of conditions and the following disclaimer.
# 
# * Redistributions in binary form must reproduce the above copyright notice,
#   this list of conditions and the following disclaimer in the documentation
#   and/or other materials provided with the distribution.
# 
# * Neither the name of gtest-tool nor the names of its
#   contributors may be used to endorse or promote products derived from
#   this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
import unittest
import stcommon

class STCommonTest(unittest.TestCase):
	def test_list2carray(self):
		s = stcommon.list2carray(['01'])
		self.assertEquals('0x01', s)

		s = stcommon.list2carray(['01', '23'])
		self.assertEquals('0x01, 0x23', s)

		s = stcommon.list2carray(['01', '23', '45', '67', '89'])
		self.assertEquals('0x01, 0x23, 0x45, 0x67, 0x89', s)

		s = stcommon.list2carray(['01', '23', '45', '67', '89', 'AB', 'CD', 'EF'])
		self.assertEquals('0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF', s)

		s = stcommon.list2carray(['01', '23', '45', '67', '89', 'AB', 'CD', 'EF', '01'])
		self.assertEquals('0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,\n0x01', s)

	def test_is_hex_string(self):
		self.assertTrue(stcommon.is_hex_string('0123456789abcdefABCDEF'))
		self.assertFalse(stcommon.is_hex_string(''))
		self.assertFalse(stcommon.is_hex_string('0'))
		for i in range(len('0123456789abcdefABCDEF')):
			s = '0123456789abcdefABCDEF'
			s = s[:i] + 'x' + s[i + 1:]
			self.assertFalse(stcommon.is_hex_string(s))

if __name__ == '__main__':
    unittest.main()

