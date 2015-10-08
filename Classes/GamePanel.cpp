#include "GamePanel.h"
#include "Smart09.h"
#include "Button.h"
USING_NS_CC;
using namespace CocosDenshion;
GamePanel * GamePanel::s_pSelf = NULL;

GamePanel::GamePanel() {
    memset(&m_Checkers, 0, sizeof(m_Checkers));
    m_nCurrentSetupCount = 0;
    m_nPoint = 0;
}

Panel * GamePanel::create() {
    if (NULL == s_pSelf) {
        s_pSelf = NEW GamePanel;
        if (s_pSelf && s_pSelf->init()) {
            s_pSelf->autorelease();
        } else {
            CC_SAFE_DELETE(s_pSelf);
        }
    }

    return s_pSelf;
}

bool GamePanel::init() {
    if (!Node::init()) {
        return false;
    }

    m_pChessboard = Chessboard::create(g_config.m_nRandom);
    m_pChessboard->setAnchorPoint(Vec2(.5f, .5f));
    m_pChessboard->setPosition(g_config.m_ScreenCenterPoint);
    m_pChessboard->setOpacity(0);
    m_pChessboard->setScale(g_config.m_fScaling);
    this->addChild(m_pChessboard);

    m_pButtonSound = Button::create(EVENT_ID_SOUND_SWITCH);
    m_pButtonSound->init("", 0, "sound_on.png");
    m_pButtonSound->setScale(g_config.m_fScaling);
    m_pButtonSound->setPosition(Vec2(
        g_config.m_VirtualScrenSize.width - 150 * g_config.m_fScaling, 
        g_config.m_ScreenCenterPoint.y + (m_pChessboard->getContentSize().height/2.0f + 75) * g_config.m_fScaling));
    m_pButtonSound->setOpacity(0);
    this->addChild(m_pButtonSound);

    m_pPointLabel = Label::createWithTTF("Point:000000", "Abduction.ttf", 45);
    m_pPointLabel->setAnchorPoint(Vec2(.0f, .5f));
    m_pPointLabel->setPosition(Vec2(
        g_config.m_ScreenCenterPoint.x - (m_pChessboard->getContentSize().width/2.0f) * g_config.m_fScaling, 
        g_config.m_ScreenCenterPoint.y + (m_pChessboard->getContentSize().height/2.0f + 75) * g_config.m_fScaling));
    m_pPointLabel->setOpacity(0);
    m_pPointLabel->setScale(g_config.m_fScaling);
    this->addChild(m_pPointLabel);

    char szBuff[64] = {0};
    SafeSprintf(szBuff, sizeof(szBuff), "Cash:%d", UserDefault::getInstance()->getIntegerForKey("Cash"));

    m_pCashLabel = Label::createWithTTF(szBuff, "Abduction.ttf", 30);
    m_pCashLabel->setColor(Color3B(218, 178, 115));
    m_pCashLabel->setAnchorPoint(Vec2(.0f, .5f));
    m_pCashLabel->setPosition(Vec2(
        g_config.m_ScreenCenterPoint.x - (m_pChessboard->getContentSize().width/2.0f - 300) * g_config.m_fScaling,
        g_config.m_ScreenCenterPoint.y + (m_pChessboard->getContentSize().height/2.0f + 150) * g_config.m_fScaling));
    m_pCashLabel->setOpacity(0);
    m_pCashLabel->setScale(g_config.m_fScaling);
    this->addChild(m_pCashLabel);

    memset(szBuff, 0, sizeof(szBuff));
    SafeSprintf(szBuff, sizeof(szBuff), "Highest:%d", UserDefault::getInstance()->getIntegerForKey("HighPoint"));
    m_pHighestLabel = Label::createWithTTF(szBuff, "Abduction.ttf", 30);
    m_pHighestLabel->setColor(Color3B(218, 178, 115));
    m_pHighestLabel->setAnchorPoint(Vec2(.0f, .5f));
    m_pHighestLabel->setPosition(Vec2(
        g_config.m_ScreenCenterPoint.x - (m_pChessboard->getContentSize().width/2.0f) * g_config.m_fScaling, 
        g_config.m_ScreenCenterPoint.y + (m_pChessboard->getContentSize().height/2.0f + 150) * g_config.m_fScaling));
    m_pHighestLabel->setOpacity(0);
    m_pHighestLabel->setScale(g_config.m_fScaling);
    this->addChild(m_pHighestLabel);

    m_pHitLabel = Label::createWithTTF("", "Abduction.ttf", 60 * g_config.m_fScaling);
    m_pHitLabel->setAnchorPoint(Vec2(.5f, .5f));
    m_pHitLabel->setPosition(g_config.m_ScreenCenterPoint);
    m_pHitLabel->setOpacity(0);
    m_pHitLabel->setScale(g_config.m_fScaling);
    this->addChild(m_pHitLabel, 5);
    
    for (s32 x=0; x<TABLECLOTH_WIDTH; x++) {
        for (s32 y=0; y<TABLECLOTH_HEIGHT; y++) {
            m_Checkers[x][y].pos = Vec2(
                g_config.m_ScreenCenterPoint.x + (x * 100 + 50 - m_pChessboard->getContentSize().width/2) * g_config.m_fScaling, 
                g_config.m_ScreenCenterPoint.y + (y * 100 + 50 - m_pChessboard->getContentSize().height/2) * g_config.m_fScaling);
            if (x - 1 >= 0) {
                m_Checkers[x][y].pLeft = &(m_Checkers[x-1][y]);
            }

            if (x + 1 < TABLECLOTH_WIDTH) {
                m_Checkers[x][y].pRight = &(m_Checkers[x+1][y]);
            }

            if (y - 1 >= 0) {
                m_Checkers[x][y].pDown = &(m_Checkers[x][y-1]);
            }

            if (y + 1 < TABLECLOTH_HEIGHT) {
                m_Checkers[x][y].pUP = &(m_Checkers[x][y+1]);
            }
            m_Checkers[x][y].bSigned = false;
            m_EmptyCheckers.push_back(&(m_Checkers[x][y]));
        }
    }

    RGS_EVENT_CALL(EVENT_ID_SOUND_SWITCH, GamePanel::soundSwitch);
    return true;
}

