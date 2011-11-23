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



#ifndef FORMULA_FORMULAOPCODEMAPPER_HXX_INCLUDED
#define FORMULA_FORMULAOPCODEMAPPER_HXX_INCLUDED

#include "formula/formuladllapi.h"
#include <cppuhelper/implbase2.hxx>
#include <com/sun/star/sheet/XFormulaOpCodeMapper.hpp>
#include <com/sun/star/lang/XServiceInfo.hpp>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <memory>
#include "formula/FormulaCompiler.hxx"


namespace formula
{

class FORMULA_DLLPUBLIC FormulaOpCodeMapperObj : public ::cppu::WeakImplHelper2<
                            ::com::sun::star::sheet::XFormulaOpCodeMapper,
                            ::com::sun::star::lang::XServiceInfo >
{
    ::std::auto_ptr<FormulaCompiler> m_pCompiler;
public:
    static ::rtl::OUString	getImplementationName_Static();
	static ::com::sun::star::uno::Sequence< ::rtl::OUString> getSupportedServiceNames_Static();
    static ::com::sun::star::uno::Reference< ::com::sun::star::uno::XInterface > create(const ::com::sun::star::uno::Reference< ::com::sun::star::uno::XComponentContext >& _xContext);

protected:
                            FormulaOpCodeMapperObj(::std::auto_ptr<FormulaCompiler> _pCompiler);
    virtual                 ~FormulaOpCodeMapperObj();

private:
                            // XFormulaOpCodeMapper
                            // Attributes
    virtual ::sal_Int32 SAL_CALL getOpCodeExternal() throw (::com::sun::star::uno::RuntimeException);
    virtual ::sal_Int32 SAL_CALL getOpCodeUnknown() throw (::com::sun::star::uno::RuntimeException);
                            // Methods
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::sheet::FormulaToken > SAL_CALL getMappings(
                                    const ::com::sun::star::uno::Sequence< ::rtl::OUString >& rNames,
                                    sal_Int32 nLanguage )
                                throw ( ::com::sun::star::lang::IllegalArgumentException,
                                        ::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::com::sun::star::sheet::FormulaOpCodeMapEntry > SAL_CALL getAvailableMappings(
                                    sal_Int32 nLanguage, sal_Int32 nGroups )
                                throw ( ::com::sun::star::lang::IllegalArgumentException,
                                        ::com::sun::star::uno::RuntimeException);

                            // XServiceInfo
    virtual ::rtl::OUString SAL_CALL getImplementationName()
                                throw(::com::sun::star::uno::RuntimeException);
    virtual sal_Bool SAL_CALL supportsService( const ::rtl::OUString& ServiceName )
                                throw(::com::sun::star::uno::RuntimeException);
    virtual ::com::sun::star::uno::Sequence< ::rtl::OUString > SAL_CALL getSupportedServiceNames()
                                throw(::com::sun::star::uno::RuntimeException);

};
// =============================================================================
} // formula
// =============================================================================

#endif // FORMULA_FORMULAOPCODEMAPPER_HXX_INCLUDED
