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



#ifndef __FRAMEWORK_CLASSES_ACTIONTRIGGERPROPERTYSET_HXX_
#define __FRAMEWORK_CLASSES_ACTIONTRIGGERPROPERTYSET_HXX_

#include <threadhelp/threadhelpbase.hxx>
#include <cppuhelper/propshlp.hxx>
#include <cppuhelper/weak.hxx>
#include <osl/mutex.hxx>
#include <rtl/ustring.hxx>

#ifndef __COM_SUN_STAR_AWT_XBITMAP_HPP_
#include <com/sun/star/awt/XBitmap.hpp>
#endif
#include <com/sun/star/lang/XMultiServiceFactory.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XTypeProvider.hpp>
#include <com/sun/star/lang/IllegalArgumentException.hpp>
#include <framework/fwedllapi.h>

#define SERVICENAME_ACTIONTRIGGER "com.sun.star.ui.ActionTrigger"
#define IMPLEMENTATIONNAME_ACTIONTRIGGER "com.sun.star.comp.ui.ActionTrigger"

namespace framework
{

class ActionTriggerPropertySet :  public ThreadHelpBase                       ,   // Struct for right initalization of mutex member! Must be first of baseclasses.
									public ::com::sun::star::lang::XServiceInfo	,
									public ::com::sun::star::lang::XTypeProvider,
									public ::cppu::OBroadcastHelper				,
									public ::cppu::OPropertySetHelper			,	// -> XPropertySet, XFastPropertySet, XMultiPropertySet
									public ::cppu::OWeakObject
{
	public:
        FWE_DLLPUBLIC ActionTriggerPropertySet( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& xServiceManager );
        FWE_DLLPUBLIC virtual ~ActionTriggerPropertySet();

		// XInterface
        virtual FWE_DLLPUBLIC ::com::sun::star::uno::Any SAL_CALL queryInterface( const ::com::sun::star::uno::Type& aType )
			throw (::com::sun::star::uno::RuntimeException);
        virtual FWE_DLLPUBLIC void SAL_CALL acquire() throw ();
        virtual FWE_DLLPUBLIC void SAL_CALL release() throw ();

		// XServiceInfo
        virtual FWE_DLLPUBLIC ::rtl::OUString SAL_CALL getImplementationName(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual FWE_DLLPUBLIC sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw (::com::sun::star::uno::RuntimeException);
        virtual FWE_DLLPUBLIC ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw (::com::sun::star::uno::RuntimeException);

		// XTypeProvider
        virtual FWE_DLLPUBLIC ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Type > SAL_CALL getTypes(  ) throw (::com::sun::star::uno::RuntimeException);
        virtual FWE_DLLPUBLIC ::com::sun::star::uno::Sequence< sal_Int8 > SAL_CALL getImplementationId(  ) throw (::com::sun::star::uno::RuntimeException);

	private:
		//---------------------------------------------------------------------------------------------------------
		//	OPropertySetHelper
		//---------------------------------------------------------------------------------------------------------
		virtual sal_Bool SAL_CALL convertFastPropertyValue(	com::sun::star::uno::Any&		aConvertedValue,
															com::sun::star::uno::Any&		aOldValue,
															sal_Int32						nHandle,
															const com::sun::star::uno::Any&	aValue			)
			throw( com::sun::star::lang::IllegalArgumentException );


		virtual void SAL_CALL setFastPropertyValue_NoBroadcast(	sal_Int32 nHandle, const com::sun::star::uno::Any& aValue )
			throw( com::sun::star::uno::Exception );

        using cppu::OPropertySetHelper::getFastPropertyValue;
		virtual void SAL_CALL getFastPropertyValue(	com::sun::star::uno::Any& aValue, sal_Int32	nHandle	) const;

		virtual ::cppu::IPropertyArrayHelper& SAL_CALL getInfoHelper();

		virtual com::sun::star::uno::Reference< com::sun::star::beans::XPropertySetInfo > SAL_CALL getPropertySetInfo()
			throw (::com::sun::star::uno::RuntimeException);

		static const com::sun::star::uno::Sequence< com::sun::star::beans::Property > impl_getStaticPropertyDescriptor();

		//---------------------------------------------------------------------------------------------------------
		//	helper
		//---------------------------------------------------------------------------------------------------------

		sal_Bool impl_tryToChangeProperty(	const	rtl::OUString&				aCurrentValue	,
											const	com::sun::star::uno::Any&	aNewValue		,
											com::sun::star::uno::Any&			aOldValue		,
											com::sun::star::uno::Any&			aConvertedValue	) throw( com::sun::star::lang::IllegalArgumentException );

		sal_Bool impl_tryToChangeProperty(	const	com::sun::star::uno::Reference< com::sun::star::awt::XBitmap >	xBitmap,
											const	com::sun::star::uno::Any&	aNewValue		,
											com::sun::star::uno::Any&			aOldValue		,
											com::sun::star::uno::Any&			aConvertedValue	) throw( com::sun::star::lang::IllegalArgumentException );

		sal_Bool impl_tryToChangeProperty(	const	com::sun::star::uno::Reference< com::sun::star::uno::XInterface > xInterface,
											const	com::sun::star::uno::Any&	aNewValue		,
											com::sun::star::uno::Any&			aOldValue		,
											com::sun::star::uno::Any&			aConvertedValue	) throw( com::sun::star::lang::IllegalArgumentException );

		//---------------------------------------------------------------------------------------------------------
		//	members
		//---------------------------------------------------------------------------------------------------------

		rtl::OUString                                                         m_aCommandURL;
		rtl::OUString                                                         m_aHelpURL;
		rtl::OUString                                                         m_aText;
		::com::sun::star::uno::Reference< ::com::sun::star::awt::XBitmap >    m_xBitmap;
		::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > m_xActionTriggerContainer;
};

}

#endif // __FRAMEWORK_CLASSES_ACTIONTRIGGERPROPERTYSET_HXX_
