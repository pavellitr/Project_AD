#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"


namespace Engine_mod {
	class Engine
	{
	public:
		Engine(sf::RenderWindow* window);
		void start();

	private:
		sf::RenderWindow* m_Window;


		
		

		void input();
		void update();
		void draw();


	};




}