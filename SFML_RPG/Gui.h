/**\file Gui.h*/
#pragma once

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE}; //enum for button states

namespace gui
{
	const float p2pX(const float perc, const sf::VideoMode& vm);
	const float p2pY(const float perc, const sf::VideoMode& vm);
	const unsigned calcCharSize( const sf::VideoMode& vm, const unsigned modifier = 60);


	class Button
	{
	private:
		short unsigned buttonState; //button states
		short unsigned id;

		sf::RectangleShape shape; //button shape
		sf::Font* font; //button font
		sf::Text text; //button text

		sf::Color textIdleColor;
		sf::Color textHoverColor;
		sf::Color textActiveColor;

		sf::Color idleColor; // button idle-color
		sf::Color hoverColor; //button hover-color
		sf::Color activeColor; //button active-color

		sf::Color outlineidleColor; // button idle-color
		sf::Color outlinehoverColor; //button hover-color
		sf::Color outlineactiveColor; //button active-color

	public:
		Button(float x, float y, float width, float height,
			sf::Font* font, std::string text, unsigned character_size,
			sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
			sf::Color idle_Color, sf::Color hover_Color, sf::Color active_Color,
			sf::Color outline_idle_Color = sf::Color::Transparent, sf::Color outline_hover_Color = sf::Color::Transparent, sf::Color outline_active_Color = sf::Color::Transparent,
			short unsigned id = 0); //constructor
		~Button(); //destructor

		//Accessors
		const bool isPressed() const; //check if button is pressed
		const std::string getText() const;
		const short unsigned& getId() const;

		//Modifiers
		void setText(const std::string text);
		void setId(const short unsigned Id);

		//functions
		void update(const sf::Vector2i& mousePosWindow); //update buttons
		void render(sf::RenderTarget& target); //render buttons
	};


	class DropDownList
	{
	private:
		float keytime;
		float keytimeMax;

		sf::Font& font;
		gui::Button* activeElement;
		std::vector<gui::Button*> list;
		bool showList;
	public:
		DropDownList(float x, float y, float width, float height, sf::Font& font, std::string list[], unsigned nrOfElements, unsigned default_index = 0);
		~DropDownList();

		//Accessors
		const unsigned short& getActiveElementId() const;
		//functions
		const bool getKeytime();
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt); //update buttons
		void render(sf::RenderTarget& target); //render buttons
	};


	class TextureSelector
	{
	private:
		float gridSize;
		bool active;
		bool hidden;
		float keytime;
		float keytimeMax;
		gui::Button* hide_btn;
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePosGrid;
		sf::IntRect textureRect;
		

	public:
		TextureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture* texture_sheet, sf::Font& font, std::string text);
		~TextureSelector();

		//Accessors
		const bool& getActive() const;
		const sf::IntRect& getTextureRect() const;
		const bool getKeytime();

		//Functions
		void updateKeytime(const float& dt);
		void update(const sf::Vector2i& mousePosWindow, const float& dt);
		void render(sf::RenderTarget& target);
	};

	class ProgressBar
	{
	private:
		std::string BarString;
		sf::Text BarText;
		sf::RectangleShape BarBack;
		sf::RectangleShape BarInner;
		float BarMaxWidth;
		int BarmaxValue;

	public:
		ProgressBar(float x, float y, float width, float height, 
			sf::Color BarInner_colour, unsigned character_size,
			sf::VideoMode& vm, sf::Font* font = NULL);
		~ProgressBar();

		//Accessors

		//Modifiers

		//Functions
		void update(const int current_value, const int max_value);
		void render(sf::RenderTarget& target);
	};
}
