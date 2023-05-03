#pragma once
// Pre-Compiled Header
#include <iostream>
#include <map>
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

constexpr int width = 1200;
constexpr int height = 900;

#ifdef NDEBUG
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#define LOG(x)
#else
#define LOG(x) std::cout << x << std::endl
#endif // NDEBUG
