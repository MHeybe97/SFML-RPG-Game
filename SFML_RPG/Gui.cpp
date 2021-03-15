/**\file Gui.cpp*/
#include "stdafx.h"
#include "Gui.h"


gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color,
	sf::Color outline_idle_Color, sf::Color outline_hover_Color, sf::Color outline_active_Color,
	short unsigned id )
{
	this->buttonState = BTN_IDLE; //set button on idle
	this->id = id;

	this->shape.setPosition(sf::Vector2f(x, y)); //set button position
	this->shape.setSize(sf::Vector2f(width, height)); //set button size
	this->shape.setFillColor(idle_Color); //set idle color to be first
	this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_Color);

	this->font = font; //button font
	this->text.setFont(*this->font); //set button font
	this->text.setString(text); //set as the text
	this->text.setFillColor(text_idle_color); //set the font color
	this->text.setCharacterSize(character_size); //set the character size
	this->text.setPosition( 
		this->shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	); //set the text on the button

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_Color; //mouse idle color
	this->hoverColor = hover_Color; //mouse hover color
	this->activeColor = active_Color; //mouse active color

	this->outlineidleColor = outline_idle_Color; 
	this->outlinehoverColor = outline_hover_Color; 
	this->outlineactiveColor = outline_active_Color; 

	

}


gui::Button::~Button()
{
}

//Accessors
const bool gui::Button::isPressed() const
{
	//check if button has been pressed
	if (this->buttonState == BTN_ACTIVE)
		return true;
	return false;
}

const std::string gui::Button::getText() const
{
	return this->text.getString();

}

const short unsigned & gui::Button::getId() const
{
	return this->id;
}

//Modifiers
void gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void gui::Button::setId(const short unsigned Id)
{
	this->id;
}


//Functions

void gui::Button::update(const sf::Vector2f& mousePos)
{
	//update booleans for hover and pressed
	
	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
	case BTN_IDLE:
		this->shape.setFillColor(this->idleColor); //if button idle then set idle color
		this->text.setFillColor(this->textIdleColor);
		this->shape.setOutlineColor(this->outlineidleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor); //if button hovered then set hover color
		this->text.setFillColor(this->textHoverColor);
		this->shape.setOutlineColor(this->outlinehoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor); //if button is pressed then set active color
		this->text.setFillColor(this->textActiveColor);
		this->shape.setOutlineColor(this->outlineactiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red); //set default color to red
		this->text.setFillColor(sf::Color::Blue);
		this->shape.setOutlineColor(sf::Color::Green);
		break;

	}
}

void gui::Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape); //render button
	target.draw(this->text); //render button text
}


//DropDownList =================================================================================================================

gui::DropDownList::DropDownList(float x, float y, float width, float height, 
	sf::Font& font, std::string list[], 
	unsigned nrOfElements, unsigned default_index)
	: font(font), showList(false),  keytimeMax(1.f), keytime(1.f)
{
	//unsigned nrOfElements = sizeof(list) / sizeof(std::string);

	this->activeElement = new gui::Button(
		x, y, width, height,
		&this->font, list[default_index], 14,
		sf::Color(255, 255, 255, 150), sf::Color(255, 255, 250, 200), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 250, 200), sf::Color(255, 255, 250, 255), sf::Color(20, 20, 20, 50)
	);

	for (size_t i = 0; i < nrOfElements; i++)
	{
		this->list.push_back(
			new gui::Button(
				x, y + ((i) * height), width, height,
				&this->font, list[i], 14,
				sf::Color(255, 255, 255, 150), sf::Color(255, 255, 250, 255), sf::Color(20, 20, 20, 50),
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200),
				sf::Color(255, 255, 250, 0), sf::Color(255, 255, 250, 0), sf::Color(20, 20, 20, 0),
				i
			)
		);
	}	

	
}

gui::DropDownList::~DropDownList()
{
	delete this->activeElement;
	for (size_t i = 0; i < this->list.size(); i++)
	{
		delete this->list[i];
	}
}



//Accessors
const unsigned short & gui::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

const bool gui::DropDownList::getKeytime()
{
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}
	return false;
}

//Functions
void gui::DropDownList::updateKeytime(const float& dt)
{
	if (this->keytime < this->keytimeMax)
		this->keytime += 10.f * dt;
}

void gui::DropDownList::update(const sf::Vector2f & mousePos, const float& dt)
{
	this->updateKeytime(dt);

	this->activeElement->update(mousePos);

	//Show and hide the list
	if (this->activeElement->isPressed() && this->getKeytime())
	{
		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}
	if (this->showList)
	{
		for (auto &i : this->list)
		{
			i->update(mousePos);

			if (i->isPressed() && this->getKeytime())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}

void gui::DropDownList::render(sf::RenderTarget & target)
{
	this->activeElement->render(target);
	if (this->showList)
	{
		for (auto &i : this->list)
		{
			i->render(target);
		}
	}

}

