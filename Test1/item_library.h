#pragma once
#ifndef ITEM_LIBRARY_H
#define ITEM_LIBRARY_H
#include "equipment.h"
#include <vector>

class ItemLibrary
{
public:

	static const std::vector<Equipment>& equipment();

	static const Equipment& equipmentById(const std::string& _id);
};

#endif // !ITEM_LIBRARY_H

