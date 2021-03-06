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
#ifndef OPENXCOM_MULTIPLETARGETSSTATE_H
#define OPENXCOM_MULTIPLETARGETSSTATE_H

#include "../Engine/State.h"

namespace OpenXcom
{

class TextButton;
class Window;
class TextList;
class Craft;
class Target;
class GeoscapeState;

/**
 * Displays a list of possible targets.
 */
class MultipleTargetsState : public State
{
private:
	std::vector<Target*> _targets;
	Craft *_craft;
	GeoscapeState *_state;
	
	Window *_window;
	TextButton *_btnCancel;
	TextList *_lstTargets;
public:
	/// Creates the Multiple Targets state.
	MultipleTargetsState(Game *game, std::vector<Target*> targets, Craft *craft, GeoscapeState *state);
	/// Cleans up the Multiple Targets state.
	~MultipleTargetsState();
	/// Updates the window.
	void init();
	/// Popup for a target.
	void popupTarget(Target *target);
	/// Handler for clicking the Cancel button.
	void btnCancelClick(Action *action);
	/// Handler for clicking the Targets list.
	void lstTargetsClick(Action *action);
};

}

#endif
