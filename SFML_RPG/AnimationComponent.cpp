/**\file AnimationComponent.cpp*/
#include "stdafx.h"
#include "AnimationComponent.h"

//Constructor
//! AnimationComponent class constructor
	/*!
	\param sprite a sf::Sprite object - the sprite to be animated
	\param texture_sheet a sf::Texture object - the texture sheet used for the animation
	*/
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite), textureSheet(texture_sheet), lastAnimation(NULL), priorityAnimation(NULL)
{

}

//Destructor
//! AnimationComponent class destructor
	/*!
	\brief delete animations
	*/
AnimationComponent::~AnimationComponent()
{
	for (auto &i : this->animations)
	{
		delete i.second;
	}
}

//Functions
	//! Function to to add an animation
	/*!
	\param key a std::string - the name of the animation
	\param animation_timer a float - how quick to loop through the spritesheet
	\param start_frame_x an int - the frame to start on the x-axis
	\param start_frame_y an int - the frame to start on the y-axis
	\param frames_x an int - frames in the x-axis
	\param frames_y an int - frames in the y-axis
	\param width an int - the width of the frame
	\param height an int - the height of the frame
	*/
void AnimationComponent::addAnimation(
	const std::string key, 
	float animation_timer,
	int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height)
{
	this->animations[key] = new Animation(
		this->sprite, this->textureSheet,
		animation_timer,
		start_frame_x, start_frame_y, frames_x, frames_y, width, height);
}

//Accessors
//! Function to get the animation that is done
	/*!
	\param key a std::string - gets the particular animation that is done
	*/
const bool & AnimationComponent::isDone(const std::string key) 
{
	return this->animations[key]->isDone();
}

//Functions
//! Function to play priority animations
	/*!
	\param key a std::string - the name of the animation
	\param dt a float - delta time 
	\return a boolean if it's a priority animation
	*/
const bool& AnimationComponent::play(const std::string key, const float & dt, const bool priority)
{
	
	if (this->priorityAnimation) //if there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			//remove when priority animation is done
			if (this->animations[key]->play(dt))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else //else play animation if no other priority animation is set
	{
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
		this->animations[key]->play(dt);
	}
	
	return this->animations[key]->isDone();
}

//! Function to play priority animations
	/*!
	\param key a std::string - the name of the animation
	\param dt a float - delta time
	\param modifier a float - animation modifier
	\param modifier_max a float - the modifier maximum value
	\return a boolean if it's a priority animation
	*/
const bool& AnimationComponent::play(const std::string key, const float & dt, const float& modifier, const float& modifier_max, const bool priority)
{
	if (this->priorityAnimation) //if there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}
			//remove when priority animation is done
			if (this->animations[key]->play(dt, abs(modifier / modifier_max)))
			{
				this->priorityAnimation = NULL;
			}

			
		}
	}
	else //else play animation if no other priority animation is set
	{
		//if this is a priority animation then set it.
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dt, abs(modifier / modifier_max));
	}

	return this->animations[key]->isDone();
}