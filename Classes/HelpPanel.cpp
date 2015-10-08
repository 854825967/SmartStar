#include "HelpPanel.h"
#include "Smart09.h"
USING_NS_CC;
HelpPanel * HelpPanel::s_pSelf = NULL;

Panel * HelpPanel::create() {
    if (NULL == s_pSelf) {
        s_pSelf = NEW HelpPanel;
        if (s_pSelf && s_pSelf->init()) {
            s_pSelf->autorelease();
        } else {
            CC_SAFE_DELETE(s_pSelf);
        }
    }

    return s_pSelf;
}

HelpPanel::HelpPanel() {

}

HelpPanel::~HelpPanel() {
    s_pSelf = NULL;
}

bool HelpPanel::init() {
    Sprite * pSprite = Sprite::create("defeat.png");
    pSprite->setAnchorPoint(Vec2(0, 0));
    pSprite->setOpacity(0);
    this->addChild(pSprite, 1);
    pSprite->setScaleX(g_config.m_ScreenSize.width / pSprite->getContentSize().width);
    pSprite->setScaleY(g_config.m_ScreenSize.height / pSprite->getContentSize().height);

    Sprite * pSpriteHelp = Sprite::create("help.png");
    pSpriteHelp->setAnchorPoint(Vec2(.5f, .5f));
    pSpriteHelp->setOpacity(0);
    pSpriteHelp->setPosition(g_config.m_ScreenCenterPoint);
    this->addChild(pSpriteHelp, 2);
    pSpriteHelp->setScale(g_config.m_fScaling);

    m_pButton = Button::create(EVENT_ID_CLOSE_HELP);
    m_pButton->init("Close");
    m_pButton->setScale(g_config.m_fScaling);
    m_pButton->setPosition(Vec2(
        g_config.m_ScreenCenterPoint.x,
        g_config.m_ScreenCenterPoint.y - pSpriteHelp->getContentSize().height * g_config.m_fScaling /2.0f - 100 * g_config.m_fScaling
        ));
    m_pButton->setOpacity(0);
    this->addChild(m_pButton, 2);

    return true;
}

void HelpPanel::show(const bool start) {
    ActionInterval * fadein = FadeIn::create(2);
    Vector<Node *> children_list = this->getChildren();
    Vector<Node *>::iterator itor = children_list.begin();
    Vector<Node *>::iterator iend = children_list.end();
    while (itor != iend) {
        ActionInterval * pAction = fadein->clone();
        (*itor)->runAction(pAction);

        itor++;
    }

    Smart09::create()->AddTouchHandle(TOUCH_GRADE_UI, m_pButton);
}

void HelpPanel::hide() {
    ActionInterval * fadeout = FadeOut::create(2);
    Vector<Node *> children_list = this->getChildren();
    Vector<Node *>::iterator itor = children_list.begin();
    Vector<Node *>::iterator iend = children_list.end();
    while (itor != iend) {
        ActionInterval * pAction = fadeout->clone();
        (*itor)->runAction(pAction);

        itor++;
    }

    Smart09::create()->RemoveTouchHandle(m_pButton);
}

void HelpPanel::reset() {

}
