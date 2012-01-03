/*********************************************************\
 *  File: BTLinux.h                                      *
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


#ifndef __PLINPUT_BLUETOOTH_LINUX_H__
#define __PLINPUT_BLUETOOTH_LINUX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLInput/Backend/Bluetooth/BTImpl.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
struct DBusConnection;


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLInput {


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
class BTDeviceLinux;


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Linux implementation of 'BTImpl'
*/
class BTLinux : public BTImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Bluetooth;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		BTLinux();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~BTLinux();

		/**
		*  @brief
		*    Enumerate Bluetooth devices
		*
		*  @param[out] lstDevices
		*    List that will receive the devices
		*  @param[in]  cConnection
		*    Used DBus connection
		*/
		void EnumerateBluetoothDevices(PLCore::List<BTDevice*> &lstDevices, DBusConnection &cConnection);


	//[-------------------------------------------------------]
	//[ Private virtual BTImpl functions                      ]
	//[-------------------------------------------------------]
	private:
		virtual void EnumerateDevices(PLCore::List<BTDevice*> &lstDevices) override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		PLCore::List<BTDeviceLinux*> m_lstDevices;	/**< List of devices */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLInput


#endif // __PLINPUT_BLUETOOTH_LINUX_H__
