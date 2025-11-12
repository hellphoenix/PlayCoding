#pragma once
#include "item.h"
#include <vector>
using std::vector;

#ifndef ITEM_LIBRARY_H
#define ITEM_LIBRARY_H

class ItemLibrary
{
public:
	static const vector<Item>& helmets();
	static const vector<Item>& chestPieces();
	static const vector<Item>& pants();
	static const vector<Item>& boots();
	static const vector<Item>& shields();
	static const vector<Item>& swords();
};

#endif // !ITEM_LIBRARY_H

