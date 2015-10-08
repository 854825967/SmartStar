#include "StartPanel.h"
#include "Smart09.h"
USING_NS_CC;
using namespace CocosDenshion;
StartPanel * StartPanel::s_pSelf = NULL;

StartPanel::StartPanel() {

}

Panel * StartPanel::create() {
    if (NULL == s_pSelf) {
        s_pSelf = NEW StartPanel;
        if (s_pSelf && s_pSelf->init()) {
            s_pSelf->autorelease();
        } else {
            CC_SAFE_DELETE(s_pSelf);
        }
    }

    return s_pSelf;
}

void StartPanel::reset() {

}

void StartPanel::soundSwitch() {
    if (g_soundSwitch) {
        s_pSelf->m_pButtonSound->changePic("sound_on.png");
    } else {
        s_pSelf->m_pButtonSound->changePic("sound_off.png");
    }
}

bool StartPanel::init() {
    if (!Node::init()) {
        return false;
    }

    const char * pPath = NULL;
    switch (g_config.m_nRandom) {
    case COLOR_BLUE:
        pPath = "big_star_blue.png";
        break;
    case COLOR_RED:
        pPath = "big_star_red.png";
        break;
    case COLOR_YELLOW:
        pPath = "big_star_yellow.png";
        break;
    default:
        ASSERT(false);
        break;
    }

    m_pBigStar = Sprite::create(pPath);
    this->addChild(m_pBigStar, 3);
    m_pTitle = Sprite::create("title.png");
    this->addChild(m_pTitle, 4);

    m_pBigStar->setAnchorPoint(Vec2(.5f, .5f));
    m_pBigStar->setPosition(g_config.m_ScreenCenterPoint);
    m_pBigStar->setOpacity(0);
    m_pBigStar->setScale(0);

    ActionInterval * scale1 = ScaleTo::create(.1, 1.5 * g_config.m_fScaling);
    ActionInterval * scale2 = ScaleTo::create(.1, .6 * g_config.m_fScaling);
    ActionInterval * scale3 = ScaleTo::create(.1, 1.3 * g_config.m_fScaling);
    ActionInterval * scale4 = ScaleTo::create(.1, .9 * g_config.m_fScaling);
    ActionInterval * scale5 = ScaleTo::create(.1, 1.1 * g_config.m_fScaling);

    ActionInterval * scale = Sequence::create(
        scale1, scale2, scale3, scale4, scale5, NULL);
    FiniteTimeAction* finite = Sequence::create(scale, CallFuncN::create(this, callfuncN_selector(StartPanel::showTitle)), NULL);

    ActionInterval * fadein = FadeIn::create(.5);
    m_pBigStar->runAction(finite);
    m_pBigStar->runAction(fadein);

    return true;
}

