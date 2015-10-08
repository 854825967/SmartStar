#ifndef TATTRIBUTE_H
#define TATTRIBUTE_H

#include "MultiSys.h"

namespace tlib {
    template <s32 attrib_count>
    class TAttribute {
    public:
        TAttribute() {
            ClearBuff();
        }

        virtual void ClearBuff() {
            memset(this, 0, sizeof(*this));
        }

        virtual void InitializeAttribBuff(const void * buff, const s32 nSize) {
            ASSERT(nSize <= sizeof(szBuff));
            memcpy(szBuff, buff, nSize);
        }

        virtual void SetAttribValue(const s32 nAttribID, const s32 nValue, bool bSync = false, bool bUpdatedCall = false) {
            ASSERT(nAttribID < attrib_count);
            szBuff[nAttribID] = nValue;
            if (bUpdatedCall) {
                AttribUpdated(nAttribID, (const char *)&szBuff[nAttribID]);
            }

            if (bSync) {
                Sync(nAttribID, (const char *)&szBuff[nAttribID], sizeof(nValue));
            }
        }

        virtual void SetAttribValue64(const s32 nAttribID, const s64 lValue, bool bSync = false, bool bUpdatedCall = false) {
            ASSERT(nAttribID < attrib_count);
            SetAttrib(nAttribID, (const char *)&lValue, sizeof(lValue), bSync, bUpdatedCall);
        }

        virtual s64 GetAttribValue64(const s32 nAttribID) {
            ASSERT(nAttribID < attrib_count);
            return *(s64 *)(&szBuff[nAttribID]);
        }

        virtual s32 GetAttribValue(const s32 nAttribID) {
            ASSERT(nAttribID < attrib_count);
            return szBuff[nAttribID];
        }

        virtual void SetAttrib(const s32 nAttribID, const char * pValue, const s32 nLen, bool bSync = false, bool bUpdatedCall = false) {
            ASSERT(nAttribID < attrib_count);
            memcpy(&szBuff[nAttribID], pValue, nLen);
            if (bUpdatedCall) {
                AttribUpdated(nAttribID, pValue);
            }
            
            if (bSync) {
                Sync(nAttribID, (const char *)&szBuff[nAttribID], nLen);
            }
        }

        virtual const char * GetAttrib(const s32 nAttribID) {
            ASSERT(nAttribID < attrib_count);
            return (const char *)&szBuff[nAttribID];
        }

        virtual const char * GetBuff() {
            return (const char *)szBuff;
        }

        virtual s32 GetAttribBuffSize() {
            return sizeof(szBuff);
        }

    protected:
        virtual void Sync(const s32 nAttribID, const char * pValue, const s32 nLen) = 0;
        virtual void AttribUpdated(const s32 nAttribID, const char * pValue) {}

    private:
        s32 szBuff[attrib_count];
    };
}

#endif //TATTRIBUTE_H
