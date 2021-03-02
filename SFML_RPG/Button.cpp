#include "Button.h"



Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color)
{
	this->buttonState = BTN_IDLE; //set button on idle

	this->shape.setPosition(sf::Vector2f(x, y)); //set button position
	this->shape.setSize(sf::Vector2f(width, height)); //set button size

	this->shape.setFillColor(idle_Color); //set idle color to be first

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
		this->text.setFillColor(this->textIdleColor);
		break;
	case BTN_HOVER:
		this->shape.setFillColor(this->hoverColor); //if button hovered then set hover color
		this->text.setFillColor(this->textHoverColor);
		break;
	case BTN_ACTIVE:
		this->shape.setFillColor(this->activeColor); //if button is pressed then set active color
		this->text.setFillColor(this->textActiveColor);
		break;
	default:
		this->shape.setFillColor(sf::Color::Red); //set default color to red
		this->text.setFillColor(sf::Color::Blue);
		break;

	}
}

void Button::render(sf::RenderTarget * target)
{
	target->draw(this->shape); //render button
	target->draw(this->text); //render button text
}
