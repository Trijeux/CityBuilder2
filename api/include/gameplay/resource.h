#ifndef RESOURCE_H
#define RESOURCE_H
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class Resource : public sf::Drawable
{
	int wood_amount_ = 100;
	int stone_amount_ = 50;
	int food_amount_ = 10;

	int last_wood_amount_ = 0;
	int last_stone_amount_ = 0;
	int last_food_amount_ = 0;

	std::optional<sf::Text> text_wood_;
	std::optional<sf::Text> text_stone_;
	std::optional<sf::Text> text_food_;
	std::optional<sf::Sprite> sprite_wood_;
	std::optional<sf::Sprite> sprite_stone_;
	std::optional<sf::Sprite> sprite_food_;
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
	void Setup();
	void Update();

	int wood_amount() const;

	int stone_amount() const;

	int food_amount() const;

	void add_wood(int amount);

	void add_stone(int amount);

	void add_food(int amount);

	void sub_wood(int amount);

	void sub_stone(int amount);

	void sub_food(int amount);
};

#endif //RESOURCE_H
