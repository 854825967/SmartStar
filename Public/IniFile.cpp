#include "IniFile.h"
#include "Util.h"
#include "Inlines.h"

// CIniFile

bool CIniFile::ParseVector2(const char * str, VECTOR2 & res)
{
	ASSERT(str != NULL);

	char	data[256];
	char *	tok;

	if (::strlen(str) >= sizeof(data))
	{
		return false;
	}

	::strcpy(data, str);

	tok = ::strtok(data, ",");

	if (NULL == tok)
	{
		return false;
	}

	float x = float(::atof(tok));

	tok = ::strtok(NULL, ",");

	if (NULL == tok)
	{
		return false;
	}

	float y = float(::atof(tok));

	res.x = x;
	res.y = y;
	
	return true;
}

bool CIniFile::ParseVector3(const char * str, VECTOR3 & res)
{
	ASSERT(str != NULL);

	char	data[256];
	char *	tok;

	if (::strlen(str) >= sizeof(data))
	{
		return false;
	}

	::strcpy(data, str);

	tok = ::strtok(data, ",");

	if (NULL == tok)
	{
		return false;
	}

	float x = float(::atof(tok));

	tok = ::strtok(NULL, ",");

	if (NULL == tok)
	{
		return false;
	}

	float y = float(::atof(tok));

	tok = ::strtok(NULL, ",");

	if (NULL == tok)
	{
		return false;
	}

	float z = float(::atof(tok));

	res.x = x;
	res.y = y;
	res.z = z;
	
	return true;
}

bool CIniFile::ParseVector4(const char * str, VECTOR4 & res)
{
	ASSERT(str != NULL);

	char	data[256];
	char *	tok;

	if (::strlen(str) >= sizeof(data))
	{
		return false;
	}

	::strcpy(data, str);

	tok = ::strtok(data, ",");

	if (NULL == tok)
	{
		return false;
	}

	float x = float(::atof(tok));

	tok = ::strtok(NULL, ",");

	if (NULL == tok)
	{
		return false;
	}

	float y = float(::atof(tok));

	tok = ::strtok(NULL, ",");

	if (NULL == tok)
	{
		return false;
	}

	float z = float(::atof(tok));

	tok = ::strtok(NULL, ",");

	if (NULL == tok)
	{
		return false;
	}

	float orient = float(::atof(tok));

	res.x = x;
	res.y = y;
	res.z = z;
	res.orient = orient;
	
	return true;
}

bool CIniFile::ParseByte4(const char * str, u32 & res)
{
	ASSERT(str != NULL);
	
	char	data[256];
	char *	tok;
	
	if (::strlen(str) >= sizeof(data))
	{
		return false;
	}
	
	::strcpy(data, str);
	
	tok = ::strtok(data, ",");

	if (NULL == tok)
	{
		return false;
	}

	u32 b4 = u32(::atoi(tok)) & 0xFF;
	
	tok = ::strtok(NULL, ",");

	if (NULL == tok)
	{
		return false;
	}

	u32 b3 = u32(::atoi(tok)) & 0xFF;
	
	tok = ::strtok(NULL, ",");

	if (NULL == tok)
	{
		return false;
	}

	u32 b2 = u32(::atoi(tok)) & 0xFF;
	
	tok = ::strtok(NULL, ",");

	if (NULL == tok)
	{
		return false;
	}

	u32 b1 = u32(::atoi(tok)) & 0xFF;
	
	res = b1 + (b2 << 8) + (b3 << 16) + (b4 << 24);
	
	return true;
}

size_t CIniFile::ParseString(const char * str, 
							 std::vector<std::string> & res)
{
	ASSERT(str != NULL);

	res.clear();

	const size_t SIZE1 = ::strlen(str);
	
	TAutoMem<char, 256> buffer(SIZE1 + 1);
	
	char * data = buffer.GetBuffer();
	
	::strcpy(data, str);

	size_t i;
	
	for (i=0; i<SIZE1; ++i)
	{
		if (data[i] == ',')
		{
			data[i] = 0;
		}
	}
	
	res.push_back(std::string(data));
	
	for (i=0; i<SIZE1; ++i)
	{
		if (data[i] == 0)
		{
			res.push_back(std::string(data + i + 1));
		}
	}

	return res.size();
}

