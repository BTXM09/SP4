#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H
#include "Mesh.h"
#include "Vector3.h"

struct Animation
{
	Animation() {}
	void Set(int startFrame, int endFrame, int repeat, float time)
	{
		this->startFrame = startFrame; this->endFrame = endFrame; this->repeatCount = repeat; this->animTime = time;
	}
	int startFrame;
	int endFrame;
	int repeatCount;
	float animTime;
	bool ended;
};
class SpriteAnimation : public Mesh
{
public:
	SpriteAnimation();
	 SpriteAnimation(const std::string &meshName, int row, int col);
	~SpriteAnimation();
	void Update(double dt);
	virtual void Render();
	int index;
	int m_row;
	int m_col;
	int speed;
	float x;
	float y;
	Vector3 direction;

	float m_currentTime;
	int m_currentFrame;
	int m_playCount;
	Animation *m_anim;

};
#endif