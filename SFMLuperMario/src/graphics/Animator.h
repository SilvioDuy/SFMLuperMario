#pragma once

#include <SFML/Graphics.hpp>
#include "Animation.h"

namespace Game
{
	namespace Graphics
	{
		/// <summary>
		/// Handles the animations of a game entity
		/// </summary>
		class Animator
		{
#pragma region Methods

		public:

			/// <summary>
			/// Plays the current selected animation on a sprite
			/// </summary>
			/// <param name="spr">Subject sprite</param>
			void animateSprite(sf::Sprite& spr);

			/// <summary>
			/// Changes the animation that animator will play
			/// </summary>
			/// <param name="animationId"></param>
			void changeAnimation(int animationId);

			/// <summary>
			/// Adds an animation to the animations list
			/// </summary>
			/// <param name="anim"></param>
			void addAnimation(Animation anim);

			inline Animator() : sheetRows(0), sheetCols(0), spriteSize(0), currentAnimationId(0), currentFrame(0), currentFrameT(0) {}
			Animator(int rows, int cols, int size);

			~Animator();

		private:


#pragma endregion

#pragma region Attributes

		public:

			/// <summary>
			/// Number of rows of the current sprite sheet
			/// </summary>
			int sheetRows;
			/// <summary>
			/// Number of columns of the current sprite sheet
			/// </summary>
			int sheetCols;
			/// <summary>
			/// Size in pixels of a single sprite in the sheet
			/// </summary>
			int spriteSize;

		private:

			/// <summary>
			/// Id of the animations played
			/// </summary>
			int currentAnimationId;

			/// <summary>
			/// List of all available animations
			/// </summary>
			std::vector<Animation> animations;

			/// <summary>
			/// Current frame of the playing animation
			/// </summary>
			int currentFrame;

			/// <summary>
			/// Elapsed time since the beginnig of the current animation frame
			/// </summary>
			float currentFrameT;

#pragma endregion

		};
	}
}