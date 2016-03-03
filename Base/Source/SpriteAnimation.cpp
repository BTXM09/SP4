#include "SpriteAnimation.h"
#include "GL\glew.h"
#include "Vertex.h"
#include <iostream>

SpriteAnimation::SpriteAnimation()
: Mesh(0)
, m_row(0)
, m_col(0)
, m_currentTime(0)
, m_currentFrame(0)
, m_playCount(0)
, x(0.0f)
, y(0.0f)
{

}
SpriteAnimation::SpriteAnimation(const std::string &meshName, int row, int col)
: Mesh(meshName)
 , m_row(row)
 , m_col(col)
 , m_currentTime(0)
 , m_currentFrame(0)
 , m_playCount(0)
 , x(0.0f)
 , y(0.0f)
 , index(0)
 , speed(0)
{
 m_anim = NULL;
}
SpriteAnimation::~SpriteAnimation()
{
	delete this->m_anim;
	this->m_anim = NULL;
}
void SpriteAnimation::Update(double dt)
{
	// If animation happens
	if (m_anim)
	{
		m_currentTime += dt;

		int numFrame = Math::Max(1, (m_anim->endFrame - m_anim->startFrame + 1));

		float frameTime = ((m_anim->animTime) / numFrame);

		m_currentFrame = Math::Min(m_anim->endFrame, static_cast <int>(m_anim->startFrame + (m_currentTime / frameTime)));

		if (m_currentTime > m_anim->animTime)
		{
			m_anim->ended = true;
			if (((m_playCount + 1) < m_anim->repeatCount) || (m_anim->repeatCount == 0))
			{
				m_playCount++;
				m_currentTime = 0;
				m_currentFrame = m_anim->startFrame;
			}
		}

	}
}
void SpriteAnimation::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	//if(textureID > 0)
	//{
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));
	//}

	
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(m_currentFrame * 6 * sizeof(GLuint)));

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	if(textureID > 0)
	{
		glDisableVertexAttribArray(3);
	}
}