void GamePanel::startGame(cocos2d::Node * pSender) {
    generateStar(6);
}

void GamePanel::updatePoint(float) {
    if (m_nPoint < g_data.m_nPoint) {
        m_nPoint++;

        char szPoint[32] = {0};
        memset(szPoint, 0, sizeof(szPoint));
        SafeSprintf(szPoint, sizeof(szPoint), "Point:%06d", m_nPoint);
        m_pPointLabel->setString(szPoint);
    }
}

void GamePanel::reset() {
    m_nPoint = 0;
    g_data.m_nPoint = 0;
    g_data.m_nRedStar = 0;
    g_data.m_nBlueStar = 0;
    g_data.m_nYellowStar = 0;

    m_EmptyCheckers.clear();
    for (s32 x=0; x<TABLECLOTH_WIDTH; x++) {
        for (s32 y=0; y<TABLECLOTH_HEIGHT; y++) {
            if (m_Checkers[x][y].pChess != NULL) {
                removeChild(m_Checkers[x][y].pChess);
                m_Checkers[x][y].pChess = NULL;
            }
            m_Checkers[x][y].bSigned = false;
            m_EmptyCheckers.push_back(&(m_Checkers[x][y]));
        }
    }
    m_pPointLabel->setString("Point:000000");
    m_pHitLabel->setString("");

    char szBuff[64] = {0};
    memset(szBuff, 0, sizeof(szBuff));
    SafeSprintf(szBuff, sizeof(szBuff), "Highest:%d", UserDefault::getInstance()->getIntegerForKey("HighPoint"));
    m_pHighestLabel->setString(szBuff);
}

