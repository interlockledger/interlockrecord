

#ifndef __dlltest_def_H__
#define __dlltest_def_H__

#ifdef __cplusplus
	#define IR_EXTERN_C extern "C"
#else
	#define IR_EXTERN_C
#endif //__cplusplus

#if defined(__GNUC__)
	#define IR_EXPORT_CALL
	#ifdef IR_EXPORTS
		#define IR_EXPORT_ATTR IR_EXTERN_C __attribute__((visibility("default")))
	#else
		#define IR_EXPORT_ATTR IR_EXTERN_C
	#endif //IR_EXPORTS
#elif defined(_MSC_VER)
	#define IR_EXPORT_CALL __cdecl
	#define IR_EXPORT_ATTR IR_EXTERN_C
#endif //__GNUC__

#endif //__dlltest_def_H__

