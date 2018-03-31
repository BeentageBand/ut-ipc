#ifndef STD_REUSE_H_
#define STD_REUSE_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
#include <iostream>

extern "C" {
#endif

typedef bool bool_t;
 
#define Num_Elems(array) (sizeof(array)/sizeof(array[0]))
#define Isnt_Nullptr(obj, retval) \
    if(NULL == obj) \
    {Dbg_Fault("%s:%s is a nullptr", __func__, #obj); return retval;}

#ifdef __cplusplus
}
#endif
 
#endif /*STD_REUSE_H_*/
