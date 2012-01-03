/*********************************************************\
 *  File: Object.h                                       *
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


#ifndef __PLCORE_OBJECT_H__
#define __PLCORE_OBJECT_H__
#pragma once


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include "PLCore/PLCoreDefinitions.h"
#include "PLCore/Xml/XmlElement.h"
#include "PLCore/Container/List.h"
#include "PLCore/Base/Rtti.h"


//[-------------------------------------------------------]
//[ Forward declarations                                  ]
//[-------------------------------------------------------]
namespace PLCore {
	class Class;
	class DynVar;
	class DynEvent;
	class DynEventHandler;
	class DynConstructor;
	class DynParams;
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
namespace PLCore {


//[-------------------------------------------------------]
//[ Classes                                               ]
//[-------------------------------------------------------]
/**
*  @brief
*    Internal Object base class
*/
class ObjectBase {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	public:
		// Properties
		pl_properties
		pl_properties_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API ObjectBase();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~ObjectBase();

		/**
		*  @brief
		*    Get class
		*
		*  @return
		*    Class of the object (do not destroy the returned instance, should never be a null pointer, unless something is *terribly* wrong ;-) )
		*/
		PLCORE_API virtual Class *GetClass() const;


};


/**
*  @brief
*    Object base class
*/
class Object : public ObjectBase {


	//[-------------------------------------------------------]
	//[ RTTI interface                                        ]
	//[-------------------------------------------------------]
	pl_class_internal(PLCORE_RTTI_EXPORT, Object, "PLCore", /* No base class */, "Object base class")
		#ifdef PLCORE_EXPORTS	// The following is only required when compiling PLCore
			// Methods
			pl_method_1(IsInstanceOf,			pl_ret_type(bool),		const String&,					"Check if object is instance of a given class. Class name (with namespace) as first parameter. Returns 'true' if the object is an instance of the class or one of it's derived classes, else 'false'.",	"")
			pl_method_2(SetAttribute,			pl_ret_type(void),		const String&,	const String&,	"Set attribute value. Attribute name as first parameter, attribute value as second parameter.",																											"")
			pl_method_1(SetAttributeDefault,	pl_ret_type(void),		const String&,					"Set attribute to it's default value. Attribute name as first parameter.",																																"")
			pl_method_2(CallMethod,				pl_ret_type(void),		const String&,	const String&,	"Call method. Method name as first parameter, parameters as string (e.g. \"Param0='x' Param1='y'\") as second parameter.",																				"")
			pl_method_1(SetValues,				pl_ret_type(void),		const String&,					"Set multiple attribute values as a string at once. String containing attributes and values as first parameter (e.g. \"Name='Bob' Position='1 2 3'\").",												"")
			pl_method_0(SetDefaultValues,		pl_ret_type(void),										"Set all attributes to default.",																																										"")
			pl_method_0(ToString,				pl_ret_type(String),									"Get the object as string. Returns string representation of object.",																																	"")
			pl_method_1(FromString,				pl_ret_type(void),		const String&,					"Set the object from string. String representation of object as first parameter.",																														"")
		#endif
	pl_class_end


	//[-------------------------------------------------------]
	//[ Public functions                                      ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Constructor
		*/
		PLCORE_API Object();

		/**
		*  @brief
		*    Destructor
		*/
		PLCORE_API virtual ~Object();

		//[-------------------------------------------------------]
		//[ Class and members                                     ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Check if object is instance of a given class by using a given class reference
		*
		*  @param[in] cClass
		*    Class
		*
		*  @return
		*    'true' if the object is an instance of the class or one of it's derived classes, else 'false'
		*/
		PLCORE_API bool IsInstanceOfByReference(const Class &cClass) const;

		/**
		*  @brief
		*    Check if object is instance of a given class
		*
		*  @param[in] sClass
		*    Class name (with namespace)
		*
		*  @return
		*    'true' if the object is an instance of the class or one of it's derived classes, else 'false'
		*/
		PLCORE_API bool IsInstanceOf(const String &sClass) const;

		/**
		*  @brief
		*    Get attributes
		*
		*  @return
		*    List of attributes (do not destroy the returned attribute instances)
		*
		*  @remarks
		*    Use this function with caution, as the list is assembled and copied each time the function is called!
		*    In general it is recommended to use GetClass()->GetAttributes() to obtain a list of attribute descriptors
		*    and then call GetAttribute() from the descriptor to get access to the actual attribute
		*/
		PLCORE_API const List<DynVar*> GetAttributes() const;

