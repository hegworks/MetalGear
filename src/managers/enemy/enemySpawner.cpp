#include "precomp.h"
#include "enemySpawner.h"

#include "src/audio/audioManager.h"
#include "src/human/enemy/enemyDelayedSpawn/enemyDelayedSpawn.h"
#include "src/human/enemy/enemyRed/enemyRed.h"
#include "src/tile/levelMap/levelMaps.h"
#include "src/tile/tileSet.h"

EnemySpawner::EnemySpawner(Surface* pScreen, LevelMaps* pLevelMaps, SpriteStorage* pSpriteStorage, Player* pPlayer, BulletManager* pBulletManager, AudioManager* pAudioManager)
{
	m_screen = pScreen;
	m_levelMaps = pLevelMaps;
	m_spriteStorage = pSpriteStorage;
	m_player = pPlayer;
	m_bulletManager = pBulletManager;
	m_audioManager = pAudioManager;

	m_relieveSprite = new Sprite(new Surface("assets/graphics/relieve.png"), 1);
}

EnemySpawner::~EnemySpawner()
{
	for(int i = 0; i < m_enemyCount; ++i)
	{
		delete m_enemies[i];
	}
	delete m_relieveSprite;
}

void EnemySpawner::Tick(const float deltaTime)
{
	if(m_isInRoom8 && !m_hasAlertedAllInRoom)
	{
		if(m_walkAnimationState == AnimationState::Started || m_walkAnimationState == AnimationState::Playing)
		{
			PlayWalkAnimation(deltaTime);
		}
		if(m_walkAnimationState == AnimationState::Finished)
		{
			m_walkAnimationState = AnimationState::NotStarted;
		}

		CheckRelieveAndComeBackRoom8(deltaTime);

		if(m_relieveAnimationState == AnimationState::Started || m_relieveAnimationState == AnimationState::Playing)
		{
			PlayRelieveSpriteAnimation(deltaTime);
		}
		if(m_relieveAnimationState == AnimationState::Finished)
		{
			CheckRelieveHideTimer(deltaTime);
		}
	}


	if(!m_hasAlertedAllInRoom)
	{
		bool isOneEnemyAlerted = false;
		for(int i = 0; i < m_enemyCount; ++i)
		{
			if(m_enemies[i]->ReportIsAlerted())
			{
				isOneEnemyAlerted = true;
			}
		}
		for(int i = 0; i < m_enemyCount; ++i)
		{
			if(isOneEnemyAlerted)
			{
				m_enemies[i]->OneEnemyAlarmedReport();
			}
		}
		if(isOneEnemyAlerted)
		{
			ResetRoom8State();
			m_hasAlertedAllInRoom = true;
			m_audioManager->EnemyAlerted();
		}
	}

	if(!m_hasReportedAllEnemiesDeadOnce && m_hasAlertedAllInRoom)
	{
		bool areAllEnemiesDead = true;
		for(int i = 0; i < m_enemyCount; ++i)
		{
			if(m_enemies[i]->GetEnemyState() != EnemyState::Dead)
			{
				areAllEnemiesDead = false;
			}
		}
		if(areAllEnemiesDead)
		{
			m_audioManager->AllEnemiesDied();
			m_hasReportedAllEnemiesDeadOnce = true;
		}
	}


	for(int i = 0; i < m_enemyCount; ++i)
	{
		m_enemies[i]->Tick(deltaTime);
	}
}

void EnemySpawner::Draw() const
{
	for(int i = 0; i < m_enemyCount; ++i)
	{
		m_enemies[i]->Draw();
	}

	if(m_relieveScale > 0)
	{
		m_relieveSprite->DrawScaled(static_cast<int>(RELIEVE_SPRITE_POS.x),
									static_cast<int>(RELIEVE_SPRITE_POS.y),
									static_cast<int>(static_cast<float>(m_relieveSprite->GetWidth()) * m_relieveScale),
									static_cast<int>(static_cast<float>(m_relieveSprite->GetHeight()) * m_relieveScale),
									m_screen);
	}
}

