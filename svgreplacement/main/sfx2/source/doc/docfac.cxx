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
#include "precompiled_sfx2.hxx"
#include <com/sun/star/registry/MergeConflictException.hpp>
#include <com/sun/star/registry/XSimpleRegistry.hpp>
#include <com/sun/star/container/XNameAccess.hpp>
#include <com/sun/star/ucb/XSimpleFileAccess.hpp>
#include <com/sun/star/document/XTypeDetection.hpp>
#include <com/sun/star/frame/XLoadable.hpp>
#include <com/sun/star/frame/XStorable.hpp>
#include <comphelper/processfactory.hxx>
#include <tools/config.hxx>
#include <unotools/pathoptions.hxx>
#include <unotools/moduleoptions.hxx>
#include <tools/urlobj.hxx>
#include <unotools/ucbstreamhelper.hxx>
#include <unotools/localfilehelper.hxx>
#include <comphelper/sequenceashashmap.hxx>
#include <comphelper/configurationhelper.hxx>

#include <sfx2/sfx.hrc>
#include <sfx2/docfilt.hxx>
#include <sfx2/docfac.hxx>
#include "sfx2/viewfac.hxx"
#include "fltfnc.hxx"
#include "arrdecl.hxx"
#include <sfx2/app.hxx>
#include <sfx2/module.hxx>
#include <sfx2/mnumgr.hxx>
#include "sfx2/sfxresid.hxx"
#include <sfx2/sfxuno.hxx>
#include "syspath.hxx"
#include <osl/file.hxx>
#include <osl/security.hxx>
#include "doc.hrc"

#include <assert.h>

namespace css = ::com::sun::star;
using namespace ::com::sun::star;

//========================================================================

DECL_PTRARRAY( SfxViewFactoryArr_Impl, SfxViewFactory*, 2, 2 )

//========================================================================

DBG_NAME(SfxObjectFactory)

//static SfxObjectFactoryArr_Impl* pObjFac = 0;

//========================================================================

struct SfxObjectFactory_Impl
{
	SfxViewFactoryArr_Impl		aViewFactoryArr;// Liste von <SfxViewFactory>s
	SfxFilterArr_Impl			aFilterArr;     // Liste von <SFxFilter>n
	ResId*						pNameResId;
	::rtl::OUString				aServiceName;
	SfxFilterContainer*			pFilterContainer;
	SfxModule*					pModule;
	sal_uInt16					nImageId;
	String						aStandardTemplate;
	sal_Bool					bTemplateInitialized;
	SvGlobalName				aClassName;

	SfxObjectFactory_Impl() :
		pNameResId			( NULL ),
		pFilterContainer	( NULL ),
		pModule				( NULL ),
		nImageId			( 0 ),
		bTemplateInitialized( sal_False )
		{}
};

//========================================================================

SfxFilterContainer* SfxObjectFactory::GetFilterContainer( sal_Bool /*bForceLoad*/ ) const
{
	return pImpl->pFilterContainer;
}

//--------------------------------------------------------------------

SfxObjectFactory::SfxObjectFactory
(
	const SvGlobalName& 	rName,
	SfxObjectShellFlags 	nFlagsP,
	const char*				pName
) :    pShortName( pName ),
       pImpl( new SfxObjectFactory_Impl ),
       nFlags( nFlagsP )
{
	DBG_CTOR(SfxObjectFactory, 0);
	pImpl->pFilterContainer = new SfxFilterContainer( String::CreateFromAscii( pName ) );

	String aShortName( String::CreateFromAscii( pShortName ) );
	aShortName.ToLowerAscii();
	pImpl->aClassName = rName;
	if ( aShortName.EqualsAscii( "swriter" ) )
		pImpl->pNameResId = new SfxResId( STR_DOCTYPENAME_SW );
	else if ( aShortName.EqualsAscii( "swriter/web" ) )
		pImpl->pNameResId = new SfxResId( STR_DOCTYPENAME_SWWEB );
	else if ( aShortName.EqualsAscii( "swriter/globaldocument" ) )
		pImpl->pNameResId = new SfxResId( STR_DOCTYPENAME_SWGLOB );
	else if ( aShortName.EqualsAscii( "scalc" ) )
		pImpl->pNameResId = new SfxResId( STR_DOCTYPENAME_SC );
	else if ( aShortName.EqualsAscii( "simpress" ) )
		pImpl->pNameResId = new SfxResId( STR_DOCTYPENAME_SI );
	else if ( aShortName.EqualsAscii( "sdraw" ) )
		pImpl->pNameResId = new SfxResId( STR_DOCTYPENAME_SD );
	else if ( aShortName.EqualsAscii( "message" ) )
		pImpl->pNameResId = new SfxResId( STR_DOCTYPENAME_MESSAGE );
}

