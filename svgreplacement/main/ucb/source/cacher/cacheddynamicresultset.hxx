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



#ifndef _CACHED_DYNAMIC_RESULTSET_HXX
#define _CACHED_DYNAMIC_RESULTSET_HXX

#include <dynamicresultsetwrapper.hxx>
#include <com/sun/star/ucb/XContentIdentifierMapping.hpp>
#include <com/sun/star/ucb/XCachedDynamicResultSetFactory.hpp>

#define CACHED_DRS_SERVICE_NAME "com.sun.star.ucb.CachedDynamicResultSet"
#define CACHED_DRS_FACTORY_NAME "com.sun.star.ucb.CachedDynamicResultSetFactory"

//=========================================================================

class CachedDynamicResultSet
				: public DynamicResultSetWrapper
				, public com::sun::star::lang::XTypeProvider
				, public com::sun::star::lang::XServiceInfo
{
	com::sun::star::uno::Reference<	com::sun::star::ucb::XContentIdentifierMapping >
							m_xContentIdentifierMapping;

protected:
	virtual void SAL_CALL
	impl_InitResultSetOne( const com::sun::star::uno::Reference<
				com::sun::star::sdbc::XResultSet >& xResultSet );
	virtual void SAL_CALL
	impl_InitResultSetTwo( const com::sun::star::uno::Reference<
				com::sun::star::sdbc::XResultSet >& xResultSet );

public:
	CachedDynamicResultSet(	com::sun::star::uno::Reference<
						com::sun::star::ucb::XDynamicResultSet > xOrigin
		, const com::sun::star::uno::Reference<
						com::sun::star::ucb::XContentIdentifierMapping > & xContentMapping
		, const com::sun::star::uno::Reference<
						com::sun::star::lang::XMultiServiceFactory > & xSMgr );

	virtual ~CachedDynamicResultSet();
	

	//-----------------------------------------------------------------
	// XInterface inherited
	//-----------------------------------------------------------------
	XINTERFACE_DECL()
	//-----------------------------------------------------------------
	// XTypeProvider
	//-----------------------------------------------------------------
	XTYPEPROVIDER_DECL()
	//-----------------------------------------------------------------
    // XServiceInfo
	//-----------------------------------------------------------------
	XSERVICEINFO_NOFACTORY_DECL()
	
	//-----------------------------------------------------------------
	// own methods ( inherited )
	//-----------------------------------------------------------------
    virtual void SAL_CALL
	impl_disposing( const com::sun::star::lang::EventObject& Source )
		throw( com::sun::star::uno::RuntimeException );
};

//=========================================================================

class CachedDynamicResultSetFactory
				: public cppu::OWeakObject
				, public com::sun::star::lang::XTypeProvider
				, public com::sun::star::lang::XServiceInfo
				, public com::sun::star::ucb::XCachedDynamicResultSetFactory
{
protected:
	com::sun::star::uno::Reference<
		com::sun::star::lang::XMultiServiceFactory >	m_xSMgr;

public:

	CachedDynamicResultSetFactory(
		const com::sun::star::uno::Reference<
		com::sun::star::lang::XMultiServiceFactory > & rSMgr);

	virtual ~CachedDynamicResultSetFactory();

	//-----------------------------------------------------------------
	// XInterface
	XINTERFACE_DECL()

	//-----------------------------------------------------------------
	// XTypeProvider
	XTYPEPROVIDER_DECL()

	//-----------------------------------------------------------------
    // XServiceInfo
	XSERVICEINFO_DECL()

	//-----------------------------------------------------------------
    // XCachedDynamicResultSetFactory

	virtual com::sun::star::uno::Reference<
				com::sun::star::ucb::XDynamicResultSet > SAL_CALL
	createCachedDynamicResultSet(
				  const com::sun::star::uno::Reference<
					com::sun::star::ucb::XDynamicResultSet > &
						SourceStub
				, const com::sun::star::uno::Reference<
					com::sun::star::ucb::XContentIdentifierMapping > &
						ContentIdentifierMapping
				)
			throw( com::sun::star::uno::RuntimeException );
};

#endif

