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


#ifndef SW_VBA_WINDOW_HXX
#define SW_VBA_WINDOW_HXX
#include <cppuhelper/implbase1.hxx>
#include <ooo/vba/word/XWindow.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>

#include <vbahelper/vbahelperinterface.hxx>
#include <vbahelper/vbawindowbase.hxx>

typedef cppu::ImplInheritanceHelper1< VbaWindowBase, ov::word::XWindow > WindowImpl_BASE;

class SwVbaWindow : public WindowImpl_BASE
{		
public:	
    SwVbaWindow(
        const css::uno::Reference< ov::XHelperInterface >& xParent,
        const css::uno::Reference< css::uno::XComponentContext >& xContext,
        const css::uno::Reference< css::frame::XModel >& xModel,
        const css::uno::Reference< css::frame::XController >& xController )
        throw (css::uno::RuntimeException);

    // Attributes
    virtual css::uno::Any SAL_CALL getView() throw (css::uno::RuntimeException);
    virtual void SAL_CALL setView( const css::uno::Any& _view ) throw (css::uno::RuntimeException);
	// Methods
	virtual void SAL_CALL Activate(  ) throw (css::uno::RuntimeException);
	virtual void SAL_CALL Close( const css::uno::Any& SaveChanges, const css::uno::Any& RouteDocument ) throw (css::uno::RuntimeException);
    virtual css::uno::Any SAL_CALL Panes( const css::uno::Any& aIndex ) throw (css::uno::RuntimeException);
    virtual css::uno::Any SAL_CALL ActivePane() throw (css::uno::RuntimeException);
	// XHelperInterface
	virtual rtl::OUString& getServiceImplName();
	virtual css::uno::Sequence<rtl::OUString> getServiceNames();
};

#endif //SW_VBA_WINDOW_HXX
