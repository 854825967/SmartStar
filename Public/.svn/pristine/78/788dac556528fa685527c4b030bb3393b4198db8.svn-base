#include "MultiSys.h"
#include <stdio.h>
#include <string>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
    void _AssertionFail(const char * strFile, int nLine, const char * pFunName) {
        fflush(stdout);
        fprintf(stderr, "\nAsssertion failed: file %s, line %d, function %s ", strFile, nLine, pFunName);
        fflush(stderr);
        assert(false);
    }
    
    void _void_fun(void) {
        
    }
    
#ifdef __cplusplus
};
#endif //__cplusplus
