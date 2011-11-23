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



/** === begin UNO includes === **/
#include <com/sun/star/awt/grid/XGridColumnModel.hpp>
#include <com/sun/star/awt/grid/XGridColumn.hpp>
#include <com/sun/star/lang/XEventListener.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/lang/XUnoTunnel.hpp>
#include <com/sun/star/style/VerticalAlignment.hpp>
#include <com/sun/star/util/Color.hpp>
/** === end UNO includes === **/

#include <cppuhelper/basemutex.hxx>
#include <cppuhelper/compbase2.hxx>
#include <comphelper/componentcontext.hxx>
#include <vector>

namespace comphelper
{
    class ComponentGuard;
}

namespace toolkit
{

//enum broadcast_type { column_added, column_removed, column_changed};

typedef ::cppu::WeakComponentImplHelper2    <   ::com::sun::star::awt::grid::XGridColumnModel
                                            ,   ::com::sun::star::lang::XServiceInfo
                                            >   DefaultGridColumnModel_Base;

class DefaultGridColumnModel    :public ::cppu::BaseMutex
                                ,public DefaultGridColumnModel_Base
{
public:
	DefaultGridColumnModel( const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory >& xFactory );
    DefaultGridColumnModel( DefaultGridColumnModel const & i_copySource );
	virtual ~DefaultGridColumnModel();
	
	// XGridColumnModel
	virtual ::sal_Int32 SAL_CALL getColumnCount() throw (::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::awt::grid::XGridColumn > SAL_CALL createColumn(  ) throw (::com::sun::star::uno::RuntimeException);
	virtual ::sal_Int32 SAL_CALL addColumn(const ::com::sun::star::uno::Reference< ::com::sun::star::awt::grid::XGridColumn > & column) throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::lang::IllegalArgumentException);
    virtual void SAL_CALL removeColumn( ::sal_Int32 i_columnIndex )  throw (::com::sun::star::uno::RuntimeException, ::com::sun::star::lang::IndexOutOfBoundsException);
	virtual ::com::sun::star::uno::Sequence< ::com::sun::star::uno::Reference< ::com::sun::star::awt::grid::XGridColumn > > SAL_CALL getColumns() throw (::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Reference< ::com::sun::star::awt::grid::XGridColumn > SAL_CALL getColumn(::sal_Int32 index) throw (::com::sun::star::lang::IndexOutOfBoundsException, ::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL setDefaultColumns(sal_Int32 rowElements) throw (::com::sun::star::uno::RuntimeException);

    // XServiceInfo
	virtual ::rtl::OUString SAL_CALL getImplementationName(  ) throw (::com::sun::star::uno::RuntimeException);
	virtual ::sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName ) throw (::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames(  ) throw (::com::sun::star::uno::RuntimeException);

    // XContainer
    virtual void SAL_CALL addContainerListener( const ::com::sun::star::uno::Reference< ::com::sun::star::container::XContainerListener >& xListener ) throw (::com::sun::star::uno::RuntimeException);
    virtual void SAL_CALL removeContainerListener( const ::com::sun::star::uno::Reference< ::com::sun::star::container::XContainerListener >& xListener ) throw (::com::sun::star::uno::RuntimeException);

    // XCloneable
    virtual ::com::sun::star::uno::Reference< ::com::sun::star::util::XCloneable > SAL_CALL createClone(  ) throw (::com::sun::star::uno::RuntimeException);
    
    // OComponentHelper
    virtual void SAL_CALL disposing();

private:
    typedef ::std::vector< ::com::sun::star::uno::Reference< ::com::sun::star::awt::grid::XGridColumn > >   Columns;

    ::comphelper::ComponentContext      m_aContext;
    ::cppu::OInterfaceContainerHelper   m_aContainerListeners;
    Columns                             m_aColumns;
};

}
