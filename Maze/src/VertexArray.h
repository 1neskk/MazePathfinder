#pragma once
#include "stdafx.h"
#include "GlobalVariables.h"

class VertexArray : public sf::Drawable
{
	std::vector<sf::Vertex> nodes;
	std::vector<sf::Vertex> grid;

	void addQuad(const int index_X, const int index_Y);
	void addStrip(const int index_X, const int index_Y, const float max_strip_size, const bool vertical);

	void initNodes();
	void initGrid();
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	const sf::Color default_color = sf::Color(255, 255, 255);

	VertexArray();
	
	void setNodeColor(const int index_X, const int index_Y, sf::Color color);
	void setNodeColor(size_t index, sf::Color color);
	void resetNodes();
};