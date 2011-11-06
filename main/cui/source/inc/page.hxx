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


#ifndef _SVX_PAGE_HXX
#define _SVX_PAGE_HXX


#include <sfx2/tabdlg.hxx>
#include <vcl/field.hxx>
#include <vcl/fixed.hxx>
#include <vcl/group.hxx>
#include <vcl/lstbox.hxx>
#include <svtools/stdctrl.hxx>
#include <svx/pagectrl.hxx>
#include <svx/frmdirlbox.hxx>
#include <editeng/svxenum.hxx>
#include <i18npool/paper.hxx>
#include <svx/flagsdef.hxx>

// enum ------------------------------------------------------------------

//CHINA001 enum SvxModeType
//CHINA001 {
//CHINA001 	SVX_PAGE_MODE_STANDARD,
//CHINA001 	SVX_PAGE_MODE_CENTER,
//CHINA001 	SVX_PAGE_MODE_PRESENTATION
//CHINA001 };

// class SvxPageDescPage -------------------------------------------------

/*  {k:\svx\prototyp\dialog\page.bmp}

	[Beschreibung]
	TabPage zur Einstellung einer Seite (Groesse, Raender, ...)

	[Items]
	<SvxPageItem>:          <SID_ATTR_PAGE>
	<SvxSizeItem>:          <SID_ATTR_SIZE>
	<SvxSizeItem>:          <SID_ATTR_MAXSIZE>
	<SvxULSpaceItem>:       <SID_ATTR_LRSPACE>
	<SvxLRSpaceItem>:       <SID_ATTR_ULSPACE>
	<SfxAllEnumItem>:       <SID_ATTR_PAPERTRAY>
	<SvxPaperBinItem>:      <SID_ATTR_PAPERBIN>
	<SvxBoolItem>:          <SID_ATTR_EXT1>
	<SvxBoolItem>:          <SID_ATTR_EXT2>

	<SfxSetItem>:           <SID_ATTR_HEADERSET>
		<SfxBoolItem>:          <SID_ATTR_ON>
		<SfxBoolItem>:          <SID_ATTR_DYNAMIC>
		<SfxBoolItem>:          <SID_ATTR_SHARED>
		<SvxSizeItem>:          <SID_ATTR_SIZE>
		<SvxULSpaceItem>:       <SID_ATTR_ULSPACE>
		<SvxLRSpaceItem>:       <SID_ATTR_LRSPACE>

	<SfxSetItem>:           <SID_ATTR_FOOTERSET>
		<SfxBoolItem>:          <SID_ATTR_ON>
		<SfxBoolItem>:          <SID_ATTR_DYNAMIC>
		<SfxBoolItem>:          <SID_ATTR_SHARED>
		<SvxSizeItem>:          <SID_ATTR_SIZE>
		<SvxULSpaceItem>:       <SID_ATTR_ULSPACE>
		<SvxLRSpaceItem>:       <SID_ATTR_LRSPACE>
*/

struct	SvxPage_Impl;
typedef	sal_uInt16 MarginPosition;

class SvxPageDescPage : public SfxTabPage
{
	using TabPage::ActivatePage;
	using TabPage::DeactivatePage;

    // paper format
    FixedLine           aPaperSizeFl;
    FixedText           aPaperFormatText;
	ListBox             aPaperSizeBox;

    FixedText           aPaperWidthText;
	MetricField         aPaperWidthEdit;
	FixedText           aPaperHeightText;
	MetricField         aPaperHeightEdit;

    FixedText           aOrientationFT;
    RadioButton         aPortraitBtn;
	RadioButton         aLandscapeBtn;

    SvxPageWindow       aBspWin;

    FixedText           		aTextFlowLbl;
    svx::FrameDirectionListBox	aTextFlowBox;

    FixedText           aPaperTrayLbl;
	ListBox             aPaperTrayBox;

    // Margins
    FixedLine           aMarginFl;
    FixedText           aLeftMarginLbl;
	MetricField         aLeftMarginEdit;
	FixedText           aRightMarginLbl;
	MetricField         aRightMarginEdit;
	FixedText           aTopMarginLbl;
	MetricField         aTopMarginEdit;
	FixedText           aBottomMarginLbl;
	MetricField         aBottomMarginEdit;

