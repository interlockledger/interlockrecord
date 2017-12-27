

#ifndef __IRSemaphore_h__
#define __IRSemaphore_h__

#ifdef _WIN32
	#include <windows.h>
#else
	#include <semaphore.h>
#endif //__WIN32

class IRSemaphore {
private:
#ifdef _WIN32
	typedef HANDLE Handle_t;
#else
	typedef sem_t * Handle_t;
	sem_t _handle_concrete;
#endif //_WIN32
	
	Handle_t _handle;
public:
	IRSemaphore(int initial = 1);

	virtual ~IRSemaphore();
	
	bool tryWait(int ms);	
	
	bool wait();
	
	bool release();
};

#endif //__IRSemaphore_h__
