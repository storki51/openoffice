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
#include "xmlDatabase.hxx"
#include "xmlfilter.hxx"
#include <xmloff/xmltoken.hxx>
#include <xmloff/xmlnmspe.hxx>
#include "xmlDataSource.hxx"
#include "xmlDocuments.hxx"
#include "xmlEnums.hxx"
#include <com/sun/star/sdb/XReportDocumentsSupplier.hpp>
#include <com/sun/star/sdb/XFormDocumentsSupplier.hpp>
#include <com/sun/star/sdbcx/XTablesSupplier.hpp>
#include <com/sun/star/sdb/XQueryDefinitionsSupplier.hpp>
#include "xmlstrings.hrc"
#include <tools/debug.hxx>
#include <connectivity/dbtools.hxx>

namespace dbaxml
{
	using namespace ::com::sun::star::uno;
	using namespace ::com::sun::star::sdb;
	using namespace ::com::sun::star::sdbcx;
	using namespace ::com::sun::star::xml::sax;
DBG_NAME(OXMLDatabase)

OXMLDatabase::OXMLDatabase( ODBFilter& rImport,
				sal_uInt16 nPrfx, const ::rtl::OUString& rLName ) :
	SvXMLImportContext( rImport, nPrfx, rLName )
{
    DBG_CTOR(OXMLDatabase,NULL);

}
// -----------------------------------------------------------------------------

OXMLDatabase::~OXMLDatabase()
{

    DBG_DTOR(OXMLDatabase,NULL);
}
// -----------------------------------------------------------------------------

SvXMLImportContext* OXMLDatabase::CreateChildContext(
		sal_uInt16 nPrefix,
		const ::rtl::OUString& rLocalName,
		const Reference< XAttributeList > & xAttrList )
{
	SvXMLImportContext *pContext = 0;
	const SvXMLTokenMap&	rTokenMap	= GetOwnImport().GetDatabaseElemTokenMap();

	switch( rTokenMap.Get( nPrefix, rLocalName ) )
	{
		case XML_TOK_DATASOURCE:
			GetOwnImport().GetProgressBarHelper()->Increment( PROGRESS_BAR_STEP );
            pContext = new OXMLDataSource( GetOwnImport(), nPrefix, rLocalName, xAttrList, OXMLDataSource::eDataSource );
			break;
		case XML_TOK_FORMS:
			{
				GetOwnImport().GetProgressBarHelper()->Increment( PROGRESS_BAR_STEP );
                Any aValue;
                ::rtl::OUString sService;
                dbtools::getDataSourceSetting(GetOwnImport().getDataSource(),"Forms",aValue);
                aValue >>= sService;
                if ( !sService.getLength() )
                {
				    Reference<XFormDocumentsSupplier> xSup(GetOwnImport().GetModel(),UNO_QUERY);
				    if ( xSup.is() )
					    pContext = new OXMLDocuments( GetOwnImport(), nPrefix, rLocalName,xSup->getFormDocuments(),SERVICE_NAME_FORM_COLLECTION,SERVICE_SDB_DOCUMENTDEFINITION);
                }
			}
			break;
		case XML_TOK_REPORTS:
			{
				GetOwnImport().GetProgressBarHelper()->Increment( PROGRESS_BAR_STEP );
                Any aValue;
                ::rtl::OUString sService;
                dbtools::getDataSourceSetting(GetOwnImport().getDataSource(),"Reports",aValue);
                aValue >>= sService;
                if ( !sService.getLength() )
                {
				    Reference<XReportDocumentsSupplier> xSup(GetOwnImport().GetModel(),UNO_QUERY);
				    if ( xSup.is() )
					    pContext = new OXMLDocuments( GetOwnImport(), nPrefix, rLocalName,xSup->getReportDocuments(),SERVICE_NAME_REPORT_COLLECTION,SERVICE_SDB_DOCUMENTDEFINITION);
                }
			}
			break;
		case XML_TOK_QUERIES:
			{
				GetOwnImport().GetProgressBarHelper()->Increment( PROGRESS_BAR_STEP );
                Any aValue;
                ::rtl::OUString sService;
                dbtools::getDataSourceSetting(GetOwnImport().getDataSource(),"CommandDefinitions",aValue);
                aValue >>= sService;
                if ( !sService.getLength() )
                {
				    Reference<XQueryDefinitionsSupplier> xSup(GetOwnImport().getDataSource(),UNO_QUERY);
				    if ( xSup.is() )
					    pContext = new OXMLDocuments( GetOwnImport(), nPrefix, rLocalName,xSup->getQueryDefinitions(),SERVICE_NAME_QUERY_COLLECTION);
                }
			}
			break;
		case XML_TOK_TABLES:
        case XML_TOK_SCHEMA_DEFINITION:
			{
				GetOwnImport().GetProgressBarHelper()->Increment( PROGRESS_BAR_STEP );
				Reference<XTablesSupplier> xSup(GetOwnImport().getDataSource(),UNO_QUERY);
				if ( xSup.is() )
					pContext = new OXMLDocuments( GetOwnImport(), nPrefix, rLocalName,xSup->getTables());
			}
			break;
	}

	if( !pContext )
		pContext = new SvXMLImportContext( GetImport(), nPrefix, rLocalName );


	return pContext;
}
// -----------------------------------------------------------------------------
ODBFilter& OXMLDatabase::GetOwnImport()
{
	return static_cast<ODBFilter&>(GetImport());
}
// -----------------------------------------------------------------------------
void OXMLDatabase::EndElement()
{
	GetOwnImport().setPropertyInfo();
}

//----------------------------------------------------------------------------
} // namespace dbaxml
// -----------------------------------------------------------------------------
