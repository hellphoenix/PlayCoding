#include "button.h"

Button::Button(sf::Vector2f& mousePosView, const sf::Texture& textureIdle, const sf::Texture& textureHover, const sf::Texture& texturePressed) :
	 colorIdle(sf::Color::White), colorHover(sf::Color::Green), colorPressed(sf::Color::Red), textureIdle(&textureIdle)
	, textureHover(&textureHover), texturePressed(&texturePressed), shape(std::make_unique<sf::Sprite>(textureIdle))
	, buttonState(IDLE)
{
}

Button::~Button()
{
}

void Button::setButtonPosition(sf::Vector2f& mousePosView)
{
	sf::Vector2f shapeBounds = { this->shape->getLocalBounds().getCenter().x, this->shape->getLocalBounds().getCenter().y };
	this->shape->setPosition({ mousePosView.x - shapeBounds.x, mousePosView.y - shapeBounds.y });
}

void Button::updateButton(const sf::RenderWindow& window)
{
	sf::Vector2f mousePosView = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (this->shape->getGlobalBounds().contains(mousePosView))
	{
		this->shape->setTexture(*this->textureHover, true);
		this->buttonState = HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			this->shape->setTexture(*this->texturePressed, true);
			this->buttonState = PRESSED;
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		{
			sf::Vector2f shapeBounds = { this->shape->getLocalBounds().getCenter().x, this->shape->getLocalBounds().getCenter().y };
			this->shape->setPosition({ mousePosView.x - shapeBounds.x, mousePosView.y - shapeBounds.y});
		}
	}
	else
	{
		this->shape->setTexture(*this->textureIdle, true);
		this->buttonState = IDLE;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(*shape);
}
