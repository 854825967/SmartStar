#include "LogfileAndroid.h"
#include "MultiSys.h"
#include "Tools.h"
namespace tlib  {
    Logfile::Logfile() {
        
    }
    
    Logfile::Logfile(const char * filepath) {
        InitializeTLogger(filepath);
    }
    
    void Logfile::InitializeTLogger(const char * filepath) {
        ASSERT(!m_log_file.is_open());
        m_log_file.open(filepath, std::ios::app | std::ios::out);
        ASSERT(m_log_file.is_open());
    }
    
    void Logfile::In(const s64 lTick, const char * pContext, const char * head) {
        std::string timeStr = ::GetTimeString(lTick).c_str();
        ASSERT(m_log_file.is_open());
        if (head != NULL) {
            m_log_file << head << " | " << timeStr << " : " << pContext << "\n" << std::flush;
        } else {
            m_log_file << timeStr << " : " << pContext << "\n" << std::flush;
        }
    }
    
    void Logfile::Close() {
        if (m_log_file.is_open()) {
            m_log_file.flush();
            m_log_file.close();
            m_log_file.clear();
        }
    }
}



