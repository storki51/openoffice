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
#include "precompiled_connectivity.hxx"
#include "NDriver.hxx"
#include "NConnection.hxx"
#include <com/sun/star/lang/DisposedException.hpp>
#include "connectivity/dbexception.hxx"
//#ifndef _CONNECTIVITY_EVOAB_CONFIGACCESS_HXX_
//#include "LConfigAccess.hxx"
//#endif
#include <osl/file.hxx>
#include "osl/security.hxx"
#include <comphelper/processfactory.hxx>
#include <com/sun/star/ucb/XContentAccess.hpp>
#include <com/sun/star/ucb/XCommandEnvironment.hpp>
#include <ucbhelper/content.hxx>
#include <tools/debug.hxx>
#include "NDebug.hxx"
#include <signal.h>
#include "resource/common_res.hrc"
#include "resource/sharedresources.hxx"

using namespace osl;
using namespace connectivity::evoab;
//using namespace connectivity::file;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::sdbcx;
using namespace ::com::sun::star::sdbc;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::ucb;

// --------------------------------------------------------------------------------
OEvoabDriver::OEvoabDriver(const Reference< XMultiServiceFactory >& _rxFactory) :
		ODriver_BASE( m_aMutex ), m_xFactory( _rxFactory )
{
}
// -----------------------------------------------------------------------------
OEvoabDriver::~OEvoabDriver()
{
}
// -----------------------------------------------------------------------------
void OEvoabDriver::disposing()
{
	::osl::MutexGuard aGuard(m_aMutex);
	
	// when driver will be destroied so all our connections have to be destroied as well
	for (OWeakRefArray::iterator i = m_xConnections.begin(); m_xConnections.end() != i; ++i)
	{
		Reference< XComponent > xComp(i->get(), UNO_QUERY);
		if (xComp.is()) {
		    try {	
			xComp->dispose();
			}
		    catch (com::sun::star::lang::DisposedException e) {
			 xComp.clear();
			}
		}
	}
	m_xConnections.clear();
	connectivity::OWeakRefArray().swap(m_xConnections); // this really clears

	ODriver_BASE::disposing();
}

// static ServiceInfo
//------------------------------------------------------------------------------
rtl::OUString OEvoabDriver::getImplementationName_Static(  ) throw(RuntimeException)
{
	return rtl::OUString::createFromAscii(EVOAB_DRIVER_IMPL_NAME);
	// this name is referenced in the configuration and in the evoab.xml
	// Please take care when changing it.
}

//------------------------------------------------------------------
Sequence< ::rtl::OUString > OEvoabDriver::getSupportedServiceNames_Static(  ) throw (RuntimeException)
{
	// which service is supported 
	// for more information @see com.sun.star.sdbc.Driver
	Sequence< ::rtl::OUString > aSNS( 1 );
	aSNS[0] = ::rtl::OUString::createFromAscii("com.sun.star.sdbc.Driver");
	return aSNS;
}
//------------------------------------------------------------------
::rtl::OUString SAL_CALL OEvoabDriver::getImplementationName(  ) throw(RuntimeException)
{
	return getImplementationName_Static();
}
//------------------------------------------------------------------
sal_Bool SAL_CALL OEvoabDriver::supportsService( const ::rtl::OUString& _rServiceName ) throw(RuntimeException)
{
    Sequence< ::rtl::OUString > aSupported(getSupportedServiceNames());
	const ::rtl::OUString* pSupported = aSupported.getConstArray();
	const ::rtl::OUString* pEnd = pSupported + aSupported.getLength();
	for (;pSupported != pEnd && !pSupported->equals(_rServiceName); ++pSupported)
		;

	return pSupported != pEnd;
}
//------------------------------------------------------------------
Sequence< ::rtl::OUString > SAL_CALL OEvoabDriver::getSupportedServiceNames(  ) throw(RuntimeException)
{
	return getSupportedServiceNames_Static();
}

//------------------------------------------------------------------
::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface >  SAL_CALL connectivity::evoab::OEvoabDriver_CreateInstance(const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& _rxFactory) throw( ::com::sun::star::uno::Exception )
{
	return *(new OEvoabDriver(_rxFactory));
}
// --------------------------------------------------------------------------------
Reference< XConnection > SAL_CALL OEvoabDriver::connect( const ::rtl::OUString& url, const Sequence< PropertyValue >& info ) throw(SQLException, RuntimeException)
{
	::osl::MutexGuard aGuard( m_aMutex );
	if (ODriver_BASE::rBHelper.bDisposed)
		throw DisposedException();
	
	if ( ! acceptsURL(url) )
		return NULL;
	
	OEvoabConnection* pCon = new OEvoabConnection( *this );
	pCon->construct(url,info);
        Reference< XConnection > xCon = pCon;
        m_xConnections.push_back(WeakReferenceHelper(*pCon));
	
	return xCon;
}
// --------------------------------------------------------------------------------
sal_Bool SAL_CALL OEvoabDriver::acceptsURL( const ::rtl::OUString& url )
	throw(SQLException, RuntimeException)
{
	return acceptsURL_Stat(url);
}

// --------------------------------------------------------------------------------
Sequence< DriverPropertyInfo > SAL_CALL OEvoabDriver::getPropertyInfo( const ::rtl::OUString& url, const Sequence< PropertyValue >& /*info*/ ) throw(SQLException, RuntimeException)
{
	if ( ! acceptsURL(url) )
    {
        ::connectivity::SharedResources aResources;
        const ::rtl::OUString sMessage = aResources.getResourceString(STR_URI_SYNTAX_ERROR);
		::dbtools::throwGenericSQLException(sMessage ,*this);
    } // if ( ! acceptsURL(url) )

	// if you have somthing special to say return it here :-)
	return Sequence< DriverPropertyInfo >();
}

// --------------------------------------------------------------------------------
sal_Int32 SAL_CALL OEvoabDriver::getMajorVersion(  ) throw(RuntimeException)
{
	return 1;
}
// --------------------------------------------------------------------------------
sal_Int32 SAL_CALL OEvoabDriver::getMinorVersion(  ) throw(RuntimeException)
{
	return 0;
}
// --------------------------------------------------------------------------------
sal_Bool OEvoabDriver::acceptsURL_Stat( const ::rtl::OUString& url )
{
	return (url.equalsAscii("sdbc:address:evolution:local") || url.equalsAscii("sdbc:address:evolution:groupwise")||url.equalsAscii("sdbc:address:evolution:ldap"))&& EApiInit();
}
// -----------------------------------------------------------------------------