		/**
		*  @brief
		*    Get attribute
		*
		*  @param[in] sName
		*    Attribute name
		*
		*  @return
		*    Attribute (do not destroy the returned instance, can be a null pointer, if no attribute with that name could be found)
		*/
		PLCORE_API DynVar *GetAttribute(const String &sName) const;

		/**
		*  @brief
		*    Get all callable methods
		*
		*  @param[out] lstMethods
		*    Receives the list of callable methods, the given list is not cleared before new entries are added (do not destroy the returned instances)
		*
		*  @remarks
		*    Performance warning: Use this function with caution, as the list is assembled and callable method
		*    instances are created each time the function is called!
		*    If you only need the method descriptors, use GetClass()->GetMethods() instead.
		*/
		PLCORE_API void GetMethods(List<DynFuncPtr> &lstMethods);

		/**
		*  @brief
		*    Get callable method by using a given method name
		*
		*  @param[in] sName
		*    Method name
		*
		*  @return
		*    Callable method (do not destroy the returned instance, can be a null pointer, if no method with that name could be found)
		*
		*  @remarks
		*    Performance warning: Use this function with caution, as the callable method instance is
		*    created each time the function is called!
		*    If you only need the method descriptor, use GetClass()->GetMethod() instead.
		*/
		PLCORE_API DynFuncPtr GetMethod(const String &sName);

		/**
		*  @brief
		*    Get a list of all signals
		*
		*  @return
		*    List of signals (do not destroy the returned instances)
		*
		*  @remarks
		*    Use this function with caution, as the list is assembled and copied each time the function is called!
		*    In general it is recommended to use GetClass()->GetSignals() to obtain a list of signal descriptors
		*    and then call GetSignal() from the descriptor to get access to the actual signal
		*/
		PLCORE_API const List<DynEvent*> GetSignals() const;

		/**
		*  @brief
		*    Get signal by using a given signal name
		*
		*  @param[in] sName
		*    Signal name
		*
		*  @return
		*    Signal (do not destroy the returned instance, can be a null pointer, if no signal with that name could be found)
		*/
		PLCORE_API DynEvent *GetSignal(const String &sName) const;

		/**
		*  @brief
		*    Get a list of all slots
		*
		*  @return
		*    List of slots (do not destroy the returned instances)
		*
		*  @remarks
		*    Use this function with caution, as the list is assembled and copied each time the function is called!
		*    In general it is recommended to use GetClass()->GetSlots() to obtain a list of slot descriptors
		*    and then call GetSlot() from the descriptor to get access to the actual slot
		*/
		PLCORE_API const List<DynEventHandler*> GetSlots() const;

		/**
		*  @brief
		*    Get slot by using a given slot name
		*
		*  @param[in] sName
		*    Slot name
		*
		*  @return
		*    Slot (do not destroy the returned instance, can be a null pointer, if no slot with that name could be found)
		*/
		PLCORE_API DynEventHandler *GetSlot(const String &sName) const;

		//[-------------------------------------------------------]
		//[ Direct access functions                               ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Set attribute value by using a given string value
		*
		*  @param[in] sName
		*    Attribute name
		*  @param[in] sValue
		*    Attribute value as string
		*/
		PLCORE_API void SetAttribute(const String &sName, const String &sValue);

		/**
		*  @brief
		*    Set attribute value by using a given dynamic variable reference
		*
		*  @param[in] sName
		*    Attribute name
		*  @param[in] cVar
		*    Attribute value as dynamic variable reference
		*/
		PLCORE_API void SetAttribute(const String &sName, const DynVar &cVar);

		/**
		*  @brief
		*    Set attribute value by using a given dynamic variable pointer
		*
		*  @param[in] sName
		*    Attribute name
		*  @param[in] pVar
		*    Attribute value as dynamic variable pointer, in case of a null pointer, nothing happens at all
		*
		*  @remarks
		*    This is a comfort method allowing to write e.g.
		*      pFirstObject->SetAttribute("MyAttribute", pSecondObject->GetAttribute("MyAttribute"));
		*    instead of
		*      DynVar *pDynVar = pSecondObject->GetAttribute();
		*      if (pDynVar)
		*        pFirstObject->SetAttribute("MyAttribute", *pDynVar);
		*    In case there's no such attribute in "pSecondObject", nothing happens at all.
		*/
		PLCORE_API void SetAttribute(const String &sName, const DynVar *pVar);

