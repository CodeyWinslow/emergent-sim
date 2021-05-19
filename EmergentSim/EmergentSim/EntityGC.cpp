#include "EntityGC.h"

EntityGC& EntityGC::GetInstance()
{
	static EntityGC* m_instance = new EntityGC();

	return *m_instance;
}

void EntityGC::Register(void* ptr)
{
	m_entities.push_back(ptr);
}

void EntityGC::Unregister(void* ptr)
{
	for (auto iter = m_entities.begin();
		iter != m_entities.end();
		iter++)
	{
		if (*iter = ptr)
		{
			iter = m_entities.erase(iter);
			return;
		}
	}

	//throw an exception or smthn idk
}

void EntityGC::Clear()
{
	for (void* ptr : m_entities)
	{
		delete ptr;
	}

	m_entities.clear();
}
