#ifndef TFSM_H
#define TFSM_H
#include "CHashMap.h"
#include "Tools.h"
#include <map>

namespace tlib {
    template<typename type>
    struct TStateTranser{
        TStateTranser() {

        }

        TStateTranser(const type & state, const type & transer) {
            m_state = state;
            m_transer = transer;
        }

        TStateTranser<type> & operator = (const TStateTranser<type> & target) {
            m_state = target.m_state;
            m_transer = target.m_transer;
            return *this;
        }

        bool operator < (const TStateTranser<type> & target) const {
            return (this->m_state < target.m_state);
        }

        bool operator == (const TStateTranser<type> & target) const {
            return (this->m_state == target.m_state && this->m_transer == target.m_transer);
        }

        type m_state;
        type m_transer;
    }; //状态迁移节点,用于查找从某一状态迁移到另一状态的事件.

    template<typename type, typename host, type initState>
    class TFsm {
        typedef bool (host:: * state_event)();
        typedef void (host:: * update_event)(s64);

        struct updateinfo {
            update_event pEvent;
            s64 lCycle;

            updateinfo(const update_event pEvent, const s64 lCycle){
                this->pEvent = pEvent;
                this->lCycle = lCycle;
            }
        };

        typedef TStateTranser<type> TRANSER;
        typedef CHashMap<type, state_event> ENTRY_MAP, LEAVE_MAP;
        typedef CHashMap<type, updateinfo> UPDATE_MAP;
        typedef std::map<TRANSER, state_event> TRANSER_MAP;

    public:
        TFsm() {
            m_pHost = NULL;
            m_state = initState;
            m_lTick = ::GetCurrentTimeTick();
            m_lLastUpdateTick = m_lTick;
            m_lDuration = 0;
            m_lock = false;
        }

        TFsm(host * pHost) {
            ASSERT(pHost);
            m_pHost = pHost;
            m_state = initState;
            m_lTick = ::GetCurrentTimeTick();
            m_lDuration = 0;
            m_lock = false;
        }

        void SetHost(host * pHost) {
            ASSERT(pHost);
            m_pHost = pHost;
        }

        type GetState() {
            return m_state;
        }

        void Update() {
            s64 lTick = ::GetCurrentTimeTick();
            typename UPDATE_MAP::iterator itor = m_UpdateEvent_Map.find(m_state);
            if (m_UpdateEvent_Map.end() != itor) {
                update_event pEvent = itor->second.pEvent;
                if (itor->second.lCycle > 0) {
                    if (lTick - m_lLastUpdateTick >= itor->second.lCycle) {
                        m_lLastUpdateTick += itor->second.lCycle;
                        (m_pHost->*pEvent)(lTick);
                    }
                } else {
                    (m_pHost->*pEvent)(lTick);
                }
            }
            
            if (m_lDuration != 0) {
                if (lTick - m_lTick >= m_lDuration) {
                    m_lock = false;
                    EntryState(m_nextState);
                    m_lDuration = 0;
                }
            }
        }

        s64 GetLastEntryStateTimeTick() {
            return m_lTick;
        }

        void SetNextState(const type & state) {
            m_nextState = state;
        }
        
        bool IsLock() {
            return m_lock;
        }

        bool EntryState(const type & state, const s64 duration = 0, const bool lock = false, const type nextState = initState) {
            if (state == m_state) {
                m_state = state;
                return true;
            }

            if (m_lock) {
                return false;
            }

            if (!Leave() || !Transer(state)) {
                return false;
            }

            typename ENTRY_MAP::iterator itor = m_EntryEvent_Map.find(state);
            if (m_EntryEvent_Map.end() == itor) {
                m_state = state;
                return true;
            }
            state_event pEvent = itor->second;
            if (!(m_pHost->*pEvent)()) {
                return false;
            }

            m_state = state;
            m_lTick = ::GetCurrentTimeTick();
            m_lLastUpdateTick = m_lTick;
            m_lDuration = duration;
            m_lock = lock;
            m_nextState = nextState;
            return true;
        }

        void RgsUpdateEvent(const type & state, const update_event event, const s64 lCycle = 0) {
            ASSERT(event != NULL && lCycle >= 0 && m_UpdateEvent_Map.find(state) == m_UpdateEvent_Map.end());
            m_UpdateEvent_Map.insert(make_pair(state, updateinfo(event, lCycle)));
        }

        void UnRgsUpdateEvent(const type & state) {
            ASSERT(event != NULL && m_UpdateEvent_Map.find(state) != m_UpdateEvent_Map.end());
            m_UpdateEvent_Map.erase(m_UpdateEvent_Map.find(state));
        }

        void RgsEntryEvent(const type & state, const state_event event) {
            ASSERT(event != NULL && m_EntryEvent_Map.find(state) == m_EntryEvent_Map.end());
            m_EntryEvent_Map.insert(make_pair(state, event));
        }

        void UnRgsEntryEvent(const type & state) {
            ASSERT(m_EntryEvent_Map.find(state) != m_EntryEvent_Map.end());
            m_EntryEvent_Map.erase(m_EntryEvent_Map.find(state));
        }

        void RgsLeaveEvent(const type & state, const state_event event) {
            ASSERT(m_LeaveEvent_Map.find(state) == m_LeaveEvent_Map.end());
            m_LeaveEvent_Map.insert(make_pair(state, event));
        }

        void UnRgsLeaveEvent(const type & state) {
            ASSERT(m_LeaveEvent_Map.find(state) != m_LeaveEvent_Map.end());
            m_LeaveEvent_Map.erase(m_LeaveEvent_Map.find(state));
        }

        void RgsTranserEvent(const type & state, const type & trancer, const state_event event) {
            ASSERT(m_TranserEvent_Map.find(TRANSER(state, trancer)) == m_TranserEvent_Map.end());
            m_TranserEvent_Map.insert(make_pair(TRANSER(state, trancer), event));
        }

        void UnRgsTranserEvent(const type & state, const type & trancer) {
            ASSERT(m_TranserEvent_Map.find(TRANSER(state, trancer)) != m_TranserEvent_Map.end());
            m_TranserEvent_Map.erase(m_TranserEvent_Map.find(TRANSER(state, trancer)));
        }

    private:
        bool Leave() {
            typename LEAVE_MAP::iterator itor = m_LeaveEvent_Map.find(m_state);
            if (m_LeaveEvent_Map.end() == itor) {
                return true;
            }

            state_event pEvent = itor->second;
            return (m_pHost->*pEvent)(); 
        }

        bool Transer(const type & transer) {
            typename TRANSER_MAP::iterator itor = m_TranserEvent_Map.find( TRANSER(m_state, transer) );
            if (m_TranserEvent_Map.end() == itor) {
                return true;
            }

            state_event pEvent = itor->second;
            return (m_pHost->*pEvent)(); 
        }

    private:
        ENTRY_MAP m_EntryEvent_Map;
        LEAVE_MAP m_LeaveEvent_Map;
        UPDATE_MAP m_UpdateEvent_Map;
        TRANSER_MAP m_TranserEvent_Map;
        
        host * m_pHost;
        type m_state;
        type m_nextState;
        s64 m_lTick;
        s64 m_lDuration;
        s64 m_lLastUpdateTick;
        bool m_lock;
    };
}

#endif //TFSM_H
