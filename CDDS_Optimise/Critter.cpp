#include "Critter.h"


Critter::Critter()
{
	m_position = Vector2{ 0, 0 };
	m_velocity = Vector2{ 0, 0 };
	m_radius = 0;
	m_isLoaded = false;
}

//Critter::Critter(const Critter& copy_Critter)
//{
//	m_position = copy_Critter.m_position;
//	m_velocity = copy_Critter.m_velocity; 
//	m_radius = copy_Critter.m_radius;
//	m_isLoaded = false;
//}

Critter::~Critter()
{
	UnloadTexture(m_texture);
	m_isLoaded = false;
}

void Critter::Init(Vector2 position, Vector2 velocity, float radius, const char* texture)
{
	m_position = position;
	m_velocity = velocity;
	m_radius = radius;
	
	m_texture = LoadTexture(texture);	

	m_isLoaded = true;
}

void Critter::respawn(Vector2 position, Vector2 velocity, Vector2 Screenbondry)
{ 
	if (position.x < 0)
	{
		position.x = 0;
	}
	if (position.y < 0)
	{
		position.y = 0;
	}
	if (position.x > Screenbondry.x)
	{
		position.x = Screenbondry.x;
	}
	if (position.y > Screenbondry.y)
	{
		position.y = Screenbondry.y;
	}
	
	m_position = position, m_velocity = velocity, m_isLoaded = true; 
}

void Critter::Destroy()
{
	//UnloadTexture(m_texture);

	m_position.x = -12;
	m_position.y = -12;
	m_isLoaded = false;
}

void Critter::Update(float dt)
{
	if (m_isLoaded == false)
		return;

	m_position.x += m_velocity.x * dt;
	m_position.y += m_velocity.y * dt;

	m_isDirty = false;
}


void Critter::Draw()
{
	if (m_isLoaded == false)
		return;

	DrawTexture(m_texture, m_position.x, m_position.y, WHITE);
}
