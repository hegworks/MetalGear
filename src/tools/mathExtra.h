#pragma once

class MathExtra
{
public:
	static double Map(const double inputStart, const double inputEnd, const double outputStart, const double outputEnd, const double input)
	{
		if(input <= inputStart)
		{
			return outputStart;
		}
		if(input >= inputEnd)
		{
			return outputEnd;
		}
		const double slope = 1.0 * (outputEnd - outputStart) / (inputEnd - inputStart);
		return  outputStart + slope * (input - inputStart);
	}
};
