/*
 * Copyright 2010 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "TextButton.h"
#include "SDL.h"
#include "Text.h"
#include "../Engine/Font.h"
#include "../Engine/Sound.h"

namespace OpenXcom
{

Sound *TextButton::soundPress = 0;

/**
 * Sets up a text button with the specified size and position.
 * The text is centered on the button.
 * @param width Width in pixels.
 * @param height Height in pixels.
 * @param x X position in pixels.
 * @param y Y position in pixels.
 */
TextButton::TextButton(int width, int height, int x, int y) : InteractiveSurface(width, height, x, y), _color(0), _group(0)
{
	_validButton = SDL_BUTTON_LEFT;

	_text = new Text(width, height, 0, 0);
	_text->setSmall();
	_text->setAlign(ALIGN_CENTER);
	_text->setVerticalAlign(ALIGN_MIDDLE);
}

/**
 * Deletes the contained Text.
 */
TextButton::~TextButton()
{
	delete _text;
}

/**
 * Changes the color for the button and text.
 * @param color Color value.
 */
void TextButton::setColor(Uint8 color)
{
	_color = color;
	_text->setColor(_color - 3);
	draw();
}

/**
 * Returns the color for the button and text.
 * @return Color value.
 */
Uint8 TextButton::getColor() const
{
	return _color;
}

/**
 * Changes the various fonts for the text label to use.
 * The different fonts need to be passed in advance since the
 * text size can change mid-text.
 * @param big Pointer to large-size font.
 * @param small Pointer to small-size font.
 */
void TextButton::setFonts(Font *big, Font *small)
{
	_text->setFonts(big, small);
}

/**
 * Changes the text of the button label.
 * @param text Text string.
 */
void TextButton::setText(const std::wstring &text)
{
	_text->setText(text);
	draw();
}

/**
 * Returns the text of the button label.
 * @return Text string.
 */
std::wstring TextButton::getText() const
{
	return _text->getText();
}

/**
 * Changes the button group this button belongs to.
 * @param group Pointer to the pressed button pointer in the group.
 * Null makes it a regular button.
 */
void TextButton::setGroup(TextButton **group)
{
	_group = group;
	draw();
}

/**
 * Replaces a certain amount of colors in the surface's palette.
 * @param colors Pointer to the set of colors.
 * @param firstcolor Offset of the first color to replace.
 * @param ncolors Amount of colors to replace.
 */
void TextButton::setPalette(SDL_Color *colors, int firstcolor, int ncolors)
{
	Surface::setPalette(colors, firstcolor, ncolors);
	_text->setPalette(colors, firstcolor, ncolors);
}

/**
 * Draws the labelled button.
 * The colors are inverted if the button is pressed.
 */
void TextButton::draw()
{
	SDL_Rect square;
	int color = _color - 2;

	square.x = 0;
	square.y = 0;
	square.w = getWidth();
	square.h = getHeight();

	for (int i = 0; i < 5; i++)
	{
		drawRect(&square, color);
		
		if (i % 2 == 0)
		{
			square.x++;
			square.y++;
		}
		square.w--;
		square.h--;

		switch (i)
		{
		case 0:
			color = _color + 2;
			setPixel(square.w, 0, color);
			break;
		case 1:
			color = _color - 1;
			break;
		case 2:
			color = _color + 1;
			setPixel(square.w+1, 1, color);
			break;
		case 3:
			color = _color;
			break;
		}
	}
	
	bool press;
	if (_group == 0)
		press = _isPressed;
	else
		press = (*_group == this);

	if (press)
	{
		this->invert(_color);
	}
	_text->setInvert(press);

	_text->draw();
	_text->blit(this);
}

/**
 * Sets the button as the pressed button if it's part of a group.
 * @param action Pointer to an action.
 * @param state State that the action handlers belong to.
 */
void TextButton::mousePress(Action *action, State *state)
{
	if (soundPress != 0)
		soundPress->play();

	if (_group != 0)
	{
		TextButton *old = *_group;
		*_group = this;
		old->draw();
	}

	InteractiveSurface::mousePress(action, state);
	draw();
}

/**
 * Sets the button as the released button.
 * @param action Pointer to an action.
 * @param state State that the action handlers belong to.
 */
void TextButton::mouseRelease(Action *action, State *state)
{
	InteractiveSurface::mouseRelease(action, state);
	draw();
}

}
