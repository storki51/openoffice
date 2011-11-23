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
#include "precompiled_svx.hxx"
#include "EnhancedCustomShapeHandle.hxx"
#include "svx/EnhancedCustomShape2d.hxx"
#include "svx/unoapi.hxx"

// -----------------------------------------------------------------------------

EnhancedCustomShapeHandle::EnhancedCustomShapeHandle( com::sun::star::uno::Reference< com::sun::star::drawing::XShape >& xCustomShape, sal_uInt32 nIndex ) :
	mnIndex		( nIndex ),
	mxCustomShape ( xCustomShape )
{
}

// -----------------------------------------------------------------------------

EnhancedCustomShapeHandle::~EnhancedCustomShapeHandle()
{
}

// -----------------------------------------------------------------------------

void SAL_CALL EnhancedCustomShapeHandle::acquire() throw()
{
	OWeakObject::acquire();
}

// -----------------------------------------------------------------------------

void SAL_CALL EnhancedCustomShapeHandle::release() throw()
{
	OWeakObject::release();
}

// XCustomShapeHandle
com::sun::star::awt::Point SAL_CALL EnhancedCustomShapeHandle::getPosition()
	throw ( com::sun::star::uno::RuntimeException )
{
	SdrObject* pSdrObjCustomShape( GetSdrObjectFromXShape( mxCustomShape ) );
	if ( !pSdrObjCustomShape )
		throw com::sun::star::uno::RuntimeException();

	Point aPosition;
	EnhancedCustomShape2d aCustomShape2d( pSdrObjCustomShape );
	if ( !aCustomShape2d.GetHandlePosition( mnIndex, aPosition ) )
		throw com::sun::star::uno::RuntimeException();
	return com::sun::star::awt::Point( aPosition.X(), aPosition.Y() );
}

void SAL_CALL EnhancedCustomShapeHandle::setControllerPosition( const com::sun::star::awt::Point& aPnt )
	throw ( com::sun::star::uno::RuntimeException )
{
	SdrObject* pSdrObjCustomShape( GetSdrObjectFromXShape( mxCustomShape ) );
	if ( !pSdrObjCustomShape )
		throw com::sun::star::uno::RuntimeException();

	EnhancedCustomShape2d aCustomShape2d( pSdrObjCustomShape );
	if ( !aCustomShape2d.SetHandleControllerPosition( mnIndex, aPnt ) )
		throw com::sun::star::uno::RuntimeException();
}

// XInitialization
void SAL_CALL EnhancedCustomShapeHandle::initialize( const com::sun::star::uno::Sequence< com::sun::star::uno::Any >& /* aArguments */ )
	throw ( com::sun::star::uno::Exception, com::sun::star::uno::RuntimeException )
{
}