#ifdef _DEBUG
void EnemySpawner::DrawColliders() const
{
	for(int i = 0; i < m_enemyCount; ++i)
	{
		m_enemies[i]->DrawColliders();
	}
}
#endif

bool EnemySpawner::Spawn()
{
	const int currentLevelId = m_levelMaps->GetCurrentLevelId();
	const bool isExceptionLevel4 = currentLevelId == 4;
	const bool isPlayerCloserToBottom = m_player->GetPosition().y > SCRHEIGHT / 2;
	bool skipLeftSpawn = false;
	bool skipRightSpawn = false;

	if(isExceptionLevel4)
	{
		skipLeftSpawn = !isPlayerCloserToBottom;
		skipRightSpawn = !skipLeftSpawn;
	}

	const bool isEnemyRedLevel8 = currentLevelId == 8;
	const bool isEnemyDelayedSpawnLevel = currentLevelId == 5 || currentLevelId == 9;

	m_enemyCount = 0;

	int** levelColls = m_levelMaps->GetLevelColliderPointers();
	for(int i = 0; i < LEVELMAP_ROWS; i++)
	{
		for(int j = 0; j < LEVELMAP_COLS; j++)
		{
			int tileIndex = levelColls[i][j];
			if(tileIndex != -1)
			{
				const TileType tileType = m_levelMaps->GetTileType(levelColls[i][j]);

				if(tileType == TileType::ESD || tileType == TileType::ESL || tileType == TileType::ESR || tileType == TileType::ESU)
				{
					Direction spawnDir;
					switch(tileType)
					{
						case TileType::ESD:
							spawnDir = Direction::Down;
							break;
						case TileType::ESL:
							spawnDir = Direction::Left;
							break;
						case TileType::ESR:
							spawnDir = Direction::Right;
							break;
						case TileType::ESU:
							spawnDir = Direction::Up;
							break;
						default:
							throw exception("Invalid tile type");
					}
					// this if below, is to skip one of the enemies in level4 based on player's position
					if(!isExceptionLevel4 ||
					   (spawnDir == Direction::Up || spawnDir == Direction::Down) ||
					   (spawnDir == Direction::Left && !skipLeftSpawn) ||
					   spawnDir == Direction::Right && !skipRightSpawn)
					{
						float2 spawnPos = {static_cast<float>(j * TILESET_TILEWIDTH), static_cast<float>(i * TILESET_TILEHEIGHT - 96)};
						if(isEnemyRedLevel8)
						{
							m_enemies[m_enemyCount] = new EnemyRed(m_screen, m_levelMaps, m_spriteStorage, spawnPos, spawnDir, m_player, m_bulletManager, m_audioManager);
						}
						else if(isEnemyDelayedSpawnLevel)
						{
							m_enemies[m_enemyCount] = new EnemyDelayedSpawn(m_screen, m_levelMaps, m_spriteStorage, spawnPos, spawnDir, m_player, m_bulletManager, m_audioManager);
						}
						else
						{
							m_enemies[m_enemyCount] = new Enemy(m_screen, m_levelMaps, m_spriteStorage, spawnPos, spawnDir, m_player, m_bulletManager, m_audioManager);
						}
						m_enemyCount++;
						if(m_enemyCount >= MAX_ENEMIES)
						{
							return true;
						}
					}
				}
			}
		}
	}
	return m_enemyCount > 0;
}

void EnemySpawner::PlayerPunchReported() const
{
	for(int i = 0; i < m_enemyCount; ++i)
	{
		m_enemies[i]->PlayerPunchReported();
	}
}

void EnemySpawner::RoomChanged()
{
	for(int i = 0; i < m_enemyCount; i++)
	{
		delete m_enemies[i];
	}

	m_enemyCount = 0;
	m_hasAlertedAllInRoom = false;
	m_hasReportedAllEnemiesDeadOnce = false;
	m_isInRoom8 = m_levelMaps->GetCurrentLevelId() == 8;
	ResetRoom8State();
}