size_t CIniFile::ParseStrList(char * buf, const char * res[], size_t res_max)
{
	ASSERT(buf != NULL);
	ASSERT(res_max > 0);
	
	if (res_max == 0)
	{
		return 0;
	}
	
	size_t count = 0;
	
	const size_t SIZE1 = ::strlen(buf);
	
	size_t i;
	
	for (i=0; i<SIZE1; ++i)
	{
		if (buf[i] == ',')
		{
			buf[i] = 0;
		}
	}
	
	res[count] = buf;

	if (++count == res_max)
	{
		return count;
	}
	
	for (i=0; i<SIZE1; ++i)
	{
		if (buf[i] == 0)
		{
			res[count] = buf + i + 1;

			if (++count == res_max)
			{
				return count;
			}
		}
	}
	
	return count;
}

CIniFile::CIniFile()
{
	m_bLoad = false;
}

CIniFile::CIniFile(const char * filename)
: m_strFileName(filename)
{
	ASSERT(filename != NULL);
	
	m_bLoad = false;
}

CIniFile::~CIniFile()
{
}

void CIniFile::SetFileName(const char * filename)
{
	ASSERT(filename != NULL);

	m_strFileName = filename;
}

const char * CIniFile::GetFileName() const
{
	return m_strFileName.c_str();
}

bool CIniFile::Loaded() const
{
	return m_bLoad;
}

const CIniFile::SECTION * CIniFile::GetSection(const char * name) const
{
	ASSERT(name != NULL);

	u32 hash = ::GetHashValue(name);

	const size_t SIZE1 = m_Sections.size();
	
	for (size_t i=0; i<SIZE1; i++)
	{
		if ( (m_Sections[i].nHash == hash)
			&& (::stricmp(m_Sections[i].strName.c_str(), name) == 0) )
		{
			return &m_Sections[i];
		}
	}

	return NULL;
}

const CIniFile::ITEM * CIniFile::GetItem(const SECTION * pSection, 
										 const char * name) const
{
	ASSERT(pSection != NULL);
	ASSERT(name != NULL);

	u32 hash = ::GetHashValue(name);

	const size_t SIZE1 = pSection->items.size();

	for (size_t i=0; i<SIZE1; i++)
	{
		if ( (pSection->items[i].nHash == hash)
			&& (::stricmp(pSection->items[i].strName.c_str(), name) == 0) )
		{
			return &(pSection->items[i]);
		}
	}

	return NULL;
}

size_t CIniFile::GetSectCount() const
{
	return m_Sections.size();
}

const char * CIniFile::GetSectName(size_t index) const
{
	ASSERT(index < m_Sections.size());

	return m_Sections[index].strName.c_str();
}

size_t CIniFile::GetSectItemCount(size_t index) const
{
	ASSERT(index < m_Sections.size());

	return m_Sections[index].items.size();
}

bool CIniFile::GetSectItemData(size_t sect, size_t index, 
							   const char * & key, const char * & value) const
{
	ASSERT(sect < m_Sections.size());

	const SECTION * pSection = &m_Sections[sect];

	ASSERT(index < pSection->items.size());

	key = pSection->items[index].strName.c_str();
	value = pSection->items[index].strValue.c_str();

	return true;
}

