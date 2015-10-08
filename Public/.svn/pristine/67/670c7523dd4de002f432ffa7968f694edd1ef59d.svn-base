#ifndef LOGFILEWIN_H
#define LOGFILEWIN_H
#ifdef WIN32
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
#endif
#endif //LOGFILEWIN_H
