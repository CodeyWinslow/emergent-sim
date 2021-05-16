#include "Toolbox.h"
#include "Wall.h"
#include "Resource.h"
#include "Agent.h"

void Toolbox::UseTool(Tool tool, Sandbox* sandbox, int x, int y)
{
	switch (tool)
	{
	case Tool::PLACE_WALL:
		PlaceWall(sandbox, x, y);
		break;
	case Tool::PLACE_AGENT:
		PlaceAgent(sandbox, x, y);
		break;
	case Tool::PLACE_RESOURCE:
		PlaceResource(sandbox, x, y);
		break;
	case Tool::DESTROY_ENTITY:
		Destroy(sandbox, x, y);
		break;
	}
}

void Toolbox::PlaceWall(Sandbox* sandbox, int x, int y)
{
	Transform trans(0,0,Transform::Direction::UP);
	Wall* wall = new Wall(trans);
	sandbox->PlaceEntity(wall, x, y);
}

void Toolbox::PlaceAgent(Sandbox* sandbox, int x, int y)
{
	Transform trans(0, 0, Transform::Direction::UP);
	Agents::Agent* agent= new Agents::Agent(trans);
	sandbox->PlaceEntity(agent, x, y);
}

void Toolbox::PlaceResource(Sandbox* sandbox, int x, int y)
{
	Transform trans(0, 0, Transform::Direction::UP);
	Resource* resource = new Resource(trans);
	sandbox->PlaceEntity(resource, x, y);
}

void Toolbox::Destroy(Sandbox* sandbox, int x, int y)
{
	Transform trans(x, y, Transform::Direction::UP);
	sandbox->RemoveEntity(sandbox->At(trans));
}
