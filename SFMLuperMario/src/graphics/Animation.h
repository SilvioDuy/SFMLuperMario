#pragma once

#include <iostream>

namespace Game
{
	namespace Graphics
	{
		/// <summary>
		/// A single frame of a complete animation
		/// </summary>
		struct AnimationFrame
		{
			int xPos;
			int yPos;
			float duration;

			inline AnimationFrame(int x, int y, float frameDuration) : xPos(x), yPos(y), duration(frameDuration) {};
		};

		/// <summary>
		/// Representation of a single animation (es. Run, Idle, etc)
		/// </summary>
		struct Animation
		{
			std::vector<AnimationFrame> frames;
			bool loop;

			static Animation loadAnimation(std::string path);

			inline Animation(std::vector<AnimationFrame>& animFrames, bool loopAnim) : frames(animFrames), loop(loopAnim) {};
		};
	}
}