bool CIniFile::LoadFromFile()
{
	m_Sections.clear();
	
	m_bLoad = false;
	
	FILE * fp = ::fopen(m_strFileName.c_str(), "rb");
	
	if (NULL == fp)
	{
		return false;
	}
	
	::fseek(fp, 0, SEEK_END);

	size_t size = ::ftell(fp);

	::fseek(fp, 0, SEEK_SET);
	
	CAutoBuffer auto_buf(size + 2);
	
	char * buffer = auto_buf.GetBuffer();
	
	if (::fread(buffer, sizeof(char), size, fp) != size)
	{
		::fclose(fp);
		return false;
	}
	
	buffer[size] = '\r';
	buffer[size + 1] = '\n';
	
	::fclose(fp);
	
	std::vector<const char *> lines;
	
	lines.reserve(256);
	
	size_t count = 0;
	
	const size_t SIZE1 = size + 2;

	size_t i;
	
	for (i=0; i<SIZE1; i++)
	{
		if ( (buffer[i] == '\r') || (buffer[i] == '\n') )
		{
			buffer[i] = 0;
			count = 0;
		}
		else
		{
			if (count == 0)
			{
				lines.push_back(&buffer[i]);
			}
			count++;
		}
	}
	
	std::vector<char> s;
	std::vector<char> t;

	s.reserve(256);
	t.reserve(256);
	
	SECTION * pSection = NULL;
	
	const size_t SIZE2 = lines.size();
	
	for (i=0; i<SIZE2; i++)
	{
		size_t len = ::strlen(lines[i]);
		
		s.resize(len + 1);

		len = ::TrimStringLen(lines[i], len, &s[0], s.size());
		
		if (len < 2)
		{
			continue;
		}
		
		const char * line = &s[0];
		
		if ( (len > 2) && ('[' == s[0]) && (']' == s[len - 1]) )
		{
			std::string sect(line + 1, len - 2);
			
			pSection = (SECTION *)GetSection(sect.c_str());
			
			if (NULL == pSection)
			{
				m_Sections.push_back(SECTION());
				
				pSection = &m_Sections.back();
				
				pSection->strName = sect;
				pSection->nHash = ::GetHashValue(sect.c_str());
			}
			
			continue;
		}
		
		if ( (s[0] == '/') && (s[1] == '/') )
		{
			continue;
		}
		
		if (s[0] == ';')
		{
			continue;
		}
		
		if (NULL == pSection)
		{
			continue;
		}
		
		const char * equal = ::strchr(line, '=');
		
		if ( (NULL == equal) || (equal == line) )
		{
			continue;
		}
		
		pSection->items.push_back(ITEM());
		
		ITEM * pItem = &pSection->items.back();
		
		t.resize(len + 1);
		
		::TrimStringLen(&s[0], (equal - line), &t[0], t.size());

		pItem->strName = &t[0];
		pItem->nHash = ::GetHashValue(&t[0]);
		
		if ((line + len) > (equal + 1))
		{
			::TrimString(equal + 1, &t[0], t.size());
			
			pItem->strValue = &t[0];
		}
		else
		{
			pItem->strValue = "";
		}
	}
	
	m_bLoad = true;

	return true;
}

bool CIniFile::SaveToFile() const
{
	FILE * fp = ::fopen(m_strFileName.c_str(), "wb");

	if (NULL == fp)
	{
		return false;
	}

	const SECTION *	pSection;
	
	std::string str;
	
	const size_t SIZE1 = m_Sections.size();

	for (size_t i=0; i<SIZE1; i++)
	{
		pSection = &m_Sections[i];

		str = "[";
		str += pSection->strName;
		str += "]\r\n";

		::fwrite(str.c_str(), sizeof(char), str.length(), fp);

		for (size_t k=0; k<pSection->items.size(); k++)
		{
			str = pSection->items[k].strName + "=" + 
				pSection->items[k].strValue + "\r\n";

			::fwrite(str.c_str(), sizeof(char), str.length(), fp);
		}

		str = "\r\n";

		::fwrite(str.c_str(), sizeof(char), str.length(), fp);
	}
	
	::fclose(fp);

	return true;
}

bool CIniFile::AddSection(const char * section)
{
	ASSERT(section != NULL);

	m_Sections.push_back(SECTION());

	SECTION & data = m_Sections.back();
	
	data.strName = section;
	data.nHash = ::GetHashValue(section);

	return true;
}

bool CIniFile::FindSection(const char * section) const
{
	ASSERT(section != NULL);

	return (GetSection(section) != NULL);
}

