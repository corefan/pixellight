/*********************************************************\
 *  File: SNMLookController.cpp                          *
 *
 *  Copyright (C) 2002-2010 The PixelLight Team (http://www.pixellight.org/)
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
#include <PLGeneral/Tools/Timing.h>
#include <PLMath/EulerAngles.h>
#include "PLScene/Scene/SceneNode.h"
#include "PLScene/Scene/SceneContext.h"
#include "PLScene/Scene/SceneNodeModifiers/LookController.h"
#include "PLScene/Scene/SceneNodeModifiers/SNMLookController.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLGeneral;
using namespace PLMath;
using namespace PLInput;
namespace PLScene {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(SNMLookController)


//[-------------------------------------------------------]
//[ Public RTTI get/set functions                         ]
//[-------------------------------------------------------]
void SNMLookController::SetFlags(uint32 nValue)
{
	// Call base implementation
	SNMTransform::SetFlags(nValue);

	// Connect/disconnect event handler
	if (IsActive())
		GetSceneNode().EventUpdate.Connect(&EventHandlerUpdate);
	else
		GetSceneNode().EventUpdate.Disconnect(&EventHandlerUpdate);
}


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
SNMLookController::SNMLookController(SceneNode &cSceneNode) : SNMTransform(cSceneNode),
	EventHandlerUpdate(&SNMLookController::NotifyUpdate, this),
	InputSemantic(this),
	Flags(this),
	m_pController(new LookController())
{
	// Overwrite the default setting of the flags
	SetFlags(GetFlags()|UseRotationKey);

	// Emit the input controller found event of the scene context to tell everyone about our input controller
	GetSceneNode().GetSceneContext()->EventInputControllerFound.Emit(m_pController, InputSemantic);
}

/**
*  @brief
*    Destructor
*/
SNMLookController::~SNMLookController()
{
	// Destroy the input controller
	delete m_pController;
}


//[-------------------------------------------------------]
//[ Public virtual SceneNodeModifier functions            ]
//[-------------------------------------------------------]
Controller *SNMLookController::GetInputController() const
{
	return m_pController;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when the scene node needs to be updated
*/
void SNMLookController::NotifyUpdate()
{
	// Check if input is active and whether or not the rotation key required and pressed
	if (m_pController->GetActive() && (!(GetFlags() & UseRotationKey) || m_pController->Rotate.IsPressed())) {
		// Get rotation
		float fX = m_pController->RotX.GetValue();
		float fY = m_pController->RotY.GetValue();
		float fZ = m_pController->RotZ.GetValue();
		if (fX || fY || fZ) {
			// Get the current time difference
			const float fTimeDiff = Timing::GetInstance()->GetTimeDifference();

			// Do we need to take the current time difference into account?
			if (!m_pController->RotX.IsValueRelative())
				fX *= fTimeDiff;
			if (!m_pController->RotY.IsValueRelative())
				fY *= fTimeDiff;
			if (!m_pController->RotZ.IsValueRelative())
				fZ *= fTimeDiff;

			// Get a quaternion representation of the rotation delta
			Quaternion qRotInc;
			EulerAngles::ToQuaternion(float(fX*Math::DegToRad),
									  float(fY*Math::DegToRad),
									  float(fZ*Math::DegToRad),
									  qRotInc);

			// Update rotation
			GetSceneNode().GetTransform().SetRotation(GetSceneNode().GetTransform().GetRotation()*qRotInc);
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene
