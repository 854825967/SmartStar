#ifndef INIFILE_H
#define INIFILE_H

#include "MultiSys.h"

#include <vector>
#include <string>

// CIniFile 

class CIniFile
{
public:
	struct VECTOR2
	{
		float x;
		float y;
		
		VECTOR2()
		{
			x = 0.0f;
			y = 0.0f;
		}
		VECTOR2(float _x, float _y)
		{
			x = _x;
			y = _y;
		}
	};
	
	struct VECTOR3
	{
		float x;
		float y;
		float z;
		
		VECTOR3()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}
		VECTOR3(float _x, float _y, float _z)
		{
			x = _x;
			y = _y;
			z = _z;
		}
	};
	
	struct VECTOR4
	{
		float x;
		float y;
		float z;
		float orient;
		
		VECTOR4()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			orient = 0.0f;
		}
		VECTOR4(float _x, float _y, float _z, float _orient)
		{
			x = _x;
			y = _y;
			z = _z;
			orient = _orient;
		}
	};
	
private:
	struct ITEM
	{
		std::string		strName;
		u32			nHash;
		std::string		strValue;
	};
	
	struct SECTION
	{
		std::string		strName;
		u32			nHash;
		std::vector<ITEM > items;
	};
	
public:
	static bool ParseVector2(const char * str, VECTOR2 & res);
	static bool ParseVector3(const char * str, VECTOR3 & res);
	static bool ParseVector4(const char * str, VECTOR4 & res);
	static bool ParseByte4(const char * str, u32 & res);
	static size_t ParseString(const char * str, 
		std::vector<std::string> & res);
	static size_t ParseStrList(char * buf, 
		const char * res[], size_t res_max);

public:
	CIniFile();
	CIniFile(const char * filename);
	~CIniFile();

	// 设置文件名
	void SetFileName(const char * filename);
	// 获得文件名
	const char * GetFileName() const;
	// 加载文件
	bool LoadFromFile();
	// 保存文件
	bool SaveToFile() const;
	// 测试是否加载成功
	bool Loaded() const;
	// 添加段
	bool AddSection(const char * section);
	// 查找段
	bool FindSection(const char * section) const;
	// 查找段下的键
	bool FindItem(const char * section, const char * key) const;
	// 获得键值
	bool FindValue(const char * section, 
		const char * key, std::string & value) const;
	// 删除键
	bool DeleteItem(const char * section, const char * key);
	// 获得所有键的数量
	size_t GetItemCount() const;
	// 获得键的数据
	bool GetItem(size_t index, const char * & section, 
		const char * & key, const char * & value) const;
	// 获得段的数量
	size_t GetSectCount() const;
	// 获得段名称
	const char * GetSectName(size_t index) const;
	// 获得指定段下的键数量
	size_t GetSectItemCount(size_t index) const;
	// 获得指定段下的键数据
	bool GetSectItemData(size_t sect, size_t index, 
		const char * & key, const char * & value) const;

	// 读取键数据，当键不存在的时候返回缺省值(def)
	int ReadInteger(const char * section, const char * key, int def) const;
	char * ReadString(const char * section, 
		const char * key, char * value, size_t maxlen) const;
	std::string ReadString(const char * section, 
		const char * key, const char * def) const;
	bool ReadBool(const char * section, const char * key, bool def) const;
	float ReadFloat(const char * section, const char * key, float def) const;
	CIniFile::VECTOR2 ReadVector2(const char * section, 
		const char * key, const VECTOR2 & def) const;
	CIniFile::VECTOR3 ReadVector3(const char * section, 
		const char * key, const VECTOR3 & def) const;
	CIniFile::VECTOR4 ReadVector4(const char * section, 
		const char * key, const VECTOR4 & def) const;
	u32 ReadByte4(const char * section, const char * key, u32 def) const;

	// 改写键数据（如果段或键不存在则添加）
	bool WriteInteger(const char * section, const char * key, int value);
	bool WriteString(const char * section, 
		const char * key, const char * value);
	bool WriteBool(const char * section, const char * key, bool value);
	bool WriteFloat(const char * section, const char * key, float value);
	bool WriteVector2(const char * section, 
		const char * key, const VECTOR2 & value);
	bool WriteVector3(const char * section, 
		const char * key, const VECTOR3 & value);
	bool WriteVector4(const char * section, 
		const char * key, const VECTOR4 & value);
	bool WriteByte4(const char * section, const char * key, u32 value);

	// 合并另外一个文件
	void Append(const CIniFile & other);

private:
	bool SetData(const char * section, const char * key, const char * data);
	const char * GetData(const char * section, const char * key) const;
	const CIniFile::SECTION * GetSection(const char * name) const;
	const CIniFile::ITEM * GetItem(
		const SECTION * pSection, const char * name) const;

private:
	std::vector<SECTION>	m_Sections;
	std::string				m_strFileName;
	bool					m_bLoad;
};

#endif // _INIFILE_H
