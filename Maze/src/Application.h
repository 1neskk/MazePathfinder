#pragma once

#include "stdafx.h"
#include "VertexArray.h"
#include "Button.h"
#include "GlobalVariables.h"
#include "Node.h"
#include "AStar.h"

class Application
{
public:
	Application();

	void Update();
	void Render();

	bool isRunning() const;
private:
	void startPathfinding();

	bool checkNode(Node& node) const;
	int getIndex(const int X, const int Y) const;
	sf::Vector2i raycast() const;
	void resetNode(Node& node);
	void resetPathNodes();
	void markPathNodes();
	
	void updateSingleNode(Node& node, const int index);
	void updateNodes();
	void initNodes();

	void updateButtons();
	void initButtons();

	void updateTexts();
	void initTexts();
	void initFont();

	void updateMousePosition();
	void updateDeltaTime();
	void updateFPS();
	void handleEvents();
	void initWindow();
private:
	sf::RenderWindow window;
	sf::VideoMode video_mode;
	sf::Event event;

	sf::Clock delta_clock;
	sf::Clock FPS_clock;
	sf::Font font;

	sf::Vector2f mouse_position;
	VertexArray vertex_array;

	std::map<const std::string, sf::Text> Texts;
	std::map<const std::string, Button> Buttons;

	std::vector<Node>nodes;

	Node* start_node = nullptr;
	Node* end_node = nullptr;

	float delta_time = 1.f / 60.f;
	unsigned int FPS = 0;
	float last_time = 0.f;
	bool diagonal = true;
};
