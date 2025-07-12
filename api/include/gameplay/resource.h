#ifndef RESOURCE_H
#define RESOURCE_H

class Resource
{
	int wood_amount_ = 50;
	int stone_amount_ = 50;
public:
	int wood_amount() const;

	int stone_amount() const;

	void add_wood(int amount);

	void add_stone(int amount);
};

#endif //RESOURCE_H
