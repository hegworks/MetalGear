// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#pragma once
class TextRenderer;
class Radio;
class PixelPerfectCollisionChecker;
class LoseScreen;
class WinScreen;
class GameStateManager;
class BulletManager;
class EnemySpawner;
class Enemy;
class SpriteStorage;
class RoomChangeStorage;
class RoomFinder;
class Player;
class LevelMaps;
class TileSet;

namespace Tmpl8
{

class TileMap;

class Game : public TheApp
{
public:
	// game flow methods
	void Init();
	void Tick(float deltaTime);
	void Shutdown() { /* implement if you want to do something on exit */ }
	// input handling
	void MouseUp(int) { /* implement if you want to detect mouse button presses */ }
	void MouseDown(int) { /* implement if you want to detect mouse button presses */ }
	void MouseMove(int x, int y) { mousePos.x = x, mousePos.y = y; }
	void MouseWheel(float) { /* implement if you want to handle the mouse wheel */ }
	void KeyUp(int glfwKey);
	void KeyDown(int glfwKey);
	// data members
	int2 mousePos;

private:
	TileSet* m_tileSet = nullptr;
	TileMap* m_tileMap = nullptr;
	LevelMaps* m_levelMaps = nullptr;
	Player* m_player = nullptr;
	RoomFinder* m_roomFinder = nullptr;
	RoomChangeStorage* m_roomChangeStorage = nullptr;
	SpriteStorage* m_spriteStorage = nullptr;
	EnemySpawner* m_enemySpawner = nullptr;
	BulletManager* m_bulletManager = nullptr;
	GameStateManager* m_gameStateManager = nullptr;
	WinScreen* m_winScreen = nullptr;
	LoseScreen* m_loseScreen = nullptr;
	PixelPerfectCollisionChecker* m_pixelPerfectCollisionChecker = nullptr;
	TextRenderer* m_fontTextRenderer = nullptr;
	Radio* m_radio = nullptr;

	/* this function here and in this form (static constexpr), has the best place and form in my opinion.
	 * because first this is the game.h and is/will not be included in any other file.
	 * and second, this is a function which is being passed as an argument to another function (constructor of TextRenderer). so it really needs to be the same across all instances of this class.
	 * we have the same thing but a bit different in the radio.cpp
	 * and third, game.h exists through the whole session anyway, and this function is the same.
	 */
	static constexpr int FontTextRendererCharToIndex(char c)
	{
		if(c >= 'a' && c <= 'z') return c - 'a'; // 0-25
		if(c >= 'A' && c <= 'Z') return c - 'A'; // 0-25
		if(c >= '0' && c <= '9') return c - '0' + 26; // 26-35
		if(c == '*') return 35 + 1;
		if(c == '>') return 35 + 2;
		if(c == ',') return 35 + 3;
		if(c == '.') return 35 + 4;
		if(c == ' ') return 35 + 5;
		throw exception("character not supported");
	}
};

} // namespace Tmpl8