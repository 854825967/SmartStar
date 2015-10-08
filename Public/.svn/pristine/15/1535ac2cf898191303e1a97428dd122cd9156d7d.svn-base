#ifndef ARCHIVE_H
#define ARCHIVE_H

typedef enum {
    VAR_TYPE_INT8 = 0,
    VAR_TYPE_INT16 = 1,
    VAR_TYPE_INT32 = 2,
    VAR_TYPE_INT64 = 3,
    VAR_TYPE_DOUBLE = 4,
    VAR_TYPE_STRING = 5,
    VAR_TYPE_STRUCT = 6,

    /*===ADD BEFOR THIS ===*/
    VAR_TYPE_UNKNOWN
}eVarType;

struct var_info {
    s8 type;
    s32 index;
};

#define SEND_ARCHIVE(nConnection, archive) { \
    archive.m_nLen = sizeof(s32) + sizeof(s32) + sizeof(s32) + sizeof(s32) + archive.m_nCount * sizeof(var_info) + archive.m_nCurrent; \
    s_pKernel->Send(nConnection, &(archive.m_nLen), sizeof(archive.m_nLen)); \
    s_pKernel->Send(nConnection, &(archive.m_nID), sizeof(archive.m_nID)); \
    s_pKernel->Send(nConnection, &(archive.m_nCount), sizeof(archive.m_nCount)); \
    s_pKernel->Send(nConnection, &(archive.m_nCurrent), sizeof(archive.m_nCurrent)); \
    s_pKernel->Send(nConnection, archive.GetVarInfo(), sizeof(var_info) * archive.m_nCount); \
    s_pKernel->Send(nConnection, archive.GetBuff(), archive.m_nCurrent); \
}

template <s32 count = 8, s32 size = 4096>
class Archive{
public:
    Archive() {
        memset(this, 0, sizeof(*this));
    }

    Archive(char * pBuff, s32 size) {
        memset(this, 0, sizeof(*this));
        m_nLen = *(s32 *)pBuff;
        m_nID = *(s32 *)(pBuff + sizeof(s32));
        m_nCount = *(s32 *)(pBuff + sizeof(s32) + sizeof(s32));
        m_nCurrent = *(s32 *)(pBuff + sizeof(s32) + sizeof(s32) + sizeof(s32));
        m_pVarInfo = (var_info *)(pBuff + sizeof(s32) + sizeof(s32) + sizeof(s32) + sizeof(s32));
        m_pBuff = (char *)(pBuff + sizeof(s32) + sizeof(s32) + sizeof(s32) + sizeof(s32) + sizeof(var_info) * m_nCount);
    }

    void SetID(const s32 id) {
        m_nID = id;
    }

    void In(const s8 & nValue) {
        ASSERT(m_nCurrent + sizeof(nValue) <= size && m_nCount < count);
        m_szVarInfo[m_nCount].type = VAR_TYPE_INT8;
        m_szVarInfo[m_nCount].index = m_nCurrent;
        memcpy(&m_szBuff[m_nCurrent], &nValue, sizeof(nValue));
        m_nCount++;
        m_nCurrent+=sizeof(nValue);
    }

    void In(const s16 & nValue) {
        ASSERT(m_nCurrent + sizeof(nValue) <= size && m_nCount < count);
        m_szVarInfo[m_nCount].type = VAR_TYPE_INT16;
        m_szVarInfo[m_nCount].index = m_nCurrent;
        memcpy(&m_szBuff[m_nCurrent], &nValue, sizeof(nValue));
        m_nCount++;
        m_nCurrent+=sizeof(nValue);
    }

    void In(const s32 & nValue) {
        ASSERT(m_nCurrent + sizeof(nValue) <= size && m_nCount < count);
        m_szVarInfo[m_nCount].type = VAR_TYPE_INT32;
        m_szVarInfo[m_nCount].index = m_nCurrent;
        memcpy(&m_szBuff[m_nCurrent], &nValue, sizeof(nValue));
        m_nCount++;
        m_nCurrent+=sizeof(nValue);
    }

    void In(const s64 & lValue) {
        ASSERT(m_nCurrent + sizeof(lValue) <= size && m_nCount < count);
        m_szVarInfo[m_nCount].type = VAR_TYPE_INT64;
        m_szVarInfo[m_nCount].index = m_nCurrent;
        memcpy(&m_szBuff[m_nCurrent], &lValue, sizeof(lValue));
        m_nCount++;
        m_nCurrent+=sizeof(lValue);
    }

    void In(const double & dValue) {
        ASSERT(m_nCurrent + sizeof(dValue) <= size && m_nCount < count);
        m_szVarInfo[m_nCount].type = VAR_TYPE_DOUBLE;
        m_szVarInfo[m_nCount].index = m_nCurrent;
        memcpy(&m_szBuff[m_nCurrent], &dValue, sizeof(dValue));
        m_nCount++;
        m_nCurrent+=sizeof(dValue);
    }

    void In(const char * pValue) {
        s32 nLen = strlen(pValue) + 1;
        ASSERT(m_nCurrent + nLen <= size && m_nCount < count);
        m_szVarInfo[m_nCount].type = VAR_TYPE_STRING;
        m_szVarInfo[m_nCount].index = m_nCurrent;
        memcpy(&m_szBuff[m_nCurrent], pValue, nLen);
        m_nCount++;
        m_nCurrent+=nLen;
    }

