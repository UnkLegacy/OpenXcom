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
#ifndef OPENXCOM_RESOURCEPACK_H
#define OPENXCOM_RESOURCEPACK_H

#include <map>
#include <string>
#include <list>
#include <vector>
#include "SDL.h"

namespace OpenXcom
{

class Surface;
class SurfaceSet;
class Font;
class Palette;
class Polygon;
class Polyline;
class Music;
class SoundSet;
class SavedBattleGame;
class RuleTerrain;
class MapBlock;

/**
 * Packs of external game media.
 * Resource packs contain all the game media that's
 * loaded externally, like graphics, fonts, languages,
 * audio and world map.
 * @note The game is still hardcoded to X-Com resources,
 * so for now this just serves to keep all the file loading
 * in one place.
 */
class ResourcePack
{
protected:
	std::string _folder;
	std::map<std::string, Palette*> _palettes;
	std::map<std::string, Font*> _fonts;
	std::map<std::string, Surface*> _surfaces;
	std::map<std::string, SurfaceSet*> _sets;
	std::map<std::string, SoundSet*> _sounds;
	std::list<Polygon*> _polygons;
	std::list<Polyline*> _polylines;
	std::map<std::string, Music*> _musics;
	std::vector<Uint16> _voxelData;
public:
	/// Create a new resource pack with a folder's contents.
	ResourcePack(const std::string &folder);
	/// Cleans up the resource pack.
	virtual ~ResourcePack();
	/// Converts a filename to its existing case-insensitive name.
	static std::string insensitive(const std::string &filename);
	/// Gets the data folder name.
	std::string getFolder() const;
	/// Gets a particular font.
	Font *const getFont(const std::string &name);
	/// Gets a particular surface.
	Surface *const getSurface(const std::string &name);
	/// Gets a particular surface set.
	SurfaceSet *const getSurfaceSet(const std::string &name);
	/// Gets the list of world polygons.
	std::list<Polygon*> *const getPolygons();
	/// Gets the list of world polylines.
	std::list<Polyline*> *const getPolylines();
	/// Gets a particular music.
	Music *const getMusic(const std::string &name);
	/// Gets a particular sound set.
	SoundSet *const getSoundSet(const std::string &name);
	/// Gets a particular palette.
	Palette *const getPalette(const std::string &name);
	/// Sets a new palette.
	void setPalette(SDL_Color *colors, int firstcolor, int ncolors);
	/// Gets list of voxel data.
	std::vector<Uint16> *const getVoxelData();
};

}

#endif
