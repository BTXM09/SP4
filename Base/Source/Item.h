#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include "LuaUsage.h"
#include "Player.h"

using namespace std;

class Item
{
public:
	Item();
	~Item();
	void Init(string m_Name, bool 
		, int m_Price);

	int GetPrice();
	void SetPrice(int m_Price);
	string GetName();
	void SetName(string m_Name);
	bool GetBought();
	void SetBought(bool m_Bought);

private:
	string m_Name;
	int m_Price;
	bool m_Bought;
};
#endif