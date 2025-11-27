#include "button.h"

Button::Button(sf::Vector2f& mousePosView)
{
	this->colorIdle = sf::Color::White;
	this->colorHover = sf::Color::Green;
	this->colorPressed = sf::Color::Red;
	if (this->textureIdle.loadFromFile("assets/button_idle.png")
		&& this->textureHover.loadFromFile("assets/button_hover.png")
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
	setButtonIdleTexture(textureSingle);
	setButtonHoverTexture(textureSingle);
	setButtonPressedTexture(textureSingle);
	this->buttonState = IDLE;
}

Button::Button(sf::Vector2f& mousePosView, std::string& textureIdle, std::string& textureHover, std::string& texturePressed)
{
	this->colorIdle = sf::Color::White;
	this->colorHover = sf::Color::Green;
	this->colorPressed = sf::Color::Red;
	setButtonIdleTexture(textureIdle);
	setButtonHoverTexture(textureHover);
	setButtonPressedTexture(texturePressed);
	this->buttonState = IDLE;
}

Button::~Button()
{
}

const bool& Button::isPressed() const
{
	return this->buttonState == PRESSED;
}

const bool& Button::isHover() const
{
	return this->buttonState == HOVER;
}

void Button::setButtonIdleTexture(std::string& textureIdle)
{
	if (this->textureIdle.loadFromFile(textureIdle))
	{
		std::cout << "Button Idle texture Loaded\n";
		this->shape.emplace(this->textureIdle);
	}
	else std::cout << "Button Idle Texture could not load\n";
}

void Button::setButtonHoverTexture(std::string& textureHover)
{
	if (this->textureHover.loadFromFile(textureHover))
	{
		std::cout << "Button Hover texture Loaded\n";
		this->shape.emplace(this->textureHover);
	}
	else std::cout << "Button Hover Texture could not load\n";
}

void Button::setButtonPressedTexture(std::string& texturePressed)
{
	if (this->texturePressed.loadFromFile(texturePressed))
	{
		std::cout << "Button Pressed texture Loaded\n";
		this->shape.emplace(this->texturePressed);
	}
	else std::cout << "Button Pressed Texture could not load\n";
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
