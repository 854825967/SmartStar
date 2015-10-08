#include "Smart09.h"
#include "StartPanel.h"
#include "GamePanel.h"
#include "DefeatPanel.h"
#include "HelpPanel.h"
#include "ExitPanel.h"

USING_NS_CC;
using namespace CocosDenshion;

Smart09 * Smart09::s_pSelf = NULL;
TCallBack<s32, event_fun> Smart09::s_CallBackPool;

Scene* Smart09::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Smart09::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


bool Smart09::RgsEventCall(const s32 nEventID, const event_fun call, const char * debug) {
    return s_CallBackPool.RegisterCall(nEventID, call, debug);
}

bool Smart09::UnRgsEventCall(const s32 nEventID, const event_fun call) {
    return s_CallBackPool.UnRgsCall(nEventID, call);
}

void Smart09::CallEvent(const s32 nEventID) {
    s_CallBackPool.Call(nEventID);
}

Smart09 * Smart09::create() {
    if (NULL == s_pSelf) {
        s_pSelf = NEW Smart09;
        if (s_pSelf && s_pSelf->init()) {
            s_pSelf->autorelease();
        } else {
            delete s_pSelf;
            s_pSelf = NULL;
        }
    }

    return s_pSelf;
}

// on "init" you need to initialize your instance
bool Smart09::init() {
    // 1. super init first
    if ( !CTouchEngine::init() ) {
        return false;
    }

    Director::getInstance()->getTextureCache()->addImage("title.png");
    Director::getInstance()->getTextureCache()->addImage("tiny_star_yellow.png");
    Director::getInstance()->getTextureCache()->addImage("tiny_star_red.png");
    Director::getInstance()->getTextureCache()->addImage("tiny_star_blue.png");
    Director::getInstance()->getTextureCache()->addImage("tablecloth_yellow.png");
    Director::getInstance()->getTextureCache()->addImage("tablecloth_red.png");
    Director::getInstance()->getTextureCache()->addImage("tablecloth_blue.png");
    Director::getInstance()->getTextureCache()->addImage("small_star_yellow.png");
    Director::getInstance()->getTextureCache()->addImage("small_star_red.png");
    Director::getInstance()->getTextureCache()->addImage("small_star_blue.png");
    Director::getInstance()->getTextureCache()->addImage("big_star_yellow.png");
    Director::getInstance()->getTextureCache()->addImage("big_star_red.png");
    Director::getInstance()->getTextureCache()->addImage("big_star_blue.png");
    Director::getInstance()->getTextureCache()->addImage("background_yellow.png");
    Director::getInstance()->getTextureCache()->addImage("background_red.png");
    Director::getInstance()->getTextureCache()->addImage("background_blue.png");

    Director::getInstance()->getTextureCache()->addImage("pay.png");
    Director::getInstance()->getTextureCache()->addImage("pay1.png");
    Director::getInstance()->getTextureCache()->addImage("pay2.png");
    Director::getInstance()->getTextureCache()->addImage("pay3.png");
    Director::getInstance()->getTextureCache()->addImage("pay4.png");
    Director::getInstance()->getTextureCache()->addImage("pay5.png");
    Director::getInstance()->getTextureCache()->addImage("payclose.png");
    Director::getInstance()->getTextureCache()->addImage("paybutton.png");

    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("world.mp3");
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("game.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("Eliminate0.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("Eliminate1.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("Eliminate2.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("Eliminate3.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("Eliminate4.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("Eliminate5.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("Eliminate6.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("Eliminate7.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("move.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("bonus.mp3");

    createBackground();

    RGS_EVENT_CALL(EVENT_ID_PLAY, Smart09::buttonPlayTouchEvent);
    RGS_EVENT_CALL(EVENT_ID_DEFEAT, Smart09::defeatEvent);
    RGS_EVENT_CALL(EVENT_ID_REPLAY, Smart09::replayEvent);
    RGS_EVENT_CALL(EVENT_ID_HELP, Smart09::helpEvent);
    RGS_EVENT_CALL(EVENT_ID_CLOSE_HELP, Smart09::closeHelpEvent);
    RGS_EVENT_CALL(EVENT_ID_EXIT_YES, Smart09::exitYes);
    RGS_EVENT_CALL(EVENT_ID_EXIT_NO, Smart09::exitNo);
    RGS_EVENT_CALL(EVENT_ID_ESC, Smart09::eventEsc);
    RGS_EVENT_CALL(EVENT_ID_GIFT_PACKS, Smart09::clearStar);
    RGS_EVENT_CALL(EVENT_ID_SOUND_SWITCH, Smart09::soundSwitch);

    auto listener = EventListenerKeyboard::create(); 
    listener->onKeyReleased = CC_CALLBACK_2(Smart09::onKeyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    if (!UserDefault::getInstance()->getBoolForKey("inited")) {
        UserDefault::getInstance()->setBoolForKey("inited", true);
        UserDefault::getInstance()->setIntegerForKey("HighPoint", 0);
        UserDefault::getInstance()->setIntegerForKey("Cash", 10);
        UserDefault::getInstance()->flush();
    } else {
        CCLog("UserData is exist");
    }

    return true; 
}

void Smart09::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent) { 
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE:
        Smart09::create()->CallEvent(EVENT_ID_ESC);
        break;
    default:
        break;
    }
} 

void Smart09::createBackground() {
    const char * pPath = NULL;
    switch (g_config.m_nRandom) {
    case COLOR_BLUE:
        pPath = "background_blue.png";
        break;
    case COLOR_RED:
        pPath = "background_red.png";
        break;
    case COLOR_YELLOW:
        pPath = "background_yellow.png";
        break;
    }

    Sprite * pSprite = Sprite::create(pPath);
    pSprite->setAnchorPoint(Vec2(.5f, .5f));
    pSprite->setPosition(g_config.m_ScreenCenterPoint);
    pSprite->setScale(g_config.m_fScaling);
    this->addChild(pSprite, 0);
    ActionInterval * rotate180 = RotateTo::create(10, 180);
    ActionInterval * rotate360 = RotateTo::create(10, 360);
    pSprite->runAction(RepeatForever::create(Sequence::create(rotate180, rotate360, NULL)));
}

void Smart09::defeatEvent() {
    if (g_data.m_nPoint > UserDefault::getInstance()->getIntegerForKey("HighPoint")) {
        UserDefault::getInstance()->setIntegerForKey("HighPoint", g_data.m_nPoint);
        CCLog("Update highest point %d", g_data.m_nPoint);
    }

    s_pSelf->m_pPanelGame->hide();
    s_pSelf->m_pPanelDefeat->show();
}

void Smart09::replayEvent() {
    s_pSelf->m_pPanelDefeat->hide();
    s_pSelf->m_pPanelDefeat->reset();
    s_pSelf->m_pPanelGame->reset();
    s_pSelf->m_pPanelGame->show(true);
}

void Smart09::helpEvent() {
    s_pSelf->m_pPanelHelp->show();
    s_pSelf->m_pPanelStart->hide();
}

void Smart09::closeHelpEvent() {
    s_pSelf->m_pPanelStart->show();
    s_pSelf->m_pPanelHelp->hide();
}

void Smart09::eventEsc() {
    s_pSelf->m_pPanelExit->show();
}

void Smart09::exitYes() {
    Director::getInstance()->end();
}

void Smart09::exitNo() {
    s_pSelf->m_pPanelExit->hide();
}

void Smart09::clearStar() {
    s_pSelf->m_pPanelGame->show();
    s_pSelf->m_pPanelDefeat->hide();
    CallEvent(EVENT_ID_CLEAR);
}

void Smart09::soundSwitch() {
    g_soundSwitch = !g_soundSwitch;
    if (g_soundSwitch) {
        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
        SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
    } else {
        SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
    }
}

void Smart09::buttonPlayTouchEvent() {
    s_pSelf->m_pPanelStart->hide();
    s_pSelf->m_pPanelGame->show(true);

    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void Smart09::onEnter() {
    CTouchEngine::onEnter();
    schedule(schedule_selector(Smart09::createStar), .25f);

    m_pPanelStart = StartPanel::create();
    this->addChild(m_pPanelStart, 1);

    m_pPanelGame = GamePanel::create();
    this->addChild(m_pPanelGame, 2);

    m_pPanelDefeat = DefeatPanel::create();
    this->addChild(m_pPanelDefeat, 3);

    m_pPanelHelp = HelpPanel::create();
    this->addChild(m_pPanelHelp, 3);

    m_pPanelExit = ExitPanel::create();
    this->addChild(m_pPanelExit, 4);

	if (!isMusicEnabled()) {
		Smart09::create()->CallEvent(EVENT_ID_SOUND_SWITCH);
	} else {
	    SimpleAudioEngine::getInstance()->playBackgroundMusic("world.mp3", true);
	}
}

void Smart09::onExit() {
    Layer::onExit();
    unschedule(schedule_selector(Smart09::createStar));
}

void Smart09::createStar(float) {
    const char * pPath = NULL;
    s8 cRandom = ((s32) (CCRANDOM_0_1() * 1000)) % COLOR_COUNT;
    switch (cRandom) {
    case COLOR_BLUE:
        pPath = "small_star_blue.png";
        break;
    case COLOR_RED:
        pPath = "small_star_red.png";
        break;
    case COLOR_YELLOW:
        pPath = "small_star_yellow.png";
        break;
    }
    
    Sprite * pSprite = Sprite::create(pPath);
    pSprite->setAnchorPoint(Vec2(.5f, .5f));
    pSprite->setPosition(g_config.m_ScreenCenterPoint);
    pSprite->setOpacity(0);
    pSprite->setScale(.25f * g_config.m_fScaling);

    s32 nRadius = g_config.m_VirtualScrenSize.height;
    s32 nRotate = CCRANDOM_0_1() * 360;

    this->addChild(pSprite, 0);
    s32 targetX = nRadius * sin(nRotate);
    s32 targetY = nRadius * cos(nRotate);
    ActionInterval * moveto = MoveTo::create(5, Vec2(g_config.m_ScreenCenterPoint.x + targetX, g_config.m_ScreenCenterPoint.y + targetY));
    FiniteTimeAction* finite = Sequence::create(moveto, CallFuncN::create(this, callfuncN_selector(Smart09::fadeOutStar)), NULL);
    pSprite->runAction(finite);

    ActionInterval * rotateto180 = RotateTo::create(1, 180);
    ActionInterval * rotateto360 = RotateTo::create(1, 360);
    pSprite->runAction(RepeatForever::create(Sequence::create(rotateto180, rotateto360, NULL)));
    ActionInterval * scaleto = ScaleTo::create(5, 1);
    ActionInterval * fadein = FadeIn::create(.5);
    pSprite->runAction(fadein);
    pSprite->runAction(scaleto);
}

void Smart09::fadeOutStar(cocos2d::Node * pSender) {
    this->removeChild(pSender);
}
