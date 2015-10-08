#ifndef LOGFILEIOS_H
#define LOGFILEIOS_H
#ifdef CC_TARGET_OS_IPHONE
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
#endif //CC_TARGET_OS_IPHONE
#endif //LOGFILEIOS_H
