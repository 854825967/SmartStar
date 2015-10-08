//
//  IOSTools.h
//  HelloCpp
//
//  Created by Alax on 14-3-21.
//
//

#ifndef IOSTools_h
#define IOSTools_h
#ifdef CC_TARGET_OS_IPHONE
#include "MultiSys.h"
#include <string>
#include <unistd.h>
#include <libgen.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <pthread.h>
#include <errno.h>
#include <netdb.h>

ThreadID GetCurrentThreadID();

inline std::string GetHostIp(const char * pUrl){
    struct hostent *hp;
    struct in_addr in;
	hp = gethostbyname(pUrl);
	if(NULL == hp) {
		return "";
	}
    memcpy (&in.s_addr,hp->h_addr,4);
    return inet_ntoa(in);
}

inline s64 GetCurrentTimeTick() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec/1000;
}

inline s64 GetTimeTickOfDayBeginning() {
    time_t curTime = time(NULL);
    tm localTm = *localtime(&curTime);
    localTm.tm_hour = 0;
    localTm.tm_min = 0;
    localTm.tm_sec = 0;
    return mktime(&localTm) * 1000;
}

inline std::string GetCurrentTimeString(const char * format = "%4d-%02d-%02d %02d:%02d:%02d") {
    struct timeval nowTimeval;
    gettimeofday(&nowTimeval, NULL);
    struct tm * tm;
    time_t time_sec ;
    time_sec = nowTimeval.tv_sec;
    tm = localtime(&time_sec);
    int year = tm->tm_year + 1900;
    int month = tm->tm_mon + 1;
    int day = tm->tm_mday;
    int hour=tm->tm_hour;
    int minute=tm->tm_min;
    int second=tm->tm_sec;
    char szTime[64] = {0};
    SafeSprintf(szTime, sizeof(szTime), format, year, month, day, hour, minute, second);
    return szTime;
}

inline std::string GetTimeString(const s64 tick, const char * format = "%4d-%02d-%02d %02d:%02d:%02d") {
    struct tm * tm = NULL;
    time_t t = (time_t) tick;
    tm = localtime(&t);
    
    int year = tm->tm_year + 1900;
    int month = tm->tm_mon + 1;
    int day = tm->tm_mday;
    int hour=tm->tm_hour;
    int minute=tm->tm_min;
    int second=tm->tm_sec;
    char temp[64] = {0};
    SafeSprintf(temp, sizeof(temp), format, year, month, day, hour, minute, second);
    return std::string(temp);
}

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus
    
//    const char * GetAppPath() {
//        return "./";
//    }
//    
//    void CopyString(char * buf, size_t len, const char * str)
//    {
//        const size_t SIZE = ::strlen(str) + 1;
//        
//        if (SIZE <= len) {
//            ::memcpy(buf, str, SIZE);
//        } else {
//            ::memcpy(buf, str, len - 1);
//            buf[len - 1] = 0;
//        }
//    }
    
#ifdef __cplusplus
};
#endif //__cplusplus

//inline u32 StringAsInt(const char * value) {
//    ASSERT(value);
//    return atoi(value);
//}

inline s64 StringAsInt64(const char * value) {
    ASSERT(value);
    return atoll(value);
}

inline std::string Int64AsString(const s64 value) {
    char str[64];
    memset(str, 0, sizeof(str));
    SafeSprintf(str, sizeof(str), "%lld", value);
    return str;
}

inline s32 StringAsInt(const char * value) {
    ASSERT(value);
    return atoi(value);
}

inline std::string IntAsString(const s32 value) {
    char str[32];
    memset(str, 0, sizeof(str));
    SafeSprintf(str, sizeof(str), "%d", value);
    return str;
}

#endif //CC_TARGET_OS_IPHONE

#endif
