#ifndef EXITTPANEL_H
#define EXITTPANEL_H

#include "Panel.h"
#include "Button.h"
#include "ITouchHandle.h"

class ExitPanel : public Panel, public ITouchHandle {
public:
    static Panel * create();

    virtual bool init();
    virtual void show(const bool start = false);
    virtual void hide();
    virtual void reset();

    ~ExitPanel() {
        s_pSelf = NULL;
    }


    s32 GetTouchIndex() {
        return 0;
    }

    bool IsTouch(const cocos2d::Point & point) {
        return true;
    }

    void TouchEvent(const cocos2d::Point & point, const CTouchEventType nEventType) {
        
    }

private:
    ExitPanel() {

    }

private:
    Button * m_pButtonYes;
    Button * m_pButtonNo;

    static ExitPanel * s_pSelf;
};

#endif //EXITTPANEL_H
