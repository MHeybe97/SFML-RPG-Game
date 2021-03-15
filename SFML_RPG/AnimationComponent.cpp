/**\file AnimationComponent.cpp*/
#include "stdafx.h"
#include "AnimationComponent.h"

//Constructor
AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite), textureSheet(texture_sheet), lastAnimation(NULL), priorityAnimation(NULL)
{

}

//Destructor
AnimationComponent::~AnimationComponent()
{
	for (auto &i : this->animations)
	{
		delete i.second;
	}
}



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
const bool & AnimationComponent::isDone(const std::string key) 
{
	return this->animations[key]->isDone();
}

//Functions
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