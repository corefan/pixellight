/*********************************************************\
 *  File: UniformBuffer.h                                *
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


#ifndef __PLRENDEREROPENGL_UNIFORMBUFFER_H__
#define __PLRENDEREROPENGL_UNIFORMBUFFER_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLRenderer/Renderer/UniformBuffer.h>
#include "PLRendererOpenGL/PLRendererOpenGL.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLRendererOpenGL {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    OpenGL uniform buffer
*/
class UniformBuffer : public PLRenderer::UniformBuffer {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class ShaderLanguageGLSL;


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Destructor
		*/
		PLRENDEREROPENGL_API virtual ~UniformBuffer();


	//[-------------------------------------------------------]
	//[ Protected functions                                   ]
	//[-------------------------------------------------------]
	protected:
		/**
		*  @brief
		*    Constructor
		*
		*  @param[in] cRenderer
		*    Owner renderer
		*/
		PLRENDEREROPENGL_API UniformBuffer(PLRenderer::Renderer &cRenderer);


	//[-------------------------------------------------------]
	//[ Protected data                                        ]
	//[-------------------------------------------------------]
	protected:
		PLGeneral::uint32 m_nUniformBuffer;	/**< OpenGL buffer buffer (VBO) */


	//[-------------------------------------------------------]
	//[ Public virtual PLRenderer::Buffer functions           ]
	//[-------------------------------------------------------]
	public:
		PLRENDEREROPENGL_API virtual bool IsAllocated() const;
		PLRENDEREROPENGL_API virtual bool Allocate(PLGeneral::uint32 nElements, PLRenderer::Usage::Enum nUsage = PLRenderer::Usage::Dynamic, bool bManaged = true, bool bKeepData = false);
		PLRENDEREROPENGL_API virtual bool Clear();
		PLRENDEREROPENGL_API virtual void *Lock(PLGeneral::uint32 nFlag = PLRenderer::Lock::ReadWrite);
		PLRENDEREROPENGL_API virtual void *GetData();
		PLRENDEREROPENGL_API virtual bool Unlock();


	//[-------------------------------------------------------]
	//[ Protected virtual PLRenderer::Resource functions      ]
	//[-------------------------------------------------------]
	protected:
		PLRENDEREROPENGL_API virtual void BackupDeviceData(PLGeneral::uint8 **ppBackup);
		PLRENDEREROPENGL_API virtual void RestoreDeviceData(PLGeneral::uint8 **ppBackup);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGL


#endif // __PLRENDEREROPENGL_UNIFORMBUFFER_H__
