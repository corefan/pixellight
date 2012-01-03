/*********************************************************\
 *  File: SceneLoader.cpp                                *
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLAssimp/SceneLoader/SceneLoader.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
namespace PLAssimp {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SceneLoader)


//[-------------------------------------------------------]
//[ Public RTTI methods                                   ]
//[-------------------------------------------------------]
bool SceneLoader::Load(SceneContainer &cContainer, File &cFile)
{
	return LoadParams(cContainer, cFile, 3);
}

bool SceneLoader::Save(SceneContainer &cContainer, File &cFile)
{
	// Error - not implemented!
	return false;
}


//[-------------------------------------------------------]
//[ Protected functions                                   ]
//[-------------------------------------------------------]
/**
*  @brief
*    Default constructor
*/
SceneLoader::SceneLoader()
{
}

/**
*  @brief
*    Destructor
*/
SceneLoader::~SceneLoader()
{
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLAssimp
