#ifndef _UTIL_H
#define _UTIL_H

#include "MultiSys.h"

// CLogFile
// 写日志文件的类

class CLogFile
{
public:
	CLogFile();
	CLogFile(const char * filename);
	~CLogFile();

	// 设置文件名
	void SetFileName(const char * filename);
	// 获得文件名
	const char * GetFileName() const;

	// 写字符串
	bool SaveString(const char * str) const;
	// 写日志信息（自动加时间）
	bool SaveLog(const char * log) const;

	// 清除日志
	bool Clear() const;
	// 日志文件长度
	size_t Size() const;

private:
	CLogFile(const CLogFile &);
	CLogFile & operator=(const CLogFile &);

private:
	char * m_pFileName;
};

// CAutoBuffer
// 自动管理的缓冲区

class CAutoBuffer
{
public:
	explicit CAutoBuffer(size_t size)
	{
		ASSERT(size > 0);

		m_nSize = size;
		m_pBuffer = NEW char[size];
	}

	~CAutoBuffer()
	{
		delete[] m_pBuffer;
	}

	char * GetBuffer() const
	{
		return m_pBuffer;
	}

	size_t GetSize() const
	{
		return m_nSize;
	}

private:
	CAutoBuffer();
	CAutoBuffer(const CAutoBuffer &);
	CAutoBuffer & operator=(const CAutoBuffer &);

private:
	char *	m_pBuffer;
	size_t	m_nSize;
};

// TAutoMem
// 自动管理的内存，可根据需要使用局部栈或堆

template<typename TYPE, size_t SIZE>
class TAutoMem
{
public:
	explicit TAutoMem(size_t len)
	{
		if (len > SIZE)
		{
			m_pMem = NEW TYPE[len];
		}
		else
		{
			m_pMem = NULL;
		}
	}

	~TAutoMem()
	{
		if (m_pMem)
		{
			delete[] m_pMem;
		}
	}

	TYPE * GetBuffer()
	{
		if (m_pMem)
		{
			return m_pMem;
		}
		else
		{
			return m_stack;
		}
	}

private:
	TAutoMem();
	TAutoMem(const TAutoMem &);
	TAutoMem & operator=(const TAutoMem &);

private:
	TYPE	m_stack[SIZE];
	TYPE *	m_pMem;
};

// CExceptMsg

class CExceptMsg
{
public:
	CExceptMsg(const char * msg)
	{
		ASSERT(msg != NULL);
		
		m_pMsg = msg;
	}

	~CExceptMsg()
	{
	}

	const char * GetMsg() const
	{
		return m_pMsg;
	}

private:
	CExceptMsg();

private:
	const char * m_pMsg;
};

#endif // _UTIL_H
