/**\file EditorState.cpp*/
#include "stdafx.h"
#include "EditorState.h"

//initializer functions
void EditorState::initVariables()
{

	this->cameraSpeed = 1000.f;
}

void EditorState::initEditorStateData()
{
	this->editorStateData.view = &this->view;
	this->editorStateData.font = &this->font;
	this->editorStateData.keytime = &this->keytime;
	this->editorStateData.keytimeMax = &this->keytimeMax;
	this->editorStateData.keybinds = &this->keybinds;
	this->editorStateData.mousePosGrid = &this->mousePosGrid;
	this->editorStateData.mousePosScreen = &this->mousePosScreen;
	this->editorStateData.mousePosView = &this->mousePosView;
	this->editorStateData.mousePosWindow = &this->mousePosWindow;
}

void EditorState::initView()
{
	this->view.setSize(sf::Vector2f(
		static_cast<float>(this->stateData->gfxSettings->resolution.width), 
		static_cast<float>(this->stateData->gfxSettings->resolution.height)
	)
	
	);

	this->view.setCenter(
		static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f, 
		static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
	);
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/KurriIslandItaPersonalBold-d95qR.ttf")) //load Kurri Island font from Fonts file
	{
		throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT"); //throw error if file was not found
	}
}

void EditorState::initText()
{
	//MousePosition For Debugging
	
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

void EditorState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT", gui::p2pY(71.6f, vm), gui::p2pX(11.f, vm), gui::p2pY(6.5f, vm), gui::calcCharSize(vm), "Quit");
	this->pmenu->addButton("SAVE", gui::p2pY(45.5f, vm), gui::p2pX(11.f, vm), gui::p2pY(6.5f, vm), gui::calcCharSize(vm), "Save");
	this->pmenu->addButton("LOAD", gui::p2pY(58.5f, vm), gui::p2pX(11.f, vm), gui::p2pY(6.5f, vm), gui::calcCharSize(vm), "Load");
}

void EditorState::initButtons()
{
	
}

void EditorState::initGui()
{


}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/Images/Tiles/tilesheet3.png");
}

void EditorState::initModes()
{
	this->modes.push_back(new DefaultEditorMode(this->stateData, this->tileMap, &this->editorStateData));
	this->modes.push_back(new EnemyEditorMode(this->stateData, this->tileMap, &this->editorStateData));

	this->activeMode = EditorModes::DEFAULT_DITOR_MODE;
}

EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initEditorStateData();
	this->initView();
	this->initFonts(); //initialise fonts
	this->initText();
	this->initKeybinds(); //initialise keybinds
	this->initPauseMenu();
	this->initButtons(); //initialise buttons
	this->initTileMap();
	this->initGui();

	this->initModes();
}

EditorState::~EditorState()
{
	//delete the buttons
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->pmenu;

	delete this->tileMap;

	

	for (size_t i = 0;i < this->modes.size(); i++)
	{
		delete this->modes[i];
	}
}

void EditorState::updateInput(const float & dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pausedState();
		else
			this->unpauseState();
	}
}

void EditorState::updateButtons()
{
	//updates all buttons in the state and handles their functionality
	for (auto &it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	
}

void EditorState::updateEditorInput(const float & dt)
{
	//Move view 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_UP"))))
	{
		this->view.move(0.f, -this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_DOWN"))))
	{
		this->view.move(0.f, this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_LEFT"))))
	{
		this->view.move(-this->cameraSpeed * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_CAMERA_RIGHT"))))
	{
		this->view.move(this->cameraSpeed * dt, 0.f);
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_UP"))))
	{
		if (this->activeMode < this->modes.size() - 1)
		{
			this->activeMode++;
		}
		else
		{
			std::cout << "ERROR::EDITORSTATE::CANNOT CHANGE MODE UP" << "\n";
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MODE_DOWN"))))
	{
		if (activeMode > 0)
		{
			this->activeMode--;
		}
		else
		{
			std::cout << "ERROR::EDITORSTATE::CANNOT CHANGE MODE DOWN" << "\n";
		}
	}

	

}

void EditorState::updateGui(const float& dt)
{

	
}

void EditorState::updatePausedMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();

	if (this->pmenu->isButtonPressed("SAVE"))
		this->tileMap->saveToFile("text.slmp");

	if (this->pmenu->isButtonPressed("LOAD"))
		this->tileMap->loadFromFile("text.slmp");
}

void EditorState::updateModes(const float & dt)
{

	this->modes[this->activeMode]->update(dt);
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions(&this->view); //update mouse position in menue state
	this->updateKeytime(dt);
	this->updateInput(dt); //update input in menu state

	if (!this->paused) //Unpaused
	{
		this->updateButtons();
		this->updateGui(dt);
		this->updateEditorInput(dt);
		this->updateModes(dt);
	}
	else //paused
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePausedMenuButtons();
	}

}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	//this->gamestate_btn->render(target);
	for (auto &it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget & target)
{
	/*if (!this->textureSelector->getActive())
	{
		target.setView(this->view);
		target.draw(this->selectorRect);
	}

	target.setView(this->window->getDefaultView());
	this->textureSelector->render(target);
	target.draw(this->sidebar);

	target.setView(this->view);
	target.draw(this->cursorText);*/
	
	
}

void EditorState::renderModes(sf::RenderTarget & target)
{
	this->modes[this->activeMode]->render(target);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target) //if there is nothing on the target
		target = this->window; //then set the target to the window

	target->setView(this->view);
	this->tileMap->render(*target, this->mousePosGrid, NULL, sf::Vector2f(), true);
	this->tileMap->renderDeffered(*target);

	target->setView(this->window->getDefaultView());
	this->renderButtons(*target); //render buttons

	this->renderGui(*target);

	this->renderModes(*target);
	if (this->paused) //Pause menu render
	{
		target->setView(this->window->getDefaultView());
		this->pmenu->render(*target);
	}
}