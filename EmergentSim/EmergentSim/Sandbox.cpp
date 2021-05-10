#include <ctime>
#include "Sandbox.h"
#include "Wall.h"
#include "Resource.h"

#include<string>
using std::string;

Sandbox::Sandbox(int width, int height) : m_width(width), m_height(height), m_sandbox(width)
{
    for (vector<Entity*>& row : m_sandbox)
    {
        row.resize(height);
    }

    srand((unsigned int)time(NULL));

	SetupSandbox();
}

void Sandbox::SetupSandbox()
{
    float max_wall_percent = MAX_WALL_PERCENT;
    float min_wall_percent = MIN_WALL_PERCENT;
    float totalPercent = MAX_RESOURCE_PERCENT + MAX_WALL_PERCENT;
    if (totalPercent > 1)
    {
        max_wall_percent = MAX_WALL_PERCENT / totalPercent;
        min_wall_percent = MIN_WALL_PERCENT / totalPercent;
    }

    int cells = m_width * m_height;
    int max_walls = (int)(cells * max_wall_percent);
    int min_walls = (int)(cells * min_wall_percent);
    int num_walls = (rand() % max_walls) + min_walls;
    int num_resources = rand() % (cells - num_walls);


    for (int i = 0; i < num_walls; ++i)
    {
        int randomX = rand() % m_height;
        int randomY = rand() % m_width;
        Transform::Direction randomDir = (Transform::Direction)(rand() % 4);
        Transform transform(randomX, randomY, randomDir);
        Wall* ent = new Wall(transform);
        if (!RandomlyPlaceEntity(ent))
            throw string("Failed to place entity. Not enough space");
    }

    for (int i = 0; i < num_resources; ++i)
    {
        int randomX = rand() % m_height;
        int randomY = rand() % m_width;
        Transform::Direction randomDir = (Transform::Direction)(rand() % 4);
        Transform transform(randomX, randomY, randomDir);
        Resource* ent = new Resource(transform);
        if (!RandomlyPlaceEntity(ent))
            throw string("Failed to place entity. Not enough space");
    }
}

bool Sandbox::RandomlyPlaceEntity(Entity* ent)
{
    if (m_entityCount == m_width * m_height)
        return false;

    while (true)
    {
        int x = rand() % m_width;
        int y = rand() % m_height;
        if (m_sandbox[x][y] == nullptr)
        {
            return PlaceEntity(ent, x, y);
        }
    }
}

bool Sandbox::PlaceEntity(Entity* ent, int x, int y)
{
    if (m_sandbox[x][y] != nullptr)
        return false;

    ent->m_transform.m_x = x;
    ent->m_transform.m_y = y;
    m_sandbox[x][y] = ent;
    ++m_entityCount;

    return true;
}

bool Sandbox::MoveEntity(Entity* ent, Transform destination)
{
    if (destination.m_x < 0 ||
        destination.m_x >= m_width ||
        destination.m_y < 0 ||
        destination.m_y >= m_height)
        return false;

    m_sandbox[ent->m_transform.m_x][ent->m_transform.m_y] = nullptr;
    ent->m_transform = destination;
    m_sandbox[destination.m_x][destination.m_y] = ent;
}

Sandbox::~Sandbox()
{
	m_width = 0;
	m_height = 0;
    for (vector<Entity*>& row : m_sandbox)
    {
        for (Entity*& ent : row)
        {
            //delete ent;
            ent = nullptr;
        }
    }
}