//--------------------------------------------------------------------

SfxObjectFactory::~SfxObjectFactory()
{
	DBG_DTOR(SfxObjectFactory, 0);

	const sal_uInt16 nCount = pImpl->aFilterArr.Count();
	for ( sal_uInt16 i = 0; i < nCount; ++i )
		delete pImpl->aFilterArr[i];
	delete pImpl->pNameResId;
	delete pImpl;
}

//--------------------------------------------------------------------

void SfxObjectFactory::RegisterViewFactory
(
	SfxViewFactory &rFactory
)
{
#if OSL_DEBUG_LEVEL > 0
    {
        const String sViewName( rFactory.GetAPIViewName() );
	    for ( sal_uInt16 i = 0; i < pImpl->aViewFactoryArr.Count(); ++i )
        {
            if ( !pImpl->aViewFactoryArr[i]->GetAPIViewName().Equals( sViewName ) )
                continue;
            ByteString sMessage( "SfxObjectFactory::RegisterViewFactory: duplicate view name '" );
            sMessage += ByteString( sViewName, RTL_TEXTENCODING_ASCII_US );
            sMessage += "'!";
            OSL_ENSURE( false, sMessage.GetBuffer() );
            break;
        }
    }
#endif
	sal_uInt16 nPos;
	for ( nPos = 0;
		  nPos < pImpl->aViewFactoryArr.Count() &&
		  pImpl->aViewFactoryArr[nPos]->GetOrdinal() <= rFactory.GetOrdinal();
		  ++nPos )
	/* empty loop */;
	pImpl->aViewFactoryArr.Insert(nPos, &rFactory);
}

//--------------------------------------------------------------------

sal_uInt16 SfxObjectFactory::GetViewFactoryCount() const
{
	return pImpl->aViewFactoryArr.Count();
}

//--------------------------------------------------------------------

SfxViewFactory& SfxObjectFactory::GetViewFactory(sal_uInt16 i) const
{
	return *pImpl->aViewFactoryArr[i];
}

//--------------------------------------------------------------------

SfxModule* SfxObjectFactory::GetModule() const
{
	return pImpl->pModule;
}

void SfxObjectFactory::SetModule_Impl( SfxModule *pMod )
{
	pImpl->pModule = pMod;
}

