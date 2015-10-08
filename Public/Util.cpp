#include "Util.h"
#include <windows.h>
#include <string.h>
#include <stdio.h>

// CLogFile

CLogFile::CLogFile()
{
	m_pFileName = NULL;
}

CLogFile::CLogFile(const char * filename)
{
	m_pFileName = NULL;
	
	SetFileName(filename);
}

CLogFile::~CLogFile()
{
	if (m_pFileName)
	{
		delete[] m_pFileName;
	}
}

void CLogFile::SetFileName(const char * filename)
{
	ASSERT(filename != NULL);
	
	const size_t SIZE1 = ::strlen(filename) + 1;

	char * p = NEW char[SIZE1];
	
	::memcpy(p, filename, SIZE1);

	if (m_pFileName)
	{
		delete[] m_pFileName;
	}
	
	m_pFileName = p;
}

const char * CLogFile::GetFileName() const
{
	if (NULL == m_pFileName)
	{
		return "";
	}
	
	return m_pFileName;
}

bool CLogFile::SaveString(const char * str) const
{
	ASSERT(str != NULL);

	HANDLE handle = ::CreateFile(GetFileName(),
		GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);
	
	if (INVALID_HANDLE_VALUE == handle)
	{
		return false;
	}
	
	try
	{
		::SetFilePointer(handle, 0, NULL, FILE_END);
		
		DWORD written;
		
		::WriteFile(handle, str, DWORD(::strlen(str)), &written, NULL);
		::WriteFile(handle, "\r\n", 2, &written, NULL);
	}
	catch (...)
	{
		::CloseHandle(handle);
		return false;
	}
	
	::CloseHandle(handle);
	
	return true;
}

bool CLogFile::SaveLog(const char * log) const
{
	ASSERT(log != NULL);

	HANDLE handle = ::CreateFile(GetFileName(),
		GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);

	if (INVALID_HANDLE_VALUE == handle)
	{
		return false;
	}

	try
	{
		::SetFilePointer(handle, 0, NULL, FILE_END);
		
		SYSTEMTIME tm;
		
		::GetLocalTime(&tm);
		
		char buf[256];

		SafeSprintf(buf, sizeof(buf), 
			"[%04d-%02d-%02d %02d:%02d:%02d] ",
			tm.wYear, tm.wMonth, tm.wDay, 
			tm.wHour, tm.wMinute, tm.wSecond);

		DWORD written;

		::WriteFile(handle, buf, DWORD(::strlen(buf)), &written, NULL);
		::WriteFile(handle, log, DWORD(::strlen(log)), &written, NULL);
		::WriteFile(handle, "\r\n\r\n", 4, &written, NULL);
	}
	catch (...)
	{
		::CloseHandle(handle);
		return false;
	}

	::CloseHandle(handle);
	
	return true;
}

size_t CLogFile::Size() const
{
	HANDLE handle = ::CreateFile(GetFileName(),
		GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 
		NULL, OPEN_EXISTING, 0, NULL);
	
	if (INVALID_HANDLE_VALUE == handle)
	{
		return 0;
	}
	
	size_t num = ::GetFileSize(handle, NULL);
	
	::CloseHandle(handle);
	
	return num;
}

bool CLogFile::Clear() const
{
	HANDLE handle = ::CreateFile(GetFileName(),
		GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, 0, NULL);
	
	if (INVALID_HANDLE_VALUE == handle)
	{
		return false;
	}
	
	::CloseHandle(handle);
	
	return true;
}

