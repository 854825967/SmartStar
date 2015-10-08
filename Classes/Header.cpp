#include "Header.h"
#include <string>
using namespace std;

GameData g_data;
GameConfig g_config;
bool g_soundSwitch = true;

#ifdef __ANDROID__
char * jstringToString(JNIEnv * env, jstring jstr) {
	char* rtn = NULL;
	jclass clsstring = env->FindClass("java/lang/String");
	jstring strencode = env->NewStringUTF("utf-8");
	jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
	jsize alen = env->GetArrayLength(barr);
	jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
	if (alen > 0)
	{
		rtn = (char*)malloc(alen + 1);
		memcpy(rtn, ba, alen);
		rtn[alen] = 0;
	}
	env->ReleaseByteArrayElements(barr, ba, 0);
	return rtn;
}
#endif //__ANDROID__

bool isMusicEnabled() {
#ifdef __ANDROID__
	cocos2d::JniMethodInfo minfo;
	bool b = cocos2d::JniHelper::getStaticMethodInfo(minfo,
			"org/cocos2dx/cpp/AppActivity",
			"isMusicEnabled",
			"()Z");

	bool res = false;

	if (!b) {
		__android_log_print(ANDROID_LOG_ERROR, "cocos2d-x debug info", "JniHelp::getStaticMethodInfo error...");
	} else {
		res = (bool)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
	}

	return res;
#endif //__ANDROID__

#ifdef WIN32
	return true;
#endif //WIN32
}

bool payBilling(const char * pBillingIndex) {
#ifdef __ANDROID__
	cocos2d::JniMethodInfo minfo;
	bool b = cocos2d::JniHelper::getStaticMethodInfo(minfo,
			"org/cocos2dx/cpp/AppActivity",
			"pay",
			"(Ljava/lang/String;)Z");

	bool res = false;

	if (!b) {
		__android_log_print(ANDROID_LOG_ERROR, "cocos2d-x debug info", "JniHelp::getStaticMethodInfo error...");
	} else {
		jstring jbill = minfo.env->NewStringUTF(pBillingIndex);
		res = (bool)minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID, jbill);
	}

	return res;
#endif //__ANDROID__

#ifdef WIN32
	return true;
#endif //WIN32
}

int httpLogProc(void *buffer, size_t size, size_t nmemb, void *stream) {
    return size * nmemb;
}

bool CURL_GET_REQUEST(const char * pUrl, const curl_callback pCallAddress) {
//    CURL* pHandle = curl_easy_init();
//    CURLcode code;
//    if(NULL == pHandle){
//        curl_global_cleanup();
//        return false;
//    }
//
//    curl_easy_setopt(pHandle, CURLOPT_URL, pUrl);
//    curl_easy_setopt(pHandle, CURLOPT_WRITEFUNCTION, pCallAddress);
//    curl_easy_setopt(pHandle, CURLOPT_TIMEOUT, 10);
//    curl_easy_setopt(pHandle, CURLOPT_FORBID_REUSE, 1);
//
//    char szRet[1024] = {0};
//    curl_easy_setopt(pHandle, CURLOPT_WRITEDATA, szRet);
//    code = curl_easy_perform(pHandle);
//
//
//    if(CURLE_OK != code) {
//        curl_easy_cleanup(pHandle);
//        return false;
//    }

    return true;
}
