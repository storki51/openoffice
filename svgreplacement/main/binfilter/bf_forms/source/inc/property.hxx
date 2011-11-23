/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



#ifndef _FRM_PROPERTY_HXX_
#define _FRM_PROPERTY_HXX_



#ifndef _COMPHELPER_PROPERTY_AGGREGATION_HXX_
#include <comphelper/propagg.hxx>
#endif
#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif
namespace binfilter {

	using namespace ::comphelper;

//=========================================================================
//= property helper classes
//=========================================================================

//... namespace frm .......................................................
namespace frm
{
//.........................................................................

//==================================================================
//= assigment property handle <-> property name
//= used by the PropertySetAggregationHelper
//==================================================================

class PropertyInfoService
{
	//..................................................................
	struct PropertyAssignment
	{
		::rtl::OUString		sName;
		sal_Int32			nHandle;

		PropertyAssignment() { nHandle = -1; }
		PropertyAssignment(const PropertyAssignment& _rSource)
			:sName(_rSource.sName), nHandle(_rSource.nHandle) { }
		PropertyAssignment(const ::rtl::OUString& _rName, sal_Int32 _nHandle)
			:sName(_rName), nHandle(_nHandle) { }

	};

	DECLARE_STL_VECTOR(PropertyAssignment, PropertyMap);
	static PropertyMap		s_AllKnownProperties;

	//..................................................................
	// comparing two PropertyAssignment's
public:
	typedef PropertyAssignment PUBLIC_SOLARIS_COMPILER_HACK;
		// did not get the following compiled under with SUNPRO 5 without this
		// public typedef
private:
	friend struct PropertyAssignmentNameCompareLess;
	typedef ::std::binary_function< PUBLIC_SOLARIS_COMPILER_HACK, PUBLIC_SOLARIS_COMPILER_HACK, sal_Bool > PropertyAssignmentNameCompareLess_Base;
	struct PropertyAssignmentNameCompareLess : public PropertyAssignmentNameCompareLess_Base
	{
		inline sal_Bool operator() (const PUBLIC_SOLARIS_COMPILER_HACK& _rL, const PUBLIC_SOLARIS_COMPILER_HACK& _rR) const
		{
			return (_rL.sName.compareTo(_rR.sName) < 0);
		}
	};

public:
	PropertyInfoService() { }

public:
	static sal_Int32			getPropertyId(const ::rtl::OUString& _rName);
	static ::rtl::OUString		getPropertyName(sal_Int32 _nHandle);

private:
	static void initialize();
};

//..................................................................
// a class implementing the comphelper::IPropertyInfoService
class ConcretInfoService : public ::comphelper::IPropertyInfoService
{
public:
	virtual	sal_Int32 getPreferedPropertyId(const ::rtl::OUString& _rName);
};

//------------------------------------------------------------------------------
#define DECL_PROP_IMPL(varname, type) \
        pProps[nPos++] = com::sun::star::beans::Property(PROPERTY_##varname, PROPERTY_ID_##varname, ::getCppuType(reinterpret_cast< type* >(NULL)),

//------------------------------------------------------------------------------
#define DECL_BOOL_PROP_IMPL(varname) \
pProps[nPos++] = com::sun::star::beans::Property(PROPERTY_##varname, PROPERTY_ID_##varname, ::getBooleanCppuType(),

//------------------------------------------------------------------------------
#define DECL_IFACE_PROP_IMPL(varname, type) \
pProps[nPos++] = com::sun::star::beans::Property(PROPERTY_##varname, PROPERTY_ID_##varname, ::getCppuType(reinterpret_cast< com::sun::star::uno::Reference< type >* >(NULL)),

//------------------------------------------------------------------------------
#define BEGIN_AGGREGATION_PROPERTY_HELPER(count, aggregate)	\
	_rProps.realloc(count);	\
        com::sun::star::beans::Property* pProps = _rProps.getArray();       \
	sal_Int32 nPos = 0;	\
	\
	if (aggregate.is())	\
		_rAggregateProps = aggregate->getPropertySetInfo()->getProperties();	\

//------------------------------------------------------------------------------
#define BEGIN_PROPERTY_ARRAY_HELPER(count)	\
	staruno::Sequence<starbeans::Property> aProps(count);	\
	starbeans::Property* pProps = aProps.getArray();	\
	sal_Int32 nPos = 0;	\

// ===
//------------------------------------------------------------------------------
#define DECL_PROP0(varname, type)	\
	DECL_PROP_IMPL(varname, type) 0)

//------------------------------------------------------------------------------
#define DECL_PROP1(varname, type, attrib1)	\
        DECL_PROP_IMPL(varname, type) com::sun::star::beans::PropertyAttribute::attrib1)

//------------------------------------------------------------------------------
#define DECL_PROP2(varname, type, attrib1, attrib2)	\
        DECL_PROP_IMPL(varname, type) com::sun::star::beans::PropertyAttribute::attrib1 | com::sun::star::beans::PropertyAttribute::attrib2)

//------------------------------------------------------------------------------
#define DECL_PROP3(varname, type, attrib1, attrib2, attrib3)	\
        DECL_PROP_IMPL(varname, type) com::sun::star::beans::PropertyAttribute::attrib1 | com::sun::star::beans::PropertyAttribute::attrib2 | com::sun::star::beans::PropertyAttribute::attrib3)

//------------------------------------------------------------------------------
#define DECL_PROP4(varname, type, attrib1, attrib2, attrib3, attrib4)	\
        DECL_PROP_IMPL(varname, type) com::sun::star::beans::PropertyAttribute::attrib1 | com::sun::star::beans::PropertyAttribute::attrib2 | com::sun::star::beans::PropertyAttribute::attrib3 | com::sun::star::beans::PropertyAttribute::attrib4)

