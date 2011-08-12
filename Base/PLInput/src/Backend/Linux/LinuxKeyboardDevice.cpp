/*********************************************************\
 *  File: KeyboardLinux.cpp                              *
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
#include <X11/keysym.h>
#include "PLInput/Input/Devices/Keyboard.h"
#include "PLInput/Backend/Linux/LinuxKeyboardDevice.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
namespace PLInput {


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
LinuxKeyboardDevice::LinuxKeyboardDevice(::Display *pDisplay) :
	m_pDisplay(pDisplay)
{
	// Destroy device implementation automatically
	m_bDelete = true;

	// Init keys as 'not pressed'
	for (int i=0; i<32; i++)
		m_nKeys[i] = 0;
}

/**
*  @brief
*    Destructor
*/
LinuxKeyboardDevice::~LinuxKeyboardDevice()
{
}


//[-------------------------------------------------------]
//[ Public virtual UpdateDevice functions                 ]
//[-------------------------------------------------------]
void LinuxKeyboardDevice::Update()
{
	// Check if input device is valid
	if (m_pDevice) {
		// Get keyboard device
		Keyboard *pKeyboard = static_cast<Keyboard*>(m_pDevice);

		// Get keyboard state
		XLockDisplay(m_pDisplay);
		XQueryKeymap(m_pDisplay, m_nKeys);
		XUnlockDisplay(m_pDisplay);

		// Find changed keys
		for (int i=0; i<32*8; i++) {
			// Get state
			const int nState = (m_nKeys[i/8] >> (i%8)) & 1;

			// Get virtual key code without any modifier set (otherwise we would get different virtual key codes for one and the same physical key)
			//   Example: The user is pressing the "a"-key and the method returns "XK_a" as virtual key code.
			//            In case the user additionally is pressing the "shift"-key, the method returns "XK_A" (= a different virtual key code!).
			//            When the user releases the "a"-key on the keyboard, but is still holding the "shift"-key pressed down, then the input
			//            system wouldn't see that the "a"-key was released. The reason for this is, that the method returns "XK_A" and not "XK_a"
			//            which was the virtual key code returned when the user pressed the "a"-key in the first place.
			const KeySym nKeySym = XKeycodeToKeysym(m_pDisplay, i, 0);

			// Get button
			Button *pButton = GetKeyboardKey(pKeyboard, nKeySym);
			if (pButton) {
				// Get button state
				const bool bPressed = (nState != 0);

				// Propagate changes
				if (pButton->IsPressed() != bPressed)
					pButton->SetPressed(bPressed);
			}
		}
	}
}