void StartPanel::showTitle(cocos2d::Node * pSender) {
    ActionInterval * scale1 = ScaleTo::create(.1, .99 * g_config.m_fScaling);
    ActionInterval * scale2 = ScaleTo::create(.1, 1.01 * g_config.m_fScaling);
    pSender->runAction(RepeatForever::create(Sequence::create(scale1, scale2, NULL)));

    m_pTitle->setAnchorPoint(Vec2(.5f, .6f));
    m_pTitle->setPosition(g_config.m_ScreenCenterPoint);
    m_pTitle->setOpacity(0);
    m_pTitle->setScale(4 * g_config.m_fScaling);
    ActionInterval * scaleto = ScaleTo::create(0.3, 1 * g_config.m_fScaling);
    ActionInterval * fadein = FadeIn::create(.3);
    m_pTitle->runAction(scaleto);
    m_pTitle->runAction(fadein);

    m_pButtons[STARTUI_MENU_PLAY] = Button::create(EVENT_ID_PLAY);
    m_pButtons[STARTUI_MENU_PLAY]->init("Play");
    m_pButtons[STARTUI_MENU_PLAY]->setScale(g_config.m_fScaling);
    m_pButtons[STARTUI_MENU_PLAY]->setPosition(g_config.m_ScreenCenterPoint);
    m_pButtons[STARTUI_MENU_PLAY]->setOpacity(0);
    this->addChild(m_pButtons[STARTUI_MENU_PLAY]);
    Smart09::create()->AddTouchHandle(TOUCH_GRADE_UI, m_pButtons[STARTUI_MENU_PLAY]);

    m_pButtons[STARTUI_MENU_HELP] = Button::create(EVENT_ID_HELP);
    m_pButtons[STARTUI_MENU_HELP]->init("Help");
    m_pButtons[STARTUI_MENU_HELP]->setScale(g_config.m_fScaling);
    m_pButtons[STARTUI_MENU_HELP]->setPosition(g_config.m_ScreenCenterPoint);
    m_pButtons[STARTUI_MENU_HELP]->setOpacity(0);
    this->addChild(m_pButtons[STARTUI_MENU_HELP]);
    Smart09::create()->AddTouchHandle(TOUCH_GRADE_UI, m_pButtons[STARTUI_MENU_HELP]);

    ActionInterval * moveto1 = MoveTo::create(2, Vec2(g_config.m_ScreenCenterPoint.x - g_config.m_VirtualScrenSize.width/4.0f, g_config.m_ScreenCenterPoint.y - .5f * g_config.m_VirtualScrenSize.height/ 2.0f));
    ActionInterval * fadein1 = FadeIn::create(3);
    m_pButtons[STARTUI_MENU_PLAY]->runAction(moveto1);
    m_pButtons[STARTUI_MENU_PLAY]->runAction(fadein1);

    ActionInterval * moveto2 = MoveTo::create(2, Vec2(g_config.m_ScreenCenterPoint.x + g_config.m_VirtualScrenSize.width/4.0f, g_config.m_ScreenCenterPoint.y - .5f * g_config.m_VirtualScrenSize.height/ 2.0f));
    ActionInterval * fadein2 = FadeIn::create(3);
    m_pButtons[STARTUI_MENU_HELP]->runAction(moveto2);
    m_pButtons[STARTUI_MENU_HELP]->runAction(fadein2);

    m_pButtonSound = Button::create(EVENT_ID_SOUND_SWITCH);
    if (g_soundSwitch) {
        m_pButtonSound->init("", 0, "sound_on.png");
    } else {
        m_pButtonSound->init("", 0, "sound_off.png");
    }
    m_pButtonSound->setScale(g_config.m_fScaling);
    m_pButtonSound->setPosition(Vec2(
        g_config.m_VirtualScrenSize.width - 150 * g_config.m_fScaling, 
        g_config.m_VirtualScrenSize.height - 50 * g_config.m_fScaling));
    this->addChild(m_pButtonSound);
    Smart09::create()->AddTouchHandle(TOUCH_GRADE_UI, m_pButtonSound);

    RGS_EVENT_CALL(EVENT_ID_SOUND_SWITCH, StartPanel::soundSwitch);
}

void StartPanel::show(const bool start) {
    ActionInterval * fadein = FadeIn::create(1);
    Vector<Node *> children_list = this->getChildren();
    Vector<Node *>::iterator itor = children_list.begin();
    Vector<Node *>::iterator iend = children_list.end();
    while (itor != iend) {
        ActionInterval * pAction = fadein->clone();
        (*itor)->runAction(pAction);

        itor++;
    }

    Smart09::create()->AddTouchHandle(TOUCH_GRADE_UI, m_pButtons[STARTUI_MENU_PLAY]);
    Smart09::create()->AddTouchHandle(TOUCH_GRADE_UI, m_pButtons[STARTUI_MENU_HELP]);
    Smart09::create()->AddTouchHandle(TOUCH_GRADE_UI, m_pButtonSound);
}

void StartPanel::hide() {
    ActionInterval * fadeout = FadeOut::create(1);
    Vector<Node *> children_list = this->getChildren();
    Vector<Node *>::iterator itor = children_list.begin();
    Vector<Node *>::iterator iend = children_list.end();
    while (itor != iend) {
        ActionInterval * pAction = fadeout->clone();
        (*itor)->runAction(pAction);

        itor++;
    }
    Smart09::create()->RemoveTouchHandle(m_pButtons[STARTUI_MENU_PLAY]);
    Smart09::create()->RemoveTouchHandle(m_pButtons[STARTUI_MENU_HELP]);
    Smart09::create()->RemoveTouchHandle(m_pButtonSound);
}
