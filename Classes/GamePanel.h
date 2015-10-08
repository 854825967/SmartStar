#ifndef GAMEPANEL_H
#define GAMEPANEL_H

#include "Panel.h"
#include "Chessboard.h"
#include <vector>
using namespace std;

class Button;

class Checker {
public:
    Chess * pChess;
    bool bSigned;


    cocos2d::Point pos;
    Checker * pUP;
    Checker * pDown;
    Checker * pLeft;
    Checker * pRight;
};

typedef vector<Checker *> EMPTY_CHECKER_LIST;

class GamePanel : public Panel {
public:
    ~GamePanel() {
        s_pSelf = NULL;
    }

    static Panel * create();
    virtual bool init();
    virtual void show(const bool start = false);
    virtual void hide();
    virtual void reset();

    virtual void startGame(cocos2d::Node * pSender);
    void updatePoint(float);
private:
    GamePanel();
    //effective
    void clearEffact(const cocos2d::Point & point, const s8 cColor);
    void fadeOutStar(cocos2d::Node * pSender);

    //game contral
    bool scanTable();
    bool isSame(const Checker * pChecker1, const Checker * pChecker2);
    void matchChecker(Checker * pChecker);

    void clearStarByColor(const s8 nColor);

    bool gravityTendency(const s8 dct);
    void gravityOver(cocos2d::Node * pSender);
    void dataCorrection(cocos2d::Node * pSender);

    bool generateStar(const s32 nCount = CREATE_CHESS_COUNT);
    void generateStarOver(cocos2d::Node * pSender);
    void hit(const s32 nHit);

    static void slideUpEvent();
    static void slideDownEvent();
    static void slideRightEvent();
    static void slideLeftEvent();
    static void clearBlueStar();
    static void clearRedStar();
    static void clearYellowStar();
    static void clearAllStar();
    static void soundSwitch();
    static void paySuccess();

private:
    Chessboard * m_pChessboard;
    cocos2d::Label * m_pPointLabel;
    cocos2d::Label * m_pCashLabel;
    cocos2d::Label * m_pHighestLabel;
    cocos2d::Label * m_pHitLabel;

    Checker m_Checkers[TABLECLOTH_WIDTH][TABLECLOTH_HEIGHT];
    EMPTY_CHECKER_LIST m_EmptyCheckers;
    s32 m_nCurrentSetupCount;
    s32 m_nPoint;
    
    Button * m_pButtonSound;

    static GamePanel * s_pSelf;
};

#endif //GAMEPANEL_H
