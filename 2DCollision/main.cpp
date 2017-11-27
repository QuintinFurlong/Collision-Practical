#include <iostream>
#include <SFML/Graphics.hpp>
#define TINYC2_IMPL
#include <tinyc2.h>
#include <AnimatedSprite.h>
#include <Player.h>
#include <Input.h>
#include <Debug.h>
#include "Main.h"

using namespace std;

int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

	// Load a sprite to display
	sf::Texture sprite_sheet;
	if (!sprite_sheet.loadFromFile("assets\\grid.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}

	// Load a mouse texture to display
	sf::Texture mouse_texture;
	sf::Texture mouse_texture1;
	if (!mouse_texture.loadFromFile("assets\\mouse.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}
	if (!mouse_texture1.loadFromFile("assets\\mouse1.png")) {
		DEBUG_MSG("Failed to load file");
		return EXIT_FAILURE;
	}
	//0 = aabb 1 = circle 2 = ray
	npcShape = 0;
	//0 = aabb 1 = circle 2 = ray 3 = capsule 4 = polygon
	mouseShape = 0;

	// Setup a mouse Sprite
	aabb_mouse.setTexture(mouse_texture);

	//Setup mouse AABB
	aabb_mouse_info.min = c2V(aabb_mouse.getPosition().x, aabb_mouse.getPosition().y);
	aabb_mouse_info.max = c2V(aabb_mouse.getGlobalBounds().width, aabb_mouse.getGlobalBounds().width);


	// Setup Players AABB
	setupNpc();

	// Setup the Player

	// Collision result
	int result = 0;
	
	// Start the game loop
	while (window.isOpen())
	{
		// Move Sprite Follow Mouse
		aabb_mouse.setPosition(window.mapPixelToCoords(sf::Mouse::getPosition(window)));

		// Update mouse AABB
		aabb_mouse_info.min = c2V(aabb_mouse.getPosition().x, aabb_mouse.getPosition().y);
		aabb_mouse_info.max = c2V(aabb_mouse.getPosition().x + aabb_mouse.getGlobalBounds().width, aabb_mouse.getPosition().y + aabb_mouse.getGlobalBounds().width);

		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				// Close window : exit
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					mouseShape--;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					mouseShape++;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					npcShape++;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					npcShape--;
				}
				break;
			default:
				break;
			}
		}

		if (npcShape < 0)
			npcShape = 2;
		else if (npcShape > 2)
			npcShape = 0;

		if (mouseShape < 0)
			mouseShape = 4;
		else if (mouseShape > 4)
			mouseShape = 0;

		// Check for collisions
		switch (npcShape)
		{
		case 0:
			switch (mouseShape)
			{
			case 0:
			result = c2AABBtoAABB(aabb_npc_info, aabb_mouse_info);
			cout << ((result != 0) ? ("Collision") : "") << endl;
			if (result){
				aabb_mouse.setTexture(mouse_texture);
			}
			else {
				aabb_mouse.setTexture(mouse_texture1);
			}
			break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				break;
			}
			if (result) {
				aabb_npc.setTexture(&mouse_texture);
			}
			else {
				aabb_npc.setTexture(&mouse_texture1);
			}
		break;
		case 1:
			switch (mouseShape)
			{
			case 0:
				result = c2CircletoAABB(circle_npc_info, aabb_mouse_info);
				cout << ((result != 0) ? ("Collision") : "") << endl;
				if (result) {
					aabb_mouse.setTexture(mouse_texture);
				}
				else {
					aabb_mouse.setTexture(mouse_texture1);
				}
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				break;
			}
			if (result) {
				circle_npc.setFillColor(sf::Color::Red);
			}
			else {
				circle_npc.setFillColor(sf::Color::Green);
			}
			break;
		case 2:
			switch (mouseShape)
			{
			case 0:
				result = c2AABBtoAABB(aabb_mouse_info, aabb_npc_info);
				cout << ((result != 0) ? ("Collision") : "") << endl;
				if (result) {
					aabb_mouse.setTexture(mouse_texture);
				}
				else {
					aabb_mouse.setTexture(mouse_texture1);
				}
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				break;
			}
			if (result) {
				aabb_npc.setTexture(&mouse_texture);
			}
			else {
				aabb_npc.setTexture(&mouse_texture1);
			}
			break;
		default:
			break;
		}

		// Clear screen
		window.clear();

		switch (npcShape)
		{
		case 0:
			window.draw(aabb_npc);
			break;
		case 1:
			window.draw(circle_npc);
			break;
		case 2:
			window.draw(ray_npc);
			break;
		default:
			break;
		}
		window.draw(aabb_mouse);

		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
};

void setupNpc()
{
	aabb_npc.setSize(sf::Vector2f(100,100));
	aabb_npc.setPosition(sf::Vector2f(200, 200));
	circle_npc.setRadius(50);
	circle_npc.setPosition(sf::Vector2f(200, 200));
	ray_npc.append(sf::Vertex(sf::Vector2f(0, 50)));
	ray_npc.append(sf::Vertex(sf::Vector2f(100, 50)));

	aabb_npc_info.min = c2V(aabb_npc.getPosition().x, aabb_npc.getPosition().y);
	aabb_npc_info.max = c2V(aabb_npc.getPosition().x + aabb_npc.getGlobalBounds().width, aabb_npc.getPosition().y + aabb_npc.getGlobalBounds().height);

	circle_npc_info.p = c2V(circle_npc.getPosition().x + circle_npc.getRadius(), circle_npc.getPosition().y + circle_npc.getRadius());
	circle_npc_info.r = circle_npc.getRadius();

	ray_npc_info.p = c2V(ray_npc[0].position.x, ray_npc[0].position.y);
}