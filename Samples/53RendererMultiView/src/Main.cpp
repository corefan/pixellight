/*********************************************************\
 *  File: Main.cpp                                       *
 *      This sample will use three frames. In two frames the triangle
 *      and texturing sample scenes will be shown. The main frame consists
 *      of three scenes whereby each is rendered using another viewport.
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
#include <PLCore/Frontend/FrontendMain.h>


//[-------------------------------------------------------]
//[ Module definition                                     ]
//[-------------------------------------------------------]
pl_module_application_frontend("53RendererMultiView", "Application53", "PLFrontendPLGui::Frontend")	// Using e.g. "PLFrontendOS::Frontend" instead of "PLFrontendPLGui::Frontend" will work as well (meaning mixing frontends)
	pl_module_vendor("Copyright (C) 2002-2012 by The PixelLight Team")
	pl_module_license("GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version")
	pl_module_description("PixelLight multi view sample")
pl_module_end
