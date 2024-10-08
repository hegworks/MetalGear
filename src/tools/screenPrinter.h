#pragma once
class ScreenPrinter
{
public:
#ifdef _DEBUG
	void Print(Surface* screen, const char* prefix, double value, float2 pos, uint color = 0x00ff00)
	{
		if(IsOutOfScreen(pos)) return;

		char* text = new char[100];
		sprintf(text, "%s %f", prefix, value);
		int2 posInt = {static_cast<int>(pos.x), static_cast<int>(pos.y)};
		screen->Print(text, posInt.x, posInt.y, color);
		delete[] text;
	}

	void Print(Surface* screen, const char* prefix, int value, float2 pos, uint color = 0x00ff00)
	{
		if(IsOutOfScreen(pos)) return;

		char* text = new char[100];
		sprintf(text, "%s %i", prefix, value);
		int2 posInt = {static_cast<int>(pos.x), static_cast<int>(pos.y)};
		screen->Print(text, posInt.x, posInt.y, color);
		delete[] text;
	}

	void Print(Surface* screen, const char* prefix, const char* value, float2 pos, uint color = 0x00ff00)
	{
		if(IsOutOfScreen(pos)) return;

		char* text = new char[100];
		sprintf(text, "%s %s", prefix, value);
		int2 posInt = {static_cast<int>(pos.x), static_cast<int>(pos.y)};
		screen->Print(text, posInt.x, posInt.y, color);
		delete[] text;
	}

	void Print(Surface* screen, const char* prefix, const string& value, float2 pos, uint color = 0x00ff00)
	{
		if(IsOutOfScreen(pos)) return;

		char* text = new char[100];
		sprintf(text, "%s %s", prefix, value.c_str());
		int2 posInt = {static_cast<int>(pos.x), static_cast<int>(pos.y)};
		screen->Print(text, posInt.x, posInt.y, color);
		delete[] text;
	}

	bool IsOutOfScreen(const float2 pos) const
	{
		if(pos.x < 0 || pos.x > SCRWIDTH || pos.y < 0 || pos.y > SCRHEIGHT)
		{
			return true;
		}
		return false;
	}
#endif
};