#include "Physics.h"
#include <iostream>

namespace gcore
{
	void Physics::Tick()
	{
		for (auto& coll : colliders)
		{
			if (coll->collisions.size() > 0)
				coll->collisions.clear();
		}

		/*float timeToElapse = 1 / tickrate;
		if (clock.getElapsedTime().asSeconds() < timeToElapse)
			return;*/

		for (auto& coll1 : colliders)
		{
			float coll1PosX = coll1->xPos + coll1->xOffset;
			float coll1PosY = coll1->yPos + coll1->yOffset;

			float c1XRight = coll1PosX + coll1->width;
			float c1YBottom = coll1PosY + coll1->height;

			for (auto& coll2 : colliders)
			{
				if (coll1 != coll2)
				{
					bool canCollide = std::count(coll1->targetColliders.begin(), coll1->targetColliders.end(), coll2->colliderType) > 0;
					bool alreadyCollided = std::count(coll1->collisions.begin(), coll1->collisions.end(), coll2) > 0;
					if (alreadyCollided || !canCollide)
						continue;

					float coll2PosX = coll2->xPos + coll2->xOffset;
					float coll2PosY = coll2->yPos + coll2->yOffset;

					float coll2LBX = coll2PosX;
					float coll2LBY = coll2PosY + coll2->height;

					float coll2RBX = coll2PosX + coll2->width;
					float coll2RBY = coll2PosY + coll2->height;

					float coll2RTX = coll2PosX + coll2->width;
					float coll2RTY = coll2PosY;

					float coll2CenterX = coll2PosX + coll2->width / 2;
					float coll2CenterY = coll2PosY + coll2->height / 2;

					bool collided = false;

					if (coll2PosX >= coll1PosX && coll2PosX <= c1XRight && coll2PosY >= coll1PosY && coll2PosY <= c1YBottom) // If left top corner intersects
						collided = true;
					else if (coll2LBX >= coll1PosX && coll2LBX <= c1XRight && coll2LBY >= coll1PosY && coll2LBY <= c1YBottom)
						collided = true;
					else if (coll2RBX >= coll1PosX && coll2RBX <= c1XRight && coll2RBY >= coll1PosY && coll2RBY <= c1YBottom)
						collided = true;
					else if (coll2RTX >= coll1PosX && coll2RTX <= c1XRight && coll2RTY >= coll1PosY && coll2RTY <= c1YBottom)
						collided = true;
					else if (coll2CenterX >= coll1PosX && coll2CenterX <= c1XRight && coll2CenterY >= coll1PosY && coll2CenterY <= c1YBottom)
						collided = true;

					if (collided)
					{
						coll1->collisions.push_back(coll2);
						coll2->collisions.push_back(coll1);
					}
				}
			}
		}

		clock.restart();
	}

	void Physics::AddCollider(gcore::Collider* coll)
	{
		colliders.push_back(coll);
	}

	void Physics::RemoveCollider(gcore::Collider* coll)
	{
		colliders.erase(std::remove(colliders.begin(), colliders.end(), coll), colliders.end());
	}

	void Physics::Render(sf::RenderWindow* window)
	{
		for (auto& coll : colliders)
		{
			sf::RectangleShape box(sf::Vector2f(coll->width, coll->height));
			box.setPosition(coll->xPos + coll->xOffset, coll->yPos + coll->yOffset);
			box.setOutlineThickness(4);
			box.setFillColor(sf::Color(0, 0, 0, 0));
			box.setOutlineColor(sf::Color(0, 255, 0));
			window->draw(box);
		}
	}
}