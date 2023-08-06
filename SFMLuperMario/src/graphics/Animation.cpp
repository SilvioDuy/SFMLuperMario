#include <fstream>
#include <json.hpp>
#include "Animation.h"
#include "../utils/Utils.h"
#include "../utils/AssetsUtils.h"

using namespace Game::Graphics;

Animation Animation::loadAnimation(std::string animName)
{
	using json = nlohmann::json;

	std::string animPath = ANIMATIONS_DIR + animName + ANIM_EXTENSION;
	std::ifstream f(animPath);
	std::vector<AnimationFrame> frames;

	if (!f)
	{
		log("[Warning] Can't find Animation file for " + animName);
		return Animation(frames, false);
	}

	json data = json::parse(f);

	bool loop = data.value("loop", false);
	auto& fileFrames = data["frames"];

	for (auto& elem : fileFrames)
	{
		int xPos = elem.value("xPos", 0);
		int yPos = elem.value("yPos", 0);
		float duration = elem.value("duration", 0.f);

		frames.push_back(AnimationFrame(xPos, yPos, duration));
	}

	f.close();

	return Animation(frames, loop);
}