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



#include "precompiled_vcl.hxx"

#include "vcl/oldprintadaptor.hxx"
#include "vcl/gdimtf.hxx"

#include "com/sun/star/awt/Size.hpp"

#include <vector>

namespace vcl
{
    struct AdaptorPage
    {
        GDIMetaFile                     maPage;
        com::sun::star::awt::Size       maPageSize;
    };

    struct ImplOldStyleAdaptorData
    {
        std::vector< AdaptorPage >  maPages;
    };
}

using namespace vcl;
using namespace cppu;
using namespace com::sun::star;
using namespace com::sun::star::uno;
using namespace com::sun::star::beans;

OldStylePrintAdaptor::OldStylePrintAdaptor( const boost::shared_ptr< Printer >& i_pPrinter )
    : PrinterController( i_pPrinter )
    , mpData( new ImplOldStyleAdaptorData() )
{
}

OldStylePrintAdaptor::~OldStylePrintAdaptor()
{
}

void OldStylePrintAdaptor::StartPage()
{
    Size aPaperSize( getPrinter()->PixelToLogic( getPrinter()->GetPaperSizePixel(), MapMode( MAP_100TH_MM ) ) );
    mpData->maPages.push_back( AdaptorPage() );
    mpData->maPages.back().maPageSize.Width = aPaperSize.getWidth();
    mpData->maPages.back().maPageSize.Height = aPaperSize.getHeight();
    getPrinter()->SetConnectMetaFile( &mpData->maPages.back().maPage );
    
    // copy state into metafile
    boost::shared_ptr<Printer> pPrinter( getPrinter() );
    pPrinter->SetMapMode( pPrinter->GetMapMode() );
    pPrinter->SetFont( pPrinter->GetFont() );
    pPrinter->SetDrawMode( pPrinter->GetDrawMode() );
    pPrinter->SetLineColor( pPrinter->GetLineColor() );
    pPrinter->SetFillColor( pPrinter->GetFillColor() );
}

void OldStylePrintAdaptor::EndPage()
{
    getPrinter()->SetConnectMetaFile( NULL );
    mpData->maPages.back().maPage.WindStart();
}

int  OldStylePrintAdaptor::getPageCount() const
{
    return int(mpData->maPages.size());
}

Sequence< PropertyValue > OldStylePrintAdaptor::getPageParameters( int i_nPage ) const
{
    Sequence< PropertyValue > aRet( 1 );
    aRet[0].Name = rtl::OUString( RTL_CONSTASCII_USTRINGPARAM("PageSize") );
    if( i_nPage < int(mpData->maPages.size() ) )
        aRet[0].Value = makeAny( mpData->maPages[i_nPage].maPageSize );
    else
    {
        awt::Size aEmpty( 0, 0  );
        aRet[0].Value = makeAny( aEmpty );
    }
    return aRet;
}

void OldStylePrintAdaptor::printPage( int i_nPage ) const
{
    if( i_nPage < int(mpData->maPages.size()) )
   {
       mpData->maPages[ i_nPage ].maPage.WindStart();
       mpData->maPages[ i_nPage ].maPage.Play( getPrinter().get() );
   }
}

