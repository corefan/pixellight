/*********************************************************\
 *  File: SRPDeferredGlow.h                              *
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


#ifndef __PLCOMPOSITING_DEFERRED_GLOW_H__
#define __PLCOMPOSITING_DEFERRED_GLOW_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCompositing/Shaders/Deferred/SRPDeferred.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLRenderer {
	class Program;
	class VertexBuffer;
	class VertexShader;
	class TextureBuffer;
	class ProgramUniform;
	class FragmentShader;
	class ProgramAttribute;
	class SurfaceTextureBuffer;
	class TextureBufferRectangle;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCompositing {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Scene renderer pass for deferred rendering glow effect
*
*  @note
*    - The technique used is loosely basing on the technique described within \url{http://http.developer.nvidia.com/GPUGems/gpugems_ch21.html}
*    - The content of the emissive/light map render target of the GBuffer is used
*/
class SRPDeferredGlow : public SRPDeferred {


	//[-------------------------------------------------------]
	//[ Public definitions                                    ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Scene renderer flags (SceneRendererPass flags extension)
		*/
		enum EFlags {
			NoDiscard  = 1<<1,	/**< Disable discard (may result in better or worse performance) */
			NoBlending = 1<<2	/**< Disable blending (for debugging) */
		};
		pl_enum(EFlags)
			pl_enum_base(SRPDeferred::EFlags)
			pl_enum_value(NoDiscard,	"Disable discard (may result in better or worse performance)")
			pl_enum_value(NoBlending,	"Disable blending (for debugging)")
		pl_enum_end


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class(PLCOM_RTTI_EXPORT, SRPDeferredGlow, "PLCompositing", PLCompositing::SRPDeferred, "Scene renderer pass for deferred rendering glow effect")
		// Attributes
		pl_attribute(ShaderLanguage,	PLCore::String,			"",		ReadWrite,	DirectValue,	"Shader language to use (for example \"GLSL\" or \"Cg\"), if empty string, the default shader language of the renderer will be used",	"")
		pl_attribute(GlowFactor,		float,					1.0f,	ReadWrite,	DirectValue,	"Glow factor",																															"")
		pl_attribute(GlowBlurPasses,	PLCore::uint32,			4,		ReadWrite,	DirectValue,	"Number of glow blur passes, should be a multiple of 2",																				"")
		pl_attribute(GlowDownscale,		float,					8.0f,	ReadWrite,	DirectValue,	"Glow downscale factor, should be a multiple of 2",																						"Min='1.0'")
			// Overwritten PLScene::SceneRendererPass attributes
		pl_attribute(Flags,				pl_flag_type(EFlags),	0,		ReadWrite,	GetSet,			"Flags",																																"")
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
		PLCOM_API SRPDeferredGlow();

		/**
		*  @brief
		*    Destructur
		*/
		PLCOM_API virtual ~SRPDeferredGlow();


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Calculates the glow
		*
		*  @param[in] sShaderLanguage
		*    Shader language to use (for example "GLSL" or "Cg"), don't change the shader language on each call (performance!)
		*  @param[in] cVertexBuffer
		*    Vertex buffer of the fullscreen quad
		*  @param[in] cOriginalTexture
		*    Original HDR texture buffer to calculate the glow from
		*  @param[in] fBrightThreshold
		*    Bright threshold
		*  @param[in] nBlurPasses
		*    Number of blur passes
		*  @param[in] fDownscale
		*    Downscale factor
		*
		*  @note
		*    - Use GetTextureBuffer() to receive the result of the calculation
		*/
		void CalculateGlow(const PLCore::String &sShaderLanguage, PLRenderer::VertexBuffer &cVertexBuffer, PLRenderer::TextureBufferRectangle &cOriginalTexture, float fBrightThreshold, PLCore::uint32 nBlurPasses, float fDownscale);

