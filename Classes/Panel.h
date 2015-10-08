#ifndef PANEL_H
#define PANEL_H
#include "Header.h"

class Panel : public cocos2d::Node {
public:
    virtual void setOpacity(GLubyte opacity);
    virtual bool init() = 0;
    virtual void show(const bool start = false) = 0;
    virtual void hide() = 0;
    virtual void reset() = 0;
};

#endif //PANEL_H
