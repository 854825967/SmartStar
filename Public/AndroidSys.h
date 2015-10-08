#ifdef __ANDROID__
#ifndef __ANDROIDSYS_H__
#define __ANDROIDSYS_H__

#include <unistd.h>
#include <libgen.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <android/log.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long int u64;

typedef char s8;
typedef short s16;
typedef int s32;
typedef long long int s64;
#undef CSleep
#define CSleep(n) usleep(n*1000)
#define SafeSprintf snprintf

typedef void * THREAD_FUN;
typedef void * LPVOID;
typedef pthread_t ThreadID;

#define ECHO(format, a...) {\
    char log[4096] = {0}; \
    SafeSprintf(log, 4096, format, ##a); \
    __android_log_print(ANDROID_LOG_ERROR, "cocos2d-x debug info", log); \
}

#define ECHO_TRACE(format, a...) {\
    char log[4096] = {0}; \
    SafeSprintf(log, 4096, format, ##a); \
    printf("[info] %s|%d|%s\n\t%s\n", __FILE__, __LINE__, __FUNCTION__, log); \
}

#define ECHO_WARN(format, a...) {\
    char log[4096] = {0}; \
    SafeSprintf(log, 4096, format, ##a); \
    printf("[warn]%s|%d|%s\n\t%s\n", __FILE__, __LINE__, __FUNCTION__, log); \
}

#define ECHO_ERROR(format, a...) {\
    char log[4096] = {0}; \
    SafeSprintf(log, 4096, format, ##a); \
    printf("[error]%s|%d|%s\n\t%s\n", __FILE__, __LINE__, __FUNCTION__, log); \
}

#endif //__ANDROIDSYS_H__
#endif //__ANDROID__
