#ifndef HELPPANEL_H
#define HELPPANEL_H

#include "Panel.h"
#include "Button.h"

class HelpPanel : public Panel {
public:
    static Panel * create();
    virtual bool init();
    virtual void show(const bool start = false);
    virtual void hide();
    virtual void reset();

    ~HelpPanel();
private:
    HelpPanel();

private:
    static HelpPanel * s_pSelf;
    Button * m_pButton;
};


#endif //HELPPANEL_H
