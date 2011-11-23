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


#ifndef TOOLKIT_CONTROLS_TKSIMPLEANIMATION_HXX
#define TOOLKIT_CONTROLS_TKSIMPLEANIMATION_HXX

#include <toolkit/controls/unocontrolmodel.hxx>
#include <toolkit/helper/servicenames.hxx>
#include <toolkit/controls/unocontrolbase.hxx>
#include <toolkit/helper/macros.hxx>
#include <com/sun/star/graphic/XGraphic.hpp>
#include <com/sun/star/awt/XSimpleAnimation.hpp>
#include <comphelper/uno3.hxx>
#include <cppuhelper/implbase1.hxx>

//........................................................................
namespace toolkit
{
//........................................................................

	//====================================================================
	//= UnoSimpleAnimationControlModel
	//====================================================================
    class UnoSimpleAnimationControlModel : public UnoControlModel
    {
    protected:	
	    ::com::sun::star::uno::Any		ImplGetDefaultValue( sal_uInt16 nPropId ) const;
	    ::cppu::IPropertyArrayHelper&	SAL_CALL getInfoHelper();

    public:
						    UnoSimpleAnimationControlModel( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& i_factory );
						    UnoSimpleAnimationControlModel( const UnoSimpleAnimationControlModel& rModel ) : UnoControlModel( rModel ) {;}
    						
	    UnoControlModel*	Clone() const { return new UnoSimpleAnimationControlModel( *this ); }
    						
	    // XMultiPropertySet
        ::com::sun::star::uno::Reference< ::com::sun::star::beans::XPropertySetInfo > SAL_CALL getPropertySetInfo(  ) throw(::com::sun::star::uno::RuntimeException);

	    // XPersistObject
        ::rtl::OUString SAL_CALL getServiceName() throw(::com::sun::star::uno::RuntimeException);

	    // XServiceInfo
        ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
        ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames() throw(::com::sun::star::uno::RuntimeException);
    };

    //====================================================================
	//= UnoSimpleAnimationControl
	//====================================================================

    typedef ::cppu::AggImplInheritanceHelper1   <   UnoControlBase
                                                ,   ::com::sun::star::awt::XSimpleAnimation
                                                >   UnoSimpleAnimationControl_Base;

    class UnoSimpleAnimationControl : public UnoSimpleAnimationControl_Base
    {
    private:

    public:
								    UnoSimpleAnimationControl( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& i_factory );
	    ::rtl::OUString				GetComponentServiceName();

	    // XSimpleAnimation
        virtual void SAL_CALL start() throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL stop() throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL setImageList( const ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Reference< ::com::sun::star::graphic::XGraphic > >& ImageList )
                                            throw (::com::sun::star::uno::RuntimeException);

	    // XServiceInfo
        ::rtl::OUString SAL_CALL getImplementationName(  ) throw(::com::sun::star::uno::RuntimeException);
        ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames() throw(::com::sun::star::uno::RuntimeException);
    };

//........................................................................
} // namespacetoolkit
//........................................................................

#endif // TOOLKIT_CONTROLS_TKSIMPLEANIMATION_HXX
