/**\file PlayerGUI.h*/
#include "stdafx.h"
#include "PlayerGUI.h"


void PlayerGUI::initFonts()
{
	this->font.loadFromFile("Fonts/KurriIslandItaPersonalBold-d95qR.ttf");
}

void PlayerGUI::initLevelBar()
{
	float width = gui::p2pX(2.1f, this->vm);
	float height = gui::p2pY(3.9f, this->vm);
	float x = gui::p2pX(1.5f, this->vm);
	float y = gui::p2pY(2.6f, this->vm);

	this->levelBarBack.setSize(sf::Vector2f(width, height));
	this->levelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelBarBack.setPosition(x, y);

	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(gui::calcCharSize(this->vm, 120));
	this->levelBarText.setPosition(
		this->levelBarBack.getPosition().x + gui::p2pX(0.73f, this->vm), 
		this->levelBarBack.getPosition().y + gui::p2pY(0.65f, this->vm));
}

void PlayerGUI::initEXPBar()
{
	float width = gui::p2pX(14.6f, this->vm);
	float height = gui::p2pY(2.6f, this->vm);
	float x = gui::p2pX(1.4f, this->vm);
	float y = gui::p2pY(7.8f, this->vm);

	this->expBarMaxWidth = width;

	this->expBarBack.setSize(sf::Vector2f(width, height));
	this->expBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->expBarBack.setPosition(x, y);

	this->expBarInner.setSize(sf::Vector2f(width, height));
	this->expBarInner.setFillColor(sf::Color(20, 20, 250, 200));
	this->expBarInner.setPosition(this->expBarBack.getPosition());

	this->expBarText.setFont(this->font);
	this->expBarText.setCharacterSize(gui::calcCharSize(this->vm, 170));
	this->expBarText.setPosition(
		this->expBarBack.getPosition().x + gui::p2pX(0.73f,this->vm), 
		this->expBarBack.getPosition().y + gui::p2pY(0.45f,this->vm));
}

void PlayerGUI::initHPBar()
{
	float width = gui::p2pX(14.6f, this->vm);
	float height = gui::p2pY(3.9f, this->vm);
	float x = gui::p2pX(1.4f, this->vm);
	float y = gui::p2pY(11.7f, this->vm);

	this->hpBarMaxWidth = width;

	this->hpBarText.setFont(this->font);

	this->hpBarBack.setSize(sf::Vector2f(width, height));
	this->hpBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->hpBarBack.setPosition(x, y);

	this->hpBarInner.setSize(sf::Vector2f(width, height));
	this->hpBarInner.setFillColor(sf::Color(250, 20, 20, 200));
	this->hpBarInner.setPosition(this->hpBarBack.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setCharacterSize(gui::calcCharSize(this->vm, 120));
	this->hpBarText.setPosition(
		this->hpBarInner.getPosition().x + gui::p2pX(0.73f, this->vm),
		this->hpBarInner.getPosition().y + gui::p2pY(0.65f, this->vm)
	);

}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm)
	: vm(vm)
{
	this->player = player;

	this->initFonts();
	this->initLevelBar();
	this->initEXPBar();
	this->initHPBar();
}


PlayerGUI::~PlayerGUI()
{
}

void PlayerGUI::updateLevelBar()
{
	this->levelBarString = std::to_string(this->player->getAttributeComponent()->level);
	this->levelBarText.setString(this->levelBarString);
}

void PlayerGUI::updateEXPBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->exp) / static_cast<float>(this->player->getAttributeComponent()->expNext);

	this->expBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->expBarMaxWidth * percent)),
			this->expBarInner.getSize().y
		)

	);

	this->expBarString = std::to_string(this->player->getAttributeComponent()->exp) + " " + std::to_string(this->player->getAttributeComponent()->expNext);
	this->expBarText.setString(this->expBarString);
}

//Functions
void PlayerGUI::updateHPBar()
{
	float percent = static_cast<float>(this->player->getAttributeComponent()->hp) / static_cast<float>(this->player->getAttributeComponent()->hpMax);

	this->hpBarInner.setSize(
		sf::Vector2f(
			static_cast<float>(std::floor(this->hpBarMaxWidth * percent)), 
			this->hpBarInner.getSize().y
		)

	);

	this->hpBarString = std::to_string(this->player->getAttributeComponent()->hp) + " " + std::to_string(this->player->getAttributeComponent()->hpMax);
	this->hpBarText.setString(this->hpBarString);
}


void PlayerGUI::update(const float & dt)
{
	this->updateLevelBar();
	this->updateEXPBar();
	this->updateHPBar();
}

void PlayerGUI::renderLevelBar(sf::RenderTarget & target)
{
	target.draw(this->levelBarBack);
	target.draw(this->levelBarText);
}

void PlayerGUI::renderEXPBAR(sf::RenderTarget & target)
{
	target.draw(this->expBarBack);
	target.draw(this->expBarInner);
	target.draw(this->expBarText);
}

void PlayerGUI::renderHPBar(sf::RenderTarget & target)
{
	target.draw(this->hpBarBack);
	target.draw(this->hpBarInner);
	target.draw(this->hpBarText);
}

void PlayerGUI::render(sf::RenderTarget & target)
{
	this->renderLevelBar(target);
	this->renderEXPBAR(target);
	this->renderHPBar(target);
}