// === some property types require special handling
// === such as interfaces
//------------------------------------------------------------------------------
#define DECL_IFACE_PROP0(varname, type)	\
	DECL_IFACE_PROP_IMPL(varname, type) 0)

//------------------------------------------------------------------------------
#define DECL_IFACE_PROP1(varname, type, attrib1)	\
	DECL_IFACE_PROP_IMPL(varname, type) starbeans::PropertyAttribute::attrib1)

//------------------------------------------------------------------------------
#define DECL_IFACE_PROP2(varname, type, attrib1, attrib2)	\
        DECL_IFACE_PROP_IMPL(varname, type) com::sun::star::beans::PropertyAttribute::attrib1 | com::sun::star::beans::PropertyAttribute::attrib2)

//------------------------------------------------------------------------------
#define DECL_IFACE_PROP3(varname, type, attrib1, attrib2, attrib3)	\
	DECL_IFACE_PROP_IMPL(varname, type) starbeans::PropertyAttribute::attrib1 | starbeans::PropertyAttribute::attrib2 | starbeans::PropertyAttribute::attrib3)

//------------------------------------------------------------------------------
#define DECL_IFACE_PROP4(varname, type, attrib1, attrib2, attrib3, attrib4)	\
	DECL_IFACE_PROP_IMPL(varname, type) starbeans::PropertyAttribute::attrib1 | starbeans::PropertyAttribute::attrib2 | starbeans::PropertyAttribute::attrib3 | PropertyAttribute::attrib4)

// === or Boolean properties
//------------------------------------------------------------------------------
#define DECL_BOOL_PROP0(varname)	\
	DECL_BOOL_PROP_IMPL(varname) 0)

//------------------------------------------------------------------------------
#define DECL_BOOL_PROP1(varname, attrib1)	\
        DECL_BOOL_PROP_IMPL(varname) com::sun::star::beans::PropertyAttribute::attrib1)

//------------------------------------------------------------------------------
#define DECL_BOOL_PROP2(varname, attrib1, attrib2)	\
        DECL_BOOL_PROP_IMPL(varname) com::sun::star::beans::PropertyAttribute::attrib1 | com::sun::star::beans::PropertyAttribute::attrib2)

// ===
//------------------------------------------------------------------------------
#define END_AGGREGATION_PROPERTY_HELPER()	\
	DBG_ASSERT(nPos == _rProps.getLength(), "<...>::getInfohelper : forgot to adjust the count ?");	\

//------------------------------------------------------------------------------
#define END_PROPERTY_ARRAY_HELPER()	\
	DBG_ASSERT(nPos == aProps.getLength(), "<...>::getInfohelper : forgot to adjust the count ?");	\
	return new ::cppu::OPropertyArrayHelper(aProps);

//.........................................................................
}
//... namespace frm .......................................................

}//end of namespace binfilter
#endif // _FRM_PROPERTY_HXX_