void GamePanel::show(const bool start) {
    ActionInterval * fadein = FadeIn::create(1);
    Vector<Node *> children_list = this->getChildren();
    Vector<Node *>::iterator itor = children_list.begin();
    Vector<Node *>::iterator iend = children_list.end();
    while (itor != iend) {
        ActionInterval * pAction = fadein->clone();
        if (start && itor == children_list.begin()) {
            SimpleAudioEngine::getInstance()->playBackgroundMusic("game.mp3", true);
            SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(.75f);
            FiniteTimeAction* finite = Sequence::create(pAction, CallFuncN::create(this, callfuncN_selector(GamePanel::startGame)), NULL);
            (*itor)->runAction(finite);
        } else {
            (*itor)->runAction(pAction);
        }

        itor++;
    }

    char szBuff[64] = {0};
    SafeSprintf(szBuff, sizeof(szBuff), "Cash:%d", UserDefault::getInstance()->getIntegerForKey("Cash"));
    m_pCashLabel->setString(szBuff);

    Smart09::create()->AddTouchHandle(TOUCH_GRADE_GAME, m_pChessboard);
    Smart09::create()->AddTouchHandle(TOUCH_GRADE_UI, m_pButtonSound);
    schedule(schedule_selector(GamePanel::updatePoint), 1/4);



    RGS_EVENT_CALL(EVENT_ID_CHESSBORD_SLIDE_UP, GamePanel::slideUpEvent);
    RGS_EVENT_CALL(EVENT_ID_CHESSBORD_SLIDE_DOWN, GamePanel::slideDownEvent);
    RGS_EVENT_CALL(EVENT_ID_CHESSBORD_SLIDE_RIGHT, GamePanel::slideRightEvent);
    RGS_EVENT_CALL(EVENT_ID_CHESSBORD_SLIDE_LEFT, GamePanel::slideLeftEvent);
    RGS_EVENT_CALL(EVENT_ID_CLEAR, GamePanel::clearAllStar);
}

void GamePanel::hide() {
    ActionInterval * fadeout = FadeOut::create(1);
    Vector<Node *> children_list = this->getChildren();
    Vector<Node *>::iterator itor = children_list.begin();
    Vector<Node *>::iterator iend = children_list.end();
    while (itor != iend) {
        ActionInterval * pAction = fadeout->clone();
        (*itor)->runAction(pAction);

        itor++;
    }

    Smart09::create()->RemoveTouchHandle(m_pChessboard);
    Smart09::create()->RemoveTouchHandle(m_pButtonSound);
    unschedule(schedule_selector(GamePanel::updatePoint));


    UNRGS_EVENT_CALL(EVENT_ID_CHESSBORD_SLIDE_UP, GamePanel::slideUpEvent);
    UNRGS_EVENT_CALL(EVENT_ID_CHESSBORD_SLIDE_DOWN, GamePanel::slideDownEvent);
    UNRGS_EVENT_CALL(EVENT_ID_CHESSBORD_SLIDE_RIGHT, GamePanel::slideRightEvent);
    UNRGS_EVENT_CALL(EVENT_ID_CHESSBORD_SLIDE_LEFT, GamePanel::slideLeftEvent);
    UNRGS_EVENT_CALL(EVENT_ID_CLEAR, GamePanel::clearAllStar);
}

void GamePanel::slideUpEvent() {
    g_data.m_nEliminate = 0;
    s_pSelf->m_nCurrentSetupCount++;
    s_pSelf->m_pChessboard->slideSwitch(false);
    g_data.m_nGravity = DIRECTION_UP;
    if (!s_pSelf->gravityTendency(DIRECTION_UP)) {
        if (TABLECLOTH_WIDTH * TABLECLOTH_HEIGHT == s_pSelf->m_EmptyCheckers.size()) {
            s_pSelf->generateStar();
        } else {
            s_pSelf->m_pChessboard->slideSwitch(true);
        }
    }
}

void GamePanel::slideDownEvent() {
    g_data.m_nEliminate = 0;
    s_pSelf->m_nCurrentSetupCount++;
    s_pSelf->m_pChessboard->slideSwitch(false);
    g_data.m_nGravity = DIRECTION_DOWN;
    if (!s_pSelf->gravityTendency(DIRECTION_DOWN)) {
        if (TABLECLOTH_WIDTH * TABLECLOTH_HEIGHT == s_pSelf->m_EmptyCheckers.size()) {
            s_pSelf->generateStar();
        } else {
            s_pSelf->m_pChessboard->slideSwitch(true);
        }
    }
}

void GamePanel::paySuccess() {
    s32 nCash = UserDefault::getInstance()->getIntegerForKey("Cash");
    char szBuf[64] = {0};
    SafeSprintf(szBuf, sizeof(szBuf), "Cash:%d", nCash);
    s_pSelf->m_pCashLabel->setString(szBuf);
}

void GamePanel::soundSwitch() {
    if (g_soundSwitch) {
        s_pSelf->m_pButtonSound->changePic("sound_on.png");
    } else {
        s_pSelf->m_pButtonSound->changePic("sound_off.png");
    }
}

