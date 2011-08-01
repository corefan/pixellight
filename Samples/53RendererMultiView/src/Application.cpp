/*********************************************************\
 *  File: Application.cpp                                *
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
#include <PLCore/System/System.h>
#include <PLCore/Tools/Localization.h>
#include <PLInput/Input/Controller.h>
#include <PLInput/Input/Controls/Control.h>
#include <PLRenderer/RendererContext.h>
#include <PLRenderer/Renderer/Surface.h>
#include <PLEngine/Gui/RenderWidget.h>
#include <PLEngine/Gui/RenderWindow.h>
#include "Application.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLMath;
using namespace PLGui;
using namespace PLInput;
using namespace PLRenderer;
using namespace PLEngine;


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(Application)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
Application::Application() : RenderApplication(),
	SlotOnControl(this)
{
	// Set application name and title
	SetName("53RendererMultiView");
	SetTitle(PLT("PL multi view sample main frame"));
	SetAppDataSubdir(System::GetInstance()->GetDataDirName("PixelLight"));
}

/**
*  @brief
*    Destructor
*/
Application::~Application()
{
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Called when a control event has occurred
*/
void Application::OnControl(Control &cControl)
{
	// Check whether the escape key was pressed
	if (cControl.GetType() == ControlButton && cControl.GetName() == "Escape")
		Exit(0); // Shut down the application
}


//[-------------------------------------------------------]
//[ Private virtual PLGui::GuiApplication functions       ]
//[-------------------------------------------------------]
void Application::OnCreateMainWindow()
{
	// Call base implementation
	RenderApplication::OnCreateMainWindow();
	Widget *pWidget = GetMainWindow();

	// Get the display mode to use
	const DisplayMode *pDisplayMode = nullptr;
	if (pWidget) {
		if (pWidget->IsInstanceOf("PLEngine::RenderWidget"))
			pDisplayMode = &static_cast<const RenderWidget*>(pWidget)->GetDisplayMode();
		else if (pWidget->IsInstanceOf("PLEngine::RenderWindow"))
			pDisplayMode = &static_cast<const RenderWindow*>(pWidget)->GetDisplayMode();
	}

	// Get the used renderer
	if (GetRendererContext()) {
		Renderer &cRenderer = GetRendererContext()->GetRenderer();

		// Set the surface painter to use depending on whether or not there's a default shader language within the used renderer
		const bool bShaders = (cRenderer.GetDefaultShaderLanguage().GetLength() != 0);

		// Create the triangle sample window
		RenderWindow *pFrame = new RenderWindow(cRenderer, nullptr, pDisplayMode);
		pFrame->SetPos(Vector2i(600, 0));
		pFrame->SetSize(Vector2i(300, 300));
		pFrame->SetTitle(PLT("PL triangle sample window"));
		pFrame->GetSurface()->SetPainter(cRenderer.CreateSurfacePainter(bShaders ? "SPTriangleShaders" : "SPTriangleFixedFunctions"));
		pFrame->AddModifier("PLGui::ModClose", "CloseWindow=true");
		pFrame->SetVisible(true);

		// Create the texturing sample window
		pFrame = new RenderWindow(cRenderer, nullptr, pDisplayMode);
		pFrame->SetPos(Vector2i(600, 300));
		pFrame->SetSize(Vector2i(300, 300));
		pFrame->SetTitle(PLT("PL texturing sample window"));
		pFrame->GetSurface()->SetPainter(cRenderer.CreateSurfacePainter(bShaders ? "SPTexturingShaders" : "SPTexturingFixedFunctions"));
		pFrame->AddModifier("PLGui::ModClose", "CloseWindow=true");
		pFrame->SetVisible(true);
	}
}


//[-------------------------------------------------------]
//[ Private virtual PLEngine::RenderApplication functions ]
//[-------------------------------------------------------]
void Application::OnCreatePainter()
{
	// Get the renderer context instance
	RendererContext *pRendererContext = GetRendererContext();
	if (pRendererContext) {
		// Set the surface painter to use depending on whether or not there's a default shader language within the used renderer
		const bool bShaders = (pRendererContext->GetRenderer().GetDefaultShaderLanguage().GetLength() != 0);

		// Create and set the surface painter
		SetPainter(m_pRendererContext->GetRenderer().CreateSurfacePainter(bShaders ? "SPMultiViewShaders" : "SPMultiViewFixedFunctions"));
	}
}

void Application::OnCreateInputController()
{
	// Call base implementation
	RenderApplication::OnCreateInputController();

	// Get virtual input controller
	Controller *pController = reinterpret_cast<Controller*>(GetInputController());
	if (pController)
		pController->SignalOnControl.Connect(SlotOnControl);
}