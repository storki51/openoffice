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
#include "precompiled_sc.hxx"

#include "formulaparserpool.hxx"
#include <com/sun/star/beans/XPropertySet.hpp>
#include <com/sun/star/container/XContentEnumerationAccess.hpp>
#include <com/sun/star/lang/XComponent.hpp>
#include <com/sun/star/lang/XSingleComponentFactory.hpp>
#include <com/sun/star/sheet/XFilterFormulaParser.hpp>
#include <rtl/instance.hxx>
#include <comphelper/processfactory.hxx>
#include <sfx2/objsh.hxx>
#include "document.hxx"

using ::rtl::OUString;
using ::rtl::OUStringHash;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::container;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::sheet;
using namespace ::com::sun::star::uno;

// ============================================================================

namespace {

class ScParserFactoryMap
{
public:
    explicit            ScParserFactoryMap();

    Reference< XFormulaParser > createFormulaParser(
                            const Reference< XComponent >& rxComponent,
                            const OUString& rNamespace );

private:
    typedef ::std::hash_map< OUString, Reference< XSingleComponentFactory >, OUStringHash > FactoryMap;

    Reference< XComponentContext > mxContext;   /// Global component context.
    FactoryMap          maFactories;            /// All parser factories, mapped by formula namespace.
};

ScParserFactoryMap::ScParserFactoryMap() :
    mxContext( ::comphelper::getProcessComponentContext() )
{
    if( mxContext.is() ) try
    {
        // enumerate all implementations of the FormulaParser service
        Reference< XContentEnumerationAccess > xFactoryEA( mxContext->getServiceManager(), UNO_QUERY_THROW );
        Reference< XEnumeration > xEnum( xFactoryEA->createContentEnumeration( OUString( RTL_CONSTASCII_USTRINGPARAM( "com.sun.star.sheet.FilterFormulaParser" ) ) ), UNO_SET_THROW );
        while( xEnum->hasMoreElements() ) try // single try/catch for every element
        {
            // create an instance of the formula parser implementation
            Reference< XSingleComponentFactory > xCompFactory( xEnum->nextElement(), UNO_QUERY_THROW );
            Reference< XFilterFormulaParser > xParser( xCompFactory->createInstanceWithContext( mxContext ), UNO_QUERY_THROW );

            // store factory in the map
            OUString aNamespace = xParser->getSupportedNamespace();
            if( aNamespace.getLength() > 0 )
                maFactories[ aNamespace ] = xCompFactory;
        }
        catch( Exception& )
        {
        }
    }
    catch( Exception& )
    {
    }
}

Reference< XFormulaParser > ScParserFactoryMap::createFormulaParser(
        const Reference< XComponent >& rxComponent, const OUString& rNamespace )
{
    Reference< XFormulaParser > xParser;
    FactoryMap::const_iterator aIt = maFactories.find( rNamespace );
    if( aIt != maFactories.end() ) try
    {
        Sequence< Any > aArgs( 1 );
        aArgs[ 0 ] <<= rxComponent;
        xParser.set( aIt->second->createInstanceWithArgumentsAndContext( aArgs, mxContext ), UNO_QUERY_THROW );
    }
    catch( Exception& )
    {
    }
    return xParser;
}

struct ScParserFactorySingleton : public ::rtl::Static< ScParserFactoryMap, ScParserFactorySingleton > {};

} // namespace

// ============================================================================

ScFormulaParserPool::ScFormulaParserPool( const ScDocument& rDoc ) :
    mrDoc( rDoc )
{
}

ScFormulaParserPool::~ScFormulaParserPool()
{
}

bool ScFormulaParserPool::hasFormulaParser( const OUString& rNamespace )
{
    return getFormulaParser( rNamespace ).is();
}

Reference< XFormulaParser > ScFormulaParserPool::getFormulaParser( const OUString& rNamespace )
{
    // try to find an existing parser entry
    ParserMap::iterator aIt = maParsers.find( rNamespace );
    if( aIt != maParsers.end() )
        return aIt->second;

    // always create a new entry in the map (even if the following initialization fails)
    Reference< XFormulaParser >& rxParser = maParsers[ rNamespace ];

    // try to create a new parser object
    if( SfxObjectShell* pDocShell = mrDoc.GetDocumentShell() ) try
    {
        Reference< XComponent > xComponent( pDocShell->GetModel(), UNO_QUERY_THROW );
        ScParserFactoryMap& rFactoryMap = ScParserFactorySingleton::get();
        rxParser = rFactoryMap.createFormulaParser( xComponent, rNamespace );
    }
    catch( Exception& )
    {
    }
    return rxParser;
}

// ============================================================================

