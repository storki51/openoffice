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


#ifndef SC_VBA_CONTROLS_HXX
#define SC_VBA_CONTROLS_HXX

#include <cppuhelper/implbase1.hxx>
#include <ooo/vba/msforms/XControls.hpp>
#include <com/sun/star/awt/XControl.hpp>

#include <vbahelper/vbacollectionimpl.hxx>
#include <vbahelper/vbahelper.hxx>

typedef CollTestImplHelper< ov::msforms::XControls > ControlsImpl_BASE;

class ScVbaControls : public ControlsImpl_BASE
{
public:
    ScVbaControls(
        const css::uno::Reference< ov::XHelperInterface >& xParent,
        const css::uno::Reference< css::uno::XComponentContext >& xContext,
        const css::uno::Reference< css::awt::XControl >& xDialog,
        const css::uno::Reference< css::frame::XModel >& xModel,
        double fOffsetX, double fOffsetY );
    // XControls
    virtual void SAL_CALL Move( double cx, double cy ) throw (css::uno::RuntimeException);
    virtual css::uno::Any SAL_CALL Add( const css::uno::Any& Object, const css::uno::Any& StringKey, const css::uno::Any& Before, const css::uno::Any& After ) throw (css::uno::RuntimeException);
    virtual void SAL_CALL Remove( const css::uno::Any& StringKeyOrIndex ) throw (css::uno::RuntimeException);

    // XEnumerationAccess
    virtual css::uno::Type SAL_CALL getElementType() throw (css::uno::RuntimeException);
    virtual css::uno::Reference< css::container::XEnumeration > SAL_CALL createEnumeration() throw (css::uno::RuntimeException);

    // ScVbaCollectionBaseImpl
    virtual css::uno::Any createCollectionObject( const css::uno::Any& aSource );
    
    // XHelperInterface
    VBAHELPER_DECL_XHELPERINTERFACE

private:
	css::uno::Reference< css::awt::XControl > mxDialog;
    css::uno::Reference< css::frame::XModel > mxModel;
	double mfOffsetX;
    double mfOffsetY;
};

#endif //SC_VBA_OLEOBJECTS_HXX

