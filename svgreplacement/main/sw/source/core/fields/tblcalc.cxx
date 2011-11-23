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
#include "precompiled_sw.hxx"

#include <switerator.hxx>
#include <cntfrm.hxx>
#include <doc.hxx>
#include <pam.hxx> 		// fuer GetBodyTxtNode
#include <ndtxt.hxx>
#include <fmtfld.hxx>
#include <txtfld.hxx>
#include <expfld.hxx>
#include <docfld.hxx> 	// fuer _SetGetExpFld
#include <unofldmid.h>

using namespace ::com::sun::star;
using ::rtl::OUString;


SwTblFieldType::SwTblFieldType(SwDoc* pDocPtr)
	: SwValueFieldType( pDocPtr, RES_TABLEFLD )
{}


SwFieldType* SwTblFieldType::Copy() const
{
	return new SwTblFieldType(GetDoc());
}



void SwTblField::CalcField( SwTblCalcPara& rCalcPara )
{
	if( rCalcPara.rCalc.IsCalcError() )		// ist schon Fehler gesetzt ?
		return;

	// erzeuge aus den BoxNamen die Pointer
	BoxNmToPtr( rCalcPara.pTbl );
	String sFml( MakeFormel( rCalcPara ));
	SetValue( rCalcPara.rCalc.Calculate( sFml ).GetDouble() );
	ChgValid( !rCalcPara.IsStackOverFlow() );		// ist der Wert wieder gueltig?
}



SwTblField::SwTblField( SwTblFieldType* pInitType, const String& rFormel,
						sal_uInt16 nType, sal_uLong nFmt )
	: SwValueField( pInitType, nFmt ), SwTableFormula( rFormel ),
	sExpand( '0' ), nSubType(nType)
{
}


SwField* SwTblField::Copy() const
{
	SwTblField* pTmp = new SwTblField( (SwTblFieldType*)GetTyp(),
										SwTableFormula::GetFormula(), nSubType, GetFormat() );
	pTmp->sExpand 	  = sExpand;
	pTmp->SwValueField::SetValue(GetValue());
	pTmp->SwTableFormula::operator=( *this );
    pTmp->SetAutomaticLanguage(IsAutomaticLanguage());
    return pTmp;
}


String SwTblField::GetFieldName() const
{
    String aStr(GetTyp()->GetName());
    aStr += ' ';
    aStr += const_cast<SwTblField *>(this)->GetCommand();
    return aStr;
}

// suche den TextNode, in dem das Feld steht
const SwNode* SwTblField::GetNodeOfFormula() const
{
	if( !GetTyp()->GetDepends() )
		return 0;

	SwIterator<SwFmtFld,SwFieldType> aIter( *GetTyp() );
	for( SwFmtFld* pFmtFld = aIter.First(); pFmtFld; pFmtFld = aIter.Next() )
			if( this == pFmtFld->GetFld() )
				return (SwTxtNode*)&pFmtFld->GetTxtFld()->GetTxtNode();
	return 0;
}

String SwTblField::GetCommand()
{
    if (EXTRNL_NAME != GetNameType())
    {
        SwNode const*const pNd = GetNodeOfFormula();
        SwTableNode const*const pTblNd = (pNd) ? pNd->FindTableNode() : 0;
        if (pTblNd)
        {
            PtrToBoxNm( &pTblNd->GetTable() );
        }
    }
    return (EXTRNL_NAME == GetNameType())
        ? SwTableFormula::GetFormula()
        : String();
}

String SwTblField::Expand() const
{
	String aStr;
	if (nSubType & nsSwExtendedSubType::SUB_CMD)
	{
        aStr = const_cast<SwTblField *>(this)->GetCommand();
	}
	else
	{
		aStr = sExpand;
		if(nSubType & nsSwGetSetExpType::GSE_STRING)
		{
			// es ist ein String
			aStr = sExpand;
			aStr.Erase( 0,1 );
			aStr.Erase( aStr.Len()-1, 1 );
		}
	}
	return aStr;
}

sal_uInt16 SwTblField::GetSubType() const
{
	return nSubType;
}

void SwTblField::SetSubType(sal_uInt16 nType)
{
	nSubType = nType;
}


void SwTblField::SetValue( const double& rVal )
{
	SwValueField::SetValue(rVal);
	sExpand = ((SwValueFieldType*)GetTyp())->ExpandValue(rVal, GetFormat(), GetLanguage());
}

/*--------------------------------------------------------------------
	Beschreibung: Parameter setzen
 --------------------------------------------------------------------*/


String SwTblField::GetPar2() const
{
	return SwTableFormula::GetFormula();
}


void SwTblField::SetPar2(const String& rStr)
{
	SetFormula( rStr );
}


sal_Bool SwTblField::QueryValue( uno::Any& rAny, sal_uInt16 nWhichId ) const
{
	sal_Bool bRet = sal_True;
    switch ( nWhichId )
	{
	case FIELD_PROP_PAR2:
		{
			sal_uInt16 nOldSubType = nSubType;
			SwTblField* pThis = (SwTblField*)this;
			pThis->nSubType |= nsSwExtendedSubType::SUB_CMD;
			rAny <<= rtl::OUString( Expand() );
			pThis->nSubType = nOldSubType;
		}
		break;
	case FIELD_PROP_BOOL1:
		{
        	sal_Bool bFormula = 0 != (nsSwExtendedSubType::SUB_CMD & nSubType);
        	rAny.setValue(&bFormula, ::getBooleanCppuType());
		}
		break;
	case FIELD_PROP_PAR1:
		rAny <<= rtl::OUString(GetExpStr());
		break;
	case FIELD_PROP_FORMAT:
        rAny <<= (sal_Int32)GetFormat();
		break;
	default:
        bRet = sal_False;
	}
    return bRet;
}

sal_Bool SwTblField::PutValue( const uno::Any& rAny, sal_uInt16 nWhichId )
{
	sal_Bool bRet = sal_True;
	String sTmp;
    switch ( nWhichId )
	{
	case FIELD_PROP_PAR2:
		SetFormula( ::GetString( rAny, sTmp ));
		break;
	case FIELD_PROP_BOOL1:
        if(*(sal_Bool*)rAny.getValue())
            nSubType = nsSwGetSetExpType::GSE_FORMULA|nsSwExtendedSubType::SUB_CMD;
        else
            nSubType = nsSwGetSetExpType::GSE_FORMULA;
		break;
	case FIELD_PROP_PAR1:
        ChgExpStr( ::GetString( rAny, sTmp ));
		break;
    case FIELD_PROP_FORMAT:
        {
            sal_Int32 nTmp = 0;
            rAny >>= nTmp;
            SetFormat(nTmp);
        }
        break;
	default:
        bRet = sal_False;
	}
    return bRet;
}




