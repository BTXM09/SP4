#include "Button.h"

Button::Button()
: TempPosition(NULL)
, Position(NULL)
, Direction(NULL)
, Offset(NULL)
, Loading(NULL)
, speed(NULL)
{
}

Button::~Button()
{
	if (Loading != NULL)
	{
		delete Loading;
		Loading = NULL;
	}
}
Vector3 Button::getTempPosition()
{
	return this->TempPosition;
}
Vector3 Button::getPosition()
{
	return this->Position;
}
Vector3 Button::getOffset()
{
	return this->Offset;
}
void Button::ButtonInit(std::string Name)
{
	string LoadButton = "Button." + Name + ".";
	Loading = new LuaUsage();
	Loading->LuaUsageInit("Button");
	speed = Loading->get<float>(LoadButton + "Speed");
	string LoadButtonPosition = LoadButton + "Position.";
	Position.Set(Loading->get<float>((LoadButtonPosition + "x")), Loading->get<float>((LoadButtonPosition + "y")), 0);
	string LoadButtonTempPosition = LoadButton + "TempPosition.";
	TempPosition.Set(Loading->get<float>((LoadButtonTempPosition + "x")), Loading->get<float>((LoadButtonTempPosition + "y")), 0);
	string LoadButtonOffset = LoadButton + "Offset.";
	Offset.Set(Loading->get<float>((LoadButtonOffset + "x")), Loading->get<float>((LoadButtonOffset + "y")), 0);
	Direction = TempPosition - Position;
	Loading->LuaUsageClose();
}

void Button::update(double dt)
{
	if (TempPosition.x != Position.x || TempPosition.y != Position.y)
	{
		TempPosition -= Direction.Normalize() * dt * speed;
		if (TempPosition.x >= (Position.x - 30) && TempPosition.x <= (Position.x + 30))
		{
			TempPosition.x = Position.x;
		}
		if (TempPosition.y >= (Position.y - 30) && TempPosition.y <= (Position.y + 30))
		{
			TempPosition.y = Position.y;
		}
	}
	if (TempPosition.x < -100 || TempPosition.x > 900)
	{
		TempPosition.x = Position.x;
	}
	if (TempPosition.y < -100 || TempPosition.y > 700)
	{
		TempPosition.y = Position.y;
	}
	
}