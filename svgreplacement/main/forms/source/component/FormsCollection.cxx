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



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_forms.hxx"

#include "FormsCollection.hxx"
#include "services.hxx"
#include <comphelper/sequence.hxx>
#include <tools/debug.hxx>
#include <com/sun/star/form/XForm.hpp>
#include <rtl/logfile.hxx>

//.........................................................................
namespace frm
{
//.........................................................................
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::form;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::util;

//------------------------------------------------------------------
DBG_NAME(OFormsCollection)
//------------------------------------------------------------------
InterfaceRef SAL_CALL OFormsCollection_CreateInstance(const Reference<XMultiServiceFactory>& _rxFactory)
{
	return *(new OFormsCollection(_rxFactory));
}

//------------------------------------------------------------------------------
::rtl::OUString SAL_CALL OFormsCollection::getServiceName() throw(RuntimeException)
{
	return FRM_SUN_FORMS_COLLECTION;
}

//------------------------------------------------------------------------------
Sequence< sal_Int8 > SAL_CALL OFormsCollection::getImplementationId(  ) throw(RuntimeException)
{
	return OImplementationIds::getImplementationId(getTypes());
}

//------------------------------------------------------------------------------
Sequence<Type> SAL_CALL OFormsCollection::getTypes() throw(RuntimeException)
{
	return concatSequences(OInterfaceContainer::getTypes(), FormsCollectionComponentBase::getTypes(), OFormsCollection_BASE::getTypes());
}

//------------------------------------------------------------------
OFormsCollection::OFormsCollection(const Reference<XMultiServiceFactory>& _rxFactory)
    :FormsCollectionComponentBase( m_aMutex )
    ,OInterfaceContainer( _rxFactory, m_aMutex, XForm::static_type() )
    ,OFormsCollection_BASE()
{
	DBG_CTOR(OFormsCollection, NULL);
}

//------------------------------------------------------------------------------
OFormsCollection::OFormsCollection( const OFormsCollection& _cloneSource )
    :FormsCollectionComponentBase( m_aMutex )
    ,OInterfaceContainer( m_aMutex, _cloneSource )
    ,OFormsCollection_BASE()
{
	DBG_CTOR( OFormsCollection, NULL );
}

//------------------------------------------------------------------------------
OFormsCollection::~OFormsCollection()
{
	DBG_DTOR(OFormsCollection, NULL);
	if (!FormsCollectionComponentBase::rBHelper.bDisposed)
	{
		acquire();
		dispose();
	}
}

//------------------------------------------------------------------------------
Any SAL_CALL OFormsCollection::queryAggregation(const Type& _rType) throw(RuntimeException)
{
	Any aReturn = OFormsCollection_BASE::queryInterface(_rType);
	if (!aReturn.hasValue())
	{
		aReturn = OInterfaceContainer::queryInterface(_rType);

		if (!aReturn.hasValue())
			aReturn = FormsCollectionComponentBase::queryAggregation(_rType);
	}

	return aReturn;
}

//------------------------------------------------------------------------------
::rtl::OUString SAL_CALL OFormsCollection::getImplementationName() throw(RuntimeException)
{
	return ::rtl::OUString::createFromAscii("com.sun.star.comp.forms.OFormsCollection");
}

//------------------------------------------------------------------------------
sal_Bool SAL_CALL OFormsCollection::supportsService( const ::rtl::OUString& _rServiceName ) throw(RuntimeException)
{
	Sequence<rtl::OUString> aSupported = getSupportedServiceNames();
	const rtl::OUString* pSupported = aSupported.getConstArray();
	for (sal_Int32 i=0; i<aSupported.getLength(); ++i, ++pSupported)
		if (pSupported->equals(_rServiceName))
			return sal_True;
	return sal_False;
}

//------------------------------------------------------------------------------
StringSequence SAL_CALL OFormsCollection::getSupportedServiceNames() throw(RuntimeException)
{
	StringSequence aReturn(2);

	aReturn.getArray()[0] = FRM_SUN_FORMS_COLLECTION;
	aReturn.getArray()[1] = ::rtl::OUString::createFromAscii("com.sun.star.form.FormComponents");

	return aReturn;
}

// XCloneable
//------------------------------------------------------------------------------
Reference< XCloneable > SAL_CALL OFormsCollection::createClone(  ) throw (RuntimeException)
{
    OFormsCollection* pClone = new OFormsCollection( *this );
    osl_incrementInterlockedCount( &pClone->m_refCount );
    pClone->clonedFrom( *this );
    osl_decrementInterlockedCount( &pClone->m_refCount );
    return pClone;
}

// OComponentHelper
//------------------------------------------------------------------------------
void OFormsCollection::disposing()
{
	{
		RTL_LOGFILE_CONTEXT( aLogger, "forms::OFormsCollection::disposing" );
		OInterfaceContainer::disposing();
	}
	FormsCollectionComponentBase::disposing();
	m_xParent = NULL;
}

//XChild
//------------------------------------------------------------------------------
void OFormsCollection::setParent(const InterfaceRef& Parent) throw( NoSupportException, RuntimeException )
{
	::osl::MutexGuard aGuard( m_aMutex );
	m_xParent = Parent;
}

//------------------------------------------------------------------------------
InterfaceRef  OFormsCollection::getParent() throw( RuntimeException )
{
	return m_xParent;
}

//.........................................................................
}	// namespace frm
//.........................................................................

