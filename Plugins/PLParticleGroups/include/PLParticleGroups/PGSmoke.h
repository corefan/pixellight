/*********************************************************\
 *  File: PGSmoke.h                                      *
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


#ifndef __PLPG_PGSMOKE_H__
#define __PLPG_PGSMOKE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLParticleGroups/SNParticleGroup.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLParticleGroups {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Smoke particle group
*/
class PGSmoke : public SNParticleGroup {


	//[-------------------------------------------------------]
	//[ Public structures                                     ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Init data for the particle group
		*/
		struct InitData {
			float fSize;			/**< Radius of the spheres around particle group position, where the particle are created (by default 1.0) */
			float fEnergy;			/**< Energy of the sparkles (by default 1.0) */
			float fParticleTime;	/**< Time until the next trace particle is created (by default 0.01) */
		};


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLPG_RTTI_EXPORT, PGSmoke, "PLParticleGroups", PLParticleGroups::SNParticleGroup, "Smoke particle group")
		// Attributes
		pl_attribute(Size,						float,				2.0f,										ReadWrite,	DirectValue,	"Size",												"Min='0.0001'")
		pl_attribute(SizeTimeScale,				float,				1.0f,										ReadWrite,	DirectValue,	"Size time scale",									"")
		pl_attribute(Energie,					float,				1.0f,										ReadWrite,	DirectValue,	"Energie",											"")
		pl_attribute(Color,						PLGraphics::Color4,	PLGraphics::Color4(1.0f, 1.0f, 1.0f, 1.0f),	ReadWrite,	DirectValue,	"Color",											"")
		pl_attribute(PositionScale,				float,				1.0f,										ReadWrite,	DirectValue,	"Position scale",									"")
			// Overwritten SNParticleGroup attributes
		pl_attribute(Material,					PLCore::String,		"Data/Textures/PGSmoke.dds",				ReadWrite,	GetSet,			"Particle group material",							"Type='Material Effect Image TextureAni'")
		pl_attribute(Particles,					PLCore::uint32,		20,											ReadWrite,	GetSet,			"Number of particles",								"Min=1")
		pl_attribute(TextureAnimationColumns,	PLCore::uint32,		4,											ReadWrite,	GetSet,			"Number of animation frame columns in the texture",	"")
		pl_attribute(TextureAnimationRows,		PLCore::uint32,		4,											ReadWrite,	GetSet,			"Number of animation frame rows in the texture",	"")
		// Constructors
		pl_constructor_0(DefaultConstructor,	"Default constructor",	"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Default constructor
		*/
		PLPG_API PGSmoke();

		/**
		*  @brief
		*    Destructor
		*/
		PLPG_API virtual ~PGSmoke();

		/**
		*  @brief
		*    Returns the default settings of the particle group
		*
		*  @param[out] cData
		*    Will receive the default settings
		*/
		PLPG_API void GetDefaultSettings(PGSmoke::InitData &cData) const;

		/**
		*  @brief
		*    Returns whether new particles should be created or not
		*
		*  @return
		*    'true' if new particles should be created. else 'false'
		*/
		PLPG_API bool GetCreateNewParticles() const;

		/**
		*  @brief
		*    Sets whether new particles should be created or not
		*
		*  @param[in] bCreate
		*    Create new particles?
		*/
		PLPG_API void CreateNewParticles(bool bCreate = true);


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneNode functions          ]
	//[-------------------------------------------------------]
	private:
		virtual void OnActivate(bool bActivate) override;
		virtual void OnAddedToVisibilityTree(PLScene::VisNode &cVisNode) override;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Initializes a particle
		*
		*  @param[in] cParticle
		*    Particle to initialize
		*/
		void InitParticle(SNParticleGroup::Particle &cParticle) const;

		/**
		*  @brief
		*    Called when the scene node needs to be updated
		*/
		void OnUpdate();


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<> EventHandlerUpdate;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		bool	 m_bUpdate;				/**< Perform an update the next time? */
		InitData m_SData;				/**< Init data */
		float	 m_fParticleTime;		/**< Timer for particle generation */
		bool	 m_bCreateNewParticles;	/**< Create new particles? */


	//[-------------------------------------------------------]
	//[ Public virtual SNParticleGroup functions              ]
	//[-------------------------------------------------------]
	public:
		virtual bool InitParticleGroup(PLCore::uint32 nMaxNumOfParticles, const PLCore::String &sMaterial = "", const void *pData = nullptr) override;
	

};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLParticleGroups


#endif // __PLPG_PGSMOKE_H__