/*********************************************************\
 *  File: SNMPhysicsBodyConvexHull.cpp                   *
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


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLScene/Scene/SceneContext.h>
#include "PLPhysics/Body.h"
#include "PLPhysics/World.h"
#include "PLPhysics/SceneNodes/SCPhysicsWorld.h"
#include "PLPhysics/SceneNodeModifiers/SNMPhysicsBodyConvexHull.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
namespace PLPhysics {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMPhysicsBodyConvexHull)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
String SNMPhysicsBodyConvexHull::GetMesh() const
{
	return m_sMesh;
}

void SNMPhysicsBodyConvexHull::SetMesh(const String &sValue)
{
	if (m_sMesh != sValue) {
		m_sMesh = sValue;
		RecreatePhysicsBody();
	}
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMPhysicsBodyConvexHull::SNMPhysicsBodyConvexHull(SceneNode &cSceneNode) : SNMPhysicsBody(cSceneNode),
	Mesh(this)
{
}

/**
*  @brief
*    Destructor
*/
SNMPhysicsBodyConvexHull::~SNMPhysicsBodyConvexHull()
{
}


//[-------------------------------------------------------]
//[ Private virtual SNMPhysicsBody functions              ]
//[-------------------------------------------------------]
void SNMPhysicsBodyConvexHull::CreatePhysicsBody()
{
	if (m_pWorldContainer && m_pWorldContainer->GetWorld()) {
		// Create the PL physics body
		String sMesh = m_sMesh;
		if (!m_sMesh.GetLength()) {
			DynVar *pDynVar = GetSceneNode().GetAttribute("Mesh");
			if (pDynVar)
				sMesh = pDynVar->GetString();
		}
		if (sMesh.GetLength())
			m_pBodyHandler->SetElement(m_pWorldContainer->GetWorld()->CreateBodyConvexHull(GetSceneNode().GetSceneContext()->GetMeshManager(), sMesh, GetSceneNode().GetTransform().GetScale()));

		// Call base implementation
		SNMPhysicsBody::CreatePhysicsBody();
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLPhysics