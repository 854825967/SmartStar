#ifndef CTOUCHENGINE_H
#define CTOUCHENGINE_H
#include "Interface/ITouchHandle.h"
#include "Header.h"
#include <list>
#include <vector>
#define MAX_MULTI_TOUCH_COUNT 5

typedef std::list<ITouchHandle *> TOUCHHANDLE_LIST;

class CTouchEngine : public cocos2d::Layer {
public:
    virtual ~CTouchEngine();

    virtual bool init();
    virtual void onEnter() {
        Layer::onEnter();
    }
    virtual bool AddTouchHandle(const CTouchGrade grade, ITouchHandle * pHandle);
    virtual bool RemoveTouchHandle(ITouchHandle * pHandle);
    
protected:  
    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event  *event);
protected:
    bool dealTouch(const s8 index, const cocos2d::Point & point, const CTouchGrade grade, const CTouchEventType eventType);

protected:
    ITouchHandle * m_pCurrentHandle[MAX_MULTI_TOUCH_COUNT];
    TOUCHHANDLE_LIST m_TouchList[TOUCH_GRADE_COUNT];
    cocos2d::EventListenerTouchAllAtOnce * m_pListener;
};

#endif //CTOUCHENGINE_H
