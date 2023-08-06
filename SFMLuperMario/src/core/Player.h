#pragma once

#include "Entity.h"

namespace Game
{
	namespace Core
	{
#define stringify(name) #name

#define PLAYER_SPRITE_SIZE 20.f

		class Player : public Entity
		{

#pragma region Animations enum

			/// <summary>
			/// All the available player animations
			/// </summary>
			enum PlayerAnimation
			{
				Idle,
				Move,
				Jump
			};

			const char* playerAnimToString[3] = {
				stringify(Idle),
				stringify(Move),
				stringify(Jump)
			};

#pragma endregion

#pragma region Methods

		public:
			virtual void update() override;

			Player(std::string name, sf::Vector2f pos, sf::Vector2f rot, sf::Vector2f scale);

		private:
			void populateAnimations();
			void jump();

#pragma endregion

#pragma region Attributes

		private:
			/// <summary>
			/// Duration of the player jump
			/// </summary>
			const float JUMP_DURATION = 0.5f;
			/// <summary>
			/// Is player jumping
			/// </summary>
			bool isJumping;
			/// <summary>
			/// Speed of the player jump
			/// </summary>
			float jumpSpeed;
			/// <summary>
			/// Current "flying" time since the beginning of jump
			/// </summary>
			float currentJumpTime;
		};

#pragma endregion
	}
}