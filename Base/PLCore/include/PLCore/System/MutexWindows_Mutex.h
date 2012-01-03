/*********************************************************\
 *  File: MutexWindows_Mutex.h                           *
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


#ifndef __PLCORE_MUTEX_WINDOWS_MUTEX_H__
#define __PLCORE_MUTEX_WINDOWS_MUTEX_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/PLCoreWindowsIncludes.h"
#include "PLCore/System/MutexImpl.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Windows 'Mutex' implementation using Windows mutex (lock/unlock across multiple processes)
*/
class MutexWindows_Mutex : public MutexImpl {


	//[-------------------------------------------------------]
	//[ Friends                                               ]
	//[-------------------------------------------------------]
	friend class Mutex;


	//[-------------------------------------------------------]
	//[ Private functions                                     ]
	//[-------------------------------------------------------]
	private:
		/**
		*  @brief
		*    Constructor
		*/
		MutexWindows_Mutex();

		/**
		*  @brief
		*    Destructor
		*/
		virtual ~MutexWindows_Mutex();


	//[-------------------------------------------------------]
	//[ Private virtual MutexImpl functions                   ]
	//[-------------------------------------------------------]
	private:
		virtual bool Lock() override;
		virtual bool TryLock(uint64 nTimeout) override;
		virtual bool Unlock() override;


	//[-------------------------------------------------------]
	//[ Private data                                          ]
	//[-------------------------------------------------------]
	private:
		HANDLE m_hMutex;	/**< System mutex handle */


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_MUTEX_WINDOWS_MUTEX_H__
