/**\file SettingsState.cpp*/
#include "stdafx.h"
#include "SettingsState.h"



void SettingsState::initVariables()
{
	this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/KurriIslandItaPersonalBold-d95qR.ttf")) //load Kurri Island font from Fonts file
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT"); //throw error if file was not found
	}
}

void SettingsState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini"); //read from mainmenustate_keybinds.ini

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

void SettingsState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->background.setSize(
		sf::Vector2f
		(
			static_cast<float>(vm.width),
			static_cast<float>(vm.height)
		)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg2.png"))
	{
		throw"ERROR::Main_Menu_State::FAILED_TO_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	
	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(40.9f, vm), gui::p2pY(67.7f, vm),
		gui::p2pX(11.f, vm), gui::p2pY(6.5f, vm),
		&this->font, "Back", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["APPLY"] = new gui::Button(
		gui::p2pX(62.9f, vm), gui::p2pY(67.7f, vm),
		gui::p2pX(11.f, vm), gui::p2pY(6.5f, vm),
		&this->font, "Apply", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	std::vector<std::string> modes_str;
	for (auto &i : this->modes)
	{
		modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));
	}
	this->dropDownLists["RESOLUTION"] = new gui::DropDownList(
		gui::p2pX(58.5f, vm), gui::p2pY(32.5f, vm),
		gui::p2pX(14.64f, vm), gui::p2pY(6.5f, vm),
		font, modes_str.data(), modes_str.size());

	this->optionText.setFont(this->font);
	this->optionText.setPosition(sf::Vector2f(gui::p2pX(7.3f, vm), gui::p2pY(35.1f, vm)));
	this->optionText.setCharacterSize(gui::calcCharSize(vm, 80));
	this->optionText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionText.setString(
		"Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n "
	);
}

void SettingsState::resetGui()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
	this->dropDownLists.clear();

	this->initGui();
}

SettingsState::SettingsState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initFonts(); //initialise fonts
	this->initKeybinds(); //initialise keybinds
	this->initGui(); //initialise buttons

}


SettingsState::~SettingsState()
{
	//delete the buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
	auto it2 = this->dropDownLists.begin();
	for (it2 = this->dropDownLists.begin(); it2 != this->dropDownLists.end(); ++it2)
	{
		delete it2->second;
	}
	
}

//Accessors

//Functions

void SettingsState::updateInput(const float & dt)
{

}

void SettingsState::updateGui(const float & dt)
{
	//updates all gui elements in the state and handles their functionality
	//Buttons
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//Button functionality
	//Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	if (this->buttons["APPLY"]->isPressed())
	{
		//Test Remove later
		this->stateData->gfxSettings->resolution = this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];

		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);

		this->resetGui();
	}

	// Dropdown lists
	for (auto &it : this->dropDownLists)
	{
		it.second->update(this->mousePosWindow, dt);
	}
	//Dropdown lists functionality

	
}

void SettingsState::update(const float & dt)
{
	this->updateMousePositions(); //update mouse position in menue state
	this->updateInput(dt); //update input in menu state

	this->updateGui(dt); //update buttons in menu state

	
}

void SettingsState::renderGui(sf::RenderTarget & target)
{
	//this->gamestate_btn->render(target);
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto &it : this->dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget * target)
{
	if (!target) //if there is nothing on the target
		target = this->window; //then set the target to the window

	target->draw(this->background); //render background

	this->renderGui(*target); //render buttons
	
	target->draw(this->optionText);

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


