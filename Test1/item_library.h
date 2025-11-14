#pragma once
#include "item.h"
#include <vector>
using std::vector;

#ifndef ITEM_LIBRARY_H
#define ITEM_LIBRARY_H

class ItemLibrary
{
public:

	static const vector<Item>& items(); // all items in the game

	static const Item& byId(const string& _id);
};

#endif // !ITEM_LIBRARY_H

