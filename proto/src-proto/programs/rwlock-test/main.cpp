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
#include <thread>
#include <iostream>
#include <chrono>
#include "IRRWLock.h"

IRRWLock rwLock;
volatile int val = 0;
volatile bool running = true;
std::mutex ioLock;

void readerMain(int a) {
	do {
		rwLock.lockRead();

		ioLock.lock();
		std::cout << "Reader " << a << " started. Val=" << val << "\n";
		ioLock.unlock();

		std::this_thread::sleep_for(std::chrono::seconds(1));

		ioLock.lock();
		std::cout << "Reader " << a << " ended. Val=" << val << "\n";
		ioLock.unlock();

		rwLock.unlockRead();
	} while (running);
	ioLock.lock();
	std::cout << "Reader " << a << " terminated.\n";
	ioLock.unlock();
}

void writerMain(int a) {
	do {
		rwLock.lockWrite();

		ioLock.lock();
		std::cout << "Writer " << a << " started. Val=" << val << "\n";
		ioLock.unlock();

		val++;
		std::this_thread::sleep_for(std::chrono::seconds(1));

		ioLock.lock();
		std::cout << "Writer " << a << " ended. Val=" << val << "\n";
		ioLock.unlock();

		rwLock.unlockWrite();
	} while (running);
	ioLock.lock();
	std::cout << "Writer " << a << " terminated.\n";
	ioLock.unlock();
}

int main(int argc, char ** argv) {
	std::thread * readers[5];
	std::thread * writers[3];
	
	for(int i = 0; i < 5; i++) {
		readers[i] = new std::thread(readerMain, i);
	}
	for(int i = 0; i < 3; i++) {
		writers[i] = new std::thread(writerMain, i);
	}
	std::this_thread::sleep_for(std::chrono::seconds(30));
	running = false;
	for(int i = 0; i < 5; i++) {
		readers[i]->join();
	}
	for(int i = 0; i < 3; i++) {
		writers[i]->join();
	}
	
	return 0;
}
