#include "DefeatPanel.h"
#include "Smart09.h"
USING_NS_CC;
DefeatPanel * DefeatPanel::s_pSelf = NULL;

Panel * DefeatPanel::create() {
    if (NULL == s_pSelf) {
        s_pSelf = NEW DefeatPanel;
        if (s_pSelf && s_pSelf->init()) {
            s_pSelf->autorelease();
        } else {
            CC_SAFE_DELETE(s_pSelf);
        }
    }

    return s_pSelf;
}

bool DefeatPanel::init() {
    Sprite * pSprite = Sprite::create("defeat.png");
    pSprite->setAnchorPoint(Vec2(0, 0));
    this->addChild(pSprite, 1);
    pSprite->setScaleX(g_config.m_ScreenSize.width / pSprite->getContentSize().width);
    pSprite->setScaleY(g_config.m_ScreenSize.height / pSprite->getContentSize().height);

    Label * pDefeat = Label::createWithTTF("Defeat", "Abduction.ttf", 60);
    pDefeat->setAnchorPoint(Vec2(.5f, .5f));
    pDefeat->setPosition(Vec2(g_config.m_ScreenCenterPoint.x, g_config.m_ScreenCenterPoint.y + 350 * g_config.m_fScaling));
    pDefeat->setScale(g_config.m_fScaling);
    this->addChild(pDefeat,2 );

    Sprite * pBlueStar = Sprite::create("tiny_star_blue.png");
    pBlueStar->setPosition(Vec2(g_config.m_ScreenCenterPoint.x - 150 * g_config.m_fScaling, g_config.m_ScreenCenterPoint.y + 250 * g_config.m_fScaling));
    pBlueStar->setScale(g_config.m_fScaling);
    this->addChild(pBlueStar, 2);
    m_pBlueCountLabel = Label::createWithTTF("000000", "Abduction.ttf", 60);
    m_pBlueCountLabel->setPosition(Vec2(g_config.m_ScreenCenterPoint.x + 100 * g_config.m_fScaling, g_config.m_ScreenCenterPoint.y + 250 * g_config.m_fScaling));
    m_pBlueCountLabel->setScale(g_config.m_fScaling);
    this->addChild(m_pBlueCountLabel, 2);

    Sprite * pYellowStar = Sprite::create("tiny_star_yellow.png");
    pYellowStar->setPosition(Vec2(g_config.m_ScreenCenterPoint.x - 150 * g_config.m_fScaling, g_config.m_ScreenCenterPoint.y + 100 * g_config.m_fScaling));
    pYellowStar->setScale(g_config.m_fScaling);
    this->addChild(pYellowStar, 2);
    m_pYellowCountLabel = Label::createWithTTF("000000", "Abduction.ttf", 60);
    m_pYellowCountLabel->setPosition(Vec2(g_config.m_ScreenCenterPoint.x + 100 * g_config.m_fScaling, g_config.m_ScreenCenterPoint.y + 100 * g_config.m_fScaling));
    m_pYellowCountLabel->setScale(g_config.m_fScaling);
    this->addChild(m_pYellowCountLabel, 2);

    Sprite * pRedStar = Sprite::create("tiny_star_red.png");
    pRedStar->setPosition(Vec2(g_config.m_ScreenCenterPoint.x - 150 * g_config.m_fScaling, g_config.m_ScreenCenterPoint.y - 50 * g_config.m_fScaling));
    pRedStar->setScale(g_config.m_fScaling);
    this->addChild(pRedStar, 2);
    m_pRedCountLabel = Label::createWithTTF("000000", "Abduction.ttf", 60);
    m_pRedCountLabel->setPosition(Vec2(g_config.m_ScreenCenterPoint.x + 100 * g_config.m_fScaling, g_config.m_ScreenCenterPoint.y - 50 * g_config.m_fScaling));
    m_pRedCountLabel->setScale(g_config.m_fScaling);
    this->addChild(m_pRedCountLabel, 2);

    m_pPointLabel = Label::createWithTTF("Point:000000", "Abduction.ttf", 60);
    m_pPointLabel->setPosition(Vec2(g_config.m_ScreenCenterPoint.x, g_config.m_ScreenCenterPoint.y - 200 * g_config.m_fScaling));
    m_pPointLabel->setScale(g_config.m_fScaling);
    this->addChild(m_pPointLabel, 2);

    m_pButtonReplay = Button::create(EVENT_ID_REPLAY);
    m_pButtonReplay->setScale(g_config.m_fScaling);
    m_pButtonReplay->init("Replay", 0, "small_star_blue.png");
    m_pButtonReplay->setPosition(Vec2(g_config.m_ScreenCenterPoint.x, g_config.m_ScreenCenterPoint.y - 350 * g_config.m_fScaling));
    this->addChild(m_pButtonReplay, 2);

    this->setPosition(Vec2(- g_config.m_ScreenSize.width, 0));
    return true;
}

