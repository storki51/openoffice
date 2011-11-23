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
#include "precompiled_forms.hxx"
#include "specialdispatchers.hxx"
#include <editeng/editeng.hxx>
#include <editeng/editview.hxx>
#ifndef _SVX_SVXIDS_HRC
#include <svx/svxids.hrc>
#endif
#define ITEMID_SCRIPTSPACE          SID_ATTR_PARA_SCRIPTSPACE
#include <editeng/scriptspaceitem.hxx>

//........................................................................
namespace frm
{
//........................................................................

    using namespace ::com::sun::star::uno;
    using namespace ::com::sun::star::lang;
    using namespace ::com::sun::star::util;
    using namespace ::com::sun::star::frame;
    using namespace ::com::sun::star::beans;

    //====================================================================
    //= OSelectAllDispatcher
    //====================================================================
    //--------------------------------------------------------------------
    OSelectAllDispatcher::OSelectAllDispatcher( EditView& _rView, const URL&  _rURL )
        :ORichTextFeatureDispatcher( _rView, _rURL )
    {
    }

    //--------------------------------------------------------------------
    OSelectAllDispatcher::~OSelectAllDispatcher( )
    {
        if ( !isDisposed() )
        {
            acquire();
            dispose();
        }
    }

    //--------------------------------------------------------------------
    void SAL_CALL OSelectAllDispatcher::dispatch( const URL& _rURL, const Sequence< PropertyValue >& /*_rArguments*/ ) throw (RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex );
        OSL_ENSURE( _rURL.Complete == getFeatureURL().Complete, "OSelectAllDispatcher::dispatch: invalid URL!" );
        (void)_rURL;

        checkDisposed();

        EditEngine* pEngine = getEditView() ? getEditView()->GetEditEngine() : NULL;
        OSL_ENSURE( pEngine, "OSelectAllDispatcher::dispatch: no edit engine - but not yet disposed?" );
        if ( !pEngine )
            return;

        sal_uInt16 nParagraphs = pEngine->GetParagraphCount();
        if ( nParagraphs )
        {
            sal_uInt16 nLastParaNumber = nParagraphs - 1;
            xub_StrLen nParaLen = pEngine->GetTextLen( nLastParaNumber );
            getEditView()->SetSelection( ESelection( 0, 0, nLastParaNumber, nParaLen ) );
        }
    }
    
    //--------------------------------------------------------------------
    FeatureStateEvent OSelectAllDispatcher::buildStatusEvent() const
    {
        FeatureStateEvent aEvent( ORichTextFeatureDispatcher::buildStatusEvent() );
        aEvent.IsEnabled = sal_True;
        return aEvent;
    }

    //====================================================================
    //= OParagraphDirectionDispatcher
    //====================================================================
    //--------------------------------------------------------------------
    OParagraphDirectionDispatcher::OParagraphDirectionDispatcher( EditView& _rView, AttributeId _nAttributeId, const URL& _rURL,
            IMultiAttributeDispatcher* _pMasterDispatcher )
        :OAttributeDispatcher( _rView, _nAttributeId, _rURL, _pMasterDispatcher )
    {
    }

    //--------------------------------------------------------------------
    FeatureStateEvent OParagraphDirectionDispatcher::buildStatusEvent() const
    {
        FeatureStateEvent aEvent( OAttributeDispatcher::buildStatusEvent() );

        EditEngine* pEngine = getEditView() ? getEditView()->GetEditEngine() : NULL;
        OSL_ENSURE( pEngine, "OParagraphDirectionDispatcher::dispatch: no edit engine - but not yet disposed?" );
        if ( pEngine && pEngine->IsVertical() )
            aEvent.IsEnabled = sal_False;

        return aEvent;
    }

    //====================================================================
    //= OTextDirectionDispatcher
    //====================================================================
    //--------------------------------------------------------------------
    OTextDirectionDispatcher::OTextDirectionDispatcher( EditView& _rView, const URL& _rURL )
        :ORichTextFeatureDispatcher( _rView, _rURL )
    {
    }

    //--------------------------------------------------------------------
    void SAL_CALL OTextDirectionDispatcher::dispatch( const URL& _rURL, const Sequence< PropertyValue >& /*_rArguments*/ ) throw (RuntimeException)
    {
        ::osl::MutexGuard aGuard( m_aMutex );
        OSL_ENSURE( _rURL.Complete == getFeatureURL().Complete, "OTextDirectionDispatcher::dispatch: invalid URL!" );
        (void)_rURL;

        checkDisposed();

        EditEngine* pEngine = getEditView() ? getEditView()->GetEditEngine() : NULL;
        OSL_ENSURE( pEngine, "OTextDirectionDispatcher::dispatch: no edit engine - but not yet disposed?" );
        if ( !pEngine )
            return;

        pEngine->SetVertical( !pEngine->IsVertical() );
    }
    
    //--------------------------------------------------------------------
    FeatureStateEvent OTextDirectionDispatcher::buildStatusEvent() const
    {
        FeatureStateEvent aEvent( ORichTextFeatureDispatcher::buildStatusEvent() );

        EditEngine* pEngine = getEditView() ? getEditView()->GetEditEngine() : NULL;
        OSL_ENSURE( pEngine, "OTextDirectionDispatcher::dispatch: no edit engine - but not yet disposed?" );

        aEvent.IsEnabled = sal_True;
        aEvent.State <<= (sal_Bool)( pEngine && pEngine->IsVertical() );

        return aEvent;
    }

    //====================================================================
    //= OAsianFontLayoutDispatcher
    //====================================================================
    //--------------------------------------------------------------------
    OAsianFontLayoutDispatcher::OAsianFontLayoutDispatcher( EditView& _rView, AttributeId _nAttributeId, const URL& _rURL, IMultiAttributeDispatcher* _pMasterDispatcher )
        :OParametrizedAttributeDispatcher( _rView, _nAttributeId, _rURL, _pMasterDispatcher )
    {
    }

    //--------------------------------------------------------------------
    const SfxPoolItem* OAsianFontLayoutDispatcher::convertDispatchArgsToItem( const Sequence< PropertyValue >& _rArguments )
    {
        // look for the "Enable" parameter
        const PropertyValue* pLookup = _rArguments.getConstArray();
        const PropertyValue* pLookupEnd = _rArguments.getConstArray() + _rArguments.getLength();
        while ( pLookup != pLookupEnd )
        {
            if ( pLookup->Name.equalsAscii( "Enable" ) )
                break;
            ++pLookup;
        }
        if ( pLookup != pLookupEnd )
        {
            sal_Bool bEnable = sal_True;
            OSL_VERIFY( pLookup->Value >>= bEnable );
            if ( m_nAttributeId == SID_ATTR_PARA_SCRIPTSPACE )
                return new SvxScriptSpaceItem( bEnable, (WhichId)m_nAttributeId );
            return new SfxBoolItem( (WhichId)m_nAttributeId, bEnable );
        }

        OSL_ENSURE( sal_False, "OAsianFontLayoutDispatcher::convertDispatchArgsToItem: did not find the one and only argument!" );
        return NULL;
    }

//........................................................................
}   // namespace frm
//........................................................................

