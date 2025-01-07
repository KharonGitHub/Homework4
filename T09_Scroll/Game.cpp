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



void ObjectST::LoadSpr(sf::RenderWindow& window)
{
	//init Ship
	static Texture shipTex;
	if (!shipTex.loadFromFile("data/ship.png"))
	{
		assert(false);
	}
	shipSpr.setTexture(shipTex);
	sf::IntRect texSR = shipSpr.getTextureRect();

	//init Aster
	static Texture asterTex;
	if (!asterTex.loadFromFile("data/asteroid.png"))
	{
		assert(false);
	}
	asterSpr.setTexture(asterTex);
	sf::IntRect texAR(0, 0, 96, 96);

	switch (type)
	{
	case ObjectST::ObjT::Ship:

		shipSpr.setOrigin(texSR.width / 2.f, texSR.height / 2.f);
		shipSpr.setScale(0.1f, 0.1f);
		shipSpr.setRotation(90);
		shipSpr.setPosition(window.getSize().x * 0.05f, window.getSize().y / 2.f);

		break;

	case ObjectST::ObjT::Aster:

		asterSpr.setTextureRect(texAR);
		asterSpr.setOrigin(texAR.width / 2.f, texAR.height / 2.f);
		asterSpr.setScale(0.5f, 0.5f);
		asterSpr.setRotation(90);
		asterSpr.setPosition(window.getSize().x * 0.05f, window.getSize().y / 2.f);

		break;
	default:
		break;
	}
}

void ObjectST::Update(sf::RenderWindow& window, float elapsed)
{
	Vector2u screenSz = window.getSize();
	Vector2f shipPos = shipSpr.getPosition();
	Vector2f asterPos = asterSpr.getPosition();
	
	if (Keyboard::isKeyPressed(Keyboard::Up))

	{
		if (shipPos.y > (screenSz.y * 0.05f))
			shipPos.y -= shipSpeed * elapsed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		if (shipPos.y < (screenSz.y * 0.95f))
			shipPos.y += shipSpeed * elapsed;
	}

	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		if (shipPos.x > (screenSz.x * 0.05f))
			shipPos.x -= shipSpeed * elapsed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		if (shipPos.x < (screenSz.x * 0.95f))
			shipPos.x += shipSpeed * elapsed;
	}

	shipSpr.setPosition(shipPos);
	asterSpr.setPosition(asterPos);
}


void ObjectST::Draw(sf::RenderWindow& window)
{
	switch (type)
	{
	case ObjectST::ObjT::Ship:
		window.draw(shipSpr);
		break;
	case ObjectST::ObjT::Aster:
		window.draw(asterSpr);
		break;
	default:
		break;
	}
}
