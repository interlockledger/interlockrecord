#!/usr/bin/python
# -*- coding: utf-8 -*-
# Copyright (c) 2017, FJTC
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
import sys
import re
import stcommon
import argparse

def hex_to_int_array(s):
	ret=[]
	for i in range(0, len(s), 2):
		ret.append(int(s[i:i+2], base=16))
	return ret

# Parse arguments
parser = argparse.ArgumentParser(
	description='Applies bitwise XOR between two hexadecimal strings and outputs the result as an hexadecimal string.')
parser.add_argument('hex_str_a', help='A valid hexadecimal string.')
parser.add_argument('hex_str_b', help='A valid hexadecimal string.')
if len(sys.argv) == 1:
	parser.print_help()
	sys.exit(2)
else:
	args = parser.parse_args()

# Validate the input
if stcommon.is_hex_string(args.hex_str_a) == False:
	stcommon.die(2, 'hex_str_a is not a valid hexadecimal string.\n')
if stcommon.is_hex_string(str(args.hex_str_b)) == False:
	stcommon.die(2, 'hex_str_a is not a valid hexadecimal string.\n')
if len(args.hex_str_a) != len(args.hex_str_b):
	stcommon.die(2, 'hex_str_a and hex_str_b must have the same length.\n')

# Split in parts
a = hex_to_int_array(args.hex_str_a)
b = hex_to_int_array(args.hex_str_b)

# Apply xor
ret = []
for i in range(len(a)):
	ret.append(a[i] ^ b[i])

# Array to hex
s=''
for v in ret:
	s = s + '{0:02X}'.format(v)
sys.stdout.write(s)
sys.stdout.flush()