void SfxObjectFactory::SetSystemTemplate( const String& rServiceName, const String& rTemplateName )
{
    static const int nMaxPathSize = 16000;
	static ::rtl::OUString SERVICE_FILTER_FACTORY = ::rtl::OUString::createFromAscii( "com.sun.star.document.FilterFactory" );
	static ::rtl::OUString SERVICE_TYPE_DECTECTION = ::rtl::OUString::createFromAscii( "com.sun.star.document.TypeDetection" );
	static ::rtl::OUString SERVICE_SIMPLE_ACCESS = ::rtl::OUString::createFromAscii( "com.sun.star.ucb.SimpleFileAccess" );

	static ::rtl::OUString CONF_ROOT  = ::rtl::OUString::createFromAscii( "/org.openoffice.Setup");
	static ::rtl::OUString CONF_PATH  = ::rtl::OUString::createFromAscii( "Office/Factories/" ) + ::rtl::OUString( rServiceName );
	static ::rtl::OUString PROP_DEF_TEMPL_CHANGED  = ::rtl::OUString::createFromAscii( "ooSetupFactorySystemDefaultTemplateChanged" );
	static ::rtl::OUString PROP_ACTUAL_FILTER  = ::rtl::OUString::createFromAscii( "ooSetupFactoryActualFilter" );

	static ::rtl::OUString DEF_TPL_STR = ::rtl::OUString::createFromAscii("/soffice.");

	String      sURL;
    String      sPath;
    sal_Unicode aPathBuffer[nMaxPathSize];
    if ( SystemPath::GetUserTemplateLocation( aPathBuffer, nMaxPathSize ))
        sPath = String( aPathBuffer );
	::utl::LocalFileHelper::ConvertPhysicalNameToURL( sPath, sURL );

	::rtl::OUString aUserTemplateURL( sURL ); 
	if ( aUserTemplateURL.getLength() != 0)
	{
		try
		{
			uno::Reference< lang::XMultiServiceFactory > xFactory = ::comphelper::getProcessServiceFactory();
			uno::Reference< uno::XInterface > xConfig = ::comphelper::ConfigurationHelper::openConfig(
				xFactory, CONF_ROOT, ::comphelper::ConfigurationHelper::E_STANDARD );

			::rtl::OUString aActualFilter;
			::comphelper::ConfigurationHelper::readRelativeKey( xConfig, CONF_PATH, PROP_ACTUAL_FILTER ) >>= aActualFilter;
			sal_Bool bChanged(sal_False);
			::comphelper::ConfigurationHelper::readRelativeKey( xConfig, CONF_PATH, PROP_DEF_TEMPL_CHANGED ) >>= bChanged;

			uno::Reference< container::XNameAccess > xFilterFactory(
				xFactory->createInstance( SERVICE_FILTER_FACTORY ), uno::UNO_QUERY_THROW );
			uno::Reference< container::XNameAccess > xTypeDetection(
				xFactory->createInstance( SERVICE_TYPE_DECTECTION ), uno::UNO_QUERY_THROW );

			::rtl::OUString aActualFilterTypeName;
			uno::Sequence< beans::PropertyValue > aActuralFilterData;
			xFilterFactory->getByName( aActualFilter ) >>= aActuralFilterData;
			for ( sal_Int32 nInd = 0; nInd < aActuralFilterData.getLength(); nInd++ )
				if ( aActuralFilterData[nInd].Name.equalsAscii( "Type" ) )
					aActuralFilterData[nInd].Value >>= aActualFilterTypeName;
			::comphelper::SequenceAsHashMap aProps1( xTypeDetection->getByName( aActualFilterTypeName ) );
			uno::Sequence< ::rtl::OUString > aAllExt =
				aProps1.getUnpackedValueOrDefault( ::rtl::OUString::createFromAscii( "Extensions" ), uno::Sequence< ::rtl::OUString >() );
			//To-do: check if aAllExt is empty first
			::rtl::OUString aExt = aAllExt[0];

			aUserTemplateURL += DEF_TPL_STR;
			aUserTemplateURL += aExt;

			uno::Reference< ucb::XSimpleFileAccess > xSimpleFileAccess( 
				xFactory->createInstance( SERVICE_SIMPLE_ACCESS ), uno::UNO_QUERY_THROW );

			::rtl::OUString aBackupURL;
			::osl::Security().getConfigDir(aBackupURL);
			aBackupURL += ::rtl::OUString::createFromAscii( "/temp" );

			if ( !xSimpleFileAccess->exists( aBackupURL ) )
				xSimpleFileAccess->createFolder( aBackupURL );

			aBackupURL += DEF_TPL_STR;
			aBackupURL += aExt;

			if ( rTemplateName.Len() != 0 )
			{
				if ( xSimpleFileAccess->exists( aUserTemplateURL ) && !bChanged )
					xSimpleFileAccess->copy( aUserTemplateURL, aBackupURL );

				uno::Reference< document::XTypeDetection > xTypeDetector( xTypeDetection, uno::UNO_QUERY );
				::comphelper::SequenceAsHashMap aProps2( xTypeDetection->getByName( xTypeDetector->queryTypeByURL( rTemplateName ) ) );
				::rtl::OUString aFilterName =
					aProps2.getUnpackedValueOrDefault( ::rtl::OUString::createFromAscii("PreferredFilter"), ::rtl::OUString() );

				uno::Sequence< beans::PropertyValue > aArgs( 3 );
				aArgs[0].Name = ::rtl::OUString::createFromAscii( "FilterName" );
				aArgs[0].Value <<= aFilterName;
				aArgs[1].Name = ::rtl::OUString::createFromAscii( "AsTemplate" );
				aArgs[1].Value <<= sal_True;
				aArgs[2].Name = ::rtl::OUString::createFromAscii( "URL" );
				aArgs[2].Value <<= ::rtl::OUString( rTemplateName );

				uno::Reference< frame::XLoadable > xLoadable( xFactory->createInstance( ::rtl::OUString( rServiceName ) ), uno::UNO_QUERY );
				xLoadable->load( aArgs );

				aArgs.realloc( 2 );
				aArgs[1].Name = ::rtl::OUString::createFromAscii( "Overwrite" );
				aArgs[1].Value <<= sal_True;

				uno::Reference< frame::XStorable > xStorable( xLoadable, uno::UNO_QUERY );
				xStorable->storeToURL( aUserTemplateURL, aArgs );
				::comphelper::ConfigurationHelper::writeRelativeKey( xConfig, CONF_PATH, PROP_DEF_TEMPL_CHANGED, uno::makeAny( sal_True ));
				::comphelper::ConfigurationHelper::flush( xConfig );
			}
			else
			{
				DBG_ASSERT( bChanged, "invalid ooSetupFactorySystemDefaultTemplateChanged value!" );

				xSimpleFileAccess->copy( aBackupURL, aUserTemplateURL );
				xSimpleFileAccess->kill( aBackupURL );
				::comphelper::ConfigurationHelper::writeRelativeKey( xConfig, CONF_PATH, PROP_DEF_TEMPL_CHANGED, uno::makeAny( sal_False ));
				::comphelper::ConfigurationHelper::flush( xConfig );
			}
		}
		catch( uno::Exception& )
		{
		}
	}
}

