#include "AppDelegate.h"
#include "Smart09.h"
#include "Header.h"

USING_NS_CC;

class TestVirtual {
public:
    //virtual void test() {
    void test() {
        
    }
    
    void test1() {
        
    }
};

AppDelegate::AppDelegate() {
    TestVirtual a;
    ECHO("sizeof(TestVirtual class) %d, sizeof(TestVirtual obj) %d", sizeof(TestVirtual), sizeof(a));
}

AppDelegate::~AppDelegate() {

}

void AppDelegate::InitGameConfig() {
    auto director = Director::getInstance();
    Size size = director->getWinSize();
    if (size.width/size.height > BASE_SCREEN_WIDTH/BASE_SCREEN_HEIGHT) {
        g_config.m_fScaling = size.height / BASE_SCREEN_HEIGHT;
    } else {
        g_config.m_fScaling = size.width / BASE_SCREEN_WIDTH;
    }

    g_config.m_ScreenCenterPoint = Vec2(size.width/2.0f, size.height/2.0f);
    g_config.m_VirtualScrenSize = Vec2(BASE_SCREEN_WIDTH * g_config.m_fScaling, BASE_SCREEN_HEIGHT * g_config.m_fScaling);
    g_config.m_ScreenSize = size;
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#ifdef WIN32
        glview = GLView::createWithRect("SmartStar", Rect(0, 0, 640, 960));
#else
        glview = GLView::create("SmartStar");
#endif //win32
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    // director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    InitGameConfig();

    // create a scene. it's an autorelease object
    auto scene = Smart09::createScene();

    //glview->setDesignResolutionSize(640, 1136, kResolutionNoBorder);
    
    // run
    director->runWithScene(scene);


    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
