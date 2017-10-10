#ifndef __IntermediateTutorial1_h_
#define __IntermediateTutorial1_h_
 
#include "BaseApplication.h"
#include "UI.h"

 
class TutorialApplication : public BaseApplication
{
public:
    TutorialApplication(void);
    virtual ~TutorialApplication(void);
 
protected:
	

    virtual void createScene(void);
    virtual void createFrameListener(void);
 
    virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);

	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);
 
	virtual bool mouseMoved(const OIS::MouseEvent& me);
	virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);

	void destroyScene();
  
    Ogre::Entity *mEntity;                 // The Entity we are animating
    Ogre::SceneNode *mNode;                // The -SceneNode that the Entity is attached to

};
 
#endif // #ifndef __IntermediateTutorial1_h_