//[-------------------------------------------------------]
//[ Private functions                                     ]
//[-------------------------------------------------------]
/**
*  @brief
*    Get key for virtual key code
*/
Button *LinuxKeyboardDevice::GetKeyboardKey(Keyboard *pKeyboard, KeySym nKeySym)
{
	// Return key that corresponds to the given key code
	switch (nKeySym) {
		case XK_BackSpace:		return &pKeyboard->KeyBack;
		case XK_Tab:			return &pKeyboard->KeyTab;
		case XK_Clear:			return &pKeyboard->KeyClear;
		case XK_Shift_L:		return &pKeyboard->KeyShift;
		case XK_Control_L:		return &pKeyboard->KeyControl;
		case XK_Menu:			return &pKeyboard->KeyAlt;
		case XK_Pause:			return &pKeyboard->KeyPause;
		case XK_Caps_Lock:		return &pKeyboard->KeyCapsLock;
		case XK_Escape:			return &pKeyboard->KeyEscape;
		case XK_space:			return &pKeyboard->KeySpace;
		case XK_Prior:			return &pKeyboard->KeyPageUp;
		case XK_Next:			return &pKeyboard->KeyPageDown;
		case XK_End:			return &pKeyboard->KeyEnd;
		case XK_Home:			return &pKeyboard->KeyHome;
		case XK_Left:			return &pKeyboard->KeyLeft;
		case XK_Up:				return &pKeyboard->KeyUp;
		case XK_Right:			return &pKeyboard->KeyRight;
		case XK_Down:			return &pKeyboard->KeyDown;
		case XK_Select:			return &pKeyboard->KeySelect;
		case XK_Execute:		return &pKeyboard->KeyExecute;
		case XK_Print:			return &pKeyboard->KeyPrintScreen;
		case XK_Insert:			return &pKeyboard->KeyInsert;
		case XK_Delete:			return &pKeyboard->KeyDelete;
		case XK_Help:			return &pKeyboard->KeyHelp;
		case XK_0:				return &pKeyboard->Key0;
		case XK_1:				return &pKeyboard->Key1;
		case XK_2:				return &pKeyboard->Key2;
		case XK_3:				return &pKeyboard->Key3;
		case XK_4:				return &pKeyboard->Key4;
		case XK_5:				return &pKeyboard->Key5;
		case XK_6:				return &pKeyboard->Key6;
		case XK_7:				return &pKeyboard->Key7;
		case XK_8:				return &pKeyboard->Key8;
		case XK_9:				return &pKeyboard->Key9;
		case XK_a:				return &pKeyboard->KeyA;
		case XK_b:				return &pKeyboard->KeyB;
		case XK_c:				return &pKeyboard->KeyC;
		case XK_d:				return &pKeyboard->KeyD;
		case XK_e:				return &pKeyboard->KeyE;
		case XK_f:				return &pKeyboard->KeyF;
		case XK_g:				return &pKeyboard->KeyG;
		case XK_h:				return &pKeyboard->KeyH;
		case XK_i:				return &pKeyboard->KeyI;
		case XK_j:				return &pKeyboard->KeyJ;
		case XK_k:				return &pKeyboard->KeyK;
		case XK_l:				return &pKeyboard->KeyL;
		case XK_m:				return &pKeyboard->KeyM;
		case XK_n:				return &pKeyboard->KeyN;
		case XK_o:				return &pKeyboard->KeyO;
		case XK_p:				return &pKeyboard->KeyP;
		case XK_q:				return &pKeyboard->KeyQ;
		case XK_r:				return &pKeyboard->KeyR;
		case XK_s:				return &pKeyboard->KeyS;
		case XK_t:				return &pKeyboard->KeyT;
		case XK_u:				return &pKeyboard->KeyU;
		case XK_v:				return &pKeyboard->KeyV;
		case XK_w:				return &pKeyboard->KeyW;
		case XK_x:				return &pKeyboard->KeyX;
		case XK_y:				return &pKeyboard->KeyY;
		case XK_z:				return &pKeyboard->KeyZ;
		case XK_KP_0:			return &pKeyboard->KeyNumpad0;
		case XK_KP_1:			return &pKeyboard->KeyNumpad1;
		case XK_KP_2:			return &pKeyboard->KeyNumpad2;
		case XK_KP_3:			return &pKeyboard->KeyNumpad3;
		case XK_KP_4:			return &pKeyboard->KeyNumpad4;
		case XK_KP_5:			return &pKeyboard->KeyNumpad5;
		case XK_KP_6:			return &pKeyboard->KeyNumpad6;
		case XK_KP_7:			return &pKeyboard->KeyNumpad7;
		case XK_KP_8:			return &pKeyboard->KeyNumpad8;
		case XK_KP_9:			return &pKeyboard->KeyNumpad9;
		case XK_KP_Multiply:	return &pKeyboard->KeyNumpadMultiply;
		case XK_KP_Add:			return &pKeyboard->KeyNumpadAdd;
		case XK_KP_Separator:	return &pKeyboard->KeyNumpadSeparator;
		case XK_KP_Subtract:	return &pKeyboard->KeyNumpadSubtract;
		case XK_KP_Decimal:		return &pKeyboard->KeyNumpadDecimal;
		case XK_KP_Divide:		return &pKeyboard->KeyNumpadDivide;
		case XK_F1:				return &pKeyboard->KeyF1;
		case XK_F2:				return &pKeyboard->KeyF2;
		case XK_F3:				return &pKeyboard->KeyF3;
		case XK_F4:				return &pKeyboard->KeyF4;
		case XK_F5:				return &pKeyboard->KeyF5;
		case XK_F6:				return &pKeyboard->KeyF6;
		case XK_F7:				return &pKeyboard->KeyF7;
		case XK_F8:				return &pKeyboard->KeyF8;
		case XK_F9:				return &pKeyboard->KeyF9;
		case XK_F10:			return &pKeyboard->KeyF10;
		case XK_F11:			return &pKeyboard->KeyF11;
		case XK_F12:			return &pKeyboard->KeyF12;
		case XK_Num_Lock:		return &pKeyboard->KeyNumLock;
		case XK_Scroll_Lock:	return &pKeyboard->KeyScrollLock;
		case XK_asciicircum:	return &pKeyboard->KeyCircumflex;
		default:				return  nullptr;
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput
