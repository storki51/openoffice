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


#ifndef SW_VBA_BORDERS_HXX
#define SW_VBA_BORDERS_HXX

#include <cppuhelper/implbase1.hxx>
#include <ooo/vba/word/XBorders.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/table/XCellRange.hpp>
#include <com/sun/star/beans/XPropertySet.hpp>
#include <vbahelper/vbacollectionimpl.hxx>

typedef CollTestImplHelper< ov::word::XBorders > SwVbaBorders_BASE;
class VbaPalette;
class SwVbaBorders : public SwVbaBorders_BASE
{
	// XEnumerationAccess
	virtual css::uno::Any getItemByIntIndex( const sal_Int32 nIndex ) throw (css::uno::RuntimeException);
	css::uno::Reference< css::beans::XPropertySet > m_xProps;
public:
	SwVbaBorders( const css::uno::Reference< ov::XHelperInterface >& xParent, const css::uno::Reference< css::uno::XComponentContext > & xContext, const css::uno::Reference< css::table::XCellRange >& xRange, VbaPalette& rPalette );
	virtual ~SwVbaBorders() {}

	// XEnumerationAccess
	virtual css::uno::Type SAL_CALL getElementType() throw (css::uno::RuntimeException);
	virtual css::uno::Reference< css::container::XEnumeration > SAL_CALL createEnumeration() throw (css::uno::RuntimeException);

	// SwVbaCollectionBaseImpl	
	virtual css::uno::Any createCollectionObject( const css::uno::Any& aSource ); 
	
	virtual sal_Bool SAL_CALL getShadow() throw (css::uno::RuntimeException);
	virtual void SAL_CALL setShadow( sal_Bool _shadow ) throw (css::uno::RuntimeException);

	virtual rtl::OUString& getServiceImplName();
	virtual css::uno::Sequence<rtl::OUString> getServiceNames();
};

#endif //SW_VBA_BORDERS_HXX