bool CIniFile::FindItem(const char * section, const char * key) const
{
	ASSERT(section != NULL);
	ASSERT(key != NULL);

	const SECTION * pSection = GetSection(section);

	if (NULL == pSection)
	{
		return false;
	}
	
	return (GetItem(pSection, key) != NULL);
}

bool CIniFile::DeleteItem(const char * section, const char * key)
{
	ASSERT(section != NULL);
	ASSERT(key != NULL);

	SECTION * pSection = (SECTION *)GetSection(section);

	if (NULL == pSection)
	{
		return false;
	}

	u32 hash = ::GetHashValue(key);

	const size_t SIZE1 = pSection->items.size();

	for (size_t i=0; i<SIZE1; i++)
	{
		if ( (pSection->items[i].nHash == hash)
			&& (::stricmp(pSection->items[i].strName.c_str(), key) == 0) )
		{
			pSection->items.erase(pSection->items.begin() + i);
			return true;
		}
	}
	
	return false;
}

size_t CIniFile::GetItemCount() const
{
	size_t count = 0;
	
	const size_t SIZE1 = m_Sections.size();

	for (size_t i=0; i<SIZE1; i++)
	{
		count += m_Sections[i].items.size();
	}
	
	return count;
}

bool CIniFile::GetItem(size_t index, const char * & section, 
					   const char * & key, const char * & value) const
{
	size_t count;
	
	const size_t SIZE1 = m_Sections.size();

	for (size_t i=0; i<SIZE1; i++)
	{
		count = m_Sections[i].items.size();
		
		if (index < count)
		{
			section = m_Sections[i].strName.c_str();
			key = m_Sections[i].items[index].strName.c_str();
			value = m_Sections[i].items[index].strValue.c_str();

			return true;
		}
		else
		{
			index -= count;
		}
	}

	return false;
}

bool CIniFile::FindValue(const char * section, const char * key, 
						 std::string & value) const
{
	ASSERT(section != NULL);
	ASSERT(key != NULL);

	const SECTION * pSection = GetSection(section);

	if (NULL == pSection)
	{
		return false;
	}
	
	const ITEM * pItem = GetItem(pSection, key);

	if (NULL == pItem)
	{
		return false;
	}

	value = pItem->strValue;

	return true;
}

const char * CIniFile::GetData(const char * section, const char * key) const
{
	ASSERT(section != NULL);
	ASSERT(key != NULL);

	const SECTION * pSection = GetSection(section);

	if (NULL == pSection)
	{
		return NULL;
	}
	
	const ITEM * pItem = GetItem(pSection, key);

	if (NULL == pItem)
	{
		return NULL;
	}

	return pItem->strValue.c_str();
}

int CIniFile::ReadInteger(const char * section, const char * key, int def) const
{
	const char * str = GetData(section, key);

	if (str)
	{
		return ::atoi(str);
	}
	else
	{
		return def;
	}
}

char * CIniFile::ReadString(const char * section, const char * key, 
							char * value, size_t maxlen) const
{
	ASSERT(value != NULL);
	ASSERT(maxlen > 0);

	const char * str = GetData(section, key);

	if (str)
	{
		size_t len = ::strlen(str);

		if (len >= maxlen)
		{
			len = maxlen - 1;
		}
		
		::memcpy(value, str, len);
		
		value[len] = 0;
	}

	return value;
}

std::string CIniFile::ReadString(const char * section, const char * key, 
							const char * def) const
{
	ASSERT(def != NULL);
	
	const char * str = GetData(section, key);

	if (str)
	{
		return std::string(str);
	}
	else
	{
		return std::string(def);
	}
}

