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
#include "precompiled_editeng.hxx"
#include <tools/debug.hxx>
#include <com/sun/star/io/XActiveDataControl.hpp>
#include <com/sun/star/io/XActiveDataSource.hpp>
#include <com/sun/star/xml/sax/XParser.hpp>
#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#include <com/sun/star/io/XOutputStream.hpp>
#include <com/sun/star/text/XText.hpp>
#include <comphelper/processfactory.hxx>
#include <unotools/streamwrap.hxx>
#include <rtl/ustrbuf.hxx>
#include <sot/storage.hxx>
#include <svl/itemprop.hxx>
#include <xmloff/xmlimp.hxx>
#include <xmloff/xmlmetae.hxx>
#include <xmloff/xmlictxt.hxx>
#include <xmloff/xmltoken.hxx>
#include <xmloff/xmlnmspe.hxx>
#include <xmloff/xmlstyle.hxx>
#include "editsource.hxx"
#include <editeng/editeng.hxx>
#include <editeng/unotext.hxx>
#include <editeng/unoprnms.hxx>
#include <editeng/unoipset.hxx>

using namespace com::sun::star;
using namespace com::sun::star::document;
using namespace com::sun::star::uno;
using namespace com::sun::star::lang;
using namespace com::sun::star::xml::sax;
using namespace com::sun::star::text;
using namespace ::rtl;
using namespace cppu;
using namespace xmloff::token;


///////////////////////////////////////////////////////////////////////

class SvxXMLTextImportContext : public SvXMLImportContext
{
public:
	SvxXMLTextImportContext( SvXMLImport& rImport, sal_uInt16 nPrfx, const OUString& rLName, const uno::Reference< XAttributeList >& xAttrList, const uno::Reference< XText >& xText );
	virtual ~SvxXMLTextImportContext();

	virtual SvXMLImportContext *CreateChildContext( sal_uInt16 nPrefix, const OUString& rLocalName, const uno::Reference< XAttributeList >& xAttrList );

//	SvxXMLXTableImport& getImport() const { return *(SvxXMLXTableImport*)&GetImport(); }

private:
	const uno::Reference< XText > mxText;
};

///////////////////////////////////////////////////////////////////////

SvxXMLTextImportContext::SvxXMLTextImportContext( SvXMLImport& rImport, sal_uInt16 nPrfx, const OUString& rLName, const uno::Reference< XAttributeList >&, const uno::Reference< XText >& xText )
: SvXMLImportContext( rImport, nPrfx, rLName ), mxText( xText )
{
}

SvxXMLTextImportContext::~SvxXMLTextImportContext()
{
}

SvXMLImportContext *SvxXMLTextImportContext::CreateChildContext( sal_uInt16 nPrefix, const OUString& rLocalName, const uno::Reference< XAttributeList >& xAttrList )
{
	SvXMLImportContext* pContext = NULL;
	if(XML_NAMESPACE_OFFICE == nPrefix && IsXMLToken( rLocalName, XML_BODY ) )
	{
		pContext = new SvxXMLTextImportContext( GetImport(), nPrefix, rLocalName, xAttrList, mxText );
	}
	else if( XML_NAMESPACE_OFFICE == nPrefix && IsXMLToken( rLocalName, XML_AUTOMATIC_STYLES ) )
	{
		pContext = new SvXMLStylesContext( GetImport(), nPrefix, rLocalName, xAttrList );
		GetImport().GetTextImport()->SetAutoStyles( (SvXMLStylesContext*)pContext );

	}
	else
	{
		pContext = GetImport().GetTextImport()->CreateTextChildContext( GetImport(), nPrefix, rLocalName, xAttrList );
	}

	if( NULL == pContext )
		pContext = new SvXMLImportContext( GetImport(), nPrefix, rLocalName );

	return pContext;
}

///////////////////////////////////////////////////////////////////////

class SvxXMLXTextImportComponent : public SvXMLImport
{
public:
	// #110680#
	SvxXMLXTextImportComponent( 
		const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
		const uno::Reference< XText > & xText );

	virtual ~SvxXMLXTextImportComponent() throw ();

	static sal_Bool load( const rtl::OUString& rUrl, const com::sun::star::uno::Reference< com::sun::star::container::XNameContainer >& xTable ) throw();
protected:
	virtual SvXMLImportContext *CreateChildContext( sal_uInt16 nPrefix, const OUString& rLocalName, const uno::Reference< XAttributeList >& xAttrList );

private:
	const uno::Reference< XText > mxText;
};

// --------------------------------------------------------------------

// #110680#
SvxXMLXTextImportComponent::SvxXMLXTextImportComponent( 
	const ::com::sun::star::uno::Reference< ::com::sun::star::lang::XMultiServiceFactory > xServiceFactory,
	const uno::Reference< XText > & xText )
