/**\file AnimationComponent.h*/
#pragma once

/*!\class Animation
\brief a class to handle all the animations in the game
*/
class AnimationComponent
{
private:

	/*!\class Animation
	\brief Inner class that updates the animation for the games spritesheet 
	*/

	class Animation
	{
	public:
		//Variables
		sf::Sprite& sprite; //!< the sprite to be animated
		sf::Texture& textureSheet; //!< the spritesheet for the animation
		float animationTimer; //!< the animation timer for how fast the animation should
		float speed; //!< Speed of the animation
		float timer; //!< animation timer
		bool done; //!<check to see if animation is done
		int width; //!< width of the frame
		int height; //!< height of the frame
		sf::IntRect startRect; //!< what frame the animation will start on the spritesheet
		sf::IntRect currentRect; //!< what frame the animation is currently at;
		sf::IntRect endRect; //!< what frame the animation will end at

		//! Animation class constructor
		/*!
		\param sprite a sprite object - the sprites the game uses for animation
		\param texture_sheet object- the texture sheet for the animation
		\param animation_timer a float - how fast the animation will loop through the texture sheet
		\param start_frame_x an int - the frame the animation starts in the x-axis
		\param start_frame_y an int - the frame the animation starts in the y-axis
		\param frames_x an int - the animation frames in the x-axis
		\param frames_y an int - the animation frames in the y-axis
		\param width an int - the width of the frame
		\param height an int - the height of the frame
		*/
		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, 
			float animation_timer, 
			int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
			: sprite(sprite), textureSheet(texture_sheet), 
			animationTimer(animation_timer), timer(0.f), done(false), 
			width(width), height(height)
		{
			//Set First frame 
			this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
			//Set Current frame
			this->currentRect = this->startRect;
			//Set the last frame
			this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);
			//Set the texture to be used in the animation
			this->sprite.setTexture(this->textureSheet, true);
			//Set the sprite texture to startRect
			this->sprite.setTextureRect(this->startRect);
		}

		//Accessors
		//! Accessor function to see if an animation is
		/*!
		\
		*/
		const bool& isDone() const
		{
			return this->done;
		}

		//Functions
		//! Function to play animation
		/*!
		\param dt a float - to update function using delta-time
		*/
		const bool& play(const float& dt)
		{
			//Update Timer
			this->done = false;
			this->timer += 10.f * dt;
			if (this->timer >= this->animationTimer)
			{
				//reset timer
				this->timer = 0.f;

				//Animate
				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else //reset
				{
					this->currentRect.left = this->startRect.left;
					this->done = true;
				}

				this->sprite.setTextureRect(this->currentRect);
			}
			return this->done;
		}

		//! Function to play animation
		/*!
		\param dt a float - to update function using delta-time
		\param mod_percent - to modify the animation timer
		*/
		const bool& play(const float& dt, float mod_percent)
		{
			//Update Timer
			if (mod_percent < 0.5f)
				mod_percent = 0.5f;

			 this->done = false;
			this->timer += mod_percent * 100.f * dt;
			if (this->timer >= this->animationTimer)
			{
				//reset timer
				this->timer = 0.f;

				//Animate
				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else //reset
				{
					this->currentRect.left = this->startRect.left;
					this->done = true;
				}

				this->sprite.setTextureRect(this->currentRect);
			}
			return this->done;
		}
		
		//reset the animation
		void reset()
		{
			this->timer = this->animationTimer;
			this->currentRect = this->startRect;
			
		}
	};

	sf::Sprite& sprite; //!< the sprite to be animated
	sf::Texture& textureSheet; //!< the spritesheet for the animation
	std::map<std::string, Animation*> animations; //!< a std::map that contains string for animations and an object for the animation class
	Animation* lastAnimation; //!< an animation object to reset to previouse animation
	Animation* priorityAnimation; //!< the animation to be prioritised

public:
	
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet); //!<Constructor
	virtual ~AnimationComponent(); //!<Destructor
    
	//Accessors
	const bool& isDone(const std::string key); //!< return the animation that is done

	
	void addAnimation(const std::string key, 
		float animation_timer,
		int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height); //!< add an animation

	const bool& play(const std::string key, const float& dt, const bool priority = false); //!< play an animation when moving
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false); //!<play an animation with modifiers when moving

};