	FixedLine           aBottomSeparatorFl;
    // layout settings
    FixedLine           aLayoutFL;
	FixedText           aPageText;
    ListBox             aLayoutBox;
	FixedText			aNumberFormatText;
    ListBox             aNumberFormatBox;


    //Extras Calc
    FixedText           aTblAlignFT;
    CheckBox            aHorzBox;
	CheckBox            aVertBox;

    // Impress and Draw
	CheckBox            aAdaptBox;

	//Register Writer
	CheckBox			aRegisterCB;
	FixedText			aRegisterFT;
	ListBox				aRegisterLB;

	String				sStandardRegister;

	String              aInsideText;
	String              aOutsideText;
	String              aLeftText;
	String              aRightText;
	String				aPrintRangeQueryText;

	long				nFirstLeftMargin;
	long				nFirstRightMargin;
	long				nFirstTopMargin;
	long				nFirstBottomMargin;
	long				nLastLeftMargin;
	long				nLastRightMargin;
	long				nLastTopMargin;
	long				nLastBottomMargin;

	Size                aMaxSize;
	sal_Bool                bLandscape;
	FASTBOOL            bBorderModified;
	SvxModeType         eMode;
	Paper               ePaperStart;
	Paper               ePaperEnd;

	SvxPage_Impl*		pImpl;

#ifdef _SVX_PAGE_CXX
	void                Init_Impl();
	DECL_LINK( 			LayoutHdl_Impl, ListBox* );
	DECL_LINK( 			PaperBinHdl_Impl, ListBox* );
	DECL_LINK( 			SwapOrientation_Impl, RadioButton* );
	void                SwapFirstValues_Impl( FASTBOOL bSet );
	DECL_LINK( 			BorderModify_Impl, MetricField* );
	void                InitHeadFoot_Impl( const SfxItemSet& rSet );
	DECL_LINK( 			CenterHdl_Impl, CheckBox* );
    void                UpdateExample_Impl( bool bResetbackground = false );

	// Papiergroesse
	DECL_LINK(			PaperSizeSelect_Impl, ListBox* );
	DECL_LINK(			PaperSizeModify_Impl, Edit* );

    DECL_LINK(			FrameDirectionModify_Impl, ListBox* );

    // Hintergrund
	void                ResetBackground_Impl( const SfxItemSet& rSet );

	// Grenzwerte
	DECL_LINK(			RangeHdl_Impl, Edit* );
	void                CalcMargin_Impl();

	// Registerhaltigkeit
	DECL_LINK(			RegisterModify, CheckBox * );

    // page direction
    /** Disables vertical page direction entries in the text flow listbox. */
    void                DisableVerticalPageDir();

	bool				IsPrinterRangeOverflow( MetricField& rField, long nFirstMargin,
												long nLastMargin, MarginPosition nPos );
	void				CheckMarginEdits( bool _bClear );
	bool				IsMarginOutOfRange();
#endif

	SvxPageDescPage( Window* pParent, const SfxItemSet& rSet );

protected:
	virtual void        ActivatePage( const SfxItemSet& rSet );
	virtual int         DeactivatePage( SfxItemSet* pSet = 0 );

public:
	static SfxTabPage*  Create( Window* pParent, const SfxItemSet& rSet );
	static sal_uInt16*      GetRanges();

	virtual sal_Bool        FillItemSet( SfxItemSet& rOutSet );
	virtual void        Reset( const SfxItemSet& rSet );
	virtual void        FillUserData();

	virtual ~SvxPageDescPage();

	void                SetMode( SvxModeType eMType ) { eMode = eMType; }
	void                SetPaperFormatRanges( Paper eStart, Paper eEnd )
							{ ePaperStart = eStart, ePaperEnd = eEnd; }

	void				SetCollectionList(const List* pList);
	virtual void		PageCreated (SfxAllItemSet aSet); //add CHINA001
};

#endif // #ifndef _SVX_PAGE_HXX

