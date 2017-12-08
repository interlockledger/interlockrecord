

#ifndef __main_H__
#define __main_H__

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

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

IR_EXPORT_ATTR int IR_EXPORT_CALL function_a(int a);

#ifdef __cplusplus
} //extern "C"
#endif //__cplusplus

#endif //__main_H__

