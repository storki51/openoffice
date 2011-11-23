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


#ifndef _CHARTFRAMELOADER_HXX
#define _CHARTFRAMELOADER_HXX

#include "ServiceMacros.hxx"
#include <osl/conditn.hxx>
#include <com/sun/star/frame/XSynchronousFrameLoader.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <cppuhelper/implbase2.hxx>

//.............................................................................
namespace chart
{
//.............................................................................

class ChartFrameLoader : public ::cppu::WeakImplHelper2<
		 ::com::sun::star::frame::XSynchronousFrameLoader
		 , ::com::sun::star::lang::XServiceInfo
			//comprehends XComponent (required interface)
	//	,public ::com::sun::star::uno::XWeak			// implemented by WeakImplHelper(optional interface)
	//	,public ::com::sun::star::uno::XInterface		// implemented by WeakImplHelper(optional interface)
	//	,public ::com::sun::star::lang::XTypeProvider	// implemented by WeakImplHelper
		>
{
private:
	::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext>		   m_xCC;
	sal_Bool			m_bCancelRequired;
	::osl::Condition	m_oCancelFinished;

private:
		sal_Bool impl_checkCancel();
	//no default constructor
	ChartFrameLoader(){}
public:
	ChartFrameLoader(::com::sun::star::uno::Reference<
			   ::com::sun::star::uno::XComponentContext > const & xContext);
	virtual ~ChartFrameLoader();

	//-----------------------------------------------------------------
	// ::com::sun::star::lang::XServiceInfo
	//-----------------------------------------------------------------

	APPHELPER_XSERVICEINFO_DECL()
	APPHELPER_SERVICE_FACTORY_HELPER(ChartFrameLoader)

	//-----------------------------------------------------------------
	// ::com::sun::star::frame::XFrameLoader
	//-----------------------------------------------------------------

	virtual sal_Bool SAL_CALL
		load( const ::com::sun::star::uno::Sequence<
				::com::sun::star::beans::PropertyValue >& rMediaDescriptor
				,const ::com::sun::star::uno::Reference<
				::com::sun::star::frame::XFrame >& xFrame )
							throw (::com::sun::star::uno::RuntimeException);

    virtual void SAL_CALL
		cancel()			throw (::com::sun::star::uno::RuntimeException);
};

//.............................................................................
} //namespace chart
//.............................................................................

#endif
