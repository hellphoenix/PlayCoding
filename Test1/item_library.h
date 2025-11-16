#pragma once
#ifndef ITEM_LIBRARY_H
#define ITEM_LIBRARY_H
#include "item.h"
#include <vector>

class ItemLibrary
{
public:

	static const std::vector<Item>& items();

	static const Item& byId(const std::string& _id);
};

#endif // !ITEM_LIBRARY_H

