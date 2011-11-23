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



#include <osl/mutex.hxx>
#include <rtl/ustring.hxx>
#include <com/sun/star/uno/Reference.h>
#include <com/sun/star/uno/Reference.hxx>
#include <cppuhelper/interfacecontainer.h>
#include <cppuhelper/factory.hxx>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/uno/Exception.hpp>
#include <com/sun/star/lang/XComponent.hpp>
#include <com/sun/star/lang/XSingleServiceFactory.hpp>
#include <com/sun/star/registry/XRegistryKey.hpp>
#include <cppuhelper/factory.hxx>

#include "../dom/documentbuilder.hxx"
#include "../dom/saxbuilder.hxx"
#include "../xpath/xpathapi.hxx"
#include "../events/testlistener.hxx"

using namespace ::DOM;
using namespace ::DOM::events;
using namespace ::XPath;
using ::rtl::OUString;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::registry;

extern "C"
{

SAL_DLLPUBLIC_EXPORT void SAL_CALL
component_getImplementationEnvironment(const sal_Char **ppEnvironmentTypeName, uno_Environment ** /*ppEnvironment */)
{
	*ppEnvironmentTypeName = CPPU_CURRENT_LANGUAGE_BINDING_NAME ;
}

SAL_DLLPUBLIC_EXPORT void* SAL_CALL
component_getFactory(const sal_Char *pImplementationName, void *pServiceManager, void * /*pRegistryKey*/)
{
	void* pReturn = NULL ;
	if  ( pImplementationName && pServiceManager )
	{
		// Define variables which are used in following macros.
		Reference< XSingleServiceFactory > xFactory;
		Reference< XMultiServiceFactory >  xServiceManager(
			reinterpret_cast< XMultiServiceFactory* >(pServiceManager));

		if (CDocumentBuilder::_getImplementationName().compareToAscii( pImplementationName ) == 0 )
		{
			xFactory = Reference< XSingleServiceFactory >(
				cppu::createOneInstanceFactory(
					xServiceManager, CDocumentBuilder::_getImplementationName(),
					CDocumentBuilder::_getInstance, CDocumentBuilder::_getSupportedServiceNames()));
		}
        else if (CSAXDocumentBuilder::_getImplementationName().compareToAscii( pImplementationName ) == 0 )
		{
			xFactory = Reference< XSingleServiceFactory >(
				cppu::createSingleFactory(
					xServiceManager, CSAXDocumentBuilder::_getImplementationName(),
					CSAXDocumentBuilder::_getInstance, CSAXDocumentBuilder::_getSupportedServiceNames()));
		}
        else if (CXPathAPI::_getImplementationName().compareToAscii( pImplementationName ) == 0 )
		{
			xFactory = Reference< XSingleServiceFactory >(
				cppu::createSingleFactory(
					xServiceManager, CXPathAPI::_getImplementationName(),
					CXPathAPI::_getInstance, CXPathAPI::_getSupportedServiceNames()));
		}
        else if (CTestListener::_getImplementationName().compareToAscii( pImplementationName ) == 0 )
		{
			xFactory = Reference< XSingleServiceFactory >(
				cppu::createSingleFactory(
					xServiceManager, CTestListener::_getImplementationName(),
					CTestListener::_getInstance, CTestListener::_getSupportedServiceNames()));
		}

		// Factory is valid - service was found.
		if ( xFactory.is() )
		{
			xFactory->acquire();
			pReturn = xFactory.get();
		}
	}

	// Return with result of this operation.
	return pReturn ;
}

} // extern "C"
