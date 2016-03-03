#include "Item.h"

Item::Item()
:m_Price(0)
, m_Name("")
, m_Bought(false)
{

}
Item::~Item()
{

}

void Item::Init(string m_Name, bool m_Bought, int m_Price)
{
	this->m_Name = m_Name;
	this->m_Price = m_Price;
	this->m_Bought =  m_Bought;
}

int Item::GetPrice()
{
	return this->m_Price;
}
void Item::SetPrice(int m_Price)
{
	this->m_Price = m_Price;
}
string Item::GetName()
{
	return this->m_Name;
}
void Item::SetName(string m_Name)
{
	this->m_Name = m_Name;
}
bool Item::GetBought()
{
	return this->m_Bought;
}
void Item::SetBought(bool m_Bought)
{
	this->m_Bought = m_Bought;
}