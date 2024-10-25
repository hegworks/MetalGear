// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"

#include "audio/audioManager.h"
#include "audio/AudioPlayer.h"
#include "collider/pixelPerfect/pixelPerfectCollisionChecker.h"
#include "human/player/player.h"
#include "managers/bullet/bulletManager.h"
#include "managers/enemy/enemySpawner.h"
#include "managers/gamescreen/loseScreen.h"
#include "managers/gamescreen/winScreen.h"
#include "managers/gameState/gameStateManager.h"
#include "managers/hud/hudManager.h"
#include "managers/room/roomChangeStorage.h"
#include "managers/room/roomFinder.h"
#include "radio/radio.h"
#include "spriteStorage/spriteStorage.h"
#include "textRenderer/textRenderer.h"
#include "tile/tileMap.h"
#include "tile/tileSet.h"

void Game::Init()
{
	m_audioPlayer = new AudioPlayer();
	m_audioManager = new AudioManager(m_audioPlayer);
	m_hudManager = new HudManager(screen);
	m_tileSet = new TileSet();
	m_tileMap = new TileMap(screen, m_tileSet);
	m_roomChangeStorage = new RoomChangeStorage;
	m_roomFinder = new RoomFinder(m_roomChangeStorage);
	m_levelMaps = new LevelMaps();
	m_spriteStorage = new SpriteStorage();
	m_player = new Player(screen, m_levelMaps, m_spriteStorage, m_audioManager, m_hudManager);
	m_pixelPerfectCollisionChecker = new PixelPerfectCollisionChecker(screen);
	m_bulletManager = new BulletManager(screen, m_levelMaps, m_player, m_spriteStorage, m_pixelPerfectCollisionChecker);
	m_winScreen = new WinScreen();
	m_loseScreen = new LoseScreen();
	m_fontTextRenderer = new TextRenderer(screen, "assets/graphics/font.png", 41, 1, 4, FontTextRendererCharToIndex);
	m_radio = new Radio(screen, m_fontTextRenderer, m_audioManager);
	m_enemySpawner = new EnemySpawner(screen, m_levelMaps, m_spriteStorage, m_player, m_bulletManager, m_audioManager);
	m_gameStateManager = new GameStateManager(screen, m_winScreen, m_loseScreen, m_player, m_radio, m_roomFinder, m_levelMaps, m_enemySpawner, m_tileMap, m_bulletManager, m_audioManager, m_hudManager);
}

void Game::Tick(const float deltaTime)
{
	m_gameStateManager->Tick(deltaTime);
	m_gameStateManager->Draw();
#ifdef _DEBUG
	m_gameStateManager->DrawColliders();
#endif
}

void Game::KeyDown(const int glfwKey)
{
	m_gameStateManager->KeyDown(glfwKey);
}

void Game::KeyUp(int glfwKey)
{
	m_gameStateManager->KeyUp(glfwKey);
}