		/**
		*  @brief
		*    Set attribute to it's default value
		*
		*  @param[in] sName
		*    Attribute name
		*/
		PLCORE_API void SetAttributeDefault(const String &sName);

		/**
		*  @brief
		*    Call method with given dynamic parameters
		*
		*  @param[in] sName
		*    Method name
		*  @param[in] cParams
		*    Dynamic parameters
		*/
		PLCORE_API void CallMethod(const String &sName, DynParams &cParams);

		/**
		*  @brief
		*    Call method with given constant dynamic parameters
		*
		*  @param[in] sName
		*    Method name
		*  @param[in] cParams
		*    Constant dynamic parameters
		*/
		PLCORE_API void CallMethod(const String &sName, const DynParams &cParams);

		/**
		*  @brief
		*    Call method with parameters given as string
		*
		*  @param[in] sName
		*    Method name
		*  @param[in] sParams
		*    Parameters as string
		*/
		PLCORE_API void CallMethod(const String &sName, const String &sParams);

		/**
		*  @brief
		*    Call method with parameters given as XML element
		*
		*  @param[in] sName
		*    Method name
		*  @param[in] cElement
		*    Parameters as XML element
		*/
		PLCORE_API void CallMethod(const String &sName, const XmlElement &cElement);

		//[-------------------------------------------------------]
		//[ Object state functions                                ]
		//[-------------------------------------------------------]
		/**
		*  @brief
		*    Get attribute values as a string
		*
		*  @param[in] nDefaultValue
		*    'WithDefault' to retrieve all attributes, 'NoDefault' to only retrieve attributes that are not set to default
		*
		*  @return
		*    String containing attributes and values
		*
		*  @remarks
		*    The returned string contains the attributes and their values.
		*    Example: "Name='Test' IntValue='10'"
		*/
		PLCORE_API String GetValues(EDefaultValue nDefaultValue = NoDefault) const;

		/**
		*  @brief
		*    Set multiple attribute values as a string at once
		*
		*  @param[in] sString
		*    String containing attributes and values (e.g. \"Name='Bob' Position='1 2 3'\")
		*/
		PLCORE_API void SetValues(const String &sVars);

		/**
		*  @brief
		*    Get attribute values as XML
		*
		*  @param[out] cElement
		*    XML element
		*  @param[in] nDefaultValue
		*    'WithDefault' to retrieve all attributes, 'NoDefault' to only retrieve attributes that are not set to default
		*
		*  @remarks
		*    The attributes and their values are added as XML-attributes to the given XML-element
		*/
		PLCORE_API void GetValuesXml(XmlElement &cElement, EDefaultValue nDefaultValue = NoDefault) const;

		/**
		*  @brief
		*    Set attribute values from XML
		*
		*  @param[out] cElement
		*    XML element
		*
		*  @remarks
		*    The attributes and their values are read from the XML-attributes of the given XML-element
		*/
		PLCORE_API void SetValuesXml(const XmlElement &cElement);

		/**
		*  @brief
		*    Set all attributes to default
		*/
		PLCORE_API void SetDefaultValues();


	//[-------------------------------------------------------]
	//[ Public virtual Object functions                       ]
	//[-------------------------------------------------------]
	public:
		/**
		*  @brief
		*    Get object as string
		*
		*  @return
		*    String representation of object
		*/
		PLCORE_API virtual String ToString() const;

		/**
		*  @brief
		*    Set object from string
		*
		*  @param[in] sString
		*    String representation of object
		*/
		PLCORE_API virtual void FromString(const String &sString);

		/**
		*  @brief
		*    Get object as XML
		*
		*  @return
		*    XML representation of object
		*/
		PLCORE_API virtual XmlElement ToXml() const;

		/**
		*  @brief
		*    Set object from XML
		*
		*  @param[in] cElement
		*    XML representation of object
		*/
		PLCORE_API virtual void FromXml(const XmlElement &cElement);


};


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLCore


#endif // __PLCORE_OBJECT_H__
