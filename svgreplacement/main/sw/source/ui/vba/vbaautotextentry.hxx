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


#ifndef SW_VBA_AUTOTEXTENTRY_HXX
#define SW_VBA_AUTOTEXTENTRY_HXX

#include <vbahelper/vbacollectionimpl.hxx>
#include <ooo/vba/word/XAutoTextEntries.hpp>
#include <ooo/vba/word/XAutoTextEntry.hpp>
#include <vbahelper/vbahelperinterface.hxx>
#include <cppuhelper/implbase1.hxx>
#include <ooo/vba/word/XRange.hpp>
#include <com/sun/star/text/XAutoTextEntry.hpp>

typedef InheritedHelperInterfaceImpl1< ooo::vba::word::XAutoTextEntry > SwVbaAutoTextEntry_BASE;

class SwVbaAutoTextEntry : public SwVbaAutoTextEntry_BASE
{
private:
    css::uno::Reference< css::text::XAutoTextEntry > mxEntry;

public:
	SwVbaAutoTextEntry( const css::uno::Reference< ooo::vba::XHelperInterface >& rParent, const css::uno::Reference< css::uno::XComponentContext >& rContext, const css::uno::Reference< css::text::XAutoTextEntry >& xEntry ) throw ( css::uno::RuntimeException );
	virtual ~SwVbaAutoTextEntry();

    // XAutoTextEntry
    virtual css::uno::Reference< ooo::vba::word::XRange > SAL_CALL Insert( const css::uno::Reference< ooo::vba::word::XRange >& _where, const css::uno::Any& _richtext ) throw ( css::uno::RuntimeException );

	// XHelperInterface
	virtual rtl::OUString& getServiceImplName();
	virtual css::uno::Sequence<rtl::OUString> getServiceNames();
};


/* class SwVbaAutoTextEntries */
typedef CollTestImplHelper< ooo::vba::word::XAutoTextEntries > SwVbaAutoTextEntries_BASE;

class SwVbaAutoTextEntries : public SwVbaAutoTextEntries_BASE
{
private:
    css::uno::Reference< css::container::XIndexAccess > mxAutoTextEntryAccess;

public:
	SwVbaAutoTextEntries( const css::uno::Reference< ov::XHelperInterface >& xParent, const css::uno::Reference< css::uno::XComponentContext > & xContext, const css::uno::Reference< css::container::XIndexAccess >& xIndexAccess ) throw (css::uno::RuntimeException);
	virtual ~SwVbaAutoTextEntries() {}

	// XEnumerationAccess
	virtual css::uno::Type SAL_CALL getElementType() throw (css::uno::RuntimeException);
	virtual css::uno::Reference< css::container::XEnumeration > SAL_CALL createEnumeration() throw (css::uno::RuntimeException);

	// SwVbaAutoTextEntries_BASE
	virtual css::uno::Any createCollectionObject( const css::uno::Any& aSource ); 
	virtual rtl::OUString& getServiceImplName();
	virtual css::uno::Sequence<rtl::OUString> getServiceNames();
};    

#endif /* SW_VBA_AUTOTEXTENTRY_HXX */
