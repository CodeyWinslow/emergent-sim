#pragma once
#include "memory"

class Entity;

using std::shared_ptr;

class EventInfo
{
public:
	inline void SetEntity(Entity* entity) { m_entity = entity; }
private:
	size_t m_eventId;
	Entity* m_entity;
};