

#ifndef __dlltest_t_H__
#define __dlltest_t_H__

#include "dlltest_def.h"

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

typedef int (IR_EXPORT_CALL *function_a_t)(int a);

typedef struct _dlltest_funcs_t {
	void * handle;
	function_a_t p_function_a;
} dlltest_funcs_t;

#ifdef __cplusplus
} //extern "C"
#endif //__cplusplus

#endif //__dlltest_t_H__

