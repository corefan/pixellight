/*********************************************************\
 *  File: SPK_PLLineTrailRendererFixedFunctions.h        *
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


#ifndef __SPARK_PL_LINETRAILRENDERER_FIXEDFUNCTIONS_H__
#define __SPARK_PL_LINETRAILRENDERER_FIXEDFUNCTIONS_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "SPARK_PL/RenderingAPIs/PixelLight/SPK_PLLineTrailRenderer.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace SPARK_PL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    A Renderer drawing particles as line trails defined by the positions of particles over time using fixed functions
*
*  @note
*    - Basing on "SPK::GL::GLLineTrailRenderer" (this includes most of the comments)
*/
class SPK_PLLineTrailRendererFixedFunctions : public SPK_PLLineTrailRenderer {


	//[-------------------------------------------------------]
	//[ SPARK macro                                           ]
	//[-------------------------------------------------------]
	SPK_IMPLEMENT_REGISTERABLE(SPK_PLLineTrailRendererFixedFunctions)


	//[-------------------------------------------------------]
	//[ Public static functions                               ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Creates and registers a new SPK_PLLineTrailRendererFixedFunctions
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*
		*  @return
		*    A new registered SPK_PLLineTrailRendererFixedFunctions
		*/
		SPARK_PL_API static SPK_PLLineTrailRendererFixedFunctions *Create(PLRenderer::Renderer &cRenderer);


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor of SPK_PLLineTrailRendererFixedFunctions
		*
		*  @param[in] cRenderer
		*    PixelLight renderer to use
		*/
		SPK_PLLineTrailRendererFixedFunctions(PLRenderer::Renderer &cRenderer);

		/**
		*  @brief
		*    Destructor of SPK_PLLineTrailRendererFixedFunctions
		*/
		SPARK_PL_API virtual ~SPK_PLLineTrailRendererFixedFunctions();


	//[-------------------------------------------------------]
	//[ Public virtual SPK::Renderer functions                ]
	//[-------------------------------------------------------]
	public:
		SPARK_PL_API virtual void render(const SPK::Group &group) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // SPARK_PL


#endif	// __SPARK_PL_LINETRAILRENDERER_FIXEDFUNCTIONS_H__