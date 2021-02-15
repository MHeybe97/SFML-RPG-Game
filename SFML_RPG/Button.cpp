#include "Button.h"



Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE; //set button on idle

	this->shape.setPosition(sf::Vector2f(x, y)); //set button position
	this->shape.setSize(sf::Vector2f(width, height)); //set button size

	this->font = font; //button font
	this->text.setFont(*this->font); //set button font
	this->text.setString(text); //set as the text
	this->text.setFillColor(sf::Color::White); //set the font color
	this->text.setCharacterSize(20); //set the character size
	this->text.setPosition( 
		this->shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
		this->shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
	); //set the text on the button

	this->idleColor = idleColor; //mouse idle color
	this->hoverColor = hoverColor; //mouse hover color
	this->activeColor = activeColor; //mouse active color

	this->shape.setFillColor(this->idleColor); //set idle color to be first

}


Button::~Button()
{
}

//Accessors
const bool Button::isPressed() const
{
	//check if button has been pressed
	if (this->buttonState == BTN_ACTIVE)
		return true;
	return false;
}


//Functions

void Button::update(const sf::Vector2f mousePos)
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
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor); //if button hovered then set hover color
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor); //if button is pressed then set active color
		break;
	default:
		this->shape.setFillColor(sf::Color::Red); //set default color to red
		break;

	}
}

void Button::render(sf::RenderTarget * target)
{
	target->draw(this->shape); //render button
	target->draw(this->text); //render button text
}
