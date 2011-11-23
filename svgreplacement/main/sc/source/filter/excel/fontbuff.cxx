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

#include "lotfntbf.hxx"

#include "scitems.hxx"
#include <editeng/cntritem.hxx>
#include <editeng/crsditem.hxx>
#include <editeng/eeitem.hxx>
#include <editeng/postitem.hxx>
#include <editeng/shdditem.hxx>
#include <editeng/escpitem.hxx>
#include <editeng/udlnitem.hxx>
#include <editeng/wghtitem.hxx>
#include <sfx2/printer.hxx>

#include "attrib.hxx"
#include "document.hxx"
#include "global.hxx"
#include "docpool.hxx"
#include "patattr.hxx"
#include "ftools.hxx"

const sal_uInt16	LotusFontBuffer::nSize = 8;

void LotusFontBuffer::Fill( const sal_uInt8 nIndex, SfxItemSet& rItemSet )
{
	sal_uInt8	nIntIndex = nIndex & 0x07;

	ENTRY*	pAkt = pData + nIntIndex;

	if( pAkt->pFont )
		rItemSet.Put( *pAkt->pFont );

	if( pAkt->pHeight )
		rItemSet.Put( *pAkt->pHeight );

	if( pAkt->pColor )
		rItemSet.Put( *pAkt->pColor );

	if( nIndex & 0x08 )
	{
        SvxWeightItem aWeightItem( WEIGHT_BOLD, ATTR_FONT_WEIGHT );
		rItemSet.Put( aWeightItem );
	}

	if( nIndex & 0x10 )
	{
        SvxPostureItem aAttr( ITALIC_NORMAL, ATTR_FONT_POSTURE );
		rItemSet.Put( aAttr );
	}

	FontUnderline eUnderline;
	switch( nIndex & 0x60 )	// Bit 5+6
	{
		case 0x60:
		case 0x20:	eUnderline = UNDERLINE_SINGLE;		break;
		case 0x40:	eUnderline = UNDERLINE_DOUBLE;		break;
		default:	eUnderline = UNDERLINE_NONE;
	}
	if( eUnderline != UNDERLINE_NONE )
	{
        SvxUnderlineItem aUndItem( eUnderline, ATTR_FONT_UNDERLINE );
		rItemSet.Put( aUndItem );
	}
}


void LotusFontBuffer::SetName( const sal_uInt16 nIndex, const String& rName )
{
	DBG_ASSERT( nIndex < nSize, "*LotusFontBuffer::SetName(): Array zu klein!" );
	if( nIndex < nSize )
	{
		register ENTRY*	pEntry = pData + nIndex;
		pEntry->TmpName( rName );

		if( pEntry->nType >= 0 )
			MakeFont( pEntry );
	}
}


void LotusFontBuffer::SetHeight( const sal_uInt16 nIndex, const sal_uInt16 nHeight )
{
	DBG_ASSERT( nIndex < nSize, "*LotusFontBuffer::SetHeight(): Array zu klein!" );
	if( nIndex < nSize )
        pData[ nIndex ].Height( *( new SvxFontHeightItem( ( sal_uLong ) nHeight * 20, 100, ATTR_FONT_HEIGHT ) ) );
}


void LotusFontBuffer::SetType( const sal_uInt16 nIndex, const sal_uInt16 nType )
{
	DBG_ASSERT( nIndex < nSize, "*LotusFontBuffer::SetType(): Array zu klein!" );
	if( nIndex < nSize )
	{
		register ENTRY*	pEntry = pData + nIndex;
		pEntry->Type( nType );

		if( pEntry->pTmpName )
			MakeFont( pEntry );
	}
}


void LotusFontBuffer::MakeFont( ENTRY* pEntry )
{
	FontFamily		eFamily = FAMILY_DONTKNOW;
	FontPitch		ePitch = PITCH_DONTKNOW;
	CharSet			eCharSet = RTL_TEXTENCODING_DONTKNOW;

	switch( pEntry->nType )
	{
		case 0x00:						// Helvetica
			eFamily = FAMILY_SWISS;
			ePitch	= PITCH_VARIABLE;
			break;
		case 0x01:						// Times Roman
			eFamily = FAMILY_ROMAN;
			ePitch	= PITCH_VARIABLE;
			break;
		case 0x02:						// Courier
			ePitch	= PITCH_FIXED;
			break;
		case 0x03:						// Symbol
			eCharSet = RTL_TEXTENCODING_SYMBOL;
			break;
	}

    pEntry->pFont = new SvxFontItem( eFamily, *pEntry->pTmpName, EMPTY_STRING, ePitch, eCharSet, ATTR_FONT );

	delete pEntry->pTmpName;
	pEntry->pTmpName = NULL;
}



