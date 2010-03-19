/*
 * Copyright 2010 Daniel Albano
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
#include "ResearchState.h"

ResearchState::ResearchState(Game *game) : State(game)
{
	// Create objects
	_window = new Window(320, 200, 0, 0);
	_btnNew = new Button(game->getFont("BIGLETS.DAT"), game->getFont("SMALLSET.DAT"), 148, 16, 8, 176);
	_btnOk = new Button(game->getFont("BIGLETS.DAT"), game->getFont("SMALLSET.DAT"), 148, 16, 164, 176);
	_txtTitle = new Text(game->getFont("BIGLETS.DAT"), game->getFont("SMALLSET.DAT"), 310, 13, 5, 8);
	_txtAvailable = new Text(game->getFont("BIGLETS.DAT"), game->getFont("SMALLSET.DAT"), 150, 9, 8, 24);
	_txtAllocated = new Text(game->getFont("BIGLETS.DAT"), game->getFont("SMALLSET.DAT"), 150, 9, 160, 24);
	_txtSpace = new Text(game->getFont("BIGLETS.DAT"), game->getFont("SMALLSET.DAT"), 300, 9, 8, 34);
	_txtProject = new Text(game->getFont("BIGLETS.DAT"), game->getFont("SMALLSET.DAT"), 106, 9, 8, 44);
	_txtScientists = new Text(game->getFont("BIGLETS.DAT"), game->getFont("SMALLSET.DAT"), 144, 9, 115, 44);
	_txtProgress = new Text(game->getFont("BIGLETS.DAT"), game->getFont("SMALLSET.DAT"), 64, 9, 250, 44);
	_lstResearch = new TextList(game->getFont("BIGLETS.DAT"), game->getFont("SMALLSET.DAT"), 300, 120, 10, 54);
	
	// Set palette
	_game->setPalette(_game->getPalette("BACKPALS.DAT")->getColors(Palette::blockOffset(1)), Palette::backPos, 16);

	add(_window);
	add(_btnNew);
	add(_btnOk);
	add(_txtTitle);
	add(_txtAvailable);
	add(_txtAllocated);
	add(_txtSpace);
	add(_txtProject);
	add(_txtScientists);
	add(_txtProgress);
	add(_lstResearch);

	// Set up objects
	_window->setColor(Palette::blockOffset(13)+13);
	_window->setBg(game->getSurface("BACK05.SCR"));
	
	_btnNew->setColor(Palette::blockOffset(15)+9);
	_btnNew->setText(_game->getLanguage()->getString(85));

	_btnOk->setColor(Palette::blockOffset(15)+9);
	_btnOk->setText(_game->getLanguage()->getString(76));
	_btnOk->onMouseClick((EventHandler)&ResearchState::btnOkClick);

	_txtTitle->setColor(Palette::blockOffset(13)+10);
	_txtTitle->setBig();
	_txtTitle->setAlign(ALIGN_CENTER);
	_txtTitle->setText(_game->getLanguage()->getString(78));

	_txtAvailable->setColor(Palette::blockOffset(13)+10);
	_txtAvailable->setText(_game->getLanguage()->getString(79));

	_txtAllocated->setColor(Palette::blockOffset(13)+10);
	_txtAllocated->setText(_game->getLanguage()->getString(80));

	_txtSpace->setColor(Palette::blockOffset(13)+10);
	_txtSpace->setText(_game->getLanguage()->getString(81));

	_txtProject->setColor(Palette::blockOffset(13)+10);
	_txtProject->setText(_game->getLanguage()->getString(82));

	_txtScientists->setColor(Palette::blockOffset(13)+10);
	_txtScientists->setText(_game->getLanguage()->getString(83));

	_txtProgress->setColor(Palette::blockOffset(13)+10);
	_txtProgress->setText(_game->getLanguage()->getString(84));

	_lstResearch->setColor(Palette::blockOffset(15)+6);
	_lstResearch->setColumns(3, 158, 82, 60);
	_lstResearch->addRow(3, "Laser Weapons", "30", "Good");
}

ResearchState::~ResearchState()
{
	
}

void ResearchState::think()
{
}

void ResearchState::btnOkClick(SDL_Event *ev, int scale)
{
	_game->setState(new BasescapeState(_game));
}