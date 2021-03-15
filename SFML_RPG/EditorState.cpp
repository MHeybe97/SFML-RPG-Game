/**\file EditorState.cpp*/
#include "stdafx.h"
#include "EditorState.h"

//initializer functions
void EditorState::initVariables()
{
}

void EditorState::initBackground()
{
	
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/KurriIslandItaPersonalBold-d95qR.ttf")) //load Kurri Island font from Fonts file
	{
		throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT"); //throw error if file was not found
	}
}

void EditorState::initKeybinds()
{
	std::ifstream ifs("Config/editorstate_keybinds.ini"); //read from mainmenustate_keybinds.ini

	if (ifs.is_open()) //if file is open
	{
		std::string key = " "; //string for what key does e.g. CLOSE
		std::string key2 = " "; //string for name of key e.g. Escape

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2); //keybinds is equal to supportedkeys
		}
	}

	ifs.close(); //close file

}

void EditorState::initButtons()
{
	
}

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts(); //initialise fonts
	this->initKeybinds(); //initialise keybinds
	this->initButtons(); //initialise buttons
}

EditorState::~EditorState()
{
	//delete the buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void EditorState::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
		this->endState();
}

void EditorState::updateButtons()
{
	//updates all buttons in the state and handles their functionality
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosView);
	}

	
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions(); //update mouse position in menue state
	this->updateInput(dt); //update input in menu state

	this->updateButtons(); //update buttons in menu state

	
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	//this->gamestate_btn->render(target);
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target) //if there is nothing on the target
		target = this->window; //then set the target to the window

	

	this->renderButtons(*target); //render buttons

	//MousePosition For Debugging
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());

	target->draw(mouseText);
}