void SfxObjectFactory::SetStandardTemplate( const String& rServiceName, const String& rTemplate )
{
	SvtModuleOptions::EFactory eFac = SvtModuleOptions::ClassifyFactoryByServiceName(rServiceName);
    if (eFac == SvtModuleOptions::E_UNKNOWN_FACTORY)
        eFac = SvtModuleOptions::ClassifyFactoryByShortName(rServiceName);
    if (eFac != SvtModuleOptions::E_UNKNOWN_FACTORY)
	{
		SetSystemTemplate( rServiceName, rTemplate );
		SvtModuleOptions().SetFactoryStandardTemplate(eFac, rTemplate);
	}
}

String SfxObjectFactory::GetStandardTemplate( const String& rServiceName )
{
	SvtModuleOptions::EFactory eFac = SvtModuleOptions::ClassifyFactoryByServiceName(rServiceName);
    if (eFac == SvtModuleOptions::E_UNKNOWN_FACTORY)
        eFac = SvtModuleOptions::ClassifyFactoryByShortName(rServiceName);

    String sTemplate;
    if (eFac != SvtModuleOptions::E_UNKNOWN_FACTORY)
        sTemplate = SvtModuleOptions().GetFactoryStandardTemplate(eFac);

	return sTemplate;
}

/*
const SfxObjectFactory* SfxObjectFactory::GetFactory( const String& rFactoryURL )
{
	const SfxObjectFactory* pFactory = 0;
	String aFact( rFactoryURL );
	String aPrefix( DEFINE_CONST_UNICODE( "private:factory/" ) );
	if ( aPrefix.Len() == aFact.Match( aPrefix ) )
		// Aufruf m"oglich mit z.B. "swriter" oder "private:factory/swriter"
		aFact.Erase( 0, aPrefix.Len() );
	sal_uInt16 nPos = aFact.Search( '?' );

	// Etwaige Parameter abschneiden
	aFact.Erase( nPos, aFact.Len() );

	SfxApplication *pApp = SFX_APP();

	// "swriter4" durch "swriter" ersetzen, zum Vergleichen uppercase verwenden
	WildCard aSearchedFac( aFact.EraseAllChars('4').ToUpperAscii() );
    for( sal_uInt16 n = GetObjectFactoryCount_Impl(); !pFactory && n--; )
	{
        pFactory = &GetObjectFactory_Impl( n );
		String aCompareTo = String::CreateFromAscii( pFactory->GetShortName() );
		aCompareTo.ToUpperAscii();
		if( !aSearchedFac.Matches( aCompareTo ) )
			pFactory = 0;
	}

	return pFactory;
}
*/

