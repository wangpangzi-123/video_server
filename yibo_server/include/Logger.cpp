#include "Logger.h"


LogInfo::LogInfo(
		const char* file, int line, const char* func,
		pid_t pid, pthread_t tid, int level,
		const char* fmt, ...)
        {
            const char sLevel[][8] = {
                "INFO","DEBUG","WARNING","ERROR","FATAL"
            };
            char* buf = NULL;
            bAuto = false;
            
            int count = asprintf(&buf, "%s(%d):[%s][%s]<%d-%d>(%s) ",
                file, line, sLevel[level],
                (char*)Logger::GetTimeStr(), pid, tid, func);

            // int count = asprintf(&buf, "%s(%d):[%s]<%d-%d>(%s) ",
            //     file, line, sLevel[level], pid, tid, func);

            if (count > 0) {
                m_buf = buf;
                free(buf);
            }
            else return;

            va_list ap;
            va_start(ap, fmt);
            count = vasprintf(&buf, fmt, ap);
            if (count > 0) {
                m_buf += buf;
                free(buf);
            }
            m_buf += "\n";
            va_end(ap);
        }

LogInfo::LogInfo(
		const char* file, int line, const char* func,
		pid_t pid, pthread_t tid, int level)
        {

        }

LogInfo::LogInfo(const char* file, int line, const char* func,
		pid_t pid, pthread_t tid, int level,
		void* pData, size_t nSize)
        {

        }

LogInfo::~LogInfo()
{
    if (bAuto) 
    {
		m_buf += "\n";
		Logger::Trace(*this);
	}
}