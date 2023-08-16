#pragma once

#include "Entity.h"
#include "../physics/PhysicsHandler.h"

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
			virtual void start() override;
			virtual void update() override;

		private:
			void populateAnimations();
			void jump(Game::Physics::PPhysicsHandler physicsHandler);

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

			/// <summary>
			/// The movement speed of this entity
			/// </summary>
			float movementSpeed;
		};

#pragma endregion

		typedef std::shared_ptr<Player> PPlayer;
	}
}