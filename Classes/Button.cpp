#include "Button.h"
#include "Smart09.h"
USING_NS_CC;

Button * Button::create(const s32 nEventID) {
    Button * ret = NEW Button(nEventID);
    if (ret) {
        ret->autorelease();
    } else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool Button::init(const char * text, const s8 nColor, const char * pPic) {
    s8 cRandom = CCRANDOM_0_1() * 99;
    if (nColor != COLOR_COUNT) {
        cRandom = nColor;
    }
    if (pPic != NULL) {
        m_pSprite = Sprite::create(pPic);
    } else {
        switch (cRandom % COLOR_COUNT) {
        case COLOR_BLUE:
            m_pSprite = Sprite::create("small_star_blue.png");
            break;
        case COLOR_RED:
            m_pSprite = Sprite::create("small_star_red.png");
            break;
        case COLOR_YELLOW:
            m_pSprite = Sprite::create("small_star_yellow.png");
            break;
        default:
            ASSERT(false);
            break;
        }

        ActionInterval * rotateto180 = RotateTo::create(1, 180);
        ActionInterval * rotateto360 = RotateTo::create(1, 360);
        m_pSprite->runAction(RepeatForever::create(Sequence::create(rotateto180, rotateto360, NULL)));
    }

    m_pSprite->setAnchorPoint(Vec2(.5f, .5f));
    this->addChild(m_pSprite, 1);

    m_pLabel = Label::createWithTTF(text, "Abduction.ttf", 50);
    m_pLabel->setAnchorPoint(Vec2(.5f, .5f));
    this->addChild(m_pLabel, 2);

    return true;
}

void Button::changePic(const char * fileName) {
    m_pSprite->setTexture(fileName);
}

void Button::setScale(float scale) {
    Node::setScale(scale);
    m_fScale = scale;
}

void Button::setOpacity(GLubyte opacity) {
    Vector<Node *> children_list = getChildren();
    Vector<Node *>::iterator itor = children_list.begin();
    Vector<Node *>::iterator iend = children_list.end();

    while (itor != iend) {
        (*itor)->setOpacity(opacity);
        itor++;
    }
    Node::setOpacity(opacity);
}

s32 Button::GetTouchIndex() {
    return 0;
}

bool Button::IsTouch(const cocos2d::Point & point) {
    Size size = m_pSprite->getContentSize();
    if (fabs(point.x - getPositionX()) > size.width * m_fScale/2.0f || fabs(point.y - getPositionY()) > size.height * m_fScale/2.0f) {
        return false;
    }

    return true;
}

void Button::TouchEvent(const cocos2d::Point & point, const CTouchEventType nEventType) {
    if (TOUCH_EVENT_BEGAN == nEventType) {
        Smart09::CallEvent(m_nEventID);
    }
}