void EnemySpawner::CheckRelieveAndComeBackRoom8(float deltaTime)
{
	switch(m_room8State)
	{
		case Room8State::OnGuard:
			if(m_walkAnimationState == AnimationState::Playing)
			{
				break;
			}

			if(m_relieveTimer < RELIEVE_TIME)
			{
				m_relieveTimer += deltaTime;
				break;
			}
			m_relieveTimer = 0;

			StartRelieveSpriteAnimation();
			m_comeBackTimer = 0;
			m_room8State = Room8State::Relieve;

			break;

		case Room8State::Relieve:
			if(m_walkAnimationState == AnimationState::Playing)
			{
				break;
			}

			if(m_comeBackTimer < COMEBACK_TIME)
			{
				m_comeBackTimer += deltaTime;
				break;
			}
			m_comeBackTimer = 0;

			m_relieveTimer = 0;
			for(int i = 0; i < m_enemyCount; ++i)
			{
				m_enemies[i]->ComeBack(i);
			}
			StartWalkAnimation();
			m_room8State = Room8State::OnGuard;

			break;

		default:
			throw exception("invalid Room8State");
	}
}

void EnemySpawner::PlayRelieveSpriteAnimation(float deltaTime)
{
	if(m_relieveAnimationState == AnimationState::Finished)
	{
		return;
	}

	if(m_relieveAnimationTimer >= RELIEVE_ANIMATION_TIME)
	{
		m_relieveAnimationState = AnimationState::Finished;
		m_relieveAnimationTimer = 0;
		m_relieveHideTimer = 0;
		StartWalkAnimation();
		return;
	}

	m_relieveAnimationState = AnimationState::Playing;

	m_relieveScale = lerp(0, 1, m_relieveAnimationTimer / RELIEVE_ANIMATION_TIME);

	m_relieveAnimationTimer += deltaTime;
	if(m_relieveAnimationTimer > RELIEVE_ANIMATION_TIME)
	{
		m_relieveAnimationTimer = RELIEVE_ANIMATION_TIME;
		m_relieveScale = 1;
	}
}

void EnemySpawner::StartRelieveSpriteAnimation()
{
	m_relieveAnimationTimer = 0;
	m_relieveScale = 0;
	m_relieveAnimationState = AnimationState::Started;
}

void EnemySpawner::CheckRelieveHideTimer(float deltaTime)
{
	if(m_relieveHideTimer < RELIEVE_HIDE_TIME)
	{
		m_relieveHideTimer += deltaTime;
		return;
	}
	m_relieveHideTimer = RELIEVE_HIDE_TIME;

	m_relieveScale = 0;
	m_relieveAnimationState = AnimationState::NotStarted;
	for(int i = 0; i < m_enemyCount; ++i)
	{
		m_enemies[i]->Relieve();
	}
}

void EnemySpawner::PlayWalkAnimation(float deltaTime)
{
	if(m_walkAnimationState == AnimationState::Finished)
	{
		return;
	}

	m_walkAnimationState = AnimationState::Playing;

	m_walkTimer += deltaTime;
	if(m_walkTimer > WALK_TIME)
	{
		m_walkTimer = 0;
		m_comeBackTimer = 0;
		m_relieveTimer = 0;
		m_walkAnimationState = AnimationState::Finished;
	}
}

void EnemySpawner::StartWalkAnimation()
{
	m_walkTimer = 0;
	m_walkAnimationState = AnimationState::Started;
}

void EnemySpawner::ResetRoom8State()
{
	m_relieveScale = 0;
	m_relieveTimer = 0;
	m_relieveHideTimer = 0;
	m_comeBackTimer = 0;
	m_room8State = Room8State::OnGuard;
	m_walkAnimationState = AnimationState::NotStarted;
	m_relieveAnimationState = AnimationState::NotStarted;
}

