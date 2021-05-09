#pragma once
class Sprite;
enum Entity_Type 
{ 
	Agent, 
	Resource, 
	Wall 
};

class Entity 
{
public:
	virtual Entity_Type GetType() = 0;
private:
	int m_x = 0;
	int m_y = 0;
	Sprite* m_sprite = nullptr;
};