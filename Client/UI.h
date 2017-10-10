#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <Ogre.h>

class UI
{
public:
	~UI(void);
public:
	
	static UI *getInstance();

	void createButton(const CEGUI::String &type, const CEGUI::String &name, const CEGUI::String &text,
		Ogre::Vector2 size, Ogre::Vector2 pos, bool setEvent);

	void destroy();

public:
	void createChatBox();
	void setVisible(bool visible);         // Hide or show the console
    bool isVisible();

private:
	UI(void);
	void setResourceGroup();

private:
	static UI *instance;
	CEGUI::OgreRenderer* mRenderer;
	
    CEGUI::Window *m_ConsoleWindow;                            // This will be a pointer to the ConsoleRoot window.
    CEGUI::String sNamePrefix;                                  // This will be the prefix name we give the layout
    static int iInstanceNumber;                                 // This will be the instance number for this class.
    bool m_bConsole;

private:
	void CreateCEGUIWindow();                                  // The function which will load in the CEGUI Window and register event handlers
    void RegisterHandlers();                                   // Register our handler functions
    bool Handle_TextSubmitted(const CEGUI::EventArgs &e);      // Handle when we press Enter after typing
    bool Handle_SendButtonPressed(const CEGUI::EventArgs &e);  // Handle when we press the Send button         
    void ParseText(CEGUI::String inMsg);                       // Parse the text the user submitted.
    void OutputText(CEGUI::String inMsg,                       // Post the message to the ChatHistory listbox.
          CEGUI::Colour colour = CEGUI::Colour( 0xFFFFFFFF)); //   with a white color default
 

};

