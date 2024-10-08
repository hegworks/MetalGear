#pragma once
class ScreenPrinter
{
public:
	void Print(Surface* screen, const char* prefix, double value, float2 pos, uint color = 0x00ff00)
	{
#ifdef _DEBUG
		char* text = new char[100];
		sprintf(text, "%s %f", prefix, value);
		int2 posInt = {static_cast<int>(pos.x), static_cast<int>(pos.y)};
		screen->Print(text, posInt.x, posInt.y, color);
#endif
	}

	void Print(Surface* screen, const char* prefix, int value, float2 pos, uint color = 0x00ff00)
	{
#ifdef _DEBUG
		char* text = new char[100];
		sprintf(text, "%s %i", prefix, value);
		int2 posInt = {static_cast<int>(pos.x), static_cast<int>(pos.y)};
		screen->Print(text, posInt.x, posInt.y, color);
#endif
	}

	void Print(Surface* screen, const char* prefix, const char* value, float2 pos, uint color = 0x00ff00)
	{
#ifdef _DEBUG
		char* text = new char[100];
		sprintf(text, "%s %s", prefix, value);
		int2 posInt = {static_cast<int>(pos.x), static_cast<int>(pos.y)};
		screen->Print(text, posInt.x, posInt.y, color);
#endif
	}

	void Print(Surface* screen, const char* prefix, const string& value, float2 pos, uint color = 0x00ff00)
	{
#ifdef _DEBUG
		char* text = new char[100];
		sprintf(text, "%s %s", prefix, value.c_str());
		int2 posInt = {static_cast<int>(pos.x), static_cast<int>(pos.y)};
		screen->Print(text, posInt.x, posInt.y, color);
#endif
	}
};