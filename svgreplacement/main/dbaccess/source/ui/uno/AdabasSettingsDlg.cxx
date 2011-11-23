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
#include "precompiled_dbaccess.hxx"

#ifndef _DBU_REGHELPER_HXX_
#include "dbu_reghelper.hxx"
#endif
#ifndef _DBAUI_ADABASSETTINGSDLG_HXX
#include "AdabasSettingsDlg.hxx"
#endif
#ifndef DBAUI_ADABASSTATDLG_HXX
#include "AdabasStatDlg.hxx"
#endif


using namespace dbaui;

extern "C" void SAL_CALL createRegistryInfo_OAdabasSettingsDialog()
{
	static OMultiInstanceAutoRegistration< OAdabasSettingsDialog > aAutoRegistration;
}

//.........................................................................
namespace dbaui
{
//.........................................................................

	using namespace ::com::sun::star::uno;
	using namespace ::com::sun::star::lang;
	using namespace ::com::sun::star::beans;

//=========================================================================
//-------------------------------------------------------------------------
OAdabasSettingsDialog::OAdabasSettingsDialog(const Reference< XMultiServiceFactory >& _rxORB)
	:ODatabaseAdministrationDialog(_rxORB)
{
}
//-------------------------------------------------------------------------
Sequence<sal_Int8> SAL_CALL OAdabasSettingsDialog::getImplementationId(  ) throw(RuntimeException)
{
	static ::cppu::OImplementationId aId;
	return aId.getImplementationId();
}

//-------------------------------------------------------------------------
Reference< XInterface > SAL_CALL OAdabasSettingsDialog::Create(const Reference< XMultiServiceFactory >& _rxFactory)
{
	return *(new OAdabasSettingsDialog(_rxFactory));
}

//-------------------------------------------------------------------------
::rtl::OUString SAL_CALL OAdabasSettingsDialog::getImplementationName() throw(RuntimeException)
{
	return getImplementationName_Static();
}

//-------------------------------------------------------------------------
::rtl::OUString OAdabasSettingsDialog::getImplementationName_Static() throw(RuntimeException)
{
	return ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("org.openoffice.comp.dbu.OAdabasSettingsDialog"));
}

//-------------------------------------------------------------------------
::comphelper::StringSequence SAL_CALL OAdabasSettingsDialog::getSupportedServiceNames() throw(RuntimeException)
{
	return getSupportedServiceNames_Static();
}

//-------------------------------------------------------------------------
::comphelper::StringSequence OAdabasSettingsDialog::getSupportedServiceNames_Static() throw(RuntimeException)
{
	::comphelper::StringSequence aSupported(1);
	aSupported.getArray()[0] = ::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("com.sun.star.sdb.AdabasAdministrationDialog"));
	return aSupported;
}

//-------------------------------------------------------------------------
Reference<XPropertySetInfo>  SAL_CALL OAdabasSettingsDialog::getPropertySetInfo() throw(RuntimeException)
{
	Reference<XPropertySetInfo>  xInfo( createPropertySetInfo( getInfoHelper() ) );
	return xInfo;
}

//-------------------------------------------------------------------------
::cppu::IPropertyArrayHelper& OAdabasSettingsDialog::getInfoHelper()
{
	return *const_cast<OAdabasSettingsDialog*>(this)->getArrayHelper();
}

//------------------------------------------------------------------------------
::cppu::IPropertyArrayHelper* OAdabasSettingsDialog::createArrayHelper( ) const
{
	Sequence< Property > aProps;
	describeProperties(aProps);
	return new ::cppu::OPropertyArrayHelper(aProps);
}
//------------------------------------------------------------------------------
Dialog*	OAdabasSettingsDialog::createDialog(Window* _pParent)
{
	OAdabasStatPageDlg* pDlg = new OAdabasStatPageDlg(_pParent, m_pDatasourceItems, m_aContext.getLegacyServiceFactory(),m_aInitialSelection);
	return pDlg;
}

//.........................................................................
}	// namespace dbaui
//.........................................................................