:	SvXMLImport(xServiceFactory),
	mxText( xText )
{
	GetTextImport()->SetCursor( mxText->createTextCursor() );
}

SvxXMLXTextImportComponent::~SvxXMLXTextImportComponent() throw ()
{
}

void SvxReadXML( EditEngine& rEditEngine, SvStream& rStream, const ESelection& rSel )
{
	SvxEditEngineSource aEditSource( &rEditEngine );

    static const SfxItemPropertyMapEntry SvxXMLTextImportComponentPropertyMap[] =
	{
		SVX_UNOEDIT_CHAR_PROPERTIES,
		SVX_UNOEDIT_FONT_PROPERTIES,
//		SVX_UNOEDIT_OUTLINER_PROPERTIES,
		SVX_UNOEDIT_PARA_PROPERTIES,
		{0,0,0,0,0,0}
	};
	static SvxItemPropertySet aSvxXMLTextImportComponentPropertySet( SvxXMLTextImportComponentPropertyMap, EditEngine::GetGlobalItemPool() );

	uno::Reference<text::XText > xParent;
	SvxUnoText* pUnoText = new SvxUnoText( &aEditSource, &aSvxXMLTextImportComponentPropertySet, xParent );
	pUnoText->SetSelection( rSel );
	uno::Reference<text::XText > xText( pUnoText );

	try
	{
		do
		{
			uno::Reference<lang::XMultiServiceFactory> xServiceFactory( ::comphelper::getProcessServiceFactory() );		
			if( !xServiceFactory.is() )
			{
				DBG_ERROR( "SvxXMLXTableImport::load: got no service manager" );
				break;
			}

			uno::Reference< xml::sax::XParser > xParser( xServiceFactory->createInstance( OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.xml.sax.Parser" ) ) ), uno::UNO_QUERY );
			if( !xParser.is() )
			{
				DBG_ERROR( "com.sun.star.xml.sax.Parser service missing" );
				break;
			}

			uno::Reference<io::XInputStream> xInputStream = new utl::OInputStreamWrapper( rStream );

/* testcode
			const OUString aURL( RTL_CONSTASCII_USTRINGPARAM( "file:///e:/test.xml" ) );
			SfxMedium aMedium( aURL, STREAM_READ | STREAM_NOCREATE, sal_True );
			aMedium.IsRemote();
			uno::Reference<io::XOutputStream> xOut( new utl::OOutputStreamWrapper( *aMedium.GetOutStream() ) );

			aMedium.GetInStream()->Seek( 0 );
			uno::Reference< io::XActiveDataSource > xSource( aMedium.GetDataSource() );

			if( !xSource.is() )
			{
				DBG_ERROR( "got no data source from medium" );
				break;
			}

			uno::Reference< XInterface > xPipe( xServiceFactory->createInstance(OUString( RTL_CONSTASCII_USTRINGPARAM("com.sun.star.io.Pipe") ) ) );
			if( !xPipe.is() )
			{
				DBG_ERROR( "XMLReader::Read: com.sun.star.io.Pipe service missing" );
				break;
			}

			// connect pipe's output stream to the data source
			xSource->setOutputStream( uno::Reference< io::XOutputStream >::query( xPipe ) );

			xml::sax::InputSource aParserInput;
			aParserInput.aInputStream =	uno::Reference< io::XInputStream >::query( xPipe );
			aParserInput.sSystemId = aMedium.GetName();


			if( xSource.is() )
			{
				uno::Reference< io::XActiveDataControl > xSourceControl( xSource, UNO_QUERY );
				xSourceControl->start();
			}

*/

			// #110680#
			// uno::Reference< XDocumentHandler > xHandler( new SvxXMLXTextImportComponent( xText ) );
			uno::Reference< XDocumentHandler > xHandler( new SvxXMLXTextImportComponent( xServiceFactory, xText ) );

			xParser->setDocumentHandler( xHandler );

			xml::sax::InputSource aParserInput;
			aParserInput.aInputStream =	xInputStream;
//			aParserInput.sSystemId = aMedium.GetName();
			xParser->parseStream( aParserInput );				
		}
		while(0);
	}
	catch( uno::Exception& )
	{
	}
}

SvXMLImportContext *SvxXMLXTextImportComponent::CreateChildContext( sal_uInt16 nPrefix, const OUString& rLocalName, const uno::Reference< XAttributeList >& xAttrList )
{
	SvXMLImportContext* pContext;
	if(XML_NAMESPACE_OFFICE == nPrefix && ( IsXMLToken( rLocalName, XML_DOCUMENT ) || IsXMLToken( rLocalName, XML_DOCUMENT_CONTENT ) ) )
	{
		 pContext = new SvxXMLTextImportContext(*this, nPrefix, rLocalName, xAttrList, mxText );
	}
	else
	{
		pContext = SvXMLImport::CreateContext(nPrefix, rLocalName, xAttrList);
	}
	return pContext;
}

