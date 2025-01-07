#include <string>
#include <assert.h>
#include <sstream>

#include "Game.h"

using namespace std;
using namespace sf;

void Textures::LoadTextures()
{
	stringstream ss;
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		ss.str("");
		ss << "data/backgroundLayers/mountains01_00" << i << ".png";

		Texture& t = Get(static_cast<Tex>(i));
		if (!t.loadFromFile(ss.str()))
			assert(false);
		t.setRepeated(true);
	}
}

void Textures::ScrollBgnd(Tex texId, sf::RenderWindow& window, int inc)
{
	sf::Sprite spr(Get(texId));
	sf::IntRect scroll = spr.getTextureRect();
	scroll.left += inc;
	spr.setTextureRect(scroll);
	spr.setScale(window.getSize().x / (float)scroll.width, window.getSize().y / (float)scroll.height);
	spr.setPosition(0, 0);
	window.draw(spr);
}


void Textures::DrawBgnd(float elapsed, sf::RenderWindow& window)
{
	//background order of sprites
	Textures::Tex ids[MAX_TEXTURES]{
		Textures::BACK7,
		Textures::BACK5,
		Textures::BACK4,
		Textures::BACK3,
		Textures::BACK2,
		Textures::BACK1,
		Textures::BACK0,
		Textures::BACK6,
	};

	float spd = GC::BACK_SPEED * elapsed;
	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		bgndSpds[i] += spd;
		ScrollBgnd(ids[i], window, (int)bgndSpds[i]);
		spd += GC::BACK_LAYER_SPEEDINC * elapsed;
	}
}




void Asteroid::LoadAster(sf::RenderWindow& window)
{
	static Texture asterTex;
	if (!asterTex.loadFromFile("data/asteroid.png"))
	{
		assert(false);
	}


	//Draw Aster
	asterSpr.setTexture(asterTex);
	IntRect texR(0, 0, 96, 96);
	asterSpr.setTextureRect(texR);
	asterSpr.setOrigin(texR.width / 2.f, texR.height / 2.f);
	asterSpr.setScale(0.5f, 0.5f);
	asterSpr.setRotation(90);
	asterSpr.setPosition(window.getSize().x * 0.05f, window.getSize().y / 2.f);
}

void Asteroid::MoveAster(sf::RenderWindow& window, float elapsed)
{

}


void Asteroid::DrawAster(sf::RenderWindow& window)
{
	window.draw(asterSpr);
}




void ShipST::LoadShip(sf::RenderWindow& window)
{
	static Texture shipTex;
	if (!shipTex.loadFromFile("data/ship.png"))
	{
		assert(false);
	}

	//Draw Ship
	shipSprite.setTexture(shipTex);
	IntRect texR = shipSprite.getTextureRect();
	shipSprite.setOrigin(texR.width / 2.f, texR.height / 2.f);
	shipSprite.setScale(0.1f, 0.1f);
	shipSprite.setRotation(90);
	shipSprite.setPosition(window.getSize().x * 0.05f, window.getSize().y / 2.f);
}

void ShipST::MoveShip(sf::RenderWindow& window, float elapsed)
{
	Vector2u screenSz = window.getSize();
	Vector2f pos = shipSprite.getPosition();

	if (Keyboard::isKeyPressed(Keyboard::Up))

	{
		if (pos.y > (screenSz.y * 0.05f))
			pos.y -= SPEED * elapsed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		if (pos.y < (screenSz.y * 0.95f))
			pos.y += SPEED * elapsed;
	}

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (pos.x > (screenSz.x * 0.05f))
			pos.x -= SPEED * elapsed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (pos.x < (screenSz.x * 0.95f))
			pos.x += SPEED * elapsed;
	}

	shipSprite.setPosition(pos);
}

void ShipST::DrawShip(sf::RenderWindow& window)
{
	window.draw(shipSprite);
}