#include "ShopPanel.h"
#include "Smart09.h"
#include "md5.h"
#include "json/json.h"
USING_NS_CC;
ShopPanel * ShopPanel::s_pSelf = NULL;

static std::string g_phoneNumber = "";
static std::string g_imsi = "";

Panel * ShopPanel::create() {
	if (NULL == s_pSelf) {
		s_pSelf = NEW
		ShopPanel;
		if (s_pSelf && s_pSelf->init()) {
			s_pSelf->autorelease();
		} else {
			CC_SAFE_DELETE(s_pSelf);
		}
	}

	return s_pSelf;
}

ShopPanel::ShopPanel() {
	m_pButton1 = NULL;
	m_pButton2 = NULL;
	m_pButton3 = NULL;
	m_pButton4 = NULL;
	m_pButton5 = NULL;
}

bool ShopPanel::init() {
	if (!Node::init()) {
		return false;
	}

	Sprite * pSprite = Sprite::create("defeat.png");
	pSprite->setAnchorPoint(Vec2(0, 0));
	pSprite->setOpacity(0);
	this->addChild(pSprite, 0);
	pSprite->setScaleX(
			g_config.m_ScreenSize.width / pSprite->getContentSize().width);
	pSprite->setScaleY(
			g_config.m_ScreenSize.height / pSprite->getContentSize().height);

	m_pButton1 = Button::create(EVENT_ID_PAY_1);
	m_pButton1->init("", 0, "pay1.png");
	m_pButton1->setAnchorPoint(Vec2(.5f, .5f));
	m_pButton1->setOpacity(0);
	m_pButton1->setPosition(
			Vec2(g_config.m_ScreenCenterPoint.x,
					g_config.m_ScreenCenterPoint.y
							+ 300 * g_config.m_fScaling));
	m_pButton1->setScale(g_config.m_fScaling);
	this->addChild(m_pButton1, 1);

	m_pButton2 = Button::create(EVENT_ID_PAY_2);
	m_pButton2->init("", 0, "pay2.png");
	m_pButton2->setAnchorPoint(Vec2(.5f, .5f));
	m_pButton2->setOpacity(0);
	m_pButton2->setPosition(
			Vec2(g_config.m_ScreenCenterPoint.x,
					g_config.m_ScreenCenterPoint.y
							+ 200 * g_config.m_fScaling));
	m_pButton2->setScale(g_config.m_fScaling);
	this->addChild(m_pButton2, 1);

	m_pButton3 = Button::create(EVENT_ID_PAY_5);
	m_pButton3->init("", 0, "pay3.png");
	m_pButton3->setAnchorPoint(Vec2(.5f, .5f));
	m_pButton3->setOpacity(0);
	m_pButton3->setPosition(
			Vec2(g_config.m_ScreenCenterPoint.x,
					g_config.m_ScreenCenterPoint.y
							+ 100 * g_config.m_fScaling));
	m_pButton3->setScale(g_config.m_fScaling);
	this->addChild(m_pButton3, 1);

	m_pButton4 = Button::create(EVENT_ID_PAY_6);
	m_pButton4->init("", 0, "pay4.png");
	m_pButton4->setAnchorPoint(Vec2(.5f, .5f));
	m_pButton4->setOpacity(0);
	m_pButton4->setPosition(
			Vec2(g_config.m_ScreenCenterPoint.x,
					g_config.m_ScreenCenterPoint.y));
	m_pButton4->setScale(g_config.m_fScaling);
	this->addChild(m_pButton4, 1);

	m_pButton5 = Button::create(EVENT_ID_PAY_8);
	m_pButton5->init("", 0, "pay5.png");
	m_pButton5->setAnchorPoint(Vec2(.5f, .5f));
	m_pButton5->setOpacity(0);
	m_pButton5->setPosition(
			Vec2(g_config.m_ScreenCenterPoint.x,
					g_config.m_ScreenCenterPoint.y
							- 100 * g_config.m_fScaling));
	m_pButton5->setScale(g_config.m_fScaling);
	this->addChild(m_pButton5, 1);

	m_pButtonClose = Button::create(EVENT_ID_PAY_CLOSE);
	m_pButtonClose->init("", 0, "payclose.png");
	m_pButtonClose->setAnchorPoint(Vec2(.5f, .5f));
	m_pButtonClose->setOpacity(0);
	m_pButtonClose->setPosition(
			Vec2(g_config.m_ScreenCenterPoint.x,
					g_config.m_ScreenCenterPoint.y
							- 300 * g_config.m_fScaling));
	m_pButtonClose->setScale(g_config.m_fScaling);
	this->addChild(m_pButtonClose, 1);

	RGS_EVENT_CALL(EVENT_ID_PAY_10, ShopPanel::pay10);

	return true;
}