		/**
		*  @brief
		*    Returns the rectangle texture buffer storing the glow
		*
		*  @return
		*    The rectangle texture buffer storing the glow, a null pointer on error
		*
		*  @note
		*    - The texture buffer is only valid after CalculateGlow() was called
		*/
		PLRenderer::TextureBuffer *GetTextureBuffer() const;

		/**
		*  @brief
		*    Called when a program became dirty
		*
		*  @param[in] pProgram
		*    Program which became dirty
		*/
		void OnDirty(PLRenderer::Program *pProgram);


	//[-------------------------------------------------------]
	//[ Private event handlers                                ]
	//[-------------------------------------------------------]
	private:
		PLCore::EventHandler<PLRenderer::Program*> EventHandlerDirty;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLRenderer::SurfaceTextureBuffer *m_pRenderTarget[2];						/**< Render targets, can be a null pointer */
		bool							  m_bResultIndex;							/**< Index of the result texture buffer */
		PLRenderer::VertexShader		 *m_pVertexShader;							/**< Vertex shader, can be a null pointer */
		// Downscale
		PLRenderer::FragmentShader		 *m_pDownscaleFragmentShader;				/**< Downscale fragment shader, can be a null pointer */
		PLRenderer::Program				 *m_pDownscaleProgram;						/**< Downscale GPU program, can be a null pointer */
		PLRenderer::ProgramAttribute	 *m_pDownscalePositionProgramAttribute;		/**< Downscale position program attribute, can be a null pointer */
		PLRenderer::ProgramUniform		 *m_pDownscaleTextureSizeProgramUniform;	/**< Downscale texture size program uniform, can be a null pointer */
		PLRenderer::ProgramUniform		 *m_pDownscaleTextureProgramUniform;		/**< Downscale texture program uniform, can be a null pointer */
		// Blur
		PLRenderer::FragmentShader		 *m_pBlurFragmentShader;					/**< Blur fragment shader, can be a null pointer */
		PLRenderer::Program				 *m_pBlurProgram;							/**< Blur GPU program, can be a null pointer */
		PLRenderer::ProgramAttribute	 *m_pBlurPositionProgramAttribute;			/**< Blur position program attribute, can be a null pointer */
		PLRenderer::ProgramUniform		 *m_pBlurTextureSizeProgramUniform;			/**< Blur texture size program uniform, can be a null pointer */
		PLRenderer::ProgramUniform		 *m_pBlurUVScaleProgramUniform;				/**< Blur uv scale program uniform, can be a null pointer */
		PLRenderer::ProgramUniform		 *m_pBlurTextureProgramUniform;				/**< Blur texture program uniform, can be a null pointer */
		// Result
		PLRenderer::FragmentShader		 *m_pResultFragmentShader;					/**< Result fragment shader, can be a null pointer */
		PLRenderer::Program				 *m_pResultProgram;							/**< Result GPU program, can be a null pointer */
		PLRenderer::ProgramAttribute	 *m_pResultPositionProgramAttribute;		/**< Result position program attribute, can be a null pointer */
		PLRenderer::ProgramUniform		 *m_pResultTextureSizeProgramUniform;		/**< Result texture size program uniform, can be a null pointer */
		PLRenderer::ProgramUniform		 *m_pResultGlowFactorProgramUniform;		/**< Result glow factor program uniform, can be a null pointer */
		PLRenderer::ProgramUniform		 *m_pResultTextureProgramUniform;			/**< Result texture program uniform, can be a null pointer */
		bool							  m_bResultDiscard;							/**< Discard used within the result GPU program? */


	//[-------------------------------------------------------]
	//[ Private virtual PLScene::SceneRendererPass functions  ]
	//[-------------------------------------------------------]
	private:
		virtual void Draw(PLRenderer::Renderer &cRenderer, const PLScene::SQCull &cCullQuery) override;


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCompositing


#endif // __PLCOMPOSITING_DEFERRED_GLOW_H__