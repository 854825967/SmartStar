#ifndef STARTPANEL_H
#define STARTPANEL_H

#include "Panel.h"
#include "Button.h"

class StartPanel : public Panel {
public:
    static Panel * create();
    virtual bool init();
    virtual void show(const bool start);
    virtual void hide();
    virtual void reset();

    void showTitle(cocos2d::Node * pSender);
    static void soundSwitch();

private:
    StartPanel();
    ~StartPanel() {
        s_pSelf = NULL;
    }
private:
    cocos2d::Sprite * m_pBigStar;
    cocos2d::Sprite * m_pTitle;
    Button * m_pButtons[STARTUI_MENU_COUNT];

    Button * m_pButtonSound;

    static StartPanel * s_pSelf;
};

#endif //STARTPANEL_H
