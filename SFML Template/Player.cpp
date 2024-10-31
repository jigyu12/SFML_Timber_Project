#include "stdafx.h"
#include "Player.h"
#include "SceneDev1.h"	
#include "SceneDev2.h"	

Player::Player(PlayerSelect select, const std::string& name)
	: GameObject(name), playerSelect(select)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Player::SetSide(Sides s)
{
	side = s;

	if (side == Sides::Left)
	{
		SetScale({ -1.f, 1.f });
	}
	else if (side == Sides::Right)
	{
		SetScale({ 1.f, 1.f });
	}

	sf::Vector2f newPos = position + localPosPlayer[(int)s];
	spritePlayer.setPosition(newPos);
	spriteAxe.setPosition(newPos + localPosAxe);
	spriteRip.setPosition(newPos + localRipAxe);
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	SetSide(side);
}

void Player::OnDie()
{
	isAlive = false;
	isChppoing = false;


}

void Player::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	spritePlayer.setScale(this->scale);

	sf::Vector2f axeScale = this->scale;
	axeScale.x *= -1.f;
	spriteAxe.setScale(axeScale);

	sf::Vector2f axeRip = this->scale;
	axeRip.x = abs(axeScale.x);
	spriteRip.setScale(axeRip);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (preset != Origins::Custom)
	{
		origin = Utils::SetOrigin(spritePlayer, preset);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	spritePlayer.setOrigin(origin);
}

void Player::Init()
{
	spritePlayer.setTexture(TEXTURE_MGR.Get(texIdPlayer));
	SetOrigin(Origins::BC);

	spriteAxe.setTexture(TEXTURE_MGR.Get(texIdAxe));
	spriteAxe.setOrigin(originAxe);

	spriteRip.setTexture(TEXTURE_MGR.Get(texIdRip));
	Utils::SetOrigin(spriteRip, Origins::BC);
}

void Player::Reset()
{
	sfxChop.setBuffer(SOUNDBUFFER_MGR.Get(sbIdChop));

	spritePlayer.setTexture(TEXTURE_MGR.Get(texIdPlayer));
	spriteAxe.setTexture(TEXTURE_MGR.Get(texIdAxe));
	spriteRip.setTexture(TEXTURE_MGR.Get(texIdRip));

	isAlive = true;
	isChppoing = false;
	SetPosition(position);
	SetScale({ 1.f, 1.f });

	if(playerSelect == PlayerSelect::Player1)
		SetSide(Sides::Right);
	else if (playerSelect == PlayerSelect::Player2)
		SetSide(Sides::Left);
}


void Player::Release()
{
}


void Player::Update(float dt)
{
	if (!isAlive)
		return;

	Player1Update(dt);
	Player2Update(dt);
}

void Player::Draw(sf::RenderWindow& window)
{
	if (isAlive)
	{
		window.draw(spritePlayer);
		if (isChppoing)
		{
			window.draw(spriteAxe);
		}
	}
	else
	{
		window.draw(spriteRip);
	}
}

void Player::SetSceneGame(Scene* scene)
{
	sceneGame = scene;
}
void Player::Player1Update(float dt)
{
	if (playerSelect != PlayerSelect::Player1)
		return;

	if (InputMgr::GetKeyDown(sf::Keyboard::A))
	{
		isChppoing = true;
		SetSide(Sides::Left);

		if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev1)
			dynamic_cast<SceneDev1*>(sceneGame)->OnChop(Sides::Left);
		else if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev2)
			dynamic_cast<SceneDev2*>(sceneGame)->OnChop(Sides::Left);

		sfxChop.play();
	}

	if (InputMgr::GetKeyUp(sf::Keyboard::A))
	{
		isChppoing = false;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::D))
	{
		isChppoing = true;
		SetSide(Sides::Right);

		if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev1)
			dynamic_cast<SceneDev1*>(sceneGame)->OnChop(Sides::Right);
		else if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev2)
			dynamic_cast<SceneDev2*>(sceneGame)->OnChop(Sides::Right);
	}

	if (InputMgr::GetKeyUp(sf::Keyboard::D))
	{
		isChppoing = false;
	}
}

void Player::Player2Update(float dt)
{
	if (playerSelect != PlayerSelect::Player2)
		return;

	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		isChppoing = true;
		SetSide(Sides::Left);

		if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev1)
			dynamic_cast<SceneDev1*>(sceneGame)->OnChop(Sides::Left);
		else if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev2)
			dynamic_cast<SceneDev2*>(sceneGame)->OnChop(Sides::Left);

		sfxChop.play();
	}

	if (InputMgr::GetKeyUp(sf::Keyboard::Left))
	{
		isChppoing = false;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		isChppoing = true;
		SetSide(Sides::Right);

		if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev1)
			dynamic_cast<SceneDev1*>(sceneGame)->OnChop(Sides::Right);
		else if (SCENE_MGR.GetCurrentSceneId() == SceneIds::Dev2)
			dynamic_cast<SceneDev2*>(sceneGame)->OnChop(Sides::Right);
	}

	if (InputMgr::GetKeyUp(sf::Keyboard::Right))
	{
		isChppoing = false;
	}
}
