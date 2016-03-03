#include "Character.h"


CCharacter::CCharacter(void)
{
	 m_Position		= Vector3();
	 m_InitialPos   = Vector3();
	 m_Velocity		= Vector3();
	 m_Target		= Vector3();
	 m_Scale		= Vector3();
	 m_SpriteID		= 0;
	 m_ID			= 0;
	 m_HP			= 0;
	 m_CurrentZone  = 0;
	 m_Active		= false;
	 m_MoveSpeed	= 0;
	 m_Rotation		= 0;
}


CCharacter::~CCharacter(void)
{
}

void CCharacter::Init(float x, float y, float z, float scale, int newSpriteID, int newHP, int newZoneID, float newMS)
{
	m_Position.Set(x,y,z);
	m_InitialPos.Set(x,y,z);
	m_Scale.Set(scale,scale,scale);
	m_SpriteID = newSpriteID;
	m_HP = newHP;
	m_CurrentZone = newZoneID;
	m_MoveSpeed = newMS;
}

void CCharacter::setPosition(float x,float y, float z)
{
	m_Position.Set(x,y,z);
	if ( m_InitialPos.IsZero() )
	{
		m_InitialPos = m_Position;
	}
}
Vector3 CCharacter::getPosition(void)
{
	return m_Position;
}

void CCharacter::UpdateVelocity(double dt)
{
	if (m_acceleration.x == 0)
	{
		m_Velocity.x *= (1 - dt * 5);
		if (m_Velocity.x > -0.1 && m_Velocity.x < 0.1) m_Velocity.x = 0;
	}

	if (m_acceleration.y == 0)
	{
		m_Velocity.y *= (1 - dt * 5);
		if (m_Velocity.y > -0.1 && m_Velocity.y < 0.1) m_Velocity.y = 0;
	}

	m_Velocity += m_acceleration * dt;
	m_Velocity.x = Math::Clamp<float>(m_Velocity.x, -MAX_SPEED, MAX_SPEED);
	m_Velocity.y = Math::Clamp<float>(m_Velocity.y, -MAX_SPEED, MAX_SPEED);
}

void CCharacter::Update(double dt)
{
	UpdateVelocity(dt);
	//UpdatePosition(dt,tileMap);
	//m_Position += m_Velocity * dt;
	m_acceleration.Set(0, 0, 0);
}
Vector3 m_size;
void CCharacter::UpdatePosition(double dt)
{
	Vector3 position = m_Position;
	position.x += m_Velocity.x * dt;
	if (m_Velocity.x < 0)
		position.x = floor(position.x);
	else if (m_Velocity.x > 0)
		position.x = ceil(position.x);
	/*if (tileMap->getTile(position.x, floor(position.y)) >= 0 && tileMap->getTile(position.x, floor(position.y)) <= 15 || tileMap->getTile(position.x, ceil(position.y)) >= 0 && tileMap->getTile(position.x, ceil(position.y)) <= 15)
	{
		m_Position.x = position.x + (m_Velocity.x < -0.0f ? 1 : -1);
		m_Velocity.x = 0;
	}*/
	/*if (tileMap->getTile(position.x, floor(position.y)) >= 20 && tileMap->getTile(position.x, floor(position.y)) <= 23 || tileMap->getTile(position.x, ceil(position.y)) >= 20 && tileMap->getTile(position.x, ceil(position.y)) <= 23)
	{
		m_Position.x = position.x + (m_Velocity.x < -0.0f ? 1 : -1);
		m_Velocity.x = 0;
	}*/
	position = m_Position;
	position.y += m_Velocity.y * dt;
	if (m_Velocity.y < 0)
		position.y = floor(position.y);
	else if (m_Velocity.y > 0)
		position.y = ceil(position.y);
	/*if (tileMap->getTile(floor(position.x), position.y) >= 0 && tileMap->getTile(floor(position.x), position.y) <= 15  || tileMap->getTile(ceil(position.x), position.y) >= 0 && tileMap->getTile(ceil(position.x), position.y) <= 15)
	{
		m_Position.y = position.y + (m_Velocity.y < -0.0f ? 1 : -1);
		m_Velocity.y = 0;
	}*/
	/*if (tileMap->getTile(floor(position.x), position.y) >= 20 && tileMap->getTile(floor(position.x), position.y) <= 23 || tileMap->getTile(ceil(position.x), position.y) >= 20 && tileMap->getTile(ceil(position.x), position.y) <= 23)
	{
		m_Position.y = position.y + (m_Velocity.y < -0.0f ? 1 : -1);
		m_Velocity.y = 0;
	}*/

	m_Position += m_Velocity * dt;
}
void CCharacter::setVelocity(float x, float y, float z)
{
	m_Velocity.Set(x,y,z);
}
Vector3 CCharacter::getVelocity(void)
{
	return m_Velocity;
}
void CCharacter::setTarget(float x, float y , float z)
{
	m_Target.Set(x,y,z);
}
void CCharacter::setScale(float x, float y, float z)
{
	m_Scale.Set(x,y,z);
}
Vector3 CCharacter::getScale(void)
{
	return m_Scale;
}
void CCharacter::setSpriteID(int newSpriteID)
{
	m_SpriteID = newSpriteID;
}
int CCharacter::getSpriteID(void)
{
	return m_SpriteID;
}
void CCharacter::setID(int newID)
{
	m_ID = newID;
}
void CCharacter::setHP(int newHP)
{
	m_HP = newHP;
}
int CCharacter::getHP()
{
	return m_HP;
}
void CCharacter::Damaged(int Damage)
{
	m_HP -= Damage;
}
void CCharacter::setCurrentZone(int newZoneID)
{
	m_CurrentZone = newZoneID;
}
int CCharacter::getCurrentZone()
{
	return m_CurrentZone;
}
void CCharacter::setActive(bool newStatus)
{
	m_Active = newStatus;
}
bool CCharacter::getActive()
{
	return m_Active;
}
void CCharacter::setMoveSpeed(float newMS)
{
	m_MoveSpeed = newMS;
}
void CCharacter::addAccelerate(float x, float y, float z)
{
	m_acceleration.x += x;
	m_acceleration.y += y;
	m_acceleration.z += z;
}

void CCharacter::setRotation(float newRot)
{
	m_Rotation = newRot;
}

float CCharacter::getRotation(void)
{
	return m_Rotation;
}

Vector3 CCharacter::getInitPosition(void)
{
	return m_InitialPos;
}
