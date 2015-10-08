#include "Var.h"
#include "Inlines.h"

// CVar

CVar::CVar(const CVar & source)
{
	m_nValue = source.m_nValue;
	m_nDummy = source.m_nDummy;
	m_nLen = source.m_nLen;

	if (source.m_sValue != NULL)
	{
		m_sValue = NEW char[m_nLen];
		::memcpy(m_sValue, source.m_sValue, m_nLen);
	}
	else
	{
		m_sValue = NULL;
	}
}

CVar::CVar(int type)
{
	ASSERT( (type >= 0) && (type < VARTYPE_MAX) );
	
	m_nType = type;
	m_nTag = 0;
	m_nValue = 0;
	m_sValue = NULL;
	m_nLen = 0;
}

CVar::CVar(int type, bool value)
{
	ASSERT(type == VARTYPE_BOOL);
	
	m_nType = VARTYPE_BOOL;
	m_nTag = 0;
	m_bValue = value;
	m_sValue = NULL;
	m_nLen = 0;
}

CVar::CVar(int type, int value)
{
	ASSERT(type == VARTYPE_INT);
	
	m_nType = VARTYPE_INT;
	m_nTag = 0;
	m_nValue = value;
	m_sValue = NULL;
	m_nLen = 0;
}

CVar::CVar(int type, float value)
{
	ASSERT(type == VARTYPE_FLOAT);

	m_nType = VARTYPE_FLOAT;
	m_nTag = 0;
	m_fValue = value;
	m_sValue = NULL;
	m_nLen = 0;
}

CVar::CVar(int type, const char * value)
{
	ASSERT(type == VARTYPE_STRING);
	
	m_nType = VARTYPE_STRING;
	m_nTag = 0;
	m_nValue = 0;
	m_sValue = NULL;
	m_nLen = 0;

	SetString(value);
}

CVar::CVar(int type, const wchar_t * value)
{
	ASSERT(type == VARTYPE_WIDESTR);
	
	m_nType = VARTYPE_WIDESTR;
	m_nTag = 0;
	m_nValue = 0;
	m_sValue = NULL;
	m_nLen = 0;

	SetWideStr(value);
}

CVar::CVar(int type, const PERSISTID & value)
{
	ASSERT(type == VARTYPE_OBJECT);
	
	m_nType = VARTYPE_OBJECT;
	m_nTag = 0;
	m_nValue = 0;
	m_sValue = NULL;
	m_nLen = 0;

	SetObject(value);
}

void CVar::Swap(CVar & other)
{
	::SwapValue(m_nDummy, other.m_nDummy);
	::SwapValue(m_nValue, other.m_nValue);
	::SwapValue(m_sValue, other.m_sValue);
	::SwapValue(m_nLen, other.m_nLen);
}

void CVar::SetType(int type) 
{ 
	ASSERT(type < VARTYPE_MAX);

	if (m_sValue != NULL)
	{
		if ( (VARTYPE_STRING != type) 
			&& (VARTYPE_WIDESTR != type) 
			&& (VARTYPE_OBJECT != type)
			&& (VARTYPE_UNKNOWN != type) )
		{
			::delete[] m_sValue;
			m_sValue = NULL;
		}
	}

	m_nType = type;
}

void CVar::SetString(const char * value) 
{ 
	ASSERT(value != NULL);
	ASSERT( (VARTYPE_STRING == m_nType) || (VARTYPE_UNKNOWN == m_nType) ); 

	if (m_sValue != NULL)
	{
		::delete[] m_sValue;
	}
	
	const size_t LEN = ::strlen(value) + 1;
	
	m_nLen = u32((LEN + 2) & ~0x1);
	m_sValue = NEW char[m_nLen];
	::memcpy(m_sValue, value, LEN);
	m_sValue[m_nLen - 1] = 0;
	m_sValue[m_nLen - 2] = 0;
}

void CVar::SetStringFrom(const wchar_t * value) 
{ 
	ASSERT(value != NULL);
	ASSERT( (VARTYPE_STRING == m_nType) || (VARTYPE_UNKNOWN == m_nType) ); 
	
	if (m_sValue != NULL)
	{
		::delete[] m_sValue;
	}
	
	const size_t LEN = ::GetToStringLen(value);
	
	m_nLen = u32((LEN + 2) & ~0x1);
	m_sValue = NEW char[m_nLen];
	::ToString(value, m_sValue, LEN);
	m_sValue[m_nLen - 1] = 0;
	m_sValue[m_nLen - 2] = 0;
}

void CVar::SetWideStr(const wchar_t * value) 
{ 
	ASSERT(value != NULL);
	ASSERT( (VARTYPE_WIDESTR == m_nType) || (VARTYPE_UNKNOWN == m_nType) ); 

	if (m_sValue != NULL)
	{
		::delete[] m_sValue;
	}
	
	m_nLen = u32((::wcslen(value) + 1) * sizeof(wchar_t));
	m_sValue = NEW char[m_nLen];
	::memcpy(m_sValue, value, m_nLen);
}

void CVar::SetWideStrFrom(const char * value) 
{ 
	ASSERT(value != NULL);
	ASSERT( (VARTYPE_WIDESTR == m_nType) || (VARTYPE_UNKNOWN == m_nType) ); 
	
	if (m_sValue != NULL)
	{
		::delete[] m_sValue;
	}
	
	m_nLen = u32(::GetToWideStrLen(value));
	m_sValue = NEW char[m_nLen];
	::ToWideStr(value, (wchar_t *)m_sValue, m_nLen);
}

void CVar::SetObject(const PERSISTID & value) 
{ 
	ASSERT( (VARTYPE_OBJECT == m_nType) || (VARTYPE_UNKNOWN == m_nType) ); 
	
	if (m_sValue != NULL)
	{
		::delete[] m_sValue;
	}
	
	m_nLen = sizeof(PERSISTID) + 2;
	m_sValue = NEW char[sizeof(PERSISTID) + 2];
	*(PERSISTID *)m_sValue = value;
	m_sValue[sizeof(PERSISTID) + 0] = 0;
	m_sValue[sizeof(PERSISTID) + 1] = 0;
}

bool CVar::Compare(const CVar & rhs) const
{
	if (m_nType != rhs.m_nType)
	{
		return false;
	}

	switch (m_nType)
	{
	case VARTYPE_UNKNOWN:
		return true;
	case VARTYPE_BOOL:
		return (m_bValue == rhs.m_bValue);
	case VARTYPE_INT:
		return (m_nValue == rhs.m_nValue);
	case VARTYPE_FLOAT:
		return (m_fValue == rhs.m_fValue);
	case VARTYPE_STRING:
		return (::strcmp(StringVal(), rhs.StringVal()) == 0);
	case VARTYPE_WIDESTR:
		return (::wcscmp(WideStrVal(), rhs.WideStrVal()) == 0);
	case VARTYPE_OBJECT:
		return (ObjectVal() == rhs.ObjectVal());
	case VARTYPE_VOID:
		return true;
	}

	return false;
}

CVar & CVar::operator=(const CVar & source)
{
	CVar temp(source);

	Swap(temp);

	return *this;
}