void ShopPanel::pay1() {
	if (payBilling("006041658001")) {
		s32 nCash = UserDefault::getInstance()->getIntegerForKey("Cash");
		(nCash >= 0) ? (nCash = nCash + 1) : (nCash = 1);
		UserDefault::getInstance()->setIntegerForKey("Cash", nCash);
		Smart09::create()->CallEvent(EVENT_ID_PAY_SUCCESS);
		HTTP_LOG("手机用户%s充值1元成功", g_phoneNumber.c_str());
	} else {
		HTTP_LOG("手机用户%s充值1元失败", g_phoneNumber.c_str());
		Smart09::create()->CallEvent(EVENT_ID_PAY_FAILD);
	}
}

void ShopPanel::pay2() {
	if (payBilling("006041658002")) {
		s32 nCash = UserDefault::getInstance()->getIntegerForKey("Cash");
		(nCash >= 0) ? (nCash = nCash + 3) : (nCash = 3);
		UserDefault::getInstance()->setIntegerForKey("Cash", nCash);
		Smart09::create()->CallEvent(EVENT_ID_PAY_SUCCESS);
		HTTP_LOG("手机用户%s充值2元成功", g_phoneNumber.c_str());
	} else {
		HTTP_LOG("手机用户%s充值2元失败", g_phoneNumber.c_str());
		Smart09::create()->CallEvent(EVENT_ID_PAY_FAILD);
	}
}

void ShopPanel::pay5() {
	if(payBilling("006041658003")) {
        s32 nCash = UserDefault::getInstance()->getIntegerForKey("Cash");
        (nCash>=0)?(nCash=nCash+8):(nCash=8);
        UserDefault::getInstance()->setIntegerForKey("Cash", nCash);
		Smart09::create()->CallEvent(EVENT_ID_PAY_SUCCESS);
        HTTP_LOG("手机用户%s充值5元成功", g_phoneNumber.c_str());
	} else {
        HTTP_LOG("手机用户%s充值5元失败", g_phoneNumber.c_str());
        Smart09::create()->CallEvent(EVENT_ID_PAY_FAILD);
	}
}

void ShopPanel::pay6() {
	if(payBilling("006041658004")) {
		Smart09::create()->CallEvent(EVENT_ID_GIFT_PACKS);
		Smart09::create()->CallEvent(EVENT_ID_PAY_SUCCESS);
        HTTP_LOG("手机用户%s充值6元成功", g_phoneNumber.c_str());
	} else {
        HTTP_LOG("手机用户%s充值6元失败", g_phoneNumber.c_str());
        Smart09::create()->CallEvent(EVENT_ID_PAY_FAILD);
	}
}

void ShopPanel::pay8() {
	if(payBilling("006041658005")) {
        s32 nCash = UserDefault::getInstance()->getIntegerForKey("Cash");
        (nCash>=0)?(nCash=nCash+14):(nCash=14);
        UserDefault::getInstance()->setIntegerForKey("Cash", nCash);
		Smart09::create()->CallEvent(EVENT_ID_PAY_SUCCESS);
        HTTP_LOG("手机用户%s充值8元成功", g_phoneNumber.c_str());
	} else {
        HTTP_LOG("手机用户%s充值8元失败", g_phoneNumber.c_str());
        Smart09::create()->CallEvent(EVENT_ID_PAY_FAILD);
	}
}

