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


#ifndef _SVXACCFG_HXX
#define _SVXACCFG_HXX

// include ---------------------------------------------------------------

#include "editeng/editengdllapi.h"
#include <unotools/configitem.hxx>
/* -----------------------------12.10.00 11:40--------------------------------

 ---------------------------------------------------------------------------*/
class SvxAutoCorrect;
class SvxAutoCorrCfg;
class EDITENG_DLLPUBLIC SvxBaseAutoCorrCfg : public utl::ConfigItem
{
    SvxAutoCorrCfg& rParent;
    com::sun::star::uno::Sequence<rtl::OUString>    GetPropertyNames();

public:
    SvxBaseAutoCorrCfg(SvxAutoCorrCfg& rParent);
    ~SvxBaseAutoCorrCfg();

    void                    Load(sal_Bool bInit);
    virtual void            Commit();
    virtual void            Notify( const com::sun::star::uno::Sequence<rtl::OUString>& aPropertyNames);
    void                    SetModified() {ConfigItem::SetModified();}
};
/* -----------------------------12.10.00 11:40--------------------------------

 ---------------------------------------------------------------------------*/
class EDITENG_DLLPUBLIC SvxSwAutoCorrCfg : public utl::ConfigItem
{
    SvxAutoCorrCfg& rParent;
    com::sun::star::uno::Sequence<rtl::OUString>    GetPropertyNames();

public:
    SvxSwAutoCorrCfg(SvxAutoCorrCfg& rParent);
    ~SvxSwAutoCorrCfg();

    void                    Load(sal_Bool bInit);
    virtual void            Commit();
    virtual void            Notify( const com::sun::star::uno::Sequence<rtl::OUString>& aPropertyNames);
    void                    SetModified() {ConfigItem::SetModified();}
};
/*--------------------------------------------------------------------
    Beschreibung:   Konfiguration fuer Auto Correction
 --------------------------------------------------------------------*/
class EDITENG_DLLPUBLIC SvxAutoCorrCfg
{
    friend class SvxBaseAutoCorrCfg;
    friend class SvxSwAutoCorrCfg;

    SvxAutoCorrect* pAutoCorrect;

    SvxBaseAutoCorrCfg      aBaseConfig;
    SvxSwAutoCorrCfg        aSwConfig;

    // Flags f"ur Autotext:
    sal_Bool    bFileRel;
    sal_Bool    bNetRel;
    // Tiphilfe f"ur Autotext w"ahrend der Eingabe
    sal_Bool    bAutoTextTip;
    sal_Bool    bAutoTextPreview;
    sal_Bool    bAutoFmtByInput;
    sal_Bool    bSearchInAllCategories;

public:
    void        SetModified()
                {
                    aBaseConfig.SetModified();
                    aSwConfig.SetModified();
                }
    void        Commit()
                {
                    aBaseConfig.Commit();
                    aSwConfig.Commit();
                }

          SvxAutoCorrect* GetAutoCorrect()          { return pAutoCorrect; }
    const SvxAutoCorrect* GetAutoCorrect() const    { return pAutoCorrect; }
    // der Pointer geht in den Besitz des ConfigItems!
    void SetAutoCorrect( SvxAutoCorrect* );

    sal_Bool IsAutoFmtByInput() const       { return bAutoFmtByInput; }
    void SetAutoFmtByInput( sal_Bool bSet ) { bAutoFmtByInput = bSet;aSwConfig.SetModified();}

    sal_Bool IsSaveRelFile() const          { return bFileRel; }
    void SetSaveRelFile( sal_Bool bSet )    { bFileRel = bSet; aSwConfig.SetModified(); }

    sal_Bool IsSaveRelNet() const           { return bNetRel; }
    void SetSaveRelNet( sal_Bool bSet )     { bNetRel = bSet; aSwConfig.SetModified();}

    sal_Bool IsAutoTextPreview() const {return bAutoTextPreview;}
    void     SetAutoTextPreview(sal_Bool bSet) {bAutoTextPreview = bSet; aSwConfig.SetModified();}

    sal_Bool IsAutoTextTip() const          { return bAutoTextTip; }
    void SetAutoTextTip(sal_Bool bSet )     { bAutoTextTip = bSet;aSwConfig.SetModified();}

    sal_Bool IsSearchInAllCategories() const        { return bSearchInAllCategories;}
    void SetSearchInAllCategories(sal_Bool bSet )   { bSearchInAllCategories = bSet; aSwConfig.SetModified(); }

    SvxAutoCorrCfg();
    virtual ~SvxAutoCorrCfg();
    static SvxAutoCorrCfg*      Get();
};


#endif
