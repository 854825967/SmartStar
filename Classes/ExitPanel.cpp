#include "ExitPanel.h"
#include "Smart09.h"
USING_NS_CC;
ExitPanel * ExitPanel::s_pSelf = NULL;

Panel * ExitPanel::create() {
    if (NULL == s_pSelf) {
        s_pSelf = NEW ExitPanel;
        if (s_pSelf && s_pSelf->init()) {
            s_pSelf->autorelease();
        } else {
            CC_SAFE_DELETE(s_pSelf);
        }
    }

    return s_pSelf;
}

bool ExitPanel::init() {
    if (!Node::init()) {
        return false;
    }

    Sprite * pSprite = Sprite::create("defeat.png");
    pSprite->setAnchorPoint(Vec2(0, 0));
    pSprite->setOpacity(0);
    this->addChild(pSprite, 1);
    pSprite->setScaleX(g_config.m_ScreenSize.width / pSprite->getContentSize().width);
    pSprite->setScaleY(g_config.m_ScreenSize.height / pSprite->getContentSize().height);

    Label * pDefeat = Label::createWithTTF("Exit", "Abduction.ttf", 60);
    pDefeat->setAnchorPoint(Vec2(.5f, .5f));
    pDefeat->setPosition(Vec2(g_config.m_ScreenCenterPoint.x, g_config.m_ScreenCenterPoint.y + 100 * g_config.m_fScaling));
    pDefeat->setScale(g_config.m_fScaling);
    pDefeat->setOpacity(0);
    this->addChild(pDefeat,2 );

    m_pButtonYes = Button::create(EVENT_ID_EXIT_YES);
    m_pButtonYes->setScale(g_config.m_fScaling);
    m_pButtonYes->init("Yes", 0, "small_star_blue.png");
    m_pButtonYes->setPosition(Vec2(g_config.m_ScreenCenterPoint.x - 150 * g_config.m_fScaling, g_config.m_ScreenCenterPoint.y - 100 * g_config.m_fScaling));
    m_pButtonYes->setOpacity(0);
    this->addChild(m_pButtonYes, 2);

    m_pButtonNo = Button::create(EVENT_ID_EXIT_NO);
    m_pButtonNo->setScale(g_config.m_fScaling);
    m_pButtonNo->init("No", 0, "small_star_blue.png");
    m_pButtonNo->setPosition(Vec2(g_config.m_ScreenCenterPoint.x + 150 * g_config.m_fScaling, g_config.m_ScreenCenterPoint.y - 100 * g_config.m_fScaling));
    m_pButtonNo->setOpacity(0);
    this->addChild(m_pButtonNo, 2);

    return true;
}

void ExitPanel::show(const bool start) {
    ActionInterval * fadein = FadeIn::create(1);
    Vector<Node *> children_list = this->getChildren();
    Vector<Node *>::iterator itor = children_list.begin();
    Vector<Node *>::iterator iend = children_list.end();
    while (itor != iend) {
        ActionInterval * pAction = fadein->clone();
        (*itor)->runAction(pAction);

        itor++;
    }

    Smart09::create()->AddTouchHandle(TOUCH_GRADE_ALERT, m_pButtonYes);
    Smart09::create()->AddTouchHandle(TOUCH_GRADE_ALERT, m_pButtonNo);
    Smart09::create()->AddTouchHandle(TOUCH_GRADE_ALERT, this);
}

void ExitPanel::hide() {
    ActionInterval * fadeout = FadeOut::create(1);
    Vector<Node *> children_list = this->getChildren();
    Vector<Node *>::iterator itor = children_list.begin();
    Vector<Node *>::iterator iend = children_list.end();
    while (itor != iend) {
        ActionInterval * pAction = fadeout->clone();
        (*itor)->runAction(pAction);

        itor++;
    }

    Smart09::create()->RemoveTouchHandle(m_pButtonYes);
    Smart09::create()->RemoveTouchHandle(m_pButtonNo);
    Smart09::create()->RemoveTouchHandle(this);
}

void ExitPanel::reset() {

}
