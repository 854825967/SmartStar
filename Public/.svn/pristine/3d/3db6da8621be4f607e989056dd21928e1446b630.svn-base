////////////////////////////////////////////////////////////////////
//                          _ooOoo_                               //
//                         o8888888o                              //
//                         88" . "88                              //
//                         (| ^_^ |)                              //
//                         O\  =  /O                              //
//                      ____/`---'\____                           //
//                    .'  \\|     |//  `.                         //
//                   /  \\|||  :  |||//  \                        //
//                  /  _||||| -:- |||||-  \                       //
//                  |   | \\\  -  /// |   |                       //
//                  | \_|  ''\---/''  |   |                       //
//                  \  .-\__  `-`  ___/-. /                       //
//                ___`. .'  /--.--\  `. . ___                     //
//              .""' < `.___\_<|>_/___.' > '"".                   //
//            | | :  `- \`.;`\ _ /`;.`/ - ` : | |                 //
//            \  \ `-.   \_ __\ /__ _/   .-` /  /                 //
//      ========`-.____`-.___\_____/___.-`____.-'========         //
//                           `=---='                              //
//      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^        //
//            佛祖保佑       无BUG       永不修改                    //
////////////////////////////////////////////////////////////////////
#ifndef MULTISYS_H
#define MULTISYS_H
#include "WinSys.h"
#include "LinuxSys.h"
#include "MacSys.h"
#include "IOSSys.h"
#include "AndroidSys.h"

#ifdef __cplusplus
extern "C" {
#endif
    void _AssertionFail(const char * strFile, int nLine, const char * pFunName);
    typedef void (*VOID_FUN_TYPE)(void);
    void _void_fun(void);
#ifdef __cplusplus
};
#endif


#if defined _DEBUG
//#define NEW ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define NEW new
#define MALLOC malloc
#define FREE free
#ifndef ASSERT
#define  ASSERT(p) ((p) ? (void)0 : (void)_AssertionFail(__FILE__, __LINE__, __FUNCTION__))
#endif //ASSERT
#else
#define NEW new
#define MALLOC malloc
#define FREE free
#ifndef ASSERT
#define  ASSERT(p) 
#endif //ASSERT
#endif //_DEBUG

#define BUFF_SIZE 4096

#ifndef OUT
#define OUT
#endif //OUT

#ifndef IN
#define IN
#endif //IN

#pragma warning(disable: 4786)
#pragma warning(disable: 4996)

#define SAFE_DELETE(p)       { if(p) { ::delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { ::delete[] (p);   (p)=NULL; } }

#define WORD1(p)    (p & 0xFFFF)
#define WORD2(p)    ((p >> 16) & 0xFFFF)
#define BYTE1(p)    (p & 0xFF)
#define BYTE2(p)    ((p >> 8) & 0xFF)
#define BYTE3(p)    ((p >> 16) & 0xFF)
#define BYTE4(p)    ((p >> 24) & 0xFF)

#define	U32_MAX		0xFFFFFFFF
#define U16_MAX		0xFFFF
#define U8_MAX		0xFF

#endif //MULTISYS_H
