#pragma once

#include <vector>

class EntityGC
{
public:
	static EntityGC& GetInstance();

	void Register(void* ptr);

	void Unregister(void* ptr);

	void Clear();

private:
	std::vector<void*> m_entities = {};
};
