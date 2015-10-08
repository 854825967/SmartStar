#include "Panel.h"
USING_NS_CC;

void Panel::setOpacity(GLubyte opacity) {
    Vector<Node *> children_list = getChildren();
    Vector<Node *>::iterator itor = children_list.begin();
    Vector<Node *>::iterator iend = children_list.end();
    while (itor != iend) {
        (*itor)->setOpacity(0);
        itor++;
    }
}
