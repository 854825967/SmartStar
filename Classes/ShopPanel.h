#ifndef SHOPPANEL_H
#define SHOPPANEL_H
#include "Header.h"
#include "Panel.h"
#include "Button.h"
#include "ITouchHandle.h"

class ShopPanel : public Panel, public ITouchHandle {
public:
    static Panel * create();

    ~ShopPanel() {
        s_pSelf = NULL;
    }

    virtual bool init();
    virtual void show(const bool start = false);
    virtual void hide();
    virtual void reset();

    virtual s32 GetTouchIndex() {
        return 0;
    }

    virtual bool IsTouch(const cocos2d::Point & point) {
        return true;
    }

    virtual void TouchEvent(const cocos2d::Point & point, const CTouchEventType nEventType) {

    }

    static void pay1();
    static void pay2();
    static void pay5();
    static void pay6();
    static void pay8();
    static void pay10();

private:
    ShopPanel();
    static void closeShop();

private:
    static ShopPanel * s_pSelf;
    Button * m_pButton1;
    Button * m_pButton2;
    Button * m_pButton3;
    Button * m_pButton4;
    Button * m_pButton5;
    Button * m_pButtonClose;
};

#endif //SHOPPANEL_H
