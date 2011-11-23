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
#include "precompiled_chart2.hxx"

#include "CommandDispatch.hxx"
#include "CommonFunctors.hxx"
#include "macros.hxx"

#include <algorithm>
#include <functional>

using namespace ::com::sun::star;

using ::com::sun::star::uno::Reference;
using ::com::sun::star::uno::Sequence;
using ::rtl::OUString;

namespace
{
template< class Map >
    struct lcl_DisposeAndClearAndDeleteMapElement :
        public ::std::unary_function< typename Map::value_type, void >
    {
        lcl_DisposeAndClearAndDeleteMapElement( const Reference< uno::XInterface > & xEventSource ) :
                m_aEvent( xEventSource )
        {}
        void operator() ( typename Map::value_type & rElement )
        {
            if( rElement.second )
            {
                rElement.second->disposeAndClear( m_aEvent );
                delete rElement.second;
            }
        }
    private:
        lang::EventObject m_aEvent;
    };

template< class Map >
    void lcl_DisposeAndClearAndDeleteAllMapElements(
        Map & rMap,
        const Reference< uno::XInterface > & xEventSource )
{
    ::std::for_each( rMap.begin(), rMap.end(),
                     lcl_DisposeAndClearAndDeleteMapElement< Map >( xEventSource ));
}

} // anonymous namespace

namespace chart
{

CommandDispatch::CommandDispatch(
    const Reference< uno::XComponentContext > & xContext ) :
        impl::CommandDispatch_Base( m_aMutex ),
        m_xContext( xContext )
{
}

CommandDispatch::~CommandDispatch()
{}

void CommandDispatch::initialize()
{}

// ____ WeakComponentImplHelperBase ____
/// is called when this is disposed
void SAL_CALL CommandDispatch::disposing()
{
    lcl_DisposeAndClearAndDeleteAllMapElements( m_aListeners, static_cast< cppu::OWeakObject* >( this ));
    m_aListeners.clear();
}

// ____ XDispatch ____
void SAL_CALL CommandDispatch::dispatch( const util::URL& /* URL */, const Sequence< beans::PropertyValue >& /* Arguments */ )
    throw (uno::RuntimeException)
{}

void SAL_CALL CommandDispatch::addStatusListener( const Reference< frame::XStatusListener >& Control, const util::URL& URL )
    throw (uno::RuntimeException)
{
    tListenerMap::iterator aIt( m_aListeners.find( URL.Complete ));
    if( aIt == m_aListeners.end())
    {
        aIt = m_aListeners.insert(
            m_aListeners.begin(),
            tListenerMap::value_type( URL.Complete, new ::cppu::OInterfaceContainerHelper( m_aMutex )));
    }
    OSL_ASSERT( aIt != m_aListeners.end());

    aIt->second->addInterface( Control );
    fireStatusEvent( URL.Complete, Control );
}

void SAL_CALL CommandDispatch::removeStatusListener( const Reference< frame::XStatusListener >& Control, const util::URL& URL )
    throw (uno::RuntimeException)
{
    tListenerMap::iterator aIt( m_aListeners.find( URL.Complete ));
    if( aIt != m_aListeners.end())
        (*aIt).second->removeInterface( Control );
}

// ____ XModifyListener ____
void SAL_CALL CommandDispatch::modified( const lang::EventObject& /* aEvent */ )
    throw (uno::RuntimeException)
{
    fireAllStatusEvents( 0 );
}

// ____ XEventListener (base of XModifyListener) ____
void SAL_CALL CommandDispatch::disposing( const lang::EventObject& /* Source */ )
    throw (uno::RuntimeException)
{}

void CommandDispatch::fireAllStatusEvents(
    const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XStatusListener > & xSingleListener )
{
    fireStatusEvent( OUString(), xSingleListener );
}

void CommandDispatch::fireStatusEventForURL(
    const OUString & rURL,
    const uno::Any & rState,
    bool bEnabled,
    const Reference< frame::XStatusListener > & xSingleListener, /* = 0 */
    const OUString & rFeatureDescriptor /* = OUString() */ )
{
    // prepare event to send
    util::URL aURL;
    aURL.Complete = rURL;
    if( !m_xURLTransformer.is())
    {
        m_xURLTransformer.set(
            m_xContext->getServiceManager()->createInstanceWithContext(
                C2U( "com.sun.star.util.URLTransformer" ),
                m_xContext ),
            uno::UNO_QUERY );
    }
    if( m_xURLTransformer.is())
        m_xURLTransformer->parseStrict( aURL );

    frame::FeatureStateEvent aEventToSend(
        static_cast< cppu::OWeakObject* >( this ), // Source
        aURL,                                      // FeatureURL
        rFeatureDescriptor,                        // FeatureDescriptor
        bEnabled,                                  // IsEnabled
        false,                                     // Requery
        rState                                     // State
        );

    // send event either to single listener or all registered ones
    if( xSingleListener.is())
        xSingleListener->statusChanged( aEventToSend );
    else
    {
        tListenerMap::iterator aIt( m_aListeners.find( aURL.Complete ));
        if( aIt != m_aListeners.end())
        {
//             ::cppu::OInterfaceContainerHelper * pCntHlp = rBHelper.getContainer(
//                 ::getCppuType( reinterpret_cast< Reference< frame::XStatusListener > * >(0)));
            if( aIt->second )
            {
                ::cppu::OInterfaceIteratorHelper aIntfIt( *((*aIt).second) );

                while( aIntfIt.hasMoreElements())
                {
                    Reference< frame::XStatusListener > xListener( aIntfIt.next(), uno::UNO_QUERY );
                    try
                    {
                        if( xListener.is())
                            xListener->statusChanged( aEventToSend );
                    }
                    catch( const uno::Exception & ex )
                    {
                        ASSERT_EXCEPTION( ex );
                    }
                }
            }
        }
    }
}



} //  namespace chart