void GamePanel::slideRightEvent() {
    g_data.m_nEliminate = 0;
    s_pSelf->m_nCurrentSetupCount++;
    s_pSelf->m_pChessboard->slideSwitch(false);
    g_data.m_nGravity = DIRECTION_RIGHT;
    if (!s_pSelf->gravityTendency(DIRECTION_RIGHT)) {
        if (TABLECLOTH_WIDTH * TABLECLOTH_HEIGHT == s_pSelf->m_EmptyCheckers.size()) {
            s_pSelf->generateStar();
        } else {
            s_pSelf->m_pChessboard->slideSwitch(true);
        }
    }
}

void GamePanel::slideLeftEvent() {
    g_data.m_nEliminate = 0;
    s_pSelf->m_nCurrentSetupCount++;
    s_pSelf->m_pChessboard->slideSwitch(false);
    g_data.m_nGravity = DIRECTION_LEFT;
    if (!s_pSelf->gravityTendency(DIRECTION_LEFT)) {
        if (TABLECLOTH_WIDTH * TABLECLOTH_HEIGHT == s_pSelf->m_EmptyCheckers.size()) {
            s_pSelf->generateStar();
        } else {
            s_pSelf->m_pChessboard->slideSwitch(true);
        }
    }
}

void GamePanel::generateStarOver(cocos2d::Node * pSender) {
    ECHO("generateStarOver");
    if (!scanTable() && m_EmptyCheckers.empty()) {
        Smart09::create()->CallEvent(EVENT_ID_DEFEAT);
    }
    m_pChessboard->slideSwitch(true);
}

void GamePanel::hit(const s32 nHit) {
    char szBuff[8] = {0};
    SafeSprintf(szBuff, sizeof(szBuff), "+%dx%d", nHit, COMBO_POINT);
    m_pHitLabel->setString(szBuff);
    m_pHitLabel->stopAllActions();
    m_pHitLabel->setOpacity(0);
    m_pHitLabel->setScale(2.0f);

    ActionInterval * scaleto = ScaleTo::create(.3f, 1);
    ActionInterval * fadein = FadeIn::create(.3f);
    ActionInterval * fadeout = FadeOut::create(1);
    m_pHitLabel->runAction(scaleto);
    m_pHitLabel->runAction(Sequence::create(fadein, fadeout, NULL));
}

bool GamePanel::isSame(const Checker * pChecker1, const Checker * pChecker2) {
    if (NULL == pChecker1 || NULL == pChecker2) {
        return false;
    }

    if (NULL == pChecker1->pChess || NULL == pChecker2->pChess) {
        return false;
    }

    if (pChecker1->pChess->m_nColor != pChecker2->pChess->m_nColor) {
        return false;
    }

    return true;
}

void GamePanel::matchChecker(Checker * pChecker) {
    if (pChecker->bSigned) {
        return;
    }

    pChecker->bSigned = true;
    if (isSame(pChecker, pChecker->pUP) && isSame(pChecker, pChecker->pDown)) {
        matchChecker(pChecker->pUP);
        matchChecker(pChecker->pDown);
    }

    if (isSame(pChecker, pChecker->pRight) && isSame(pChecker, pChecker->pLeft)) {
        matchChecker(pChecker->pRight);
        matchChecker(pChecker->pLeft);
    }

}


void GamePanel::fadeOutStar(cocos2d::Node * pSender) {
    this->removeChild(pSender);
}

