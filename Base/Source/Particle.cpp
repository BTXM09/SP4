#include "Particle.h"

Particle::Particle()
:theSpriteHolder(NULL)
{

}
Particle::~Particle()
{
	for (vector<SpriteAnimation*>::iterator it = theSpriteHolder.begin(); it != theSpriteHolder.end(); ++it)
	{
		SpriteAnimation* sa = (SpriteAnimation*)*it;

		if (sa != NULL)
		{
			delete sa->m_anim;
			sa->m_anim = NULL;
		}
		delete sa;
	}
}
void Particle::ParticleInit(int size, float x, float y, int style)
{
	this->x = x;
	this->y = y;
	this->size = size;
	this->particlestyle = style;
	this->confettiRightside = false;
}
void Particle::SpritePushBack(SpriteAnimation* Holder, float m_windowheight, float m_windowwidth)
{
	if (this->confettiRightside)
		Holder->direction = -(Vector3(Holder->x, Holder->y, 0) - Vector3(m_windowwidth, m_windowheight, 0));
	else if (this->confettiRightside == false)
		Holder->direction = -(Vector3(Holder->x, Holder->y, 0) - Vector3(m_windowwidth, m_windowheight, 0));
	Holder->direction.Normalize();

	theSpriteHolder.push_back(Holder);
}
void Particle::SetConfettiRightSide(bool confettiRightside)
{
	this->confettiRightside = confettiRightside;
}
int Particle::GetSize()
{
	return this->size;
}
float Particle::GetX()
{
	return this->x;
}
float Particle::GetY()
{
	return this->y;
}
int Particle::Getparticlestyle()
{
	return this->particlestyle;
}
void Particle::Update(double dt)
{
	for (int i = 0; i < this->size; i++)
	{
		this->theSpriteHolder[i]->Update(dt);


		if (this->particlestyle == 0)
		{
			this->theSpriteHolder[i]->y += this->theSpriteHolder[i]->direction.y * this->theSpriteHolder[i]->speed * dt;
			if (this->theSpriteHolder[i]->y < 0)
			{
				this->theSpriteHolder[i]->y = this->y;
			}
		}
		else if (this->particlestyle == 1)
		{
			this->theSpriteHolder[i]->y += this->theSpriteHolder[i]->direction.y * this->theSpriteHolder[i]->speed * dt;
			this->theSpriteHolder[i]->x += this->theSpriteHolder[i]->direction.x * this->theSpriteHolder[i]->speed * dt;
			if (this->theSpriteHolder[i]->y > 600)
			{
				this->theSpriteHolder[i]->y = this->y;
				this->theSpriteHolder[i]->x = this->x;
			}
			if (this->theSpriteHolder[i]->x < 425 && this->theSpriteHolder[i]->x > 375)
			{
				this->theSpriteHolder[i]->y = this->y;
				this->theSpriteHolder[i]->x = this->x;
			}
		}
		
		//this->theSpriteHolder[i]->y = this->theSpriteHolder[i]->y + this->theSpriteHolder[i]->direction.y * dt;
		//this->theSpriteHolder[i]->y = y + 2 * dt;
	}
}

void Particle::Render()
{
	for (int i = 0; i < size; i++)
	{
		this->theSpriteHolder[i]->Render();
	}
}
