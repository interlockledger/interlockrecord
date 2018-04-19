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
import sys
import stcommon
import argparse

def fromFile(inp):
	"""
	Reads the file and returns its contents as a list of hexadecimal values.
	"""
	ret=''
	try:
		b = inp.read(1)
		while b != '':
			ret = ret + '{0:02X}'.format(ord(b))
			b = inp.read(1)
		return ret
	except:
		stcommon.die(2, 'Unable to open the file {0}\n'.format(inp_file))

# Parse arguments
parser = argparse.ArgumentParser(
	description='Converts binary files into an hexadecimal string.')
parser.add_argument('-c', help='Read input from stdin.', 
	default=False, action='store_true')
parser.add_argument('file', nargs='?', help='File to be loaded.')
if len(sys.argv) == 1:
	parser.print_help()
	sys.exit(2)
else:
	args = parser.parse_args()

# Execute the process according to the arguments
if args.c:
	ret = fromFile(sys.stdin)
else:
	with open(args.file, 'rb') as inp:
		ret = fromFile(inp)
sys.stdout.write(ret)
sys.stdout.flush()

