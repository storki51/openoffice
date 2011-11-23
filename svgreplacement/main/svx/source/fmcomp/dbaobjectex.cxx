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
#include <svx/dbaobjectex.hxx>
#include <osl/diagnose.h>
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#include <com/sun/star/sdb/XSQLQueryComposerFactory.hpp>
#include <com/sun/star/sdb/XSQLQueryComposerFactory.hpp>
#ifndef _SVX_FMPROP_HRC
#include "fmprop.hrc"
#endif
#include <comphelper/extract.hxx>
#include <sot/formats.hxx>
#include <sot/exchange.hxx>
#include <comphelper/propertysetinfo.hxx>
#ifndef _SVX_FMPROP_HRC
#include "fmprop.hrc"
#endif

//........................................................................
namespace svx
{
//........................................................................

	using namespace ::com::sun::star::uno;
	using namespace ::com::sun::star::beans;
	using namespace ::com::sun::star::sdb;
	using namespace ::com::sun::star::sdbc;
	using namespace ::com::sun::star::lang;
	using namespace ::com::sun::star::ucb;
	using namespace ::com::sun::star::sdbcx;
	using namespace ::com::sun::star::container;
	using namespace ::com::sun::star::datatransfer;
	using namespace ::comphelper;

	//====================================================================
	//= OComponentTransferable
	//====================================================================
	//--------------------------------------------------------------------
	OComponentTransferable::OComponentTransferable(const ::rtl::OUString& _rDatasourceOrLocation
			,const Reference< XContent>& _xContent)
	{
		m_aDescriptor.setDataSource(_rDatasourceOrLocation);
		m_aDescriptor[daComponent] <<= _xContent;
	}


	//--------------------------------------------------------------------
	sal_uInt32 OComponentTransferable::getDescriptorFormatId(sal_Bool _bExtractForm)
	{
		static sal_uInt32 s_nReportFormat = (sal_uInt32)-1;
		static sal_uInt32 s_nFormFormat = (sal_uInt32)-1;
		if ( _bExtractForm && (sal_uInt32)-1 == s_nFormFormat )
		{
			s_nFormFormat = SotExchange::RegisterFormatName(String::CreateFromAscii("application/x-openoffice;windows_formatname=\"dbaccess.FormComponentDescriptorTransfer\"" ));
			OSL_ENSURE((sal_uInt32)-1 != s_nFormFormat, "OComponentTransferable::getDescriptorFormatId: bad exchange id!");
		}
		else if ( !_bExtractForm && (sal_uInt32)-1 == s_nReportFormat)
		{
			s_nReportFormat = SotExchange::RegisterFormatName(String::CreateFromAscii("application/x-openoffice;windows_formatname=\"dbaccess.ReportComponentDescriptorTransfer\""));
			OSL_ENSURE((sal_uInt32)-1 != s_nReportFormat, "OComponentTransferable::getDescriptorFormatId: bad exchange id!");
		}
		return _bExtractForm ? s_nFormFormat : s_nReportFormat;
	}

	//--------------------------------------------------------------------
	void OComponentTransferable::AddSupportedFormats()
	{
		sal_Bool bForm = sal_True;
		try
		{
			Reference<XPropertySet> xProp;
			m_aDescriptor[daComponent] >>= xProp;
			if ( xProp.is() )
				xProp->getPropertyValue(::rtl::OUString(RTL_CONSTASCII_USTRINGPARAM("IsForm"))) >>= bForm;
		}
		catch(Exception)
		{}
		AddFormat(getDescriptorFormatId(bForm));
	}

	//--------------------------------------------------------------------
	sal_Bool OComponentTransferable::GetData( const DataFlavor& _rFlavor )
	{
		const sal_uInt32 nFormatId = SotExchange::GetFormat(_rFlavor);
		if ( nFormatId == getDescriptorFormatId(sal_True) || nFormatId == getDescriptorFormatId(sal_False) )
			return SetAny( makeAny( m_aDescriptor.createPropertyValueSequence() ), _rFlavor );

		return sal_False;
	}

	//--------------------------------------------------------------------
	sal_Bool OComponentTransferable::canExtractComponentDescriptor(const DataFlavorExVector& _rFlavors,sal_Bool _bForm )
	{
		DataFlavorExVector::const_iterator aEnd = _rFlavors.end();
		for (	DataFlavorExVector::const_iterator aCheck = _rFlavors.begin();
				aCheck != aEnd;
				++aCheck
			)
		{
			if ( getDescriptorFormatId(_bForm) == aCheck->mnSotId )
				return sal_True;
		}

		return sal_False;
	}

	//--------------------------------------------------------------------
	ODataAccessDescriptor OComponentTransferable::extractComponentDescriptor(const TransferableDataHelper& _rData)
	{
		sal_Bool bForm = _rData.HasFormat(getDescriptorFormatId(sal_True));
		if ( bForm || _rData.HasFormat(getDescriptorFormatId(sal_False)) )
		{
			// the object has a real descriptor object (not just the old compatible format)

			// extract the any from the transferable
			DataFlavor aFlavor;
#if OSL_DEBUG_LEVEL > 0
			sal_Bool bSuccess =
#endif
			SotExchange::GetFormatDataFlavor(getDescriptorFormatId(bForm), aFlavor);
			OSL_ENSURE(bSuccess, "OComponentTransferable::extractColumnDescriptor: invalid data format (no flavor)!");

			Any aDescriptor = _rData.GetAny(aFlavor);

			// extract the property value sequence
			Sequence< PropertyValue > aDescriptorProps;
#if OSL_DEBUG_LEVEL > 0
			bSuccess =
#endif
			aDescriptor >>= aDescriptorProps;
			OSL_ENSURE(bSuccess, "OComponentTransferable::extractColumnDescriptor: invalid clipboard format!");

			// build the real descriptor
			return ODataAccessDescriptor(aDescriptorProps);
		}

		return ODataAccessDescriptor();
	}

	//--------------------------------------------------------------------
	sal_Bool OComponentTransferable::extractComponentDescriptor(const TransferableDataHelper& _rData
		,sal_Bool _bExtractForm
		, ::rtl::OUString&	_rDatasourceOrLocation
		, ::com::sun::star::uno::Reference< XContent>& _xContent)
	{
		if ( _rData.HasFormat( getDescriptorFormatId(_bExtractForm)) )
		{
			ODataAccessDescriptor aDescriptor = extractComponentDescriptor(_rData);
			_rDatasourceOrLocation = aDescriptor.getDataSource();
			aDescriptor[daComponent]			>>= _xContent;
			return sal_True;
		}

		return sal_False;
	}
//........................................................................
}	// namespace svx
//........................................................................


