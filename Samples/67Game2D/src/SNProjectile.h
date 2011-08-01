/*********************************************************\
 *  File: SNProjectile.h                                 *
 *
 *  Copyright (C) 2002-2011 The PixelLight Team (http://www.pixellight.org/)
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


#ifndef __PLSAMPLE_67_SNPROJECTILE_H__
#define __PLSAMPLE_67_SNPROJECTILE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneNode.h>


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Projectile scene node
*/
class SNProjectile : public PLScene::SceneNode {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(pl_rtti_export, SNProjectile, "", PLScene::SceneNode, "Projectile scene node")
		// Attributes
		pl_attribute(Direction,	PLMath::Vector2,	PLMath::Vector2(0.0f, 0.0f),	ReadWrite,	DirectValue,	"Projectile direction",	"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
		// Slots
		pl_slot_0(OnUpdate,														"Called when the scene node needs to be updated",																			"")
		pl_slot_2(OnSceneNode,	PLScene::SceneQuery&,	PLScene::SceneNode&,	"Called when a scene node was found, query found the scene node as first parameter, found scene node as second parameter",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		SNProjectile();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~SNProjectile();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void OnUpdate();

		/**
		*  @brief
		*    Called when a scene node was found
		*
		*  @param[in] cQuery
		*    Query found the scene node
		*  @param[in] cSceneNode
		*    Found scene node
		*/
		void OnSceneNode(PLScene::SceneQuery &cQuery, PLScene::SceneNode &cSceneNode);


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNode functions          ]
	//[-------------------------------------------------------]
	private:
		virtual void OnActivate(bool bActivate) override;


};


#endif // __PLSAMPLE_67_SNPROJECTILE_H__