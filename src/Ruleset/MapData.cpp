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
#include "MapData.h"

namespace OpenXcom
{

/**
*  Creates a new Map Data Object.
* @param dataset The dataset this object belongs to.
*/
MapData::MapData(MapDataSet *dataset) : _dataset(dataset)
{

}

/**
* Destroy the object.
*/
MapData::~MapData()
{

}

/**
* Get the dataset this object belongs to.
* @return Pointer to MapDataSet.
*/
MapDataSet *MapData::getDataset()
{
	return _dataset;
}

/**
* Get the sprite index.
* @param frameID Animation frame 0-7
* @return the original sprite index
*/
int MapData::getSprite(int frameID)
{
	return _sprite[frameID];
}

/**
* Set the sprite index for a certain frame.
* @param frameID Animation frame
* @param value The sprite index in the surfaceset of the mapdataset.
*/
void MapData::setSprite(int frameID, int value)
{
	_sprite[frameID] = value;
}

/**
  * Get whether this is an animated ufo door.
  * @return bool 
  */
bool MapData::isUFODoor()
{
	return _isUfoDoor;
}

/**
  * Get whether this is a floor.
  * @return bool 
  */
bool MapData::isNoFloor()
{
	return _isNoFloor;
}

/**
  * Get whether this is a big wall, which blocks all surrounding paths.
  * @return bool 
  */
bool MapData::isBigWall()
{
	if (_terrainLevel < 0) return false; // this is a hack for eg. Skyranger Ramps
	return _isBigWall;
}

/**
  * Get whether this is a normal door.
  * @return bool 
  */
bool MapData::isDoor()
{
	return _isDoor;
}

/**
  * Set all kinds of flags.
  * @param isUfoDoor
  * @param stopLOS
  * @param isNoFloor
  * @param isBigWall
  * @param isGravLift
  * @param isDoor
  * @param blockFire
  * @param blockSmoke
  */
void MapData::setFlags(bool isUfoDoor, bool stopLOS, bool isNoFloor, bool isBigWall, bool isGravLift, bool isDoor, bool blockFire, bool blockSmoke)
{
	_isUfoDoor = isUfoDoor;
	_stopLOS = stopLOS;
	_isNoFloor = isNoFloor;
	_isBigWall = isBigWall;
	_isGravLift = isGravLift;
	_isDoor = isDoor;
	_blockFire = blockFire;
	_blockSmoke = blockSmoke;
}

/**
  * Get the amount of blockage of a certain type.
  * @param type
  * @return blockage (0-255)
  */
int MapData::getBlock(ItemDamageType type)
{
	if (type == DT_NONE)
		return _block[1];
	if (type == DT_HE)
		return _block[2]; 
	if (type == DT_SMOKE)
		return _block[3]; 
	if (type == DT_IN)
		return _block[4]; 
	if (type == DT_STUN)
		return _block[5]; 

	return 0;
}

/**
  * Sets the amount of blockage for all types.
  * @param lightBlock
  * @param visionBlock
  * @param HEBlock
  * @param smokeBlock
  * @param fireBlock
  * @param gasBlock
  */
void MapData::setBlockValue(int lightBlock, int visionBlock, int HEBlock, int smokeBlock, int fireBlock, int gasBlock)
{
	_block[0] = lightBlock; // not used...
	_block[1] = visionBlock==1?255:0;
	_block[2] = HEBlock;
	_block[3] = smokeBlock==1?255:0;
	_block[4] = fireBlock==1?255:0;
	_block[5] = gasBlock==1?255:0;
}

/**
  * Get the Y offset for drawing.
  * @return int height in pixels
  */
int MapData::getYOffset()
{
	return _yOffset;
}

/**
  * Sets the offset on the Y axis for drawing this object.
  * @param value
  */
void MapData::setYOffset(int value)
{
	_yOffset = value;
}

/**
  * Gets the Y offset for drawing.
  * @return int height in pixels
  */
SpecialTileType MapData::getSpecialType()
{
	return _specialType;
}

/**
  * Get the type of object.
  * @return 0-3
  */
int MapData::getObjectType()
{
	return _objectType;
}

/**
  * Sets a special tile type and object type.
  * @param value Special tile type.
  * @param otype Object type.
  */
void MapData::setSpecialType(int value, int otype)
{
	_specialType = (SpecialTileType)value;
	_objectType = otype;
}

/*
 * Gets the TU cost to walk over the object.
 * @param movementType
 * @return TU cost
 */
int MapData::getTUCost(MovementType movementType)
{
	switch (movementType)
	{
	case MT_WALK:
		return _TUWalk;
		break;
	case MT_FLY:
		return _TUFly;
		break;
	case MT_SLIDE:
		return _TUSlide;
		break;
	}
	return 0;
}

/**
  * Set TU cost to move over the object.
  * @param walk
  * @param fly
  * @param slide
  */
void MapData::setTUCosts(int walk, int fly, int slide)
{
	_TUWalk = walk;
	_TUFly = fly;
	_TUSlide = slide;
}

/**
  * Add this to the graphical Y offset of units or objects on this tile.
  * @return Y offset
  */
int MapData::getTerrainLevel()
{
	return _terrainLevel;
}

/**
  * Sets Y offset for units/objects on this tile.
  * @param value
  */
void MapData::setTerrainLevel(int value)
{
	_terrainLevel = value;
}

/**
  * Get index to the footstep sound.
  * @return sound ID
  */
int MapData::getFootstepSound()
{
	return _footstepSound;
}

/**
  * Set the index to the footstep sound.
  * @param value
  */
void MapData::setFootstepSound(int value)
{
	_footstepSound = value;
}

/**
  * Get the alternative object ID.
  * @return object ID 
  */
int MapData::getAltMCD()
{
	return _altMCD;
}

/**
  * Set the alternative object ID.
  * @param value
  */
void MapData::setAltMCD(int value)
{
	_altMCD = value;
}

/**
  * Get the dead object ID.
  * @return object ID 
  */
int MapData::getDieMCD()
{
	return _dieMCD;
}

/**
  * Set the dead object ID.
  * @param value
  */
void MapData::setDieMCD(int value)
{
	_dieMCD = value;
}

/**
  * Get the amount of light the object is emitting.
  * @return lightsource
  */
int MapData::getLightSource()
{
	return _lightSource;
}

/**
  * Set the amount of light the object is emitting.
  * @param value
  */
void MapData::setLightSource(int value)
{
	_lightSource = value;
}

/**
  * Get the amount of armor.
  * @return armor
  */
int MapData::getArmor()
{
	return _armor;
}

/**
  * Set the amount of armor.
  * @value armor
  */
void MapData::setArmor(int value)
{
	_armor = value;
}

/**
  * Get the amount of flammable.
  * @return armor
  */
int MapData::getFlammable()
{
	return _flammable;
}

/**
  * Set the amount of flammable.
  * @value armor
  */
void MapData::setFlammable(int value)
{
	_flammable = value;
}

/**
  * Get the amount of fuel.
  * @return fuel
  */
int MapData::getFuel()
{
	return _fuel;
}

/**
  * Set the amount of fuel.
  * @value fuel
  */
void MapData::setFuel(int value)
{
	_fuel = value;
}

/// Get the loft index for a certain layer.
int MapData::getLoftID(int layer)
{
	return _loftID[layer];
}

/// Set the loft index for a certain layer.
void MapData::setLoftID(int loft, int layer)
{
	_loftID[layer] = loft;
}

}
