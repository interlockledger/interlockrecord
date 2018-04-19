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

# Parse arguments
parser = argparse.ArgumentParser(
	description='Converts hexadecimal strings inst into C/C++ byte array constants.')
parser.add_argument('-c', help='Read input from stdin.', 
	default=False, action='store_true')
parser.add_argument('hex_string', nargs='?', help='A valid hexadecimal string.')
if len(sys.argv) == 1:
	parser.print_help()
	sys.exit(2)
else:
	args = parser.parse_args()

# Read the input
if (args.c):
	hex_str = stcommon.read_all_from_stdin()
else:
	hex_str = sys.argv[1]
# Check integrity
if stcommon.is_hex_string(hex_str) == False:
	stcommon.die(2, 'Invalid hexadecimal string.\n')

# Split in parts
ret=[]
for i in range(0, len(hex_str), 2):
	ret.append(hex_str[i:i+2])
print(stcommon.list2carray(ret))

