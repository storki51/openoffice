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
#include "precompiled_extensions.hxx"

#include<osl/module.hxx>
#include <osl/time.h>
#include <rtl/ustring.hxx>
#include <stdio.h>
#include <cppuhelper/factory.hxx>
#include <cppuhelper/servicefactory.hxx>
#include <cppuhelper/bootstrap.hxx>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/lang/XSingleServiceFactory.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XComponent.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/registry/XSimpleRegistry.hpp>

#include <stdio.h>
using namespace ::rtl;
using namespace ::osl;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::lang;
using namespace ::cppu;
using namespace ::com::sun::star::registry;


sal_Bool test1();
sal_Bool test2();
sal_Bool test3();
sal_Bool test4();

int main(int, char**)
{
   	sal_Bool bTest1= test1();
   	sal_Bool bTest2= test2();
	sal_Bool bTest3= test3();
	sal_Bool bTest4= test4();

	if( bTest1 && bTest2 && bTest3 && bTest4)
		printf("\n#########################\n Test was successful\n#######################\n");

	return 0;
}

sal_Bool test1()
{
	printf("\n Test1:  com.sun.star.bridge.oleautomation.BridgeSupplier\n");
	Reference<XSimpleRegistry> xreg= createSimpleRegistry();
	xreg->open( OUString( RTL_CONSTASCII_USTRINGPARAM("services.rdb")),
							   sal_False, sal_False );

	Reference< XComponentContext > context= bootstrap_InitialComponentContext(xreg);
	Reference<XMultiComponentFactory> fac= context->getServiceManager();
	OUString sService1( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.bridge.oleautomation.BridgeSupplier"));
	Reference<XInterface> xint1= fac->createInstanceWithContext( sService1, context);

	OUString sModule(
        RTL_CONSTASCII_USTRINGPARAM("oleautobridge.uno" SAL_DLLEXTENSION));
	oslModule hMod= osl_loadModule( sModule.pData, 0);
	osl_unloadModule( hMod);

	rtl_unloadUnusedModules( NULL);
	
	OUString sFactoryFunc( RTL_CONSTASCII_USTRINGPARAM("component_getFactory"));
	void* pSymbol= osl_getSymbol( hMod,sFactoryFunc.pData);
	// true, instance alive
	sal_Bool bTest1= pSymbol ? sal_True : sal_False;

	xint1=0;
	rtl_unloadUnusedModules( NULL);
	pSymbol= osl_getSymbol( hMod,sFactoryFunc.pData);
	sal_Bool bTest2= pSymbol ? sal_False : sal_True;

	Reference<XComponent> xcomp( context, UNO_QUERY);
	xcomp->dispose();

	return bTest2 && bTest1;
}

sal_Bool test2()
{
	printf("Test2:  com.sun.star.bridge.OleBridgeSupplierVar1\n");
	Reference<XSimpleRegistry> xreg= createSimpleRegistry();
	xreg->open( OUString( RTL_CONSTASCII_USTRINGPARAM("services.rdb")),
							   sal_False, sal_False );

	Reference< XComponentContext > context= bootstrap_InitialComponentContext(xreg);
	Reference<XMultiComponentFactory> fac= context->getServiceManager();
  	OUString sService2( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.bridge.OleBridgeSupplierVar1"));
	Reference<XInterface> xint= fac->createInstanceWithContext( sService2, context);

	OUString sModule(
        RTL_CONSTASCII_USTRINGPARAM("oleautobridge.uno" SAL_DLLEXTENSION));
	oslModule hMod= osl_loadModule( sModule.pData, 0);
	osl_unloadModule( hMod);

	rtl_unloadUnusedModules( NULL);
	OUString sFactoryFunc( RTL_CONSTASCII_USTRINGPARAM("component_getFactory"));
	void* pSymbol= osl_getSymbol( hMod,sFactoryFunc.pData);
	// true, instance alive
	sal_Bool bTest1= pSymbol ? sal_True : sal_False;

	xint=0;
	rtl_unloadUnusedModules( NULL);
	pSymbol= osl_getSymbol( hMod,sFactoryFunc.pData);
	sal_Bool bTest2= pSymbol ? sal_False : sal_True;

	Reference<XComponent> xcomp( context, UNO_QUERY);
	xcomp->dispose();
	return bTest1 && bTest2;
}

sal_Bool test3()
{
	printf("Test3:  com.sun.star.bridge.oleautomation.Factory\n");
	Reference<XSimpleRegistry> xreg= createSimpleRegistry();
	xreg->open( OUString( RTL_CONSTASCII_USTRINGPARAM("services.rdb")),
				sal_False, sal_False );
	
	Reference< XComponentContext > context= bootstrap_InitialComponentContext(xreg);

	Reference<XMultiComponentFactory> fac= context->getServiceManager();
  	OUString sService( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.bridge.oleautomation.Factory"));
	Reference<XInterface> xint= fac->createInstanceWithContext( sService, context);


	OUString sModule(
        RTL_CONSTASCII_USTRINGPARAM("oleautobridge.uno" SAL_DLLEXTENSION));
	oslModule hMod= osl_loadModule( sModule.pData, 0);
	osl_unloadModule( hMod);

	rtl_unloadUnusedModules( NULL);
	OUString sFactoryFunc( RTL_CONSTASCII_USTRINGPARAM("component_getFactory"));
	void* pSymbol= osl_getSymbol( hMod,sFactoryFunc.pData);
	// true, instance alive
	sal_Bool bTest1= pSymbol ? sal_True : sal_False;

	xint=0;
	rtl_unloadUnusedModules( NULL);
	pSymbol= osl_getSymbol( hMod,sFactoryFunc.pData);
	sal_Bool bTest2= pSymbol ? sal_False : sal_True;

	Reference<XComponent> xcomp( context, UNO_QUERY);
	xcomp->dispose();

//	for (int i=0; i < 10; i++)
//	{	
//		Reference<XSimpleRegistry> xreg= createSimpleRegistry();
//		xreg->open( OUString( RTL_CONSTASCII_USTRINGPARAM("applicat.rdb")),
//							   sal_False, sal_False );
//		Reference< XComponentContext > context= bootstrap_InitialComponentContext(xreg);	
//		Reference<XComponent> xcomp( context, UNO_QUERY);
//		xcomp->dispose();
//
//	}

//	return sal_True;
	return bTest1 && bTest2;
}

sal_Bool test4()
{
	void* pSymbol= NULL;
	sal_Bool bTest1= sal_False;
	sal_Bool bTest2= sal_False;
	oslModule hMod= NULL;
	OUString sModule(
        RTL_CONSTASCII_USTRINGPARAM("oleautobridge.uno" SAL_DLLEXTENSION));
	OUString sFactoryFunc( RTL_CONSTASCII_USTRINGPARAM("component_getFactory"));
	{
	printf("Test4:  com.sun.star.bridge.oleautomation.ApplicationRegistration\n");
   	Reference<XSimpleRegistry> xreg= createSimpleRegistry();
	xreg->open( OUString( RTL_CONSTASCII_USTRINGPARAM("services.rdb")),
							   sal_False, sal_False );

	Reference< XComponentContext > context= bootstrap_InitialComponentContext(xreg);
	Reference<XMultiComponentFactory> fac= context->getServiceManager();
	OUString sService4( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.bridge.oleautomation.ApplicationRegistration"));
	Reference<XInterface> xint= fac->createInstanceWithContext( sService4, context);

	hMod= osl_loadModule( sModule.pData, 0);
	osl_unloadModule( hMod);

	rtl_unloadUnusedModules( NULL);
	void* pSymbol= osl_getSymbol( hMod,sFactoryFunc.pData);
	// true, instance alive
	bTest1= pSymbol ? sal_True : sal_False;
	// ApplicationRegistration is a one-instance-service, therefore kill service manager first
	Reference<XComponent> xcomp( context, UNO_QUERY);
	xcomp->dispose();
	
	}
	rtl_unloadUnusedModules( NULL);
	pSymbol= osl_getSymbol( hMod,sFactoryFunc.pData);
	bTest2= pSymbol ? sal_False : sal_True;

	return bTest1 && bTest2;
}
