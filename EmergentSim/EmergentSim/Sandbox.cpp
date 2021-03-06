#include <ctime>
#include "Sandbox.h"
#include "Wall.h"
#include "Resource.h"
#include "Perlin.h"

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
    const float wallBegin = MIN_WALL_PERCENT;
    const float wallLimit = MAX_WALL_PERCENT;
    const float resourceBegin = MIN_RESOURCE_PERCENT;
    const float resourceLimit = MAX_RESOURCE_PERCENT;

    PerlinNoise perlin(time(NULL));
    const float perlinFrequency = 10.0;

    for (int x = 0; x < m_width; ++x)
    {
        for (int y = 0; y < m_height; ++y)
        {
            /* graveyard of mysterious noise */
            //float perlinVal = perlin.noise((float)x / m_width, (float)y / m_height, 0) - 0.5f;
            //float perlinVal = ((perlin.noise(((float)x / m_width) * 20, ((float)y / m_height) * 20, 0)) - 0.5f) * 2;
            //float perlinVal = perlin.noise(x*50, y*50, 0);
            float perlinVal = (perlin.noise((float)x / perlinFrequency, (float)y / perlinFrequency, 0) - 0.5) * 2;

            if (perlinVal >= wallBegin && perlinVal <= wallLimit)
            {
                Transform::Direction randomDir = (Transform::Direction)(rand() % 4);
                Transform transform(x, y, randomDir);
                Wall* ent = new Wall(transform);
                if (!PlaceEntity(ent, x, y))
                    throw string("Failed to place entity. Not enough space");
            }
            else if (perlinVal >= resourceBegin && perlinVal <= resourceLimit)
            {
                perlinVal = (rand() % 100) / 100.0;
                if (perlinVal <= resourceLimit - resourceBegin)
                {
                    Transform::Direction randomDir = (Transform::Direction)(rand() % 4);
                    Transform transform(x, y, randomDir);
                    Resource* ent = new Resource(transform);
                    if (!PlaceEntity(ent, x, y))
                        throw string("Failed to place entity. Not enough space");
                }
            }
        }
    }

    return;

    /*float max_wall_percent = MAX_WALL_PERCENT;
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
        if (Perlin::compute(randomX, randomY) < 0.5f)
        {
            Transform::Direction randomDir = (Transform::Direction)(rand() % 4);
            Transform transform(randomX, randomY, randomDir);
            Wall* ent = new Wall(transform);
            if (!RandomlyPlaceEntity(ent))
                throw string("Failed to place entity. Not enough space");
        }
        else
            --i;
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
    }*/
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

template<typename T, typename Q, typename Z>
static T Clamp(T val, Q min, Z max)
{
    if (val < min) return min;
    if (val > max) return max;
    return val;
}

static bool HasLineOfSight(const Entity* me, const Entity* them, const Sandbox* sandbox)
{
    if (me == them) return false;

    Transform my = me->GetTransform();
    Transform their = them->GetTransform();

    int xDiff = abs(their.x - my.x);
    int yDiff = abs(their.y - my.y);

    if (xDiff == 0)
    {
        int yStep = ((double)their.y - my.y) / (double)yDiff;
        int x = my.x;
        int y = my.y + yStep;

        while (sandbox->GetEntity(x, y) && sandbox->GetEntity(x, y)->GetType() != EntityType::WALL)
        {
            if (sandbox->GetEntity(x, y) == them) return true;
            y += yStep;
        }
    }
    else if (yDiff == 0)
    {
        int xStep = ((double)their.x - my.x) / (double)xDiff;
        int x = my.x + xStep;
        int y = my.y;

        while (sandbox->GetEntity(x, y) && sandbox->GetEntity(x, y)->GetType() != EntityType::WALL)
        {
            if (sandbox->GetEntity(x, y) == them) return true;
            x += xStep;
        }
    }
    else
    {
        double xStep = ((double)their.x - my.x) / (double)xDiff;
        double yStep = ((double)their.y - my.y) / (double)xDiff;

        double x = my.x + xStep;
        double y = my.y + yStep;
        x = Clamp(x, 0, sandbox->GetWidth() - 1);
        y = Clamp(y, 0, sandbox->GetHeight() - 1);

        while (sandbox->GetEntity(x, y) && sandbox->GetEntity(x, y)->GetType() != EntityType::WALL)
        {
            if (sandbox->GetEntity(x, y) == them) return true;
            x += xStep;
            y += yStep;

            if (xStep > 0)
                x = Clamp(x, 0, their.x);
            else
                x = Clamp(x, their.x, sandbox->GetWidth() - 1);

            if (yStep > 0)
                y = Clamp(y, 0, their.y);
            else
                y = Clamp(y, their.y, sandbox->GetHeight() - 1);
        }
    }
    return false;
}

vector<Entity*> Sandbox::GetEntitiesInView(const Entity* ent, unsigned int distance) const
{
    vector<Entity*> entities{};
    int _distance = (int)distance;

    Transform transform = ent->GetTransform();
    int minX{ transform.x - _distance };
    int maxX{ transform.x + _distance };
    int minY{ transform.y - _distance };
    int maxY{ transform.y + _distance };

    switch (transform.direction)
    {
    case Transform::Direction::UP:
        maxY = transform.y;
        break;
    case Transform::Direction::DOWN:
        minY = transform.y;
        break;
    case Transform::Direction::LEFT:
        maxX = transform.x;
        break;
    case Transform::Direction::RIGHT:
        minX = transform.x;
        break;
    }

    // ensure we don't go out of bounds
    minX = Clamp(minX, 0, m_width-1);
    maxX = Clamp(maxX, 0, m_width-1);
    minY = Clamp(minY, 0, m_height-1);
    maxY = Clamp(maxY, 0, m_height-1);

    Entity* entity{};
    for (int x{ minX }; x <= maxX; ++x)
    {
        for (int y{ minY }; y <= maxY; ++y)
        {
            entity = m_sandbox[x][y];
            if (entity != nullptr && entity->GetType() != EntityType::WALL && HasLineOfSight(ent, entity, this))
                entities.push_back(entity);
        }
    }

    return entities;
}

bool Sandbox::PlaceEntity(Entity* ent, int x, int y)
{
    if (m_sandbox[x][y] != nullptr)
        return false;

    ent->m_transform.x = x;
    ent->m_transform.y = y;
    m_sandbox[x][y] = ent;
    ++m_entityCount;

    return true;
}

bool Sandbox::MoveEntity(Entity* ent, Transform destination)
{
    if (destination.x < 0 ||
        destination.x >= m_width ||
        destination.y < 0 ||
        destination.y >= m_height)
        return false;
    
    Entity* e = m_sandbox[destination.x][destination.y];
    // if there is something in that space already don't move it there
    if (e != nullptr && e != ent) return false;

    m_sandbox[ent->m_transform.x][ent->m_transform.y] = nullptr;
    ent->m_transform = destination;
    m_sandbox[destination.x][destination.y] = ent;

    return true;
}

bool Sandbox::RemoveEntity(const Entity* ent)
{
    if (ent == nullptr) return false;

    Transform transform = ent->GetTransform();
    const Entity* entity = At(transform);
    m_sandbox[transform.x][transform.y] = nullptr;

    return true;
}

const Entity* Sandbox::At(Transform transform) const
{
    if (transform.x >= m_width || transform.x < 0
        || transform.y >= m_height || transform.y < 0) 
        return nullptr;

    return m_sandbox[transform.x][transform.y];
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
