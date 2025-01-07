#include <assert.h>
#include <string>

#include "SFML/Graphics.hpp"
#include "Game.h"
#include "main.h"

using namespace sf;
using namespace std;




int main()
{

	// Create the main window
	RenderWindow window(VideoMode(GC::SCREEN_RES.x, GC::SCREEN_RES.y), "Homework 4");

	Textures tex;
	tex.LoadTextures();


	ObjectST ship;
	ship.type = ObjectST::ObjT::Ship;
	ship.LoadSpr(window);

	ObjectST aster;
	aster.type = ObjectST::ObjT::Aster;
	aster.LoadSpr(window);


	Clock clock;

	// Start the game loop 
	while (window.isOpen())
	{
		// Process events
		Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::TextEntered)
			{
				if (event.text.unicode == GC::ESCAPE_KEY)
					window.close();
			}
		}

		float elapsed = clock.getElapsedTime().asSeconds();
		clock.restart();

		// Clear screen
		window.clear();
		//Draw background
		tex.DrawBgnd(elapsed, window);

		//Ship
		ship.Update(window, elapsed);
		ship.Draw(window);

		//Aster
		aster.Update(window, elapsed);
		aster.Draw(window);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}