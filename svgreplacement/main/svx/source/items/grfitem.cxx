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
#include "precompiled_svx.hxx"


#include <tools/stream.hxx>
#include <svx/grfcrop.hxx>
#include <editeng/itemtype.hxx>
#include <com/sun/star/text/GraphicCrop.hpp>

using namespace ::com::sun::star;

#define TWIP_TO_MM100(TWIP) 	((TWIP) >= 0 ? (((TWIP)*127L+36L)/72L) : (((TWIP)*127L-36L)/72L))
#define MM100_TO_TWIP(MM100)	((MM100) >= 0 ? (((MM100)*72L+63L)/127L) : (((MM100)*72L-63L)/127L))
//TYPEINIT1_FACTORY( SvxGrfCrop, SfxPoolItem , new  SvxGrfCrop(0))

/******************************************************************************
 *	Implementierung		class SwCropGrf
 ******************************************************************************/

SvxGrfCrop::SvxGrfCrop( sal_uInt16 nItemId )
	: SfxPoolItem( nItemId ),
	nLeft( 0 ), nRight( 0 ), nTop( 0 ), nBottom( 0 )
{}

SvxGrfCrop::SvxGrfCrop( sal_Int32 nL, sal_Int32 nR,
						sal_Int32 nT, sal_Int32 nB, sal_uInt16 nItemId )
	: SfxPoolItem( nItemId ),
	nLeft( nL ), nRight( nR ), nTop( nT ), nBottom( nB )
{}

SvxGrfCrop::~SvxGrfCrop()
{
}

int SvxGrfCrop::operator==( const SfxPoolItem& rAttr ) const
{
	DBG_ASSERT( SfxPoolItem::operator==( rAttr ), "not equal attributes" );
	return nLeft 	== ((const SvxGrfCrop&)rAttr).GetLeft() &&
		   nRight 	== ((const SvxGrfCrop&)rAttr).GetRight() &&
		   nTop 	== ((const SvxGrfCrop&)rAttr).GetTop() &&
		   nBottom	== ((const SvxGrfCrop&)rAttr).GetBottom();
}

/*
SfxPoolItem* SvxGrfCrop::Clone( SfxItemPool* ) const
{
	return new SvxGrfCrop( *this );
}
*/

/*
sal_uInt16 SvxGrfCrop::GetVersion( sal_uInt16 nFFVer ) const
{
	DBG_ASSERT( SOFFICE_FILEFORMAT_31==nFFVer ||
				SOFFICE_FILEFORMAT_40==nFFVer ||
				SOFFICE_FILEFORMAT_NOW==nFFVer,
				"SvxGrfCrop: exist a new fileformat?" );
	return GRFCROP_VERSION_SWDEFAULT;
}
*/

SfxPoolItem* SvxGrfCrop::Create( SvStream& rStrm, sal_uInt16 nVersion ) const
{
	sal_Int32 top, left, right, bottom;
	rStrm >> top >> left >> right >> bottom;

	if( GRFCROP_VERSION_SWDEFAULT == nVersion )
		top = -top, bottom = -bottom, left = -left, right = -right;

	SvxGrfCrop* pNew = (SvxGrfCrop*)Clone();
	pNew->SetLeft( left );
	pNew->SetRight( right );
	pNew->SetTop( top );
	pNew->SetBottom( bottom );
	return pNew;
}


SvStream& SvxGrfCrop::Store( SvStream& rStrm, sal_uInt16 nVersion ) const
{
	sal_Int32 left = GetLeft(), right = GetRight(),
			top = GetTop(), bottom = GetBottom();
	if( GRFCROP_VERSION_SWDEFAULT == nVersion )
		top = -top, bottom = -bottom, left = -left, right = -right;

	rStrm << top << left << right << bottom;

	return rStrm;
}



sal_Bool SvxGrfCrop::QueryValue( uno::Any& rVal, sal_uInt8 nMemberId ) const
{
    sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
    nMemberId &= ~CONVERT_TWIPS;
	text::GraphicCrop aRet;
	aRet.Left 	= nLeft;
	aRet.Right	= nRight;
	aRet.Top 	= nTop;
	aRet.Bottom = nBottom;

    if( bConvert )
	{
	   aRet.Right 	= TWIP_TO_MM100(aRet.Right );
	   aRet.Top    	= TWIP_TO_MM100(aRet.Top );
	   aRet.Left  	= TWIP_TO_MM100(aRet.Left 	);
	   aRet.Bottom	= TWIP_TO_MM100(aRet.Bottom);
	}


	rVal <<= aRet;
	return	 sal_True;
}

sal_Bool SvxGrfCrop::PutValue( const uno::Any& rVal, sal_uInt8 nMemberId )
{
    sal_Bool bConvert = 0!=(nMemberId&CONVERT_TWIPS);
    nMemberId &= ~CONVERT_TWIPS;
	text::GraphicCrop aVal;

	if(!(rVal >>= aVal))
		return sal_False;
    if( bConvert )
	{
	   aVal.Right 	= MM100_TO_TWIP(aVal.Right );
	   aVal.Top    	= MM100_TO_TWIP(aVal.Top );
	   aVal.Left  	= MM100_TO_TWIP(aVal.Left 	);
	   aVal.Bottom	= MM100_TO_TWIP(aVal.Bottom);
	}

	nLeft	= aVal.Left	 ;
	nRight  = aVal.Right ;
	nTop	= aVal.Top	 ;
	nBottom = aVal.Bottom;
	return	sal_True;
}

SfxItemPresentation SvxGrfCrop::GetPresentation(
    SfxItemPresentation ePres, SfxMapUnit eCoreUnit, SfxMapUnit /*ePresUnit*/,
    String &rText, const IntlWrapper* pIntl ) const
{
	rText.Erase();
	switch( ePres )
	{
	case SFX_ITEM_PRESENTATION_NAMELESS:
	case SFX_ITEM_PRESENTATION_COMPLETE:
		if( SFX_ITEM_PRESENTATION_COMPLETE == ePres )
		{
			( rText.AssignAscii( "L: " )) += ::GetMetricText( GetLeft(),
                                            eCoreUnit, SFX_MAPUNIT_MM, pIntl );
			( rText.AppendAscii( " R: " )) += ::GetMetricText( GetRight(),
                                            eCoreUnit, SFX_MAPUNIT_MM, pIntl );
			( rText.AppendAscii( " T: " )) += ::GetMetricText( GetTop(),
                                            eCoreUnit, SFX_MAPUNIT_MM, pIntl );
			( rText.AppendAscii( " B: " )) += ::GetMetricText( GetBottom(),
                                            eCoreUnit, SFX_MAPUNIT_MM, pIntl );
		}
		break;

	default:
		ePres = SFX_ITEM_PRESENTATION_NONE;
		break;
	}
	return ePres;
}




