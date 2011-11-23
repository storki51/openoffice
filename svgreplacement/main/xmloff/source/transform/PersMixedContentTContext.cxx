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
#include "precompiled_xmloff.hxx"

#ifndef _XMLOFF_TRANSFORMERBASE_HXX
#include "TransformerBase.hxx"
#endif
#include "PersMixedContentTContext.hxx"

using ::rtl::OUString;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;

//------------------------------------------------------------------------------
class XMLPersTextTContext_Impl : public XMLTransformerContext
{
	::rtl::OUString m_aCharacters;

public:
	TYPEINFO();

	XMLPersTextTContext_Impl( XMLTransformerBase& rTransformer, 
						   const ::rtl::OUString& rChars );
	virtual ~XMLPersTextTContext_Impl();

	virtual XMLTransformerContext *CreateChildContext( sal_uInt16 nPrefix,
								   const ::rtl::OUString& rLocalName,
								   const ::rtl::OUString& rQName,
								   const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );
	virtual void StartElement( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& xAttrList );
	virtual void EndElement();
	virtual void Characters( const ::rtl::OUString& rChars );

	virtual sal_Bool IsPersistent() const;
	virtual void Export();
	const ::rtl::OUString& GetText() const { return m_aCharacters; }
};

TYPEINIT1( XMLPersTextTContext_Impl, XMLTransformerContext );

XMLPersTextTContext_Impl::XMLPersTextTContext_Impl( 
		XMLTransformerBase& rImp, 
		const OUString& rChars ) :
	XMLTransformerContext( rImp, OUString() ),
	m_aCharacters( rChars )
{
}

XMLPersTextTContext_Impl::~XMLPersTextTContext_Impl()
{
}

XMLTransformerContext *XMLPersTextTContext_Impl::CreateChildContext(
		sal_uInt16,
		const OUString&,
		const OUString&,
		const Reference< XAttributeList >& )
{
	OSL_ENSURE( !this, "illegal call to CreateChildContext" );
	return 0;
}

void XMLPersTextTContext_Impl::StartElement( 
	const Reference< XAttributeList >& )
{
	OSL_ENSURE( !this, "illegal call to StartElement" );
}

void XMLPersTextTContext_Impl::EndElement()
{
	OSL_ENSURE( !this, "illegal call to EndElement" );
}

sal_Bool XMLPersTextTContext_Impl::IsPersistent() const
{
	return sal_True;
}

void XMLPersTextTContext_Impl::Characters( const OUString& rChars )
{
	m_aCharacters += rChars;
}

void XMLPersTextTContext_Impl::Export()
{
	GetTransformer().GetDocHandler()->characters( m_aCharacters );
}

//------------------------------------------------------------------------------

TYPEINIT1( XMLPersMixedContentTContext, XMLPersElemContentTContext );

XMLPersMixedContentTContext::XMLPersMixedContentTContext( 
		XMLTransformerBase& rImp, 
		const OUString& rQName ) :
	XMLPersElemContentTContext( rImp, rQName )
{
}

XMLPersMixedContentTContext::XMLPersMixedContentTContext( 
		XMLTransformerBase& rImp, 
		const OUString& rQName,
	   sal_uInt16 nActionMap ) :
	XMLPersElemContentTContext( rImp, rQName, nActionMap )
{
}

XMLPersMixedContentTContext::XMLPersMixedContentTContext( 
		XMLTransformerBase& rImp, 
		const OUString& rQName,
	    sal_uInt16 nPrefix,
		::xmloff::token::XMLTokenEnum eToken ) :
	XMLPersElemContentTContext( rImp, rQName, nPrefix, eToken )
{
}

XMLPersMixedContentTContext::XMLPersMixedContentTContext( 
		XMLTransformerBase& rImp, 
		const OUString& rQName,
	    sal_uInt16 nPrefix,
		::xmloff::token::XMLTokenEnum eToken,
	   sal_uInt16 nActionMap ) :
	XMLPersElemContentTContext( rImp, rQName, nPrefix, eToken, nActionMap )
{
}

XMLPersMixedContentTContext::~XMLPersMixedContentTContext()
{
}

void XMLPersMixedContentTContext::Characters( const OUString& rChars )
{
	AddContent( new XMLPersTextTContext_Impl( GetTransformer(), rChars ) );
}
