#include "stdafx.h"
#include "GraphicsSettings.h"



GraphicsSettings::GraphicsSettings()
{
	this->title = "DEFAULT";
	this->resolution = sf::VideoMode::getDesktopMode();
	this->fullscreen = false;
	this->verticalSync = false;
	this->frameRateLimit = 120;
	this->contextSettings.antialiasingLevel = 0;
	this->videoModes = sf::VideoMode::getFullscreenModes();
}


GraphicsSettings::~GraphicsSettings()
{
}

//Functions
void GraphicsSettings::saveToFile(const std::string path)
{
	std::ofstream ofs(path);

	//check if file is open
	if (ofs.is_open())
	{
		ofs << this->title; //get the window name title from window.ini
		ofs << this->resolution.width << " " << this->resolution.height; //get the window height and width from window.ini
		ofs << this->fullscreen;
		ofs << this->frameRateLimit; //get the framerate limit from ini
		ofs << this->verticalSync; //check whether vsync is enabled 
		ofs << this->contextSettings.antialiasingLevel;
	}

	ofs.close();
}
void GraphicsSettings::loadFromFile(const std::string path)
{
	std::ifstream ifs(path); //read from window.ini file in the config folder

	//check if file is open
	if (ifs.is_open())
	{
		std::getline(ifs, this->title); //get the window name title from window.ini
		ifs >> this->resolution.width >> this->resolution.height; //get the window height and width from window.ini
		ifs >> this->fullscreen;
		ifs >> this->frameRateLimit; //get the framerate limit from ini
		ifs >> this->verticalSync; //check whether vsync is enabled 
		ifs >> this->contextSettings.antialiasingLevel;
	}

	ifs.close();
}
