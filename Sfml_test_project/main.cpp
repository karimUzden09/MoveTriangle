#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
using namespace sf;
class Player {
public:
	float w, h, dx, dy, x, y, speed;
	int dir, playerScore, health;
	bool life, isMove, isSelect;//добавили переменные состояния движения и выбора объекта 
	Texture texture;
	RectangleShape sprite{ Vector2f(50,50) };
	Player(float X, float Y, float W, float H) {
		dir = 0; speed = 0; playerScore = 0; health = 100; dx = 0; dy = 0;
		life = true; isMove = false; isSelect = false;
		w = W; h = H;
		sprite.setPosition(55, 55);
		sprite.setRotation(45);
		x = X; y = Y;
	}
	void update(float time)
	{
		switch (dir)
		{
		case 0: dx = speed; dy = 0; break;
		case 1: dx = -speed; dy = 0; break;
		case 2: dx = 0; dy = speed; break;
		case 3: dx = 0; dy = -speed; break;
		}

		x += dx * time;
		y += dy * time;
		if (!isMove) speed = 0;
		sprite.setPosition(x, y);

	}
};




int main()
{
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	Player rectangle(250, 250, 136, 74);
	int tempX = 0;
	int tempY = 0;
	float distansce = 0;
	float dX = 0;
	float dY = 0;


	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
		sf::Vector2f pos = window.mapPixelToCoords(pixelPos);
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
				if (event.key.code==sf::Mouse::Left)
				{
					if (rectangle.sprite.getGlobalBounds().contains(pos.x,pos.y))
					{
						rectangle.sprite.setFillColor(sf::Color::Green);
						rectangle.isSelect = true;
					}
				}

				if (rectangle.isSelect)
					if (event.type == sf::Event::MouseButtonPressed)
						if (event.key.code == sf::Mouse::Right)
						{
							rectangle.isMove = true;
							rectangle.isSelect = false;
							rectangle.sprite.setFillColor(sf::Color::White);
							tempX = pos.x;
							tempY = pos.y;
						}
								
		}

		if (rectangle.isMove)
		{
			distansce = sqrt((tempX - rectangle.x) * (tempX - rectangle.x) + (tempY - rectangle.y) * (tempY - rectangle.y));
			if (distansce > 2) {

				rectangle.x += 0.1 * time * (tempX - rectangle.x) / distansce;
				rectangle.y += 0.1 * time * (tempY - rectangle.y) / distansce;
			}
			else { rectangle.isMove = false; std::cout << "priehali\n"; }
		}
		rectangle.update(time);
		//window.clear();
		window.draw(rectangle.sprite);
		//window.draw(shaper);
		window.display();
	}

}