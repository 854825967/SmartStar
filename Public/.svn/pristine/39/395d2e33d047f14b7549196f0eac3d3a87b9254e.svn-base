#ifndef TARRAY_H
#define TARRAY_H

#include "MultiSys.h"
namespace tlib {
    template<typename type, int SIZE>
    class TArray {
    public:
        TArray() {
            m_count = 0;
        }
        
        TArray<type, SIZE> & operator << (const type & value) {
            m_value[m_count++] = value;
            return *this;
        }
        
        type & operator[] (int index) {
            ASSERT(index < m_count);
            return m_value[index];
        }
        
        const type & operator[] (int index) const {
            ASSERT(index < m_count);
            return m_value[index];
        }
        
        int length() const {
            return sizeof(m_count) + sizeof(type) * m_count;
        }
        
        int size() const {
            return m_count;
        }
        
        void clear() {
            m_count = 0;
        }
    private:
        int m_count;
        type m_value[SIZE];
    };
}

#endif //TARRAY_H
