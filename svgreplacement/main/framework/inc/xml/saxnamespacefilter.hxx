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



#ifndef __FRAMEWORK_SERVICES_SAXNAMESPACEFILTER_HXX_
#define __FRAMEWORK_SERVICES_SAXNAMESPACEFILTER_HXX_

#include <com/sun/star/xml/sax/XDocumentHandler.hpp>
#include <threadhelp/threadhelpbase.hxx>
#include <xml/xmlnamespaces.hxx>
#include <rtl/ustring.hxx>
#include <vcl/menu.hxx>
#include <cppuhelper/implbase1.hxx>

#include <stack>
#include <framework/fwedllapi.h>

//_________________________________________________________________________________________________________________
//	namespace
//_________________________________________________________________________________________________________________

namespace framework
{

class FWE_DLLPUBLIC SaxNamespaceFilter : public ThreadHelpBase,	// Struct for right initalization of mutex member! Must be first of baseclasses.
						   public ::cppu::WeakImplHelper1< ::com::sun::star::xml::sax::XDocumentHandler >
{
	public:
		SaxNamespaceFilter( ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XDocumentHandler >& rSax1DocumentHandler );
		virtual ~SaxNamespaceFilter();

		// XDocumentHandler
		virtual void SAL_CALL startDocument(void)
		throw (	::com::sun::star::xml::sax::SAXException,
				::com::sun::star::uno::RuntimeException );

		virtual void SAL_CALL endDocument(void)
		throw(	::com::sun::star::xml::sax::SAXException,
				::com::sun::star::uno::RuntimeException );

		virtual void SAL_CALL startElement(
			const rtl::OUString& aName,
			const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList > &xAttribs)
		throw(	::com::sun::star::xml::sax::SAXException,
				::com::sun::star::uno::RuntimeException );

		virtual void SAL_CALL endElement(const rtl::OUString& aName)
		throw(	::com::sun::star::xml::sax::SAXException,
				::com::sun::star::uno::RuntimeException );

		virtual void SAL_CALL characters(const rtl::OUString& aChars)
		throw(	::com::sun::star::xml::sax::SAXException,
				::com::sun::star::uno::RuntimeException );

		virtual void SAL_CALL ignorableWhitespace(const rtl::OUString& aWhitespaces)
		throw(	::com::sun::star::xml::sax::SAXException,
				::com::sun::star::uno::RuntimeException );

		virtual void SAL_CALL processingInstruction(const rtl::OUString& aTarget,
													const rtl::OUString& aData)
		throw(	::com::sun::star::xml::sax::SAXException,
				::com::sun::star::uno::RuntimeException );

		virtual void SAL_CALL setDocumentLocator(
			const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XLocator > &xLocator)
		throw(	::com::sun::star::xml::sax::SAXException,
				::com::sun::star::uno::RuntimeException );

	protected:
		typedef ::std::stack< XMLNamespaces > NamespaceStack;

		::rtl::OUString getErrorLineString();

		::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XLocator > m_xLocator;
		::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XDocumentHandler> xDocumentHandler;
		NamespaceStack	m_aNamespaceStack;
		sal_Int32		m_nDepth;
};

}

#endif // __FRAMEWORK_SERVICES_SAXNAMESPACEFILTER_HXX_
