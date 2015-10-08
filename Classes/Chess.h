#ifndef CHESS_H
#define CHESS_H
#include "Header.h"

class Chess : public cocos2d::Sprite {
public:
    static Chess * create(const s8 nColor);
    virtual bool init();
    ~Chess() {
    }

    s8 m_nColor;
private:
    Chess(const s8 nColor);
    //cocos2d::Sprite * m_pSprite;
};

#endif //CHESS_H
