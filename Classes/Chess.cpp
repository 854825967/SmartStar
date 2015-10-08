#include "Chess.h"
USING_NS_CC;

Chess * Chess::create(const s8 nColor) {
    Chess * ret = NEW Chess(nColor);
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    } else {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

Chess::Chess(const s8 nColor) {
    ASSERT(nColor >= 0 && nColor < COLOR_COUNT);
    m_nColor = nColor;
}

bool Chess::init() {
    if (!Sprite::init()) {
        return false;
    }

    char szPath[64];
    memset(szPath, 0, sizeof(szPath));

    switch (m_nColor) {
    case COLOR_BLUE:
        initWithFile("tiny_star_blue.png");
        break;
    case COLOR_RED:
        initWithFile("tiny_star_red.png");
        break;
    case COLOR_YELLOW:
        initWithFile("tiny_star_yellow.png");
        break;
    }

    this->setAnchorPoint(Vec2(.5f, .5f));
    return true;
}
