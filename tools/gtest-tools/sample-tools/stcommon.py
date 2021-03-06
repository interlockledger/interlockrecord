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

def die(error_code, message = None):
	"""Exits the program with the specified error code. If message is set,
	print it before exiting.
	"""
	if message != None: 
		sys.stderr.write(message)
	sys.exit(error_code)

def list2carray(l):
	"""Converts a list into a C/C++ array constant."""
	ret=''
	for i in range(0, len(l)):
		mod = i % 8
		if (mod != 0):
			ret = ret + ' '
		ret = ret + '0x' + l[i] + ','
		if (mod == 7):
			ret = ret + '\n'
	ret = ret.strip()
	ret = ret[0:len(ret)-1]
	return ret

def is_hex_string(s):
	"""Verifies if a given string is a valid hexadecimal value."""
	return re.match('^(?:[0-9a-fA-F]{2})+$', s) != None

def read_all_from_stdin():
	s = ''
	b = sys.stdin.read(1)
	while b != '':
		s = s + b
		b = sys.stdin.read(1)
	return s

