#include "gameplay/resource.h"

#include <iostream>

int Resource::wood_amount() const
{ return wood_amount_; }

int Resource::stone_amount() const
{ return stone_amount_; }

void Resource::add_wood(const int amount)
{
	wood_amount_ += amount;
	std::cout << wood_amount_ << " wood" << std::endl;
}

void Resource::add_stone(const int amount)
{
	stone_amount_ += amount;
	std::cout << stone_amount_ << " stone" << std::endl;
}