void GamePanel::clearEffact(const cocos2d::Point & point, const s8 cColor) {
    for (s32 i=0; i<10; i++) {
        s32 random = CCRANDOM_0_1() * g_config.m_ScreenSize.width;
        s32 randomHigh = CCRANDOM_0_1() * 50 + 150;
        const char * pPath = NULL;
        switch (cColor) {
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
        pSprite->setPosition(point);
        pSprite->setAnchorPoint(Vec2(.5f, .5f));
        pSprite->setScale((CCRANDOM_0_1() * 15 + 5)/100.0f * g_config.m_fScaling);
        this->addChild(pSprite, 4);

        ActionInterval * jumpto = JumpTo::create(2, Vec2(random, -20), randomHigh, 1);
        FiniteTimeAction* finite = Sequence::create(jumpto, CallFuncN::create(this, callfuncN_selector(GamePanel::fadeOutStar)), NULL);
        ActionInterval * fadeout = FadeOut::create(2);
        pSprite->runAction(finite);
        pSprite->runAction(fadeout);
    }
}

void GamePanel::dataCorrection(cocos2d::Node * pSender) {
    //ECHO("pSender position: %f, %f", pSender->getPositionX(), pSender->getPositionY());
}

void GamePanel::gravityOver(cocos2d::Node * pSender) {
    if (!scanTable()) {
        generateStar();
    } else {
        if (!gravityTendency(g_data.m_nGravity)) {
            m_pChessboard->slideSwitch(true);
        }
    }
}

void GamePanel::clearAllStar() {
    s_pSelf->clearStarByColor(COLOR_BLUE);
    s_pSelf->clearStarByColor(COLOR_RED);
    s_pSelf->clearStarByColor(COLOR_YELLOW);
}

void GamePanel::clearStarByColor(const s8 nColor) {
    for (s32 x=0; x<TABLECLOTH_WIDTH; x++) {
        for (s32 y=0; y<TABLECLOTH_HEIGHT; y++) {
            if (m_Checkers[x][y].pChess != NULL && nColor == m_Checkers[x][y].pChess->m_nColor) {
                removeChild(m_Checkers[x][y].pChess);
                clearEffact(m_Checkers[x][y].pos, nColor);
                m_Checkers[x][y].pChess = NULL;
                m_Checkers[x][y].bSigned = false;
                m_EmptyCheckers.push_back(&(m_Checkers[x][y]));
            }
        }
    }

    SimpleAudioEngine::getInstance()->playEffect("bonus.mp3", false);
}

bool GamePanel::gravityTendency(const s8 dct) {
    bool res = false;
    switch (dct) {
    case DIRECTION_UP:
        for (s32 x=0; x<TABLECLOTH_WIDTH; x++) {
            Vector<Chess *> chesses;
            for (s32 y=TABLECLOTH_HEIGHT-1; y>=0; y--) {
                if (NULL != m_Checkers[x][y].pChess) {
                    chesses.pushBack(m_Checkers[x][y].pChess);
                    m_Checkers[x][y].pChess = NULL;
                }
            }

            for (s32 y=TABLECLOTH_HEIGHT-1; y>=0; y--) {
                if (chesses.empty()) {
                    break;
                }
                Chess * pChess = *(chesses.begin());
                chesses.erase(chesses.begin());
                m_Checkers[x][y].pChess = pChess;
                if (((s32)(pChess->getPositionX())) == (s32)(m_Checkers[x][y].pos.x)
                    && ((s32)(pChess->getPositionY())) == (s32)(m_Checkers[x][y].pos.y)) {
                        continue;
                }

                ActionInterval * moveto = MoveTo::create(.1f, m_Checkers[x][y].pos);
                if (!res) {
                    FiniteTimeAction* finite = Sequence::create(
                        moveto, 
                        CallFuncN::create(this, callfuncN_selector(GamePanel::dataCorrection)),
                        CallFuncN::create(this, callfuncN_selector(GamePanel::gravityOver)), 
                        NULL
                        );

                    pChess->runAction(finite);
                    SimpleAudioEngine::getInstance()->playEffect("move.mp3", false);
                    res = true;
                } else {
                    FiniteTimeAction* finite = Sequence::create(
                        moveto, 
                        CallFuncN::create(this, callfuncN_selector(GamePanel::dataCorrection)),
                        NULL
                        );
                    pChess->runAction(finite);
                }
            }
        }
        break;
    case DIRECTION_DOWN:
        for (s32 x=0; x<TABLECLOTH_WIDTH; x++) {
            Vector<Chess *> chesses;
            for (s32 y=0; y<TABLECLOTH_HEIGHT; y++) {
                if (NULL != m_Checkers[x][y].pChess) {
                    chesses.pushBack(m_Checkers[x][y].pChess);
                    m_Checkers[x][y].pChess = NULL;
                }
            }

            for (s32 y=0; y<TABLECLOTH_HEIGHT; y++) {
                if (chesses.empty()) {
                    break;
                }

                Chess * pChess = *(chesses.begin());
                chesses.erase(chesses.begin());
                m_Checkers[x][y].pChess = pChess;
                if (((s32)(pChess->getPositionX())) == (s32)(m_Checkers[x][y].pos.x)
                    && ((s32)(pChess->getPositionY())) == (s32)(m_Checkers[x][y].pos.y)) {
                        continue;
                }
                
                ActionInterval * moveto = MoveTo::create(.1f, m_Checkers[x][y].pos);
                if (!res) {
                    FiniteTimeAction* finite = Sequence::create(
                        moveto, 
                        CallFuncN::create(this, callfuncN_selector(GamePanel::dataCorrection)),
                        CallFuncN::create(this, callfuncN_selector(GamePanel::gravityOver)), 
                        NULL
                        );

                    pChess->runAction(finite);
                    SimpleAudioEngine::getInstance()->playEffect("move.mp3", false);
                    res = true;
                } else {
                    FiniteTimeAction* finite = Sequence::create(
                        moveto, 
                        CallFuncN::create(this, callfuncN_selector(GamePanel::dataCorrection)),
                        NULL
                        );
                    pChess->runAction(finite);
                }
            }
        }
        break;
    case DIRECTION_LEFT:
        for (s32 y=0; y<TABLECLOTH_HEIGHT; y++) {
            Vector<Chess *> chesses;
            for (s32 x=0; x<TABLECLOTH_WIDTH; x++) {
                if (NULL != m_Checkers[x][y].pChess) {
                    chesses.pushBack(m_Checkers[x][y].pChess);
                    m_Checkers[x][y].pChess = NULL;
                }
            }

            for (s32 x=0; x<TABLECLOTH_WIDTH; x++) {
                if (chesses.empty()) {
                    break;
                }

                Chess * pChess = *(chesses.begin());
                chesses.erase(chesses.begin());
                m_Checkers[x][y].pChess = pChess;
                if (((s32)(pChess->getPositionX())) == (s32)(m_Checkers[x][y].pos.x)
                    && ((s32)(pChess->getPositionY())) == (s32)(m_Checkers[x][y].pos.y)) {
                        continue;
                }

                ActionInterval * moveto = MoveTo::create(.1f, m_Checkers[x][y].pos);
                if (!res) {
                    FiniteTimeAction* finite = Sequence::create(
                        moveto, 
                        CallFuncN::create(this, callfuncN_selector(GamePanel::dataCorrection)),
                        CallFuncN::create(this, callfuncN_selector(GamePanel::gravityOver)), 
                        NULL
                        );

                    pChess->runAction(finite);
                    SimpleAudioEngine::getInstance()->playEffect("move.mp3", false);
                    res = true;
                } else {
                    FiniteTimeAction* finite = Sequence::create(
                        moveto, 
                        CallFuncN::create(this, callfuncN_selector(GamePanel::dataCorrection)),
                        NULL
                        );
                    pChess->runAction(finite);
                }
            }
        }
        break;
    case DIRECTION_RIGHT:
        for (s32 y=0; y<TABLECLOTH_HEIGHT; y++) {
            Vector<Chess *> chesses;
            for (s32 x=TABLECLOTH_WIDTH-1; x>=0; x--) {
                if (NULL != m_Checkers[x][y].pChess) {
                    chesses.pushBack(m_Checkers[x][y].pChess);
                    m_Checkers[x][y].pChess = NULL;
                }
            }

            for (s32 x=TABLECLOTH_WIDTH-1; x>=0; x--) {
                if (chesses.empty()) {
                    break;
                }

                Chess * pChess = *(chesses.begin());
                chesses.erase(chesses.begin());
                m_Checkers[x][y].pChess = pChess;
                if (((s32)(pChess->getPositionX())) == (s32)(m_Checkers[x][y].pos.x)
                    && ((s32)(pChess->getPositionY())) == (s32)(m_Checkers[x][y].pos.y)) {
                        continue;
                }

                ActionInterval * moveto = MoveTo::create(.1f, m_Checkers[x][y].pos);
                if (!res) {
                    FiniteTimeAction* finite = Sequence::create(
                        moveto, 
                        CallFuncN::create(this, callfuncN_selector(GamePanel::dataCorrection)),
                        CallFuncN::create(this, callfuncN_selector(GamePanel::gravityOver)), 
                        NULL
                        );

                    pChess->runAction(finite);
                    SimpleAudioEngine::getInstance()->playEffect("move.mp3", false);
                    res = true;
                } else {
                    FiniteTimeAction* finite = Sequence::create(
                        moveto, 
                        CallFuncN::create(this, callfuncN_selector(GamePanel::dataCorrection)),
                        NULL
                        );
                    pChess->runAction(finite);
                }
            }
        }
        break;
    default:
        ASSERT(false);
        break;
    }

    if (!res) {
        return res;
    }

    m_EmptyCheckers.clear();
    for (s32 x=0; x<TABLECLOTH_WIDTH; x++) {
        for (s32 y=0; y<TABLECLOTH_HEIGHT; y++) {
            if (NULL == m_Checkers[x][y].pChess) {
                m_EmptyCheckers.push_back(&(m_Checkers[x][y]));
            }
        }
    }

    return res;
}

bool GamePanel::scanTable() {
    bool res = false;
    for (s32 x=0; x<TABLECLOTH_WIDTH; x++) {
        for (s32 y=0; y<TABLECLOTH_WIDTH; y++) {
            Checker * pChecker = &(m_Checkers[x][y]);
            if (pChecker->bSigned) {
                continue;
            }

            if ( (isSame(pChecker, pChecker->pUP) && isSame(pChecker, pChecker->pDown)) 
                || (isSame(pChecker, pChecker->pLeft) && isSame(pChecker, pChecker->pRight))) {
                    matchChecker(pChecker);
                    res = true;
            }
        }
    }

    if (!res) {
        return res;
    }

    for (s32 x=0; x<TABLECLOTH_WIDTH; x++) {
        for (s32 y=0; y<TABLECLOTH_WIDTH; y++) {
            Checker * pChecker = &(m_Checkers[x][y]);
            if (pChecker->bSigned) {
                switch(pChecker->pChess->m_nColor) {
                case COLOR_BLUE:
                    g_data.m_nBlueStar ++;
                    break;
                case COLOR_RED:
                    g_data.m_nRedStar ++;
                    break;
                case COLOR_YELLOW:
                    g_data.m_nYellowStar ++;
                    break;
                }
                clearEffact(pChecker->pos, pChecker->pChess->m_nColor);
                this->removeChild(pChecker->pChess);
                pChecker->pChess = NULL;
                m_EmptyCheckers.push_back(pChecker);
                g_data.m_nPoint += POINT_BASE;
                pChecker->bSigned = false;
            }
        }
    }

    char szPath[64] = {0};
    SafeSprintf(szPath, sizeof(szPath), "Eliminate%d.mp3", g_data.m_nEliminate%ELIMINATE_COUNT);
    SimpleAudioEngine::getInstance()->stopAllEffects();
    SimpleAudioEngine::getInstance()->playEffect(szPath);
    g_data.m_nPoint += g_data.m_nEliminate * COMBO_POINT;
    if (g_data.m_nEliminate > 0) {
        hit(g_data.m_nEliminate);
    }
    g_data.m_nEliminate++;
    return res;
}

bool GamePanel::generateStar(const s32 nCount) {
    if (m_EmptyCheckers.empty()) {
        return false;
    }

    for (s32 count=0; count<nCount; count ++) {
        s32 size = m_EmptyCheckers.size();
        s32 nRandom = ((s32)(CCRANDOM_0_1() * 256)) % size;
        Checker * pChecker = m_EmptyCheckers[nRandom];
        ASSERT(NULL == pChecker->pChess);
        m_EmptyCheckers.erase(m_EmptyCheckers.begin() + nRandom);

        pChecker->pChess = Chess::create(((s32)(CCRANDOM_0_1() * 10000)) % COLOR_COUNT);
        pChecker->pChess->setPosition(pChecker->pos);
        pChecker->pChess->setScale(.1f * g_config.m_fScaling);
        pChecker->pChess->setOpacity(0);
        this->addChild(pChecker->pChess);
        ActionInterval * fadein = FadeIn::create(.25);
        ActionInterval * scaleto = ScaleTo::create(.25, 1 * g_config.m_fScaling);
        pChecker->pChess->runAction(scaleto);
        if (count == nCount-1 || m_EmptyCheckers.empty()) {
            FiniteTimeAction* finite = Sequence::create(fadein, CallFuncN::create(this, callfuncN_selector(GamePanel::generateStarOver)), NULL);
            pChecker->pChess->runAction(finite);
            break;
        }

        pChecker->pChess->runAction(fadein);
    }

    return true;
}
