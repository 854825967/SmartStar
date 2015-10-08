#include "CTouchEngine.h"
USING_NS_CC;
using namespace std;

CTouchEngine::~CTouchEngine() {
    ECHO("CTouchEngine release");
    if (m_pListener) {
        _eventDispatcher->removeEventListener(m_pListener);
    }
}

bool CTouchEngine::init() {
    m_pListener = NULL;

    memset(m_pCurrentHandle, 0, sizeof(m_pCurrentHandle));
    if (Layer::init()) {
        m_pListener = EventListenerTouchAllAtOnce::create();
        m_pListener->onTouchesBegan = CC_CALLBACK_2(CTouchEngine::onTouchesBegan, this);
        m_pListener->onTouchesMoved = CC_CALLBACK_2(CTouchEngine::onTouchesMoved, this);
        m_pListener->onTouchesEnded = CC_CALLBACK_2(CTouchEngine::onTouchesEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(m_pListener, this);

        return true;
    }
    return false;
}

bool CTouchEngine::AddTouchHandle(const CTouchGrade grade, ITouchHandle * pHandle) {
    ASSERT(grade < TOUCH_GRADE_COUNT && pHandle->m_grade == TOUCH_GRADE_COUNT);
    m_TouchList[grade].push_back(pHandle);
    pHandle->m_grade = grade;
    return true;
}

bool CTouchEngine::RemoveTouchHandle(ITouchHandle * pHandle) {
    ASSERT(pHandle->m_grade < TOUCH_GRADE_COUNT);
    TOUCHHANDLE_LIST::iterator iend = m_TouchList[pHandle->m_grade].end();
    TOUCHHANDLE_LIST::iterator itor = std::find(m_TouchList[pHandle->m_grade].begin(), iend, pHandle);
    ASSERT(itor != iend);
    
    m_TouchList[pHandle->m_grade].erase(itor);

    pHandle->m_grade = TOUCH_GRADE_COUNT;
    return true;
}

bool CTouchEngine::dealTouch(const s8 index, const Point & point, const CTouchGrade grade, const CTouchEventType eventType) {
    bool res = false;
    switch(eventType) {
    case TOUCH_EVENT_BEGAN:
        {
            ITouchHandle * pHandle = NULL;
            TOUCHHANDLE_LIST::iterator itor = m_TouchList[grade].begin();
            TOUCHHANDLE_LIST::iterator iend = m_TouchList[grade].end();
            while (itor != iend) {
                if ((*itor)->IsTouch(point)) {
                    if (NULL == pHandle || (*itor)->GetTouchIndex() > pHandle->GetTouchIndex()) {
                        pHandle = *itor;
                    }
                }

                itor++;
            }
            
            if (pHandle != NULL) {
                m_pCurrentHandle[index] = pHandle;
                m_pCurrentHandle[index]->TouchEvent(point, TOUCH_EVENT_BEGAN);
                res = true;
            }

            break;
        }
    case TOUCH_EVENT_MOVED:
        {
            if (m_pCurrentHandle[index] != NULL) {
                m_pCurrentHandle[index]->TouchEvent(point, TOUCH_EVENT_MOVED);
                res = true;
            }

            ITouchHandle * pHandle = NULL;
            TOUCHHANDLE_LIST::iterator itor = m_TouchList[grade].begin();
            TOUCHHANDLE_LIST::iterator iend = m_TouchList[grade].end();
            while (itor != iend) {
                if ((*itor)->IsTouch(point)) {
                    if (NULL == pHandle || (*itor)->GetTouchIndex() > pHandle->GetTouchIndex()) {
                        pHandle = *itor;
                    }
                }

                itor++;
            }

            if (pHandle != NULL) {
                if (pHandle != m_pCurrentHandle[index]) {
                    if (m_pCurrentHandle[index] != NULL) {
                        m_pCurrentHandle[index]->TouchEvent(point, TOUCH_EVENT_CANCELED);
                    }
                    m_pCurrentHandle[index] = pHandle;
                    m_pCurrentHandle[index]->TouchEvent(point, TOUCH_EVENT_BEGAN);
                    res = true;
                }
            }

            break;
        }
    case TOUCH_EVENT_ENDED:
    case TOUCH_EVENT_CANCELED:
        {
            if (m_pCurrentHandle[index] != NULL) {
                if (m_pCurrentHandle[index]->IsTouch(point)) {
                    m_pCurrentHandle[index]->TouchEvent(point, TOUCH_EVENT_ENDED);
                } else {
                    m_pCurrentHandle[index]->TouchEvent(point, TOUCH_EVENT_CANCELED);
                }
                m_pCurrentHandle[index] = NULL;
                res = true;
            }
            break;
        }
    default:
        ASSERT(false);
        break;
    }

    return res;
}

void CTouchEngine::onTouchesBegan(const std::vector<Touch*> & touches, cocos2d::Event  *event) {
    std::vector<Touch*>::const_iterator itor = touches.begin();
    std::vector<Touch*>::const_iterator iend = touches.end();
    while (itor != iend) {
        CCTouch * pTouch = (CCTouch *)(* itor);    
        for (s8 i=TOUCH_GRADE_TOP; i< TOUCH_GRADE_COUNT; i++) {
            if (dealTouch(pTouch->getID(), pTouch->getLocation(), (CTouchGrade)i, TOUCH_EVENT_BEGAN)) {
                break;
            }
        }

        itor++;
    }
}

void CTouchEngine::onTouchesMoved(const std::vector<Touch*>& touches, cocos2d::Event  *event) {
    std::vector<Touch*>::const_iterator itor = touches.begin();
    std::vector<Touch*>::const_iterator iend = touches.end();
    while (itor != iend) {
        CCTouch * pTouch = (CCTouch *)(* itor);    
        for (s8 i=TOUCH_GRADE_TOP; i< TOUCH_GRADE_COUNT; i++) {
            if (dealTouch(pTouch->getID(), pTouch->getLocation(), (CTouchGrade)i, TOUCH_EVENT_MOVED)) {
                break;
            }
        }

        itor++;
    }
}

void CTouchEngine::onTouchesEnded(const std::vector<Touch*>& touches, cocos2d::Event  *event) {
    std::vector<Touch*>::const_iterator itor = touches.begin();
    std::vector<Touch*>::const_iterator iend = touches.end();
    while (itor != iend) {
        CCTouch * pTouch = (CCTouch *)(* itor);    
        for (s8 i=TOUCH_GRADE_TOP; i< TOUCH_GRADE_COUNT; i++) {
            if (dealTouch(pTouch->getID(), pTouch->getLocation(), (CTouchGrade)i, TOUCH_EVENT_ENDED)) {
                break;
            }
        }

        itor++;
    }
}

void CTouchEngine::onTouchesCancelled(const std::vector<Touch*>& touches, cocos2d::Event  *event) {
    std::vector<Touch*>::const_iterator itor = touches.begin();
    std::vector<Touch*>::const_iterator iend = touches.end();
    while (itor != iend) {
        CCTouch * pTouch = (CCTouch *)(* itor);    
        for (s8 i=TOUCH_GRADE_TOP; i< TOUCH_GRADE_COUNT; i++) {
            if (dealTouch(pTouch->getID(), pTouch->getLocation(), (CTouchGrade)i, TOUCH_EVENT_CANCELED)) {
                break;
            }
        }

        itor++;
    }
}
