#include "TutorialApplication.h"
 
//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}
 
//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
	// Create a Light and set its position
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
	Ogre::Light* light = mSceneMgr->createLight("MainLight");
	light->setPosition(20.0f, 80.0f, 50.0f);

	// create skydome
	mSceneMgr->setSkyDome(true, "Examples/CloudySky", 5, 8);

	///////////////////////////////////////////////////////////////////////////////////////
	//UI::getInstance()->createButton("TaharezLook/Button", "QuitButton", "Quit", Ogre::Vector2(0.15, 0.05), Ogre::Vector2::ZERO, false);
	//UI::getInstance()->createButton("TaharezLook/Button", "TestButton", "Test", Ogre::Vector2(0.15, 0.05), Ogre::Vector2(0.5, 0), false);
	UI::getInstance()->createChatBox();

	////quat 에 이벤트 등록
	 //   quit->subscribeEvent(CEGUI::PushButton::EventClicked,
	//   CEGUI::Event::Subscriber(&TutorialApplication::quit, this));

}

void TutorialApplication::createFrameListener(void){
	BaseApplication::createFrameListener();
} 
 
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent &evt){
    
	return BaseApplication::frameRenderingQueued(evt);
	
}



void TutorialApplication::destroyScene(void){
	BaseApplication::destroyScene();
}
 
bool TutorialApplication::keyPressed( const OIS::KeyEvent &arg )
{
    CEGUI::System &sys = CEGUI::System::getSingleton();
	sys.getDefaultGUIContext().injectKeyDown((CEGUI::Key::Scan)arg.key);
    sys.getDefaultGUIContext().injectChar(arg.text);
  
    mCameraMan->injectKeyDown(arg);
    return true;
}
 
bool TutorialApplication::keyReleased( const OIS::KeyEvent &arg )
{	

    if(CEGUI::System::getSingleton().getDefaultGUIContext().injectKeyUp((CEGUI::Key::Scan)arg.key)) return true;
    mCameraMan->injectKeyUp(arg);
    return true;
}

CEGUI::MouseButton convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
        break;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
        break;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
        break;
 
    default:
        return CEGUI::LeftButton;
        break;
    }
}
 
bool TutorialApplication::mouseMoved( const OIS::MouseEvent &arg )
{
    if(CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseMove(arg.state.X.rel, arg.state.Y.rel)) return true;
    mCameraMan->injectMouseMove(arg);
    return true;
}
 
bool TutorialApplication::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if(CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonDown(convertButton(id))) return true;
    mCameraMan->injectMouseDown(arg, id);
    return true;
}
 
bool TutorialApplication::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
    if(CEGUI::System::getSingleton().getDefaultGUIContext().injectMouseButtonUp(convertButton(id))) return true;
    mCameraMan->injectMouseUp(arg, id);
    return true;
}
 

 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
 
#ifdef __cplusplus
extern "C" {
#endif
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;
 
        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }
 
        return 0;
    }
 
#ifdef __cplusplus
}
#endif