#ifndef PARTICLE_H
#define PARTICLE_H

#include "SpriteAnimation.h"
#include "MyMath.h"
#include <iostream>
#include <vector>
#include "Vector3.h"

using namespace std;

class Particle
{

public:
	Particle();
	~Particle();

	//Particle Init
	void ParticleInit(int size, float x, float y,int style);
	//SpriteAnimation to be pushed
	void SpritePushBack(SpriteAnimation* Holder, float m_windowheight, float m_windowwidth);
	//Update SpriteAnimation
	void Update(double dt);
	//Render SpriteAnimation
	void Render();
	//Get Number of SpriteAnimation per Particle
	int GetSize();
	//Get Particle X position
	float GetX();
	//Get Particle Y position
	float GetY();
	//Get Particle way of behaving
	int Getparticlestyle();
	//Set Confetti Style for "reflection"
	void SetConfettiRightSide(bool confettiRightside);
	//SpriteAnimation Vector
	vector<SpriteAnimation*> theSpriteHolder;
private:
	//Confetti Style for "reflection"
	bool confettiRightside;
	//Number of SpriteAnimation per Particle
	int size;
	//Particle X position
	float x;
	//Particle Y position
	float y;
	//Particle way of behaving
	int particlestyle;
	
};

#endif