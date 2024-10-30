#pragma once

// the reason that this is a global inline is the same reason why every function in the tmpl8math.h is a global inline.
// it is doing a very simple math calculation and does not have any stored state, variable or any other dependencies.
// so it is safe and efficient to have it like this.
/// <summary>
/// this is a helper function to map a number from one range to another
/// </summary>
inline double map_numbers(const double inputStart, const double inputEnd, const double outputStart, const double outputEnd, const double input)
{
	if(input <= inputStart)
	{
		return outputStart;
	}
	if(input >= inputEnd)
	{
		return outputEnd;
	}
	// this part of the calculation, after carefully studying, is taken from https://stackoverflow.com/a/5732390
	const double slope = 1.0 * (outputEnd - outputStart) / (inputEnd - inputStart);
	return  outputStart + slope * (input - inputStart);
}