

#ifndef __dlltest_def_H__
#define __dlltest_def_H__

#if defined(__GNUC__)
	#define IR_EXPORT_CALL
	#ifdef IR_EXPORTS
		#define IR_EXPORT_ATTR __attribute__((visibility("default")))
	#else
		#define IR_EXPORT_ATTR
	#endif //IR_EXPORTS
#elif defined(_MSC_VER)
	#define IR_EXPORT_CALL __cdecl
	#define IR_EXPORT_ATTR
#endif //__GNUC__

#endif //__dlltest_def_H__

