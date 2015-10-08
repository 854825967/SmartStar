#ifndef DEFEATPANEL_H
#define DEFEATPANEL_H

#include "Panel.h"
#include "Button.h"

class DefeatPanel : public Panel {
public:
    static Panel * create();

    virtual bool init();
    virtual void show(const bool start = false);
    virtual void hide();
    virtual void reset();

    void showOver(cocos2d::Node * pSender);
    void clearStarCount(float);
    void clearPoint(float);


    ~DefeatPanel() {
        s_pSelf = NULL;
    }

private:
    DefeatPanel() {
        m_nBlueCount = 0;
        m_nYellowCount = 0;
        m_nRedCount = 0;
        m_nPoint = 0; 
    }

private:
    cocos2d::Label * m_pBlueCountLabel;
    cocos2d::Label * m_pRedCountLabel;
    cocos2d::Label * m_pYellowCountLabel;
    cocos2d::Label * m_pPointLabel;

    s32 m_nBlueCount;
    s32 m_nYellowCount;
    s32 m_nRedCount;
    s32 m_nPoint;

    Button * m_pButtonReplay;

    static DefeatPanel * s_pSelf;
};

#endif //DEFEATPANEL_H
