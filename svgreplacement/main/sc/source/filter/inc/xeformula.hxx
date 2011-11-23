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



#ifndef SC_XEFORMULA_HXX
#define SC_XEFORMULA_HXX

#include "xlformula.hxx"
#include "xeroot.hxx"

// External reference log =====================================================

/** Log entry for external references in a formula, used i.e. in change tracking. */
struct XclExpRefLogEntry
{
    const XclExpString* mpUrl;              /// URL of the document containing the first sheet.
    const XclExpString* mpFirstTab;         /// Name of the first sheet.
    const XclExpString* mpLastTab;          /// Name of the last sheet.
    sal_uInt16          mnFirstXclTab;      /// Calc index of the first sheet.
    sal_uInt16          mnLastXclTab;       /// Calc index of the last sheet.

    explicit            XclExpRefLogEntry();
};

/** Vector containing a log for all external references in a formula, used i.e. in change tracking. */
typedef ::std::vector< XclExpRefLogEntry > XclExpRefLog;

// Formula compiler ===========================================================

class ScRangeList;
class XclExpFmlaCompImpl;

/** The formula compiler to create Excel token arrays from Calc token arrays. */
class XclExpFormulaCompiler : protected XclExpRoot
{
public:
    explicit            XclExpFormulaCompiler( const XclExpRoot& rRoot );
    virtual             ~XclExpFormulaCompiler();

    /** Creates and returns the token array of a formula. */
    XclTokenArrayRef    CreateFormula(
                            XclFormulaType eType, const ScTokenArray& rScTokArr,
                            const ScAddress* pScBasePos = 0, XclExpRefLog* pRefLog = 0 );

    /** Creates and returns a token array containing a single cell address. */
    XclTokenArrayRef    CreateFormula( XclFormulaType eType, const ScAddress& rScPos );

    /** Creates and returns a token array containing a single cell range address. */
    XclTokenArrayRef    CreateFormula( XclFormulaType eType, const ScRange& rScRange );

    /** Creates and returns the token array for a cell range list. */
    XclTokenArrayRef    CreateFormula( XclFormulaType eType, const ScRangeList& rScRanges );

    /** Creates a single error token containing the passed error code. */
    XclTokenArrayRef    CreateErrorFormula( sal_uInt8 nErrCode );

    /** Creates a single token for a special cell reference.
        @descr  This is used for array formulas and shared formulas (token tExp),
            and multiple operation tables (token tTbl). */
    XclTokenArrayRef    CreateSpecialRefFormula( sal_uInt8 nTokenId, const XclAddress& rXclPos );

    /** Creates a single tNameXR token for a reference to an external name.
        @descr  This is used i.e. for linked macros in push buttons. */
    XclTokenArrayRef    CreateNameXFormula( sal_uInt16 nExtSheet, sal_uInt16 nExtName );

private:
    typedef ScfRef< XclExpFmlaCompImpl > XclExpFmlaCompImplRef;
    XclExpFmlaCompImplRef mxImpl;
};

// ============================================================================

#endif

