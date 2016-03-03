#include "Shop.h"

Shop::Shop()
	:m_playerMoney(0)
	, m_playerGold(0)
	, theItemHolder(NULL)
	, ShopItem(NULL)
	, itemholder(NULL)
{

}
Shop::~Shop()
{
	if (ShopItem != NULL)
	{
		delete ShopItem;
		ShopItem = NULL;
	}
	for (vector<Item*>::iterator it = theItemHolder.begin(); it != theItemHolder.end(); ++it)
	{
		Item* item = (Item*)*it;

		if (item != NULL)
		{
			delete item;
			item = NULL;
		}
	}
}
void Shop::PlayerInit(Player* playerinfo)
{
	m_playerMoney = playerinfo->GetAmtOfCurrency();
	m_playerGold = playerinfo->GetAmtOfGold();
	m_BombMaxStack = playerinfo->GetAmtOfBomb();
	m_BridgeMaxStack = playerinfo->GetAmtOfBridge();
}
void Shop::ItemInit()
{
	ShopItem = new LuaUsage();
	ShopItem->LuaUsageInit("Item");
	int sizeofvector = ShopItem->get<int>("Amount");
	for (int i = 0; i < sizeofvector; ++i)
	{
		itemholder = new Item();
		string luaitemnaming = "Item.Number";
		luaitemnaming = luaitemnaming + to_string((i + 1));
		string luaitemname = luaitemnaming + ".Name";
		string luaitemprice = luaitemnaming + ".Price";
		string luaitembought = luaitemnaming + ".Bought";
		string itemname = ShopItem->get<string>(luaitemname);
		bool itembought = ShopItem->get<bool>(luaitembought);
		int itemprice = ShopItem->get<int>(luaitemprice);
		itemholder->Init(itemname, itembought, itemprice);
		theItemHolder.push_back(itemholder);
	}
	ShopItem->LuaUsageClose();
}
void Shop::Set(Player* playerinfo)
{
	playerinfo->SetAmtOfCurrency(m_playerMoney);
	playerinfo->SetAmtOfGold(m_playerGold);
	playerinfo->SetAmtOfBomb(m_BombMaxStack);
	playerinfo->SetAmtOfBridge(m_BridgeMaxStack);
	playerinfo->SetEasyLevelUnlocked(m_playerEasyModeUnlocked);
	playerinfo->SetNormalLevelUnlocked(m_playerNormalModeUnlocked);
	playerinfo->SetHardLevelUnlocked(m_playerHardModeUnlocked);
}
int Shop::GetPlayerMoney()
{
	return m_playerMoney;
}

int Shop::GetPlayerGold()
{
	return m_playerGold;
}
int Shop::GetPlayerBomb()
{
	return m_BombMaxStack;
}
int Shop::GetPlayerBridge()
{
	return m_BridgeMaxStack;

}
void Shop::Buy(int selected)
{
	if (selected < theItemHolder.size() && m_playerMoney >= theItemHolder[selected]->GetPrice())
	{
		if (selected == 0 && m_playerEasyModeUnlocked)
		{
			m_playerMoney = m_playerMoney - theItemHolder[selected]->GetPrice();
			theItemHolder[selected]->SetBought(true);
		}
		else if (selected == 1 && m_playerNormalModeUnlocked)
		{
			m_playerMoney = m_playerMoney - theItemHolder[selected]->GetPrice();
			theItemHolder[selected]->SetBought(true);
		}
		else if (selected == 2 && m_playerHardModeUnlocked)
		{
			m_playerMoney = m_playerMoney - theItemHolder[selected]->GetPrice();
			theItemHolder[selected]->SetBought(true);
		}
	}
}

void Shop::BuyItem(int selected)
{
	if (selected < theItemHolder.size() && m_playerGold >= theItemHolder[selected]->GetPrice())
	{
		if (selected == 3 )
		{
			if (m_BombMaxStack < 20)
			{
				m_playerGold = m_playerGold - theItemHolder[selected]->GetPrice();
				m_BombMaxStack++;
			}
		}
		else if (selected == 4)
		{
			if (m_BridgeMaxStack < 20)
			{
				m_playerGold = m_playerGold - theItemHolder[selected]->GetPrice();
				m_BridgeMaxStack++;
			}
			
		}
	}
}

bool Shop::GetplayerEasyModeUnlocked()
{
	return m_playerEasyModeUnlocked;
}

bool Shop::GetplayerNormalModeUnlocked()
{
	return m_playerNormalModeUnlocked;
}

bool Shop::GetplayerHardModeUnlocked()
{
	return m_playerHardModeUnlocked;
}