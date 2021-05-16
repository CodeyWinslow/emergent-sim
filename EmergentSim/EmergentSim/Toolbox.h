#pragma once
#include "Sandbox.h"

enum class Tool {
	NONE,
	PLACE_WALL,
	PLACE_AGENT,
	PLACE_RESOURCE,
	DESTROY_ENTITY
};

static class Toolbox {
public:
	static void UseTool(Tool tool, Sandbox* sandbox, int x, int y);
	static void PlaceWall(Sandbox* sandbox, int x, int y);
	static void PlaceAgent(Sandbox* sandbox, int x, int y);
	static void PlaceResource(Sandbox* sandbox, int x, int y);
	static void Destroy(Sandbox* sandbox, int x, int y);
};
