/**\file TextTagSystem.h*/
#pragma once

enum TAGTYPES { DEFAULT_TAG, NEGATIVE_TAG, POSITIVE_TAG, EXPERIANCE_TAG}; //!< enum for different text tags

/*!\class TextTagSystem
\brief a class for text tags that float above the player
*/
class TextTagSystem
{
private:
	/*!\class TextTag
\brief an inner class for the visual of the text tag
*/
	class TextTag
	{
	private: 
		sf::Text text; //!< text tag name
		float dirY; //!< direction tag will float in the y-axis
		float dirX; //!< direction tag will float in the x-axis
		float lifeTime; //!< how long the tag will be visible
		float speed; //!< how fast the tag floats accross the screen

	public:
		//Constructor
        //! Enemy TextTag constructor
	    /*!
	    \param font a sf::Font object - the tag font
		\param text a std::string object - tag description
		\param pos_x a float 
	   */
		TextTag(sf::Font& font, std::string text,
			float pos_x, float pos_y,
			float dir_x, float dir_y,
			sf::Color color,
			unsigned char_size,
			float lifetime, float speed)
		{
			this->text.setFont(font);
			this->text.setPosition(pos_x, pos_y);
			this->text.setFillColor(color);
			this->text.setCharacterSize(char_size);
			this->text.setString(text);

			this->dirX = dir_x;
			this->dirY = dir_y;
			this->lifeTime = lifetime;
			this->speed = speed;
		}

		TextTag(TextTag* tag, float pos_x, float pos_y, std::string str)
		{
			this->text = tag->text;
			this->text.setString(str);
			this->text.setPosition(pos_x, pos_y);

			this->dirX = tag->dirX;
			this->dirY = tag->dirY;
			this->lifeTime = tag->lifeTime;
			this->speed = tag->speed;
		}

		~TextTag()
		{

		}

		//Accessors
		inline const bool hasExperired() const { return this->lifeTime <= 0.f; }

		//Functions
		void update(const float& dt)
		{
			if (this->lifeTime > 0.f)
			{
				//Update the Tag
				this->lifeTime -= 100.f * dt;

				//Move the tag
				this->text.move(this->dirX * this->speed * dt, this->dirY * this->speed * dt);


			}

		}

		void render(sf::RenderTarget& target)
		{
			target.draw(this->text);
		}

	};

	sf::Font font;
	std::map<unsigned, TextTag*> tagTemplates;
	std::vector<TextTag*> tags;

	//Private Functions
	void initFonts(std::string font_file);
	void initVariables();
	void iniTagTemplates();

public:
	TextTagSystem(std::string font_file);
	virtual ~TextTagSystem();

	//Functions
	void addTextTag(const unsigned tag_type, const float pos_x, float pos_y, const std::string str, const std::string prefix, const std::string postfix );
	void addTextTag(const unsigned tag_type, const float pos_x, float pos_y, const int i, const std::string prefix, const std::string postfix);
	void addTextTag(const unsigned tag_type, const float pos_x, float pos_y, const float f, const std::string prefix, const std::string postfix);

	void update(const float &dt);
	void render(sf::RenderTarget & target);

};

