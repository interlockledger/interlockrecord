
#include <thread>
#include <iostream>
#include <chrono>
#include "IRRWLock.h"

IRRWLock rwLock;
volatile int val = 0;

std::mutex ioLock;

void readerMain(int a) {
	do {
		rwLock.lockRead();

		ioLock.lock();
		std::cout << "Reader " << a << " started. Val=" << val << "\n";
		ioLock.unlock();

		std::this_thread::sleep_for(std::chrono::seconds(2));

		ioLock.lock();
		std::cout << "Reader " << a << " ended. Val=" << val << "\n";
		ioLock.unlock();

		rwLock.unlockRead();
	} while (true);
}

void writerMain(int a) {
	do {
		rwLock.lockWrite();

		ioLock.lock();
		std::cout << "Writer " << a << " started. Val=" << val << "\n";
		ioLock.unlock();

		val++;
		std::this_thread::sleep_for(std::chrono::seconds(2));

		ioLock.lock();
		std::cout << "Writer " << a << " ended. Val=" << val << "\n";
		ioLock.unlock();

		rwLock.unlockWrite();
	} while (true);
}

int main(int argc, char ** argv) {
	
	for(int i = 0; i < 5; i++) {
		std::thread * t;
		t = new std::thread(readerMain, i);
	}
	for(int i = 0; i < 3; i++) {
		std::thread * t;
		t = new std::thread(writerMain, i);
	}
	std::this_thread::sleep_for(std::chrono::seconds(30));
	return 0;
}
