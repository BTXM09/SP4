#include "Projectile.h"

/********************************************************************************
 Constructor
 ********************************************************************************/
CProjectile::CProjectile(void)
: m_bActive(false)
, thePosition(0, 0, 0)
, theDirection(0, 0, 0)
, theLength(0.0f)
, theType(PROJ_TYPE_DISCRETE)
, speed(0.0f)
{
}

/********************************************************************************
 Destructor
 ********************************************************************************/
CProjectile::~CProjectile(void)
{
}

/********************************************************************************
 Update the status of this projectile
 ********************************************************************************/
void CProjectile::Update(const double dt)
{
	if (m_bActive == false)
		return;

	// Update Position
	thePosition.Set(	thePosition.x + theDirection.x * speed * dt, 
						thePosition.y + theDirection.y * speed * dt, 
						thePosition.z + theDirection.z * speed * dt);
}

/********************************************************************************
 Activate the projectile. true == active, false == inactive
 ********************************************************************************/
void CProjectile::SetActivate(bool m_bActivate)
{
	if (m_bActivate == true)
		m_bActive = true;
	else
		m_bActive = false;
}

/********************************************************************************
 get status of the projectile. true == active, false == inactive
 ********************************************************************************/
bool CProjectile::GetStatus(void)
{
	return m_bActive;
}

/********************************************************************************
 Get the position of the projectile
 ********************************************************************************/
Vector3 CProjectile::GetPosition(void)
{
	return thePosition;
}

/********************************************************************************
 Get the direction of the projectile
 ********************************************************************************/
Vector3 CProjectile::GetDirection(void)
{
	return theDirection;
}

/********************************************************************************
 Get the length of the ray projectile
 ********************************************************************************/
float CProjectile::GetLength()
{
	return theLength;
}

/********************************************************************************
 Set the length of the ray projectile
 ********************************************************************************/
void CProjectile::SetLength(const float theLength)
{
	this->theLength = theLength;
	// Set this to true only when it is a sweep projectile and theLength is used
	theType = PROJ_TYPE_RAY;	
}

/********************************************************************************
 Get the projectile type
 ********************************************************************************/
int CProjectile::GetType(void)
{
	return theType;
}

/********************************************************************************
 Get the projectile type
 ********************************************************************************/
void CProjectile::SetType(const int theType)
{
	this->theType = theType;
}

/********************************************************************************
 Set the position of the projectile
 ********************************************************************************/
void CProjectile::SetPosition(Vector3 theNewPosition)
{
	thePosition.Set( theNewPosition.x, theNewPosition.y, theNewPosition.z);
}

/********************************************************************************
 Set the direction of the projectile
 ********************************************************************************/
void CProjectile::SetDirection(Vector3 theNewDirection)
{
	theDirection.Set( theNewDirection.x, theNewDirection.y, theNewDirection.z);
}

/********************************************************************************
 Set speed
 ********************************************************************************/
void CProjectile::SetSpeed(const float speed)
{
	this->speed = speed;
}