    void InStruct(const void * pValue, const s32 nLen) {
        ASSERT(m_nCurrent + nLen <= size && m_nCount < count);
        m_szVarInfo[m_nCount].type = VAR_TYPE_STRUCT;
        m_szVarInfo[m_nCount].index = m_nCurrent;
        memcpy(&m_szBuff[m_nCurrent], pValue, nLen);
        m_nCount++;
        m_nCurrent+=nLen;
    }

    s8 Type(const s32 index) const {
        ASSERT(index < m_nCount);
        const var_info * pVarInfo = (m_pVarInfo != NULL)?m_pVarInfo : m_szVarInfo;

        return pVarInfo[index].type;
    }

    s32 Count() const {
        return m_nCount;
    }

    s8 GetInt8(const s32 index) const {
        const var_info * pVarInfo = (m_pVarInfo != NULL)?m_pVarInfo : m_szVarInfo;
        const char * pBuff = (m_pBuff != NULL)?m_pBuff: m_szBuff;

        ASSERT(index < m_nCount && pVarInfo[index].type == VAR_TYPE_INT8);
        return *(s8 *)(pBuff + pVarInfo[index].index);
    }

    s16 GetInt16(const s32 index) const {
        const var_info * pVarInfo = (m_pVarInfo != NULL)?m_pVarInfo : m_szVarInfo;
        const char * pBuff = (m_pBuff != NULL)?m_pBuff: m_szBuff;

        ASSERT(index < m_nCount && pVarInfo[index].type == VAR_TYPE_INT16);
        return *(s16 *)(pBuff + pVarInfo[index].index);
    }

    s32 GetInt32(const s32 index) const {
        const var_info * pVarInfo = (m_pVarInfo != NULL)?m_pVarInfo : m_szVarInfo;
        const char * pBuff = (m_pBuff != NULL)?m_pBuff: m_szBuff;

        ASSERT(index < m_nCount && pVarInfo[index].type == VAR_TYPE_INT32);
        return *(s32 *)(pBuff + pVarInfo[index].index);
    }

    s64 GetInt64(const s32 index) const {
        const var_info * pVarInfo = (m_pVarInfo != NULL)?m_pVarInfo : m_szVarInfo;
        const char * pBuff = (m_pBuff != NULL)?m_pBuff: m_szBuff;
        ASSERT(index < m_nCount && pVarInfo[index].type == VAR_TYPE_INT64);
        return *(s64 *)(pBuff + pVarInfo[index].index);
    }

    double GetDouble(const s32 index) const {
        const var_info * pVarInfo = (m_pVarInfo != NULL)?m_pVarInfo : m_szVarInfo;
        const char * pBuff = (m_pBuff != NULL)?m_pBuff: m_szBuff;
        ASSERT(index < m_nCount && pVarInfo[index].type == VAR_TYPE_DOUBLE);
        return *(double *)(pBuff + pVarInfo[index].index);
    }

    const char * GetString(const s32 index) const {
        const var_info * pVarInfo = (m_pVarInfo != NULL)?m_pVarInfo : m_szVarInfo;
        const char * pBuff = (m_pBuff != NULL)?m_pBuff: m_szBuff;
        ASSERT(index < m_nCount && pVarInfo[index].type == VAR_TYPE_STRING);
        return pBuff + pVarInfo[index].index;
    }

    void * GetStruct(const s32 index, const s32 & nSize) const {
        const var_info * pVarInfo = (m_pVarInfo != NULL)?m_pVarInfo : m_szVarInfo;
        const char * pBuff = (m_pBuff != NULL)?m_pBuff: m_szBuff;
        ASSERT(index < m_nCount && pVarInfo[index].type == VAR_TYPE_STRUCT);
        return pBuff + pVarInfo[index].index;
    }

    void Clear() {
        memset(this, 0, sizeof(*this));
    }

    Archive<count, size> & operator << (const s8 & nValue) {
        In(nValue);
        return *this;
    }

    Archive<count, size> & operator << (const s16 & nValue) {
        In(nValue);
        return *this;
    }

    Archive<count, size> & operator << (const s32 & nValue) {
        In(nValue);
        return *this;
    }

    Archive<count, size> & operator << (const s64 & lValue) {
        In(lValue);
        return *this;
    }

    Archive<count, size> & operator << (const double & dValue) {
        In(dValue);
        return *this;
    }

    Archive<count, size> & operator << (const char * pValue) {
        In(pValue);
        return *this;
    }

    const void * GetVarInfo() {
        const var_info * pVarInfo = (m_pVarInfo != NULL)?m_pVarInfo : m_szVarInfo;
        return pVarInfo;
    }    

    const void * GetBuff() {
        const char * pBuff = (m_pBuff != NULL)?m_pBuff: m_szBuff;
        return pBuff;
    }

public:
    s32 m_nLen;
    s32 m_nID;
    s32 m_nCount;
    s32 m_nCurrent;
    

private:
    var_info m_szVarInfo[count];
    var_info * m_pVarInfo;

    char m_szBuff[size];
    char * m_pBuff;
};

#endif //ARCHIVE_H