void DefeatPanel::show(const bool start) {
    ActionInterval * moveto = MoveTo::create(1, Vec2(0, 0));
    FiniteTimeAction * finite = Sequence::create(moveto, CallFuncN::create(this, callfuncN_selector(DefeatPanel::showOver)), NULL);
    this->runAction(finite);
}

void DefeatPanel::showOver(cocos2d::Node * pSender) {
    schedule(schedule_selector(DefeatPanel::clearStarCount));
    Smart09::create()->AddTouchHandle(TOUCH_GRADE_UI, m_pButtonReplay);
}

void DefeatPanel::clearStarCount(float) {
    char szBuff[64] = {0};
    if (m_nBlueCount < g_data.m_nBlueStar) {
        SafeSprintf(szBuff, sizeof(szBuff), "%06d", m_nBlueCount);
        m_pBlueCountLabel->setString(szBuff);
        s32 nSetup = g_data.m_nBlueStar/18;
        (nSetup == 0)?(nSetup=1):NULL;
        m_nBlueCount+=nSetup;
        return;
    }
    SafeSprintf(szBuff, sizeof(szBuff), "%06d", g_data.m_nBlueStar);
    m_pBlueCountLabel->setString(szBuff);

    if (m_nYellowCount < g_data.m_nYellowStar) {
        SafeSprintf(szBuff, sizeof(szBuff), "%06d", m_nYellowCount);
        m_pYellowCountLabel->setString(szBuff);
        s32 nSetup = g_data.m_nYellowStar/18;
        (nSetup == 0)?(nSetup=1):NULL;
        m_nYellowCount+=nSetup;
        return;
    }
    SafeSprintf(szBuff, sizeof(szBuff), "%06d", g_data.m_nYellowStar);
    m_pYellowCountLabel->setString(szBuff);

    if (m_nRedCount < g_data.m_nRedStar) {
        SafeSprintf(szBuff, sizeof(szBuff), "%06d", m_nRedCount);
        m_pRedCountLabel->setString(szBuff);
        s32 nSetup = g_data.m_nRedStar/18;
        (nSetup == 0)?(nSetup=1):NULL;
        m_nRedCount+=nSetup;
        return;
    }
    SafeSprintf(szBuff, sizeof(szBuff), "%06d", g_data.m_nRedStar);
    m_pRedCountLabel->setString(szBuff);

    unschedule(schedule_selector(DefeatPanel::clearStarCount));    
    schedule(schedule_selector(DefeatPanel::clearPoint));
}

void DefeatPanel::clearPoint(float) {
    char szBuff[64] = {0};
    if (m_nPoint < g_data.m_nPoint) {
        SafeSprintf(szBuff, sizeof(szBuff), "Point:%06d", m_nPoint);
        m_nPoint += g_data.m_nPoint/60;
        m_pPointLabel->setString(szBuff);
        return;
    }
    SafeSprintf(szBuff, sizeof(szBuff), "Point:%06d", g_data.m_nPoint);
    m_pPointLabel->setString(szBuff);

    unschedule(schedule_selector(DefeatPanel::clearPoint));
}

void DefeatPanel::hide() {
    ActionInterval * moveto = MoveTo::create(1, Vec2(- g_config.m_ScreenSize.width, 0));
    this->runAction(moveto);
    Smart09::create()->RemoveTouchHandle(m_pButtonReplay);
}

void DefeatPanel::reset() {
    m_nBlueCount = 0;
    m_nYellowCount = 0;
    m_nRedCount = 0;
    m_nPoint = 0; 

    m_pBlueCountLabel->setString("000000");
    m_pRedCountLabel->setString("000000");
    m_pYellowCountLabel->setString("000000");
    m_pPointLabel->setString("Point:000000");
}
