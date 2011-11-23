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



#include "oox/core/fragmenthandler.hxx"

#include "oox/core/xmlfilterbase.hxx"

namespace oox {
namespace core {

// ============================================================================

using namespace ::com::sun::star::io;
using namespace ::com::sun::star::uno;
using namespace ::com::sun::star::xml::sax;

using ::rtl::OUString;

// ============================================================================

FragmentBaseData::FragmentBaseData( XmlFilterBase& rFilter, const OUString& rFragmentPath, RelationsRef xRelations ) :
    mrFilter( rFilter ),
    maFragmentPath( rFragmentPath ),
    mxRelations( xRelations )
{
}

// ============================================================================

FragmentHandler::FragmentHandler( XmlFilterBase& rFilter, const OUString& rFragmentPath ) :
    FragmentHandler_BASE( FragmentBaseDataRef( new FragmentBaseData( rFilter, rFragmentPath, rFilter.importRelations( rFragmentPath ) ) ) )
{
}

FragmentHandler::FragmentHandler( XmlFilterBase& rFilter, const OUString& rFragmentPath, RelationsRef xRelations ) :
    FragmentHandler_BASE( FragmentBaseDataRef( new FragmentBaseData( rFilter, rFragmentPath, xRelations ) ) )
{
}

FragmentHandler::~FragmentHandler()
{
}

// com.sun.star.xml.sax.XFastDocumentHandler interface ------------------------

void FragmentHandler::startDocument() throw( SAXException, RuntimeException )
{
}

void FragmentHandler::endDocument() throw( SAXException, RuntimeException )
{
}

void FragmentHandler::setDocumentLocator( const Reference< XLocator >& rxLocator ) throw( SAXException, RuntimeException )
{
    implSetLocator( rxLocator );
}

// com.sun.star.xml.sax.XFastContextHandler interface -------------------------

void FragmentHandler::startFastElement( sal_Int32, const Reference< XFastAttributeList >& ) throw( SAXException, RuntimeException )
{
}

void FragmentHandler::startUnknownElement( const OUString&, const OUString&, const Reference< XFastAttributeList >& ) throw( SAXException, RuntimeException )
{
}

void FragmentHandler::endFastElement( sal_Int32 ) throw( SAXException, RuntimeException )
{
}

void FragmentHandler::endUnknownElement( const OUString&, const OUString& ) throw( SAXException, RuntimeException )
{
}

Reference< XFastContextHandler > FragmentHandler::createFastChildContext( sal_Int32, const Reference< XFastAttributeList >& ) throw( SAXException, RuntimeException )
{
    return 0;
}

Reference< XFastContextHandler > FragmentHandler::createUnknownChildContext( const OUString&, const OUString&, const Reference< XFastAttributeList >& ) throw( SAXException, RuntimeException )
{
    return 0;
}

void FragmentHandler::characters( const OUString& ) throw( SAXException, RuntimeException )
{
}

void FragmentHandler::ignorableWhitespace( const OUString& ) throw( SAXException, RuntimeException )
{
}

void FragmentHandler::processingInstruction( const OUString&, const OUString& ) throw( SAXException, RuntimeException )
{
}

// XML stream handling --------------------------------------------------------

Reference< XInputStream > FragmentHandler::openFragmentStream() const
{
    return getFilter().openInputStream( getFragmentPath() );
}

// binary records -------------------------------------------------------------

const RecordInfo* FragmentHandler::getRecordInfos() const
{
    // default: no support for binary records
    return 0;
}

// ============================================================================

} // namespace core
} // namespace oox
