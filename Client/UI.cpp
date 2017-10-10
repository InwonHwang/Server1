#include "UI.h"
#include "SessionManager.h"

int UI::iInstanceNumber;                
UI *UI::instance = nullptr;

UI *UI::getInstance()
{ 
	if(!instance)
		instance = new UI();

	return instance;
};

void UI::destroy()
{
	if(instance)
		delete instance;
}

UI::UI(void)
{
	SessionManager::connect();
	setResourceGroup();
	
	mRenderer = &CEGUI::OgreRenderer::bootstrapSystem();
	
	m_ConsoleWindow = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "Chatting");

	iInstanceNumber = 0;
	sNamePrefix = "";	
}

UI::~UI(void)
{
	SessionManager::destroy();
}

void UI::createChatBox()
{
	CreateCEGUIWindow();
	setVisible(true);
	m_bConsole = true;
}

void UI::CreateCEGUIWindow()
{
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

    sNamePrefix = ++iInstanceNumber + "_";
        
 
    // Note : for CEGUI 0.8
	CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_ConsoleWindow);
	CEGUI::Window* guiLayout = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Console.layout");
	
	
	m_ConsoleWindow->addChild(guiLayout);
	
    // Being a good programmer, its a good idea to ensure that we got a valid window back. 
    if (m_ConsoleWindow)
    {
        RegisterHandlers();
    }
    else
    {
        // Something bad happened and we didn't successfully create the window lets output the information
        CEGUI::Logger::getSingleton().logEvent("Error: Unable to load the ConsoleWindow from .layout");
    }
}

void UI::RegisterHandlers()
{
   
    m_ConsoleWindow->getChild(sNamePrefix + "Console/Submit")->subscribeEvent(
                CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&UI::Handle_SendButtonPressed, this));                         
 
    m_ConsoleWindow->getChild(sNamePrefix + "Console/Editbox")->subscribeEvent(CEGUI::Editbox::EventTextAccepted,
                        CEGUI::Event::Subscriber(&UI::Handle_TextSubmitted,this));
}

void UI::ParseText(CEGUI::String inMsg)
{
    //std::string inString = inMsg.c_str();
	std::string inString = SessionManager::recv();
	
 
	if (inString.length() >= 1) // Be sure we got a string longer than 0
	{
		if (inString.at(0) == '/') // Check if the first letter is a 'command'
		{
			std::string::size_type commandEnd = inString.find(" ", 1);
			std::string command = inString.substr(1, commandEnd - 1);
			std::string commandArgs = inString.substr(commandEnd + 1, inString.length() - (commandEnd + 1));
			//convert command to lower case
			for(std::string::size_type i=0; i < command.length(); i++)
			{
				command[i] = tolower(command[i]);
			}
 
			// Begin processing
 
			if (command == "say")
			{
				std::string outString = "You:" + inString; // Append our 'name' to the message we'll display in the list
                         	OutputText(outString);
			}
			else if (command == "quit")
			{
				// do a /quit 
			}
			else if (command == "help")
			{
				// do a /help
			}
			else
			{
				std::string outString = "<" + inString + "> is an invalid command.";
				OutputText(outString,CEGUI::Colour(1.0f,0.0f,0.0f)); // With red ANGRY colors!
			}
		} // End if /
		else
		{
			OutputText(inString); // no commands, just output what they wrote
			//OutputText(m);
		}
	} 
}

void UI::OutputText(CEGUI::String inMsg, CEGUI::Colour colour)
{	
	CEGUI::Listbox *outputWindow = static_cast<CEGUI::Listbox*>(m_ConsoleWindow->getChild(sNamePrefix + "Console/History"));
 
	CEGUI::ListboxTextItem* newItem=0;
 
	newItem = new CEGUI::ListboxTextItem(inMsg);
    newItem->setTextColours(colour);
	outputWindow->addItem(newItem);
}

bool UI::Handle_TextSubmitted(const CEGUI::EventArgs &e)
{  
    const CEGUI::WindowEventArgs* args = static_cast<const CEGUI::WindowEventArgs*>(&e);
 
    CEGUI::String Msg = m_ConsoleWindow->getChild(sNamePrefix + "Console/Editbox")->getText();
 
    ParseText(Msg);

    m_ConsoleWindow->getChild(sNamePrefix + "Console/Editbox")->setText("");
 
    return true;
}

bool UI::Handle_SendButtonPressed(const CEGUI::EventArgs &e)
{
	CEGUI::String Msg = m_ConsoleWindow->getChild(sNamePrefix + "Console/Editbox")->getText();    
	SessionManager::send(Msg.c_str());
	ParseText(Msg);
    m_ConsoleWindow->getChild(sNamePrefix + "Console/Editbox")->setText("");
 
    return true;
}

void UI::setVisible(bool visible)
{
    m_ConsoleWindow->setVisible(visible);
    m_bConsole = visible;
 
    CEGUI::Editbox* editBox = static_cast<CEGUI::Editbox *>(m_ConsoleWindow->getChild(sNamePrefix + "Console/Editbox"));
    if(visible)
       editBox->activate();
    else
       editBox->deactivate();
}
 
bool UI::isVisible()
{
    return m_ConsoleWindow->isVisible();
}

void UI::createButton(const CEGUI::String &type, const CEGUI::String &name, const CEGUI::String &text,
		Ogre::Vector2 size, Ogre::Vector2 pos, bool setEvent)
{
	CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme"); 
	CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

	CEGUI::Window *quit = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/Button", name);
    quit->setText(text);
	quit->setSize(CEGUI::USize(CEGUI::UDim(size.x, 0), CEGUI::UDim(size.y, 0)));
	quit->setPosition(CEGUI::UVector2(CEGUI::UDim(pos.x, 0), CEGUI::UDim(pos.y,0)));
 
    m_ConsoleWindow->addChild(quit);
    CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(m_ConsoleWindow);
 
	/*if(setEvent)
		quit->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(eventmethod, &e));*/
}



void UI::setResourceGroup()
{
	CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
}

