/*********************************************************\
 *  File: SNText.h                                       *
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


#ifndef __PLSCENE_SCENENODE_TEXT_H__
#define __PLSCENE_SCENENODE_TEXT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLGraphics/Color/Color4.h>
#include "PLScene/Scene/SceneNode.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLScene {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Abstract text scene node
*/
class SNText : public SceneNode {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene node flags (SceneNode flags extension)
		*/
		enum EFlags {
			NoCenter = 1<<10	/**< Do not center the text */
		};
		pl_enum(EFlags)
			pl_enum_base(SceneNode::EFlags)
			pl_enum_value(NoCenter,	"Do not center the text")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLS_RTTI_EXPORT, SNText, "PLScene", PLScene::SceneNode, "Abstract text scene node")
		// Attributes
		pl_attribute(Text,		PLCore::String,			"",							ReadWrite,	GetSet,			"Text do draw",																						"")
		pl_attribute(Color,		PLGraphics::Color4,		PLGraphics::Color4::White,	ReadWrite,	DirectValue,	"Text color",																						"")
		pl_attribute(Font,		PLCore::String,			"",							ReadWrite,	GetSet,			"The used font, if empty the default font is used",													"")
		pl_attribute(FontSize,	PLCore::uint32,			0,							ReadWrite,	GetSet,			"The font size, if null the default font size is used - use scene node scale for dynamic scale",	"Max='100'")
			// Overwritten SceneNode attributes
		pl_attribute(Flags,		pl_flag_type(EFlags),	0,							ReadWrite,	GetSet,			"Flags",																							"")
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public RTTI get/set functions                         ]
	//[-------------------------------------------------------]
	public:
		PLS_API virtual PLCore::String GetText() const;
		PLS_API virtual void SetText(const PLCore::String &sValue);
		PLS_API virtual PLCore::String GetFont() const;
		PLS_API virtual void SetFont(const PLCore::String &sValue);
		PLS_API virtual PLCore::uint32 GetFontSize() const;
		PLS_API virtual void SetFontSize(PLCore::uint32 nValue);


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Default constructor
		*/
		PLS_API SNText();

		/**
		*  @brief
		*    Destructor
		*/
		PLS_API virtual ~SNText();


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::String m_sText;		/**< Text do draw */
		PLCore::String m_sFont;		/**< The used font, if empty the default font is used */
		PLCore::uint32 m_nFontSize;	/**< The font size, if null the default font size is used - use scene node scale for dynamic scale */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLScene


#endif // __PLSCENE_SCENENODE_TEXT_H__
