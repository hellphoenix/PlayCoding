#include "button.h"

Button::Button(sf::Vector2f& mousePosView)
{
	this->colorIdle = sf::Color::White;
	this->colorHover = sf::Color::Green;
	this->colorPressed = sf::Color::Red;
	this->textureIdle = loadedTexture.loadTexture("assets/button_idle.png");
	if ( this->textureHover.loadFromFile("assets/button_hover.png")
		&& this->texturePressed.loadFromFile("assets/button_pressed.png"))
	{
		std::cout << "Button textures Loaded\n";
		this->shape.emplace(this->textureIdle);
		
	}
	else std::cout << "Button Textures could not load\n";

	this->buttonState = IDLE;
	
}

Button::Button(sf::Vector2f& mousePosView, std::string& textureSingle)
{
	this->colorIdle = sf::Color::White;
	this->colorHover = sf::Color::Green;
	this->colorPressed = sf::Color::Red;
	this->textureIdle = this->textureHover = this->texturePressed = loadedTexture.loadTexture(textureSingle);
	this->buttonState = IDLE;
}

Button::Button(sf::Vector2f& mousePosView, std::string& textureIdle, std::string& textureHover, std::string& texturePressed)
{
	this->colorIdle = sf::Color::White;
	this->colorHover = sf::Color::Green;
	this->colorPressed = sf::Color::Red;
	this->textureIdle = loadedTexture.loadTexture(textureIdle);
	this->textureHover = loadedTexture.loadTexture(textureHover);
	this->texturePressed = loadedTexture.loadTexture(texturePressed);
	this->buttonState = IDLE;
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
		this->shape->setTexture(this->textureHover);
		this->buttonState = HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			this->shape->setTexture(this->texturePressed);
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
		this->shape->setTexture(this->textureIdle);
		this->buttonState = IDLE;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(*shape);
}
