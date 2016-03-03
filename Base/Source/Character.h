#ifndef CHARACTER_H
#define CHARACTER_H

#include "Mesh.h"
#include "Vector3.h"
#define MAX_SPEED 3

class CCharacter
{
public:
	CCharacter(void);
	~CCharacter(void);

	void Init(float x, float y, float z, float scale, int newSpriteID, int newHP, int newZoneID, float newMS);
	void setPosition(float x, float y, float z);
	Vector3 getPosition(void);
	void Update(double dt);
	void UpdatePosition(double dt);
	void setVelocity(float x, float y, float z);
	Vector3 getVelocity(void);
	void setTarget(float x, float y, float z);
	void setScale(float x, float y, float z);
	Vector3 getScale(void);
	void setSpriteID(int newSpriteID);
	int getSpriteID(void);
	void setID(int newID);
	void setHP(int newHP);
	int  getHP(void);
	void Damaged(int Damage);
	void setCurrentZone(int newZoneID);
	int  getCurrentZone(void);
	void setActive(bool newStatus);
	bool getActive(void);
	void setMoveSpeed(float newMS);
	void addAccelerate(float x, float y, float z);
	void UpdateVelocity(double dt);
	void setRotation(float newRot);
	float getRotation(void);
	Vector3 getInitPosition(void);

private:
	Vector3 m_Position;
	Vector3 m_Velocity;
	Vector3 m_Target;
	Vector3 m_Scale;
	Vector3 m_InitialPos;
	int m_SpriteID;
	int m_ID;
	int m_HP;
	int m_CurrentZone;
	float m_Rotation;
	bool m_Active;

protected:
	float m_MoveSpeed;
	Vector3 m_acceleration;
};

#endif

