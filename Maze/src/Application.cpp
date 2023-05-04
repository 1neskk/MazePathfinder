#include "stdafx.h"
#include "Application.h"

Application::Application()
{
	this->initWindow();
	this->initFont();
	this->initTexts();
	this->initButtons();
	this->initNodes();
}

void Application::Render()
{
	this->window.clear();

	this->window.draw(this->vertex_array);

	for (auto& t : this->Texts)
		this->window.draw(t.second);

	for (auto& b : this->Buttons)
		this->window.draw(b.second);

	this->window.display();

	this->updateDeltaTime();
	this->updateFPS();
}

void Application::Update()
{
	this->handleEvents();
	this->updateMousePosition();
	this->updateButtons();
	this->updateTexts();
	this->updateNodes();
}

bool Application::isRunning() const
{
	return this->window.isOpen();
}

void Application::startPathfinding()
{
	constexpr AStar pathfinder;
	this->resetPathNodes();
	pathfinder.startAStar(this->nodes, this->last_time, this->diagonal, this->start_node, this->end_node);
	this->markPathNodes();
}

void Application::updateSingleNode(Node& node, const int index)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (this->checkNode(node))
			return;

		if (!node.walkable)
			return;

		node.walkable = false;

		if (this->start_node != nullptr)
		{
			this->resetNode(*this->start_node);
			this->vertex_array.setNodeColor(this->start_node->x, this->start_node->y, this->vertex_array.default_color);
		}
		this->start_node = &node;
		this->resetPathNodes();
		this->vertex_array.setNodeColor(index, sf::Color::Green);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (this->checkNode(node))
			return;

		if (!node.walkable)
			return;

		node.walkable = false;

		if (this->end_node != nullptr)
		{
			this->resetNode(*this->end_node);
			this->vertex_array.setNodeColor(this->end_node->x, this->end_node->y, this->vertex_array.default_color);
		}
		this->end_node = &node;
		this->resetPathNodes();
		this->vertex_array.setNodeColor(index, sf::Color::Red);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->checkNode(node))
			return;

		node.walkable = false;
		this->vertex_array.setNodeColor(index, sf::Color::Black);
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (this->start_node != nullptr && node == *this->start_node)
			this->start_node = nullptr;
		else if (this->end_node != nullptr && node == *this->end_node)
			this->end_node = nullptr;

		this->resetNode(node);
	}
}

bool Application::checkNode(Node& node) const
{
	if (this->start_node == nullptr && this->end_node == nullptr)
		return false;
	if (this->end_node != nullptr && this->start_node != nullptr) 
		return node == *this->end_node || node == *this->start_node;
	if (this->start_node != nullptr)
		return node == *this->start_node;
	if (this->end_node != nullptr)
		return node == *this->end_node;
	return false;
}

int Application::getIndex(const int X, const int Y) const
{
	return Y * SIZE_X + X;
}

sf::Vector2i Application::raycast() const
{
	const auto mouse_position = static_cast<sf::Vector2i>(this->mouse_position);

	if (mouse_position.x < 0 || mouse_position.x >= width || mouse_position.y < 0 || mouse_position.y >= SIZE_Y * NODE_SIZE)
		return { -1, -1 };

	const int X = mouse_position.x / NODE_SIZE;
	const int Y = mouse_position.y / NODE_SIZE;

	return { X, Y };
}

void Application::resetNode(Node& node)
{
	node.f_cost		= -1;
	node.g_cost		= -1;
	node.h_cost		= -1;
	node.walkable	= true;
	node.path		= false;
	node.parent		= nullptr;

	this->vertex_array.setNodeColor(node.x, node.y, this->vertex_array.default_color);
}

void Application::resetPathNodes()
{
	for (auto& n : this->nodes)
		if (n.path)
		{
			const int index = this->getIndex(n.x, n.y);
			n.path = false;
			if (n.walkable)
				this->vertex_array.setNodeColor(index, this->vertex_array.default_color);
		}
}

void Application::markPathNodes()
{
	for (const auto& n : this->nodes)
		if (n.path)
			this->vertex_array.setNodeColor(n.x, n.y, sf::Color(180, 30, 255, 255));
}

void Application::updateNodes()
{
	const sf::Vector2i pos = this->raycast();

	if (pos.x < 0 || pos.y < 0)
		return;

	const int index = this->getIndex(pos.x, pos.y);
	auto& node = this->nodes[index];

	this->updateSingleNode(node, index);
}

void Application::initNodes()
{
	for (size_t y = 0u; y < SIZE_Y; y++)
	{
		for (size_t x = 0u; x < SIZE_X; x++)
			this->nodes.emplace_back(x, y);
	}
}

void Application::updateButtons()
{
	for (auto& b : this->Buttons)
		b.second.update(this->mouse_position);

	if (this->Buttons["start"].isPressed()) 
		this->startPathfinding();
	else if (this->Buttons["reset"].isPressed())
	{
		for (auto& n : this->nodes)
			this->resetNode(n);

		this->start_node	= nullptr;
		this->end_node		= nullptr;
	}
}

void Application::initButtons()
{
	const std::initializer_list <std::pair<const std::string, Button>> list
	{
		{
			"start", Button(&this->font, "START", sf::Vector2f(30.0f, 635.0f), sf::Color(50, 168, 82))
		},

		{
			"reset", Button(&this->font, "RESET", sf::Vector2f(30.0f, 685.0f), sf::Color(247, 40, 71))
		},
	};
	this->Buttons = list;
}

void Application::updateTexts()
{
	this->Texts["lt"].setString("Last time: " + std::to_string(this->last_time));
	this->Texts["fps"].setString(std::to_string(this->FPS) + " FPS");
}

void Application::initTexts()
{
	this->Texts["info"].setString("A* Search Algorithm\n\nHold A to place the \"start\" node\n\nHold D to place the \"goal\" node");
	this->Texts["info"].setPosition(sf::Vector2f(800.0f, 660.0f));

	this->Texts["lt"].setPosition(sf::Vector2f(30.0f, 750.0f));
	this->Texts["fps"].setPosition(sf::Vector2f(30.0f, 775.0f));

	for (auto& t : this->Texts)
	{
		t.second.setFont(this->font);
		t.second.setCharacterSize(20);
	}
}

void Application::initFont()
{
	this->font.loadFromFile("font/font.ttf");
}

void Application::updateDeltaTime()
{
	this->delta_time = this->delta_clock.restart().asSeconds();
}

void Application::updateMousePosition()
{
	this->mouse_position = this->window.mapPixelToCoords(sf::Mouse::getPosition(this->window));
}

void Application::updateFPS()
{
	this->FPS = static_cast<unsigned int>(floor(1.0f / this->FPS_clock.restart().asSeconds()));
}

void Application::handleEvents()
{
	while (this->window.pollEvent(this->event))
	{
		switch (this->event.type)
		{
		case sf::Event::Closed: { this->window.close(); }
		}
	}
}

void Application::initWindow()
{
	const sf::ContextSettings context_settings;

	this->video_mode.width	= width;
	this->video_mode.height = height;

	this->window.create(this->video_mode, "A* Search SFML", sf::Style::Close, context_settings);
	this->window.setFramerateLimit(240);
}
