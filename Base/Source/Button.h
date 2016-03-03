#ifndef BUTTON_H
#define BUTTON_H

#include <iostream>
#include "Vector3.h"
#include "LuaUsage.h"
#include <string.h>

class Button
{
public:
	Button();
	~Button();
	
	//Button Init
	void ButtonInit(std::string Name);
	//ButtonUpdate
	void update(double dt);
	//Get Button Position
	Vector3 getTempPosition();
	//Get Actual Button Position(something like waypoint)
	Vector3 getPosition();
	//Get Offset for all mesh pointing to this Button
	Vector3 getOffset();

private:
	
	//Loading value
	LuaUsage* Loading;
	//Button Direction
	Vector3 Direction;
	//Button Temp position
	Vector3 TempPosition;
	//Button Position
	Vector3 Position;
	//Offset for mesh
	Vector3 Offset;
	//Button Speed
	float speed;
};

#endif