bool CIniFile::ReadBool(const char * section, const char * key, bool def) const
{
	const char * str = GetData(section, key);

	if (str)
	{
		if (::stricmp(str, "true") == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return def;
	}
}

float CIniFile::ReadFloat(const char * section, const char * key, 
						  float def) const
{
	const char * str = GetData(section, key);

	if (str)
	{
		return (float)::atof(str);
	}
	else
	{
		return def;
	}
}

CIniFile::VECTOR2 CIniFile::ReadVector2(const char * section, const char * key, 
										const VECTOR2 & def) const
{
	const char * str = GetData(section, key);

	if (str)
	{
		VECTOR2 v;

		if (ParseVector2(str, v))
		{
			return v;
		}
	}

	return def;
}

CIniFile::VECTOR3 CIniFile::ReadVector3(const char * section, const char * key, 
										const VECTOR3 & def) const
{
	const char * str = GetData(section, key);

	if (str)
	{
		VECTOR3 v;

		if (ParseVector3(str, v))
		{
			return v;
		}
	}

	return def;
}

CIniFile::VECTOR4 CIniFile::ReadVector4(const char * section, const char * key, 
										const VECTOR4 & def) const
{
	const char * str = GetData(section, key);

	if (str)
	{
		VECTOR4 v;

		if (ParseVector4(str, v))
		{
			return v;
		}
	}

	return def;
}

u32 CIniFile::ReadByte4(const char * section, const char * key, u32 def) const
{
	const char * str = GetData(section, key);

	if (str)
	{
		u32 res;

		if (ParseByte4(str, res))
		{
			return res;
		}
	}

	return def;
}

bool CIniFile::SetData(const char * section, const char * key, const char * data)
{
	ASSERT(section != NULL);
	ASSERT(key != NULL);
	ASSERT(data != NULL);

	SECTION * pSection = (SECTION *)GetSection(section);

	if (NULL == pSection)
	{
		m_Sections.push_back(SECTION());

		pSection = &m_Sections.back();

		pSection->strName = section;
		pSection->nHash = ::GetHashValue(section);
	}
	
	ITEM * pItem = (ITEM *)GetItem(pSection, key);

	if (NULL == pItem)
	{
		pSection->items.push_back(ITEM());

		pItem = &(pSection->items.back());

		pItem->strName = key;
		pItem->nHash = ::GetHashValue(key);
	}

	pItem->strValue = data;

	return true;
}

bool CIniFile::WriteInteger(const char * section, const char * key, int value)
{
	char buf[32];

	::sprintf(buf, "%d", value);

	return SetData(section, key, buf);
}

bool CIniFile::WriteString(const char * section, const char * key, 
						   const char * value)
{
	return SetData(section, key, value);
}

bool CIniFile::WriteBool(const char * section, const char * key, bool value)
{
	if (value)
	{
		return SetData(section, key, "true");
	}
	else
	{
		return SetData(section, key, "false");
	}
}

bool CIniFile::WriteFloat(const char * section, const char * key, float value)
{
	char buf[32];

	::sprintf(buf, "%f", double(value));

	return SetData(section, key, buf);
}

bool CIniFile::WriteVector2(const char * section, const char * key, 
							const VECTOR2 & value)
{
	char buf[64];

	::sprintf(buf, "%f,%f", double(value.x), double(value.y));

	return SetData(section, key, buf);
}

bool CIniFile::WriteVector3(const char * section, const char * key, 
							const VECTOR3 & value)
{
	char buf[256];

	::sprintf(buf, "%f,%f,%f", 
		double(value.x), double(value.y), double(value.z));

	return SetData(section, key, buf);
}

bool CIniFile::WriteVector4(const char * section, const char * key, 
							const VECTOR4 & value)
{
	char buf[256];

	::sprintf(buf, "%f,%f,%f,%f", 
		double(value.x), double(value.y), 
		double(value.z), double(value.orient));

	return SetData(section, key, buf);
}

bool CIniFile::WriteByte4(const char * section, const char * key, u32 value)
{
	char buf[64];

	::sprintf(buf, "%d,%d,%d,%d", 
		BYTE1(value), BYTE2(value), BYTE3(value), BYTE4(value));

	return SetData(section, key, buf);
}

void CIniFile::Append(const CIniFile & other)
{
	m_Sections.insert(m_Sections.end(), other.m_Sections.begin(), 
		other.m_Sections.end());
}

