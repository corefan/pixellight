/*********************************************************\
 *  File: XmlTextImage.h                                 *
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


#ifndef __PLXMLTEXT_IMAGE_H__
#define __PLXMLTEXT_IMAGE_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/String/String.h>
#include <PLMath/Vector2i.h>
#include "PLXmlText/PLXmlText.h"
#include "PLXmlText/XmlText/XmlTextElement.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLGui {
	class Image;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLXmlText {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Element displaying an image
*/
class XmlTextImage : public XmlTextElement {


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] pParent
		*    Parent object, can be a null pointer
		*/
		PLXMLTEXT_API XmlTextImage(XmlTextElement *pParent = nullptr);

		/**
		*  @brief
		*    Destructor
		*/
		PLXMLTEXT_API virtual ~XmlTextImage();


	//[-------------------------------------------------------]
	//[ Protected virtual XmlTextElement functions            ]
	//[-------------------------------------------------------]
	protected:
		PLXMLTEXT_API virtual void OnParse(PLCore::XmlNode &cXmlNode) override;
		PLXMLTEXT_API virtual void OnDraw(XmlTextRenderer &cRenderer) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		// Image data
		PLCore::String	  m_sFilename;	/**< Image filename */
		PLMath::Vector2i  m_vSize;		/**< Image size */
		PLGui::Image	 *m_pImage;		/**< Image, can be a null pointer */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLXmlText


#endif // __PLXMLTEXT_IMAGE_H__