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



#ifndef OOX_PPT_PRESENTATION_FRAGMENTHANDLER
#define OOX_PPT_PRESENTATION_FRAGMENTHANDLER

#include <com/sun/star/drawing/XDrawPage.hpp>
#include <com/sun/star/awt/Size.hpp>
#include "oox/drawingml/textliststyle.hxx"
#include "oox/ppt/slidepersist.hxx"
#include "oox/core/fragmenthandler.hxx"
#include "oox/core/relations.hxx"
#include "customshowlistcontext.hxx"

#include <stack>
#include <vector>

namespace oox { namespace ppt {

class PresentationFragmentHandler : public ::oox::core::FragmentHandler
{
public:
    PresentationFragmentHandler( ::oox::core::XmlFilterBase& rFilter, const ::rtl::OUString& rFragmentPath ) throw();
	virtual ~PresentationFragmentHandler() throw();

	virtual void SAL_CALL startDocument(  ) throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);
	virtual void SAL_CALL endDocument(  ) throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastContextHandler > SAL_CALL createFastChildContext( ::sal_Int32 Element, const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XFastAttributeList >& Attribs ) throw (::com::sun::star::xml::sax::SAXException, ::com::sun::star::uno::RuntimeException);

protected:
    bool importSlide( const ::oox::core::FragmentHandlerRef& rxSlideFragmentHandler,
                        const oox::ppt::SlidePersistPtr pPersist );

private:
	std::vector< rtl::OUString > maSlideMasterVector;
	std::vector< rtl::OUString > maSlidesVector;
	std::vector< rtl::OUString > maNotesMasterVector;
	::oox::drawingml::TextListStylePtr mpTextListStyle;

	::com::sun::star::awt::Size maSlideSize;
	::com::sun::star::awt::Size maNotesSize;

	std::vector< CustomShow >	maCustomShowList;
};

} }

#endif // OOX_PPT_PRESENTATION_FRAGMENTHANDLER
