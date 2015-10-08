#include "LogfileIOS.h"
#include "Tools.h"
#include <string>
namespace tlib {
    void Logfile::InitializeTLogger(const char * filepath) {
        NSArray * directory = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString * logfile = [[directory objectAtIndex:0] stringByAppendingPathComponent:
                              [NSString stringWithFormat:@"%@", [NSString stringWithUTF8String:filepath]]];
        
        
        NSFileManager * fileManager = [NSFileManager defaultManager];
        if (![fileManager fileExistsAtPath:logfile]) {
            [fileManager createFileAtPath:logfile contents:nil attributes:nil];
            ECHO("%s", [logfile UTF8String]);
        }
        
        m_log_file.open([logfile UTF8String], std::ios::app | std::ios::out);
        //ASSERT(m_log_file.is_open());
    }
    
    Logfile::Logfile() {}
    
    Logfile::Logfile(const char * filepath) {
        InitializeTLogger(filepath);
    }
    
    void Logfile::In(const s64 lTick, const char * pContext, const char * head) {
        std::string timeStr = ::GetTimeString(lTick/1000).c_str();
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