void ShopPanel::pay10() {
	if(payBilling("006041658006")) {
        s32 nCash = UserDefault::getInstance()->getIntegerForKey("Cash");
        (nCash>=0)?(nCash=nCash+1):(nCash=1);
        UserDefault::getInstance()->setIntegerForKey("Cash", nCash);
		Smart09::create()->CallEvent(EVENT_ID_PAY_SUCCESS);
        HTTP_LOG("手机用户%s充值1元成功", g_phoneNumber.c_str());
	} else {
        HTTP_LOG("手机用户%s充值10元失败", g_phoneNumber.c_str());
        Smart09::create()->CallEvent(EVENT_ID_PAY_FAILD);
	}
}

void ShopPanel::show(const bool start) {
	ActionInterval * fadein = FadeIn::create(1);
	Vector<Node *> children_list = this->getChildren();
	Vector<Node *>::iterator itor = children_list.begin();
	Vector<Node *>::iterator iend = children_list.end();
	while (itor != iend) {
		ActionInterval * pAction = fadein->clone();
		(*itor)->runAction(pAction);

		itor++;
	}

	Smart09::create()->AddTouchHandle(TOUCH_GRADE_ALERT, m_pButton1);
	Smart09::create()->AddTouchHandle(TOUCH_GRADE_ALERT, m_pButton2);
	Smart09::create()->AddTouchHandle(TOUCH_GRADE_ALERT, m_pButton3);
	Smart09::create()->AddTouchHandle(TOUCH_GRADE_ALERT, m_pButton4);
	Smart09::create()->AddTouchHandle(TOUCH_GRADE_ALERT, m_pButton5);
	Smart09::create()->AddTouchHandle(TOUCH_GRADE_ALERT, m_pButtonClose);
	Smart09::create()->AddTouchHandle(TOUCH_GRADE_ALERT, this);

	RGS_EVENT_CALL(EVENT_ID_ESC, ShopPanel::closeShop);
	RGS_EVENT_CALL(EVENT_ID_PAY_1, ShopPanel::pay1);
	RGS_EVENT_CALL(EVENT_ID_PAY_2, ShopPanel::pay2);
	RGS_EVENT_CALL(EVENT_ID_PAY_5, ShopPanel::pay5);
	RGS_EVENT_CALL(EVENT_ID_PAY_6, ShopPanel::pay6);
	RGS_EVENT_CALL(EVENT_ID_PAY_8, ShopPanel::pay8);
}

void ShopPanel::closeShop() {
	Smart09::create()->CallEvent(EVENT_ID_PAY_CLOSE);
}

void ShopPanel::hide() {
	ActionInterval * fadeout = FadeOut::create(1);
	Vector<Node *> children_list = this->getChildren();
	Vector<Node *>::iterator itor = children_list.begin();
	Vector<Node *>::iterator iend = children_list.end();
	while (itor != iend) {
		ActionInterval * pAction = fadeout->clone();
		(*itor)->runAction(pAction);

		itor++;
	}

	Smart09::create()->RemoveTouchHandle(m_pButton1);
	Smart09::create()->RemoveTouchHandle(m_pButton2);
	Smart09::create()->RemoveTouchHandle(m_pButton3);
	Smart09::create()->RemoveTouchHandle(m_pButton4);
	Smart09::create()->RemoveTouchHandle(m_pButton5);
	Smart09::create()->RemoveTouchHandle(m_pButtonClose);
	Smart09::create()->RemoveTouchHandle(this);

	UNRGS_EVENT_CALL(EVENT_ID_ESC, ShopPanel::closeShop);
	UNRGS_EVENT_CALL(EVENT_ID_PAY_1, ShopPanel::pay1);
	UNRGS_EVENT_CALL(EVENT_ID_PAY_2, ShopPanel::pay2);
	UNRGS_EVENT_CALL(EVENT_ID_PAY_5, ShopPanel::pay5);
	UNRGS_EVENT_CALL(EVENT_ID_PAY_6, ShopPanel::pay6);
	UNRGS_EVENT_CALL(EVENT_ID_PAY_8, ShopPanel::pay8);
}

void ShopPanel::reset() {

}
