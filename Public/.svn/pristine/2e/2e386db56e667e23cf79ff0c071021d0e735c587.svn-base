#ifndef _VAR_H
#define _VAR_H

#include "MultiSys.h"

#include <stddef.h>
#include <string.h>

// PERSISTID
// 对象ID数据类型（不可初始化）

class IBaseObj;

#pragma pack(push, 1)

struct PERSISTID
{
	union
	{
		struct
		{
			u32	nIdent;
			u32	nSerial;
		};

		// 64位优化
		unsigned __int64 nDummy64;
	};

public:
	bool IsNull() const
	{
		return (0 == nDummy64);
	}
	
protected:
	PERSISTID() {}
};

#pragma pack(pop)

inline bool operator==(const PERSISTID & source, const PERSISTID & other)
{
	return (source.nDummy64 == other.nDummy64);
}

inline bool operator!=(const PERSISTID & source, const PERSISTID & other)
{
	return (source.nDummy64 != other.nDummy64);
}

// PERSISTID_INIT
// 可初始化的对象ID

struct PERSISTID_INIT: public PERSISTID
{
	PERSISTID_INIT()
	{
		nDummy64 = 0;
	}

	PERSISTID_INIT(u32 ident, u32 serial)
	{
		nIdent = ident;
		nSerial = serial;
	}

	PERSISTID_INIT(u64 nValue)
	{
		nDummy64 = nValue;
	}
	
	PERSISTID_INIT & operator=(const PERSISTID & src)
	{
		nDummy64 = src.nDummy64;
		return *this;
	}
};

// CVar
// 可变数据类型

enum VAR_TYPE
{
	VARTYPE_UNKNOWN,
	VARTYPE_BOOL,
	VARTYPE_INT,
	VARTYPE_FLOAT,
	VARTYPE_STRING,
	VARTYPE_WIDESTR,
	VARTYPE_OBJECT,
	VARTYPE_VOID,
	VARTYPE_INT64,
	VARTYPE_MAX,
};

class CVar
{
public:
	CVar();
	CVar(const CVar & source);
	explicit CVar(int type);
	CVar(int type, bool value);
	CVar(int type, int value);
	CVar(int type, float value);
	CVar(int type, const char * value);
	CVar(int type, const wchar_t * value);
	CVar(int type, const PERSISTID & value);
	~CVar();

	int Type() const;
	int Tag() const;
	void SetType(int type);
	void SetTag(int tag);		
	bool BoolVal() const;
	int IntVal() const;
	float FloatVal() const;
	const char * StringVal() const;
	const wchar_t * WideStrVal() const;
	const PERSISTID & ObjectVal() const;
	void SetBool(bool value);
	void SetInt(int value);
	void SetFloat(float value);
	void SetString(const char * value);
	void SetStringFrom(const wchar_t * value);
	void SetWideStr(const wchar_t * value);
	void SetWideStrFrom(const char * value);
	void SetObject(const PERSISTID & value);
	bool Compare(const CVar & other) const;
	void Swap(CVar & other);

	CVar & operator=(const CVar & source);
	
private:
	union
	{
		struct 
		{
			u16	m_nType;
			u16	m_nTag;
		};
		u32		m_nDummy;
	};
	union
	{
		float		m_fValue;
		int			m_nValue;
		bool		m_bValue;
	};
	char *			m_sValue;
	u32			m_nLen;
};

inline CVar::CVar()
{
	m_nValue = 0;
	m_nDummy = 0;
	m_sValue = NULL;
	m_nLen = 0;
}

inline CVar::~CVar()
{
	::delete[] m_sValue;
}

inline int CVar::Type() const
{
	return m_nType;
}

inline int CVar::Tag() const
{
	return m_nTag;
}

inline void CVar::SetTag(int tag)
{
	m_nTag = tag;
}

inline bool CVar::BoolVal() const 
{ 
	ASSERT( (VARTYPE_BOOL == m_nType) || (VARTYPE_UNKNOWN == m_nType) ); 

	return m_bValue; 
}

inline int CVar::IntVal() const 
{ 
	ASSERT( (VARTYPE_INT == m_nType) || (VARTYPE_UNKNOWN == m_nType) ); 
	
	return m_nValue; 
}

inline float CVar::FloatVal() const 
{ 
	ASSERT( (VARTYPE_FLOAT == m_nType) || (VARTYPE_UNKNOWN == m_nType) ); 
	
	return m_fValue; 
}

inline const char * CVar::StringVal() const 
{ 
	ASSERT( (VARTYPE_STRING == m_nType) || (VARTYPE_UNKNOWN == m_nType) ); 
	
	if (m_sValue != NULL)
	{
		return m_sValue;
	}
	else
	{
		return "";
	}
}

inline const wchar_t * CVar::WideStrVal() const 
{ 
	ASSERT( (VARTYPE_WIDESTR == m_nType) || (VARTYPE_UNKNOWN == m_nType) ); 
	
	if (m_sValue != NULL)
	{
		return (const wchar_t *)m_sValue;
	}
	else
	{
		return L"";
	}
}

inline const PERSISTID & CVar::ObjectVal() const 
{ 
	ASSERT( (VARTYPE_OBJECT == m_nType) || (VARTYPE_UNKNOWN == m_nType) ); 
	
	static PERSISTID_INIT s_object;
	
	if ( (m_sValue != NULL) && (m_nLen == (sizeof(PERSISTID) + 2)) )
	{
		return *(PERSISTID *)m_sValue;
	}
	else
	{
		return s_object;
	}
}

inline void CVar::SetBool(bool value) 
{ 
	ASSERT( (VARTYPE_BOOL == m_nType) || (VARTYPE_UNKNOWN == m_nType) ); 

	m_bValue = value; 
}

inline void CVar::SetInt(int value) 
{ 
	ASSERT( (VARTYPE_INT == m_nType) || (VARTYPE_UNKNOWN == m_nType) ); 

	m_nValue = value; 
}

inline void CVar::SetFloat(float value) 
{ 
	ASSERT( (VARTYPE_FLOAT == m_nType) || (VARTYPE_UNKNOWN == m_nType) ); 
	
	m_fValue = value; 
}

inline bool operator==(const CVar & lhs, const CVar & rhs)
{
	return lhs.Compare(rhs);
}

#endif // _VAR_H
