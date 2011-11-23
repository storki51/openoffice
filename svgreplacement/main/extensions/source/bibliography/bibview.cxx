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
#include "precompiled_extensions.hxx"

#ifndef BIB_HRC
#include "bib.hrc"
#endif
#include "bibcont.hxx"
#include "bibbeam.hxx"
#include "bibmod.hxx"
#include "general.hxx"
#include "bibview.hxx"
#include "datman.hxx"
#include "bibresid.hxx"
#include "bibmod.hxx"
#include "sections.hrc"
#include "bibconfig.hxx"


#include <vcl/svapp.hxx>
#include <com/sun/star/sdbc/XResultSetUpdate.hpp>
#include <com/sun/star/form/XLoadable.hpp>
#include <vcl/msgbox.hxx>
#include <tools/debug.hxx>

using namespace ::com::sun::star;
using namespace ::com::sun::star::form;
using namespace ::com::sun::star::beans;
using namespace ::com::sun::star::lang;
using namespace ::com::sun::star::uno;

#define C2U( cChar ) ::rtl::OUString::createFromAscii( cChar )

//.........................................................................
namespace bib
{
//.........................................................................

	// -----------------------------------------------------------------------
	BibView::BibView( Window* _pParent, BibDataManager* _pManager, WinBits _nStyle )
		:BibWindow( _pParent, _nStyle )
		,m_pDatMan( _pManager )
		,m_xDatMan( _pManager )
		,m_pGeneralPage( NULL )
	{
		if ( m_xDatMan.is() )
			connectForm( m_xDatMan );
	}

	// -----------------------------------------------------------------------
	BibView::~BibView()
	{
		BibGeneralPage* pGeneralPage = m_pGeneralPage;
		m_pGeneralPage = NULL;

		pGeneralPage->CommitActiveControl();
		Reference< XForm > xForm = m_pDatMan->getForm();
		Reference< XPropertySet > xProps( xForm, UNO_QUERY );
		Reference< sdbc::XResultSetUpdate > xResUpd( xProps, UNO_QUERY );
		DBG_ASSERT( xResUpd.is(), "BibView::~BibView: invalid form!" );

		if ( xResUpd.is() )
		{
			Any aModified = xProps->getPropertyValue( C2U( "IsModified" ) );
			sal_Bool bFlag = sal_False;
			if ( ( aModified >>= bFlag ) && bFlag )
			{

                try
                {
                    Any aNew = xProps->getPropertyValue( C2U( "IsNew" ) );
                    aNew >>= bFlag;
                    if ( bFlag )
                        xResUpd->insertRow();
                    else
                        xResUpd->updateRow();
                }
                catch( const uno::Exception& rEx)
                {
                   (void) rEx; 
                }            
			}
		}

		if ( isFormConnected() )
			disconnectForm();

		pGeneralPage->RemoveListeners();
		m_xGeneralPage = NULL;
	}

	/* -----------------16.11.99 13:13-------------------

	 --------------------------------------------------*/
	void BibView::UpdatePages()
	{
		// TODO:
		// this is _strange_: Why not updating the existent general page?
		// I consider the current behaviour a HACK.
		// frank.schoenheit@sun.com
		if ( m_pGeneralPage )
		{
			m_pGeneralPage->Hide();
			m_pGeneralPage->RemoveListeners();
			m_xGeneralPage = 0;
		}

		m_xGeneralPage = m_pGeneralPage = new BibGeneralPage( this, m_pDatMan );

		Resize();

		if( HasFocus() )
			// "delayed" GetFocus() because GetFocus() is initially called before GeneralPage is created
			m_pGeneralPage->GrabFocus();

		String sErrorString( m_pGeneralPage->GetErrorString() );
		if ( sErrorString.Len() )
		{
            sal_Bool bExecute = BibModul::GetConfig()->IsShowColumnAssignmentWarning();
            if(!m_pDatMan->HasActiveConnection())
            {
                //no connection is available -> the data base has to be assigned
                m_pDatMan->DispatchDBChangeDialog();
                bExecute = sal_False;
            }
            else if(bExecute)
            {
                sErrorString += '\n';
                sErrorString += String( BibResId( RID_MAP_QUESTION ) );
                QueryBox aQuery( this, WB_YES_NO, sErrorString );
                aQuery.SetDefaultCheckBoxText();
                short nResult = aQuery.Execute();
                BibModul::GetConfig()->SetShowColumnAssignmentWarning(
                    !aQuery.GetCheckBoxState());
                if( RET_YES != nResult )
                {
                    bExecute = sal_False;
                }
            }
            if(bExecute)
			{
				Application::PostUserEvent( STATIC_LINK( this, BibView, CallMappingHdl ) );
			}
		}
	}
	//---------------------------------------------------------------------
	//--- 19.10.01 16:55:49 -----------------------------------------------

	void BibView::_loaded( const EventObject& _rEvent )
	{
		UpdatePages();
		FormControlContainer::_loaded( _rEvent );
	}

	void BibView::_reloaded( const EventObject& _rEvent )
	{
		UpdatePages();
		FormControlContainer::_loaded( _rEvent );
	}

	/* -----------------------------02.02.00 16:49--------------------------------

	 ---------------------------------------------------------------------------*/
	IMPL_STATIC_LINK( BibView, CallMappingHdl, BibView*, EMPTYARG )
	{
		pThis->m_pDatMan->CreateMappingDialog( pThis );
		return 0;
	}
	/* -----------------------------13.04.00 16:12--------------------------------

	 ---------------------------------------------------------------------------*/
	void BibView::Resize()
	{
		if ( m_pGeneralPage )
		{
			::Size aSz( GetOutputSizePixel() );
			m_pGeneralPage->SetSizePixel( aSz );
		}
		Window::Resize();
	}

	//---------------------------------------------------------------------
	//--- 18.10.01 18:52:45 -----------------------------------------------

	Reference< awt::XControlContainer > BibView::getControlContainer()
	{
		Reference< awt::XControlContainer > xReturn;
		if ( m_pGeneralPage )
			xReturn = m_pGeneralPage->GetControlContainer();
		return xReturn;
	}

	void BibView::GetFocus()
	{
		if( m_pGeneralPage )
			m_pGeneralPage->GrabFocus();
	}

	sal_Bool BibView::HandleShortCutKey( const KeyEvent& rKeyEvent )
	{
		return m_pGeneralPage? m_pGeneralPage->HandleShortCutKey( rKeyEvent ) : sal_False;
	}

//.........................................................................
}	// namespace bib
//.........................................................................
