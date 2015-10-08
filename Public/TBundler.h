#ifndef TBUNDLER_H
#define TBUNDLER_H
#include "MultiSys.h"
#include "CHashMap.h"
#include "Tools.h"
#include <list>
#include <algorithm>
namespace tlib {
    class base_class {
        
    };
    
    template<typename... Args>
    class bundler {
        typedef void (base_class::*member_fun)(Args...);
    public:
        bundler(void * pObj, member_fun pAddress, const char * pDebug) {
            m_pObj = (base_class *)pObj;
            m_pAddress =(member_fun)pAddress;
            m_debug = pDebug;
            m_deleted = false;
        }
        
        ~bundler() {
//            m_pObj = NULL;
//            m_pAddress = NULL;
        }
        
        void bindler_call(Args... a) {
            (m_pObj->*m_pAddress)(a...);
        }
        
        bool operator == (const bundler<Args...> & target) {
            return (this->m_pObj == target.m_pObj && this->m_pAddress == target.m_pAddress);
        }
        
        string m_debug;
        base_class * m_pObj;
        member_fun m_pAddress;
        bool m_deleted;
    };
    
    template<typename ID_TYPE, typename... Args>
    class bundler_pool {
        typedef void (base_class::*member_fun)(Args...);
        typedef std::list< bundler<Args...> > BUNDLER_LIST;
        typedef CHashMap<ID_TYPE, BUNDLER_LIST> BUNDLER_POOL;
        struct delete_node {
            typename BUNDLER_POOL::iterator map_itor;
            typename BUNDLER_LIST::iterator list_itor;
            
            delete_node(typename BUNDLER_POOL::iterator & _mapitor, typename BUNDLER_LIST::iterator & _listitor) {
                map_itor = _mapitor;
                list_itor = _listitor;
            }
            
            void deleted() {
                //ECHO("delete %d, %s, %lx::%lx", map_itor->first, list_itor->m_debug.c_str(), list_itor->m_pObj, list_itor->m_pAddress);
                map_itor->second.erase(list_itor);
            }
        };
        typedef std::list< delete_node > DELETE_LIST;
        
    public:
        bool bind(ID_TYPE id, void * pObj, member_fun paddress, const char * pinfo = "") {
            typename BUNDLER_POOL::iterator pool_itor = m_bundler_pool.find(id);
            if (pool_itor == m_bundler_pool.end()) {
                m_bundler_pool.insert(make_pair( id, BUNDLER_LIST() ));
                pool_itor = m_bundler_pool.find(id);
                pool_itor->second.push_back(bundler<Args...>(pObj, paddress, pinfo));
            } else {
                typename BUNDLER_LIST::iterator list_itor = std::find(pool_itor->second.begin(), pool_itor->second.end(), bundler<Args...>(pObj, paddress, ""));
                if (list_itor != pool_itor->second.end()) {
                    if (list_itor->m_deleted) {
                        typename DELETE_LIST::iterator del_itor = m_delete_list.begin();
                        typename DELETE_LIST::iterator del_iend = m_delete_list.end();
                        while (del_itor != del_iend) {
                            if (del_itor->map_itor == pool_itor && del_itor->list_itor == list_itor) {
                                del_itor->deleted();
                                m_delete_list.erase(del_itor);
                                break;
                            }
                            
                            del_itor++;
                        }
                    } else {
                        //ECHO("double add bindler %s", pinfo);
                        ASSERT(false);
                        return false;
                    }
                }
                
                //ECHO("BIND %d, %s, %lx::%lx", id, pinfo, pObj, paddress);
                pool_itor->second.push_back(bundler<Args...>(pObj, paddress, pinfo));
            }
            
            return true;
        }
        
        bool unbind(ID_TYPE id, void * pObj, member_fun paddress) {
            typename BUNDLER_POOL::iterator pool_itor = m_bundler_pool.find(id);
            if (pool_itor == m_bundler_pool.end()) {
                return false;
            }
            
            typename BUNDLER_LIST::iterator list_itor = std::find( pool_itor->second.begin(), pool_itor->second.end(), bundler<Args...>(pObj, paddress, "") );
            if (list_itor == pool_itor->second.end()) {
                return false;
            }

            //ECHO("UNBIND %d, %s, %lx::%lx", id, list_itor->m_debug.c_str(), list_itor->m_pObj, list_itor->m_pAddress);
            list_itor->m_deleted = true;
            m_delete_list.push_back(delete_node(pool_itor, list_itor));
            return true;
        }
        
        void unbind(void * pObj) {
            typename BUNDLER_POOL::iterator pool_itor = m_bundler_pool.begin();
            typename BUNDLER_POOL::iterator pool_iend = m_bundler_pool.end();
            
            for(;pool_itor != pool_iend; pool_itor++) {
                typename BUNDLER_LIST::iterator list_itor = pool_itor->second.begin();
                typename BUNDLER_LIST::iterator list_iend = pool_itor->second.end();
                
                while(list_itor != list_iend) {
                    if (list_itor->m_pObj == pObj) {
                        list_itor->m_deleted = true;
                        
                        m_delete_list.push_back(delete_node(pool_itor, list_itor));
                        //ECHO("UNBIND %d, %s, %lx::%lx", pool_itor->first, list_itor->m_debug.c_str(), list_itor->m_pObj, list_itor->m_pAddress);
                    }
                    list_itor ++;
                }
            }
        }
        
        void call_bundler(ID_TYPE id, Args... a) {
            typename BUNDLER_POOL::iterator pool_itor = m_bundler_pool.find(id);
            if (pool_itor == m_bundler_pool.end()) {
                return;
            }
            
            typename BUNDLER_LIST::iterator list_itor = pool_itor->second.begin();
            typename BUNDLER_LIST::iterator list_iend = pool_itor->second.end();
            while (list_itor != list_iend) {
                if (!list_itor->m_deleted) {
                    //ECHO("call %s", list_itor->m_debug.c_str());
                    list_itor->bindler_call(a...);
                } else {
                    //ECHO("bundler %s has been deleted", list_itor->m_debug.c_str());
                }
                
                list_itor++;
            }
        }
        
        void reflush() {
            typename DELETE_LIST::iterator del_itor = m_delete_list.begin();
            typename DELETE_LIST::iterator del_iend = m_delete_list.end();
            while (del_itor != del_iend) {
                del_itor->deleted();
                del_itor++;
            }
            m_delete_list.clear();
        }
    private:
        BUNDLER_POOL m_bundler_pool;
        DELETE_LIST m_delete_list;
    };
}

#endif //TBUNDLER_H
