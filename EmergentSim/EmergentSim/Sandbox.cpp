#include <ctime>
#include "Sandbox.h"
#include "Wall.h"
#include "Resource.h"

Sandbox::Sandbox(int width, int height) : m_width(width), m_height(height), m_sandbox(width)
{
    for (vector<Entity*>& row : m_sandbox)
    {
        row.resize(height);
    }
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

    srand((unsigned int)time(NULL));

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

        if (m_sandbox[randomX][randomY] == nullptr)
        {
            Transform transform(randomX, randomY, randomDir);
            m_sandbox[randomX][randomY] = new Wall(transform);
        }
        else
        {
            --i;
        }
    }

    for (int i = 0; i < num_resources; ++i)
    {
        int randomX = rand() % m_height;
        int randomY = rand() % m_width;
        Transform::Direction randomDir = (Transform::Direction)(rand() % 4);

        if (m_sandbox[randomX][randomY] == nullptr)
        {
            Transform transform(randomX, randomY, randomDir);
            m_sandbox[randomX][randomY] = new Resource(transform);
        }
        else
        {
            --i;
        }
    }
}

void Sandbox::RandomlyPlaceAgent()
{
    for (int i = 0; i < m_width * m_height; ++i)
    {

    }
}

void Sandbox::PlaceAgent(int x, int y)
{
}

Sandbox::~Sandbox()
{
	m_width = 0;
	m_height = 0;
    for (vector<Entity*>& row : m_sandbox)
    {
        for (Entity*& ent : row)
        {
            delete ent;
            ent = nullptr;
        }
    }
}
