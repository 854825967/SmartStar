#ifndef LOGFILEANDROID_H
#define LOGFILEANDROID_H
#ifdef __ANDROID__
#include "MultiSys.h"
#include <fstream>
namespace tlib {
    class Logfile {
    public:
        Logfile();
        Logfile(const char * filepath);
        void InitializeTLogger(const char * filepath);
        void In(const s64 lTick, const char * pContext, const char * head);
        void Close();
        
    private:
        std::ofstream m_log_file;
    };
}
#endif //__ANDROID__
#endif //LOGFILEANDROID_H
