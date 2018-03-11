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
cmake_minimum_required (VERSION 3.9)
project (irecordcore-test 
	VERSION ${interlockrecord_VERSION})

enable_testing()
add_executable(irecordcore-test
	src/block/IRBlockHeaderTest.cpp
	src/block/IRBlockHeaderTest.h
	src/block/IRClosingPayloadTest.cpp
	src/block/IRClosingPayloadTest.h
	src/block/IRRecordTypeTest.cpp
	src/block/IRRecordTypeTest.h
	src/block/IRRootBlockPayloadTest.cpp
	src/block/IRRootBlockPayloadTest.h
	src/crypto/CryptoSamples.cpp
	src/crypto/CryptoSamples.h
	src/crypto/IRBotanHashTest.cpp
	src/crypto/IRBotanHashTest.h
	src/crypto/IRBotanKeccakHashTest.cpp
	src/crypto/IRBotanKeccakHashTest.h
	src/crypto/IRCopyHashTest.cpp
	src/crypto/IRCopyHashTest.h
	src/crypto/IRCryptoTest.cpp
	src/crypto/IRCryptoTest.h
	src/crypto/IRHashTest.cpp
	src/crypto/IRHashTest.h
	src/crypto/IRSHA1HashTest.cpp
	src/crypto/IRSHA1HashTest.h
	src/crypto/IRSHA256HashTest.cpp
	src/crypto/IRSHA256HashTest.h
	src/crypto/IRSHA3_256HashTest.cpp
	src/crypto/IRSHA3_256HashTest.h
	src/crypto/IRSHA3_512HashTest.cpp
	src/crypto/IRSHA3_512HashTest.h
	src/crypto/IRSHA512HashTest.cpp
	src/crypto/IRSHA512HashTest.h
	src/crypto/IRSignAlgTest.cpp
	src/crypto/IRSignAlgTest.h
	src/IRTypedRawTest.cpp
	src/IRTypedRawTest.h
	src/main.cpp
	src/tags/IRBaseType16RawTagTest.cpp
	src/tags/IRBaseType16RawTagTest.h
	src/tags/IRBlockSigTagTest.cpp
	src/tags/IRBlockSigTagTest.h
	src/tags/IRBlockTagTest.cpp
	src/tags/IRBlockTagTest.h
	src/tags/IRHashTagTest.cpp
	src/tags/IRHashTagTest.h
	src/tags/IRHeaderTagTest.cpp
	src/tags/IRHeaderTagTest.h
	src/tags/IRPayloadTagTest.cpp
	src/tags/IRPayloadTagTest.h
	src/tags/IRPubTagTest.cpp
	src/tags/IRPubTagTest.h
	src/tags/IRSignedTagTest.cpp
	src/tags/IRSignedTagTest.h
	src/tags/IRSigTagTest.cpp
	src/tags/IRSigTagTest.h
	src/tags/IRTagFactoryTest.cpp
	src/tags/IRTagFactoryTest.h
	src/tags/IRTagTypeTest.cpp
	src/tags/IRTagTypeTest.h)

target_link_libraries(irecordcore-test
	irecordcore
	GTest)

add_test(tests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/irecordcore-test)

