/*********************************************************\
 *  File: FragmentShaderCg.cpp                           *
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
#include <PLCore/Tools/Wrapper.h>
#include <PLCore/Core/MemoryManager.h>
#include "PLRendererOpenGLCg/ShaderLanguageCg.h"
#include "PLRendererOpenGLCg/CgContext.h"
#include "PLRendererOpenGLCg/FragmentShaderCg.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLRendererOpenGLCg {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Destructor
*/
FragmentShaderCg::~FragmentShaderCg()
{
	// Destroy the Cg fragment program
	if (m_pCgFragmentProgram)
		cgDestroyProgram(m_pCgFragmentProgram);

	// Release a Cg context reference
	CgContext::ReleaseCgContextReference();
}

/**
*  @brief
*    Returns the Cg profile
*/
CGprofile FragmentShaderCg::GetCgProfile() const
{
	return m_pCgProfile;
}

/**
*  @brief
*    Returns the Cg fragment program
*/
CGprogram FragmentShaderCg::GetCgFragmentProgram() const
{
	return m_pCgFragmentProgram;
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
FragmentShaderCg::FragmentShaderCg(PLRenderer::Renderer &cRenderer) : PLRenderer::FragmentShader(cRenderer),
	m_pCgProfile(CG_PROFILE_UNKNOWN),
	m_pCgFragmentProgram(nullptr)
{
	// Add a Cg context reference
	CgContext::AddCgContextReference();
}


//[-------------------------------------------------------]
//[ Public virtual PLRenderer::Shader functions           ]
//[-------------------------------------------------------]
String FragmentShaderCg::GetShaderLanguage() const
{
	return ShaderLanguageCg::Cg;
}

String FragmentShaderCg::GetSourceCode() const
{
	return m_pCgFragmentProgram ? cgGetProgramString(m_pCgFragmentProgram, CG_PROGRAM_SOURCE) : "";
}

String FragmentShaderCg::GetProfile() const
{
	return cgGetProfileString(m_pCgProfile);
}

String FragmentShaderCg::GetArguments() const
{
	return m_sArguments;
}

String FragmentShaderCg::GetEntry() const
{
	return m_sEntry;
}

bool FragmentShaderCg::SetSourceCode(const String &sSourceCode, const String &sProfile, const String &sArguments, const String &sEntry)
{
	// Destroy the previous Cg fragment program, if there's one
	if (m_pCgFragmentProgram) {
		cgDestroyProgram(m_pCgFragmentProgram);
		m_pCgFragmentProgram = nullptr;
	}

	// Get the profile from a user given string
	m_pCgProfile = cgGetProfile(sProfile.GetLength() ? sProfile : "glslf"); // We're using a GLSL profile as default so ATI users have reasonable shader support when using Cg

	// On unknown or invalid profile, choose a fallback profile
	if (m_pCgProfile == CG_PROFILE_UNKNOWN || (!cgGetProfileProperty(m_pCgProfile, CG_IS_FRAGMENT_PROFILE) && m_pCgProfile != CG_PROFILE_GLSLF)) {
		m_pCgProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);
		if (m_pCgProfile == CG_PROFILE_UNKNOWN && cgGLIsProfileSupported(CG_PROFILE_GLSLF))
			m_pCgProfile = CG_PROFILE_GLSLF;
	}

	// Create the Cg fragment program
	if (m_pCgProfile != CG_PROFILE_UNKNOWN)
		m_pCgFragmentProgram = CgContext::CreateCgProgram(m_pCgProfile, sSourceCode, sArguments, sEntry);

	// Was the Cg program created successfully?
	if (m_pCgFragmentProgram) {
		// Backup the optional shader compiler arguments and the user defined entry point
		m_sArguments = sArguments;
		m_sEntry     = sEntry;

		// Done
		return true;
	} else {
		m_pCgProfile = CG_PROFILE_UNKNOWN;
		m_sArguments = "";
		m_sEntry     = "";

		// Error!
		return false;
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLRenderer::Resource functions        ]
//[-------------------------------------------------------]
void FragmentShaderCg::BackupDeviceData(uint8 **ppBackup)
{
	// Backup data
	const char *pszProgram = m_pCgFragmentProgram ? cgGetProgramString(m_pCgFragmentProgram, CG_PROGRAM_SOURCE) : nullptr;
	if (pszProgram) {
		const uint32 nNumOfBytes = Wrapper::GetStringLength(pszProgram) + 1;
		*ppBackup = new uint8[nNumOfBytes];
		MemoryManager::Copy(*ppBackup, pszProgram, nNumOfBytes);
		cgDestroyProgram(m_pCgFragmentProgram);
		m_pCgFragmentProgram = nullptr;
	} else {
		*ppBackup = nullptr;
	}
}

void FragmentShaderCg::RestoreDeviceData(uint8 **ppBackup)
{
	// Restore data
	if (*ppBackup) {
		// The string class takes over the control of the string memory and also deletes it
		SetSourceCode(String(reinterpret_cast<char*>(*ppBackup), false), GetProfile(), m_sArguments, m_sEntry);
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLRendererOpenGLCg
