#ifndef SMART09_H
#define SMART09_H

#include "Header.h"
#include "CTouchEngine.h"
#include "Chess.h"
#include "Panel.h"
#include <vector>
#include "TCallBack.h"
using namespace tlib;

#define RGS_EVENT_CALL(id, call) \
    Smart09::RgsEventCall(id, call, #call);

#define UNRGS_EVENT_CALL(id, call) \
    Smart09::UnRgsEventCall(id, call);

class Smart09 : public CTouchEngine {
public:
    static Smart09 * create();
    static bool RgsEventCall(const s32 nEventID, const event_fun call, const char * debug);
    static bool UnRgsEventCall(const s32 nEventID, const event_fun call);
    static void CallEvent(const s32 nEventID);

    Smart09() {
        g_config.m_nRandom = ::GetCurrentTimeTick() % 3;
    }
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();

private:
    void createBackground();

    //button event
    static void buttonPlayTouchEvent();


    //start create star
    void createStar(float);
    void fadeOutStar(cocos2d::Node * pSender);

    void clearEffact(const cocos2d::Point & point, const s8 cColor);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * pEvent);

    static void defeatEvent();
    static void replayEvent();
    static void helpEvent();
    static void closeHelpEvent();
    static void eventEsc();
    static void exitYes();
    static void exitNo();
    static void clearStar();
    static void soundSwitch();

    ~Smart09() {
        s_pSelf = NULL;
    }

private:
    static Smart09 * s_pSelf;

private:
    Panel * m_pPanelStart;
    Panel * m_pPanelDefeat;
    Panel * m_pPanelGame;
    Panel * m_pPanelSetting;
    Panel * m_pPanelHelp;
    Panel * m_pPanelShop;
    Panel * m_pPanelExit;

    static TCallBack<s32, event_fun> s_CallBackPool;
};

#endif // SMART09_H
