#pragma once

#include <iostream>

//Logs in console the message "x"
#define log(x) std::cout << x << std::endl

/// <summary>
/// Horizontal orientation of an object in the 2D space
/// </summary>
enum class HorizontalOrientation
{
	Left,
	Right
};