const SfxFilter* SfxObjectFactory::GetTemplateFilter() const
{
	sal_uInt16 nVersion=0;
	SfxFilterMatcher aMatcher ( String::CreateFromAscii( pShortName ) );
	SfxFilterMatcherIter aIter( &aMatcher );
	const SfxFilter *pFilter = 0;
	const SfxFilter *pTemp = aIter.First();
	while ( pTemp )
	{
		if( pTemp->IsOwnFormat() && pTemp->IsOwnTemplateFormat() && ( pTemp->GetVersion() > nVersion ) )
		{
			pFilter = pTemp;
			nVersion = (sal_uInt16) pTemp->GetVersion();
		}

		pTemp = aIter.Next();
	}

	return pFilter;
}

void SfxObjectFactory::SetDocumentTypeNameResource( const ResId& rId )
{
	DBG_ASSERT( !pImpl->pNameResId, "UI-Namensresource mehrfach gesetzt!" );
	pImpl->pNameResId = new ResId( rId );
}

String SfxObjectFactory::GetDocumentTypeName() const
{
	if ( pImpl->pNameResId )
		return String( *pImpl->pNameResId );
	return String();
}

void SfxObjectFactory::SetDocumentServiceName( const ::rtl::OUString& rServiceName )
{
	pImpl->aServiceName = rServiceName;
}

const ::rtl::OUString& SfxObjectFactory::GetDocumentServiceName() const
{
	return pImpl->aServiceName;
}

const SvGlobalName& SfxObjectFactory::GetClassId() const
{
	return pImpl->aClassName;
}

String SfxObjectFactory::GetFactoryURL() const
{
    ::rtl::OUStringBuffer aURLComposer;
    aURLComposer.appendAscii( "private:factory/" );
    aURLComposer.appendAscii( GetShortName() );
    return aURLComposer.makeStringAndClear();
}

String SfxObjectFactory::GetModuleName() const
{
    static ::rtl::OUString SERVICENAME_MODULEMANAGER = ::rtl::OUString::createFromAscii("com.sun.star.frame.ModuleManager");
    static ::rtl::OUString PROP_MODULEUINAME         = ::rtl::OUString::createFromAscii("ooSetupFactoryUIName");

    try
    {
        css::uno::Reference< css::lang::XMultiServiceFactory > xSMGR = ::comphelper::getProcessServiceFactory();

        css::uno::Reference< css::container::XNameAccess > xModuleManager(
            xSMGR->createInstance(SERVICENAME_MODULEMANAGER),
            css::uno::UNO_QUERY_THROW);

        ::rtl::OUString sDocService(GetDocumentServiceName());
        ::comphelper::SequenceAsHashMap aPropSet( xModuleManager->getByName(sDocService) );
        ::rtl::OUString sModuleName = aPropSet.getUnpackedValueOrDefault(PROP_MODULEUINAME, ::rtl::OUString());
        return String(sModuleName);
    }
    catch(const css::uno::RuntimeException&)
        { throw; }
    catch(const css::uno::Exception&)
        {}

    return String();
}


sal_uInt16 SfxObjectFactory::GetViewNo_Impl( const sal_uInt16 i_nViewId, const sal_uInt16 i_nFallback ) const
{
    for ( sal_uInt16 curViewNo = 0; curViewNo < GetViewFactoryCount(); ++curViewNo )
    {
        const sal_uInt16 curViewId = GetViewFactory( curViewNo ).GetOrdinal();
        if ( i_nViewId == curViewId )
           return curViewNo;
    }
    return i_nFallback;
}

SfxViewFactory* SfxObjectFactory::GetViewFactoryByViewName( const String& i_rViewName ) const
{
    for (   sal_uInt16 nViewNo = 0;
            nViewNo < GetViewFactoryCount();
            ++nViewNo
        )
    {
        SfxViewFactory& rViewFac( GetViewFactory( nViewNo ) );
        if  (   ( rViewFac.GetAPIViewName() == i_rViewName )
            ||  ( rViewFac.GetLegacyViewName() == i_rViewName )
            )
            return &rViewFac;
    }
    return NULL;
}
