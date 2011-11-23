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


#ifndef _SWUILABIMP_HXX
#define _SWUILABIMP_HXX
#include "labimp.hxx"

class SwLabPage : public SfxTabPage
{
	SwNewDBMgr*   pNewDBMgr;
	String        sActDBName;
	SwLabItem	  aItem;

	FixedLine     aWritingFL;
	FixedText	  aWritingText;
	CheckBox	  aAddrBox;
	MultiLineEdit aWritingEdit;
	FixedText	  aDatabaseFT;
	ListBox 	  aDatabaseLB;
	FixedText	  aTableFT;
	ListBox 	  aTableLB;
	ImageButton   aInsertBT;
	FixedText	  aDBFieldFT;
	ListBox 	  aDBFieldLB;
//	PushButton	  aDatabaseButton;

	FixedLine     aFormatFL;
	RadioButton   aContButton;
	RadioButton   aSheetButton;
	FixedText	  aMakeText;
	ListBox 	  aMakeBox;
	FixedText	  aTypeText;
	ListBox 	  aTypeBox;
    ListBox       aHiddenSortTypeBox;
    FixedInfo     aFormatInfo;

	sal_Bool		m_bLabel;

	 SwLabPage(Window* pParent, const SfxItemSet& rSet);
	~SwLabPage();

	DECL_LINK( AddrHdl, Button * );
	DECL_LINK( DatabaseHdl, ListBox *pListBox );
//    DECL_LINK( DatabaseButtonHdl, Button * );
	DECL_LINK( FieldHdl, Button * );
	DECL_LINK( PageHdl, Button * );
	DECL_LINK( MakeHdl, ListBox * );
	DECL_LINK( TypeHdl, ListBox * );

	void DisplayFormat	();
	SwLabRec* GetSelectedEntryPos();

    using TabPage::ActivatePage;
    using TabPage::DeactivatePage;
    using Window::GetParent;

public:

    static SfxTabPage* Create(Window* pParent, const SfxItemSet& rSet);

	virtual void ActivatePage(const SfxItemSet& rSet);
	virtual int  DeactivatePage(SfxItemSet* pSet = 0);
			void FillItem(SwLabItem& rItem);
	virtual sal_Bool FillItemSet(SfxItemSet& rSet);
	virtual void Reset(const SfxItemSet& rSet);

	SwLabDlg* GetParent() {return (SwLabDlg*) SfxTabPage::GetParent()->GetParent();}

	void 	SetToBusinessCard();

	void InitDatabaseBox();
	inline void SetNewDBMgr(SwNewDBMgr* pDBMgr) { pNewDBMgr = pDBMgr; }
	inline SwNewDBMgr* GetNewDBMgr() const { return pNewDBMgr; }
};

/* -----------------08.07.99 13:48-------------------

 --------------------------------------------------*/
class SwOneExampleFrame;
class SwVisitingCardPage : public SfxTabPage
{
	FixedLine       aContentFL;
	SvTreeListBox 	aAutoTextLB;
	FixedText 		aAutoTextGroupFT;
	ListBox			aAutoTextGroupLB;

	Window 			aExampleWIN;

	String			sVisCardGroup;
	String			sTempURL;

	SwLabItem	  	aLabItem;

	SwOneExampleFrame*	pExampleFrame;
	::com::sun::star::uno::Reference< ::com::sun::star::container::XNameAccess >  	_xAutoText;


	DECL_LINK( AutoTextSelectHdl, void* );
	DECL_LINK( FrameControlInitializedHdl, void* );

	void			InitFrameControl();
	void			UpdateFields();

	void			ClearUserData();
	
    using SfxTabPage::SetUserData;
	void			SetUserData( sal_uInt32 nCnt,
									const rtl::OUString* pNames,
									const rtl::OUString* pValues );

	SwVisitingCardPage(Window* pParent, const SfxItemSet& rSet);
	~SwVisitingCardPage();

    using TabPage::ActivatePage;
    using TabPage::DeactivatePage;

public:

	static SfxTabPage* Create(Window* pParent, const SfxItemSet& rSet);

	virtual void ActivatePage(const SfxItemSet& rSet);
	virtual int  DeactivatePage(SfxItemSet* pSet = 0);
	virtual sal_Bool FillItemSet(SfxItemSet& rSet);
	virtual void Reset(const SfxItemSet& rSet);
};
/* -----------------29.09.99 08:51-------------------

 --------------------------------------------------*/
class SwPrivateDataPage : public SfxTabPage
{
    FixedLine       aDataFL;

	FixedText		aNameFT;
	Edit			aFirstNameED;
	Edit			aNameED;
	Edit			aShortCutED;

	FixedText		aName2FT;
	Edit			aFirstName2ED;
	Edit			aName2ED;
	Edit			aShortCut2ED;

	FixedText		aStreetFT;
	Edit			aStreetED;
	FixedText		aZipCityFT;
	Edit			aZipED;
	Edit			aCityED;
	FixedText		aCountryStateFT;
	Edit			aCountryED;
	Edit			aStateED;
	FixedText		aTitleProfessionFT;
	Edit			aTitleED;
	Edit			aProfessionED;
	FixedText		aPhoneFT;
	Edit			aPhoneED;
	Edit 			aMobilePhoneED;
	FixedText		aFaxFT;
	Edit			aFaxED;
	FixedText		aWWWMailFT;
	Edit			aHomePageED;
	Edit			aMailED;

	SwPrivateDataPage(Window* pParent, const SfxItemSet& rSet);
	~SwPrivateDataPage();

    using TabPage::ActivatePage;
    using TabPage::DeactivatePage;

public:

	static SfxTabPage* Create(Window* pParent, const SfxItemSet& rSet);

	virtual void ActivatePage(const SfxItemSet& rSet);
	virtual int  DeactivatePage(SfxItemSet* pSet = 0);
	virtual sal_Bool FillItemSet(SfxItemSet& rSet);
	virtual void Reset(const SfxItemSet& rSet);
};
/* -----------------29.09.99 08:51-------------------

 --------------------------------------------------*/
class SwBusinessDataPage : public SfxTabPage
{
    FixedLine       aDataFL;
	FixedText		aCompanyFT;
	Edit			aCompanyED;
	FixedText		aCompanyExtFT;
	Edit			aCompanyExtED;
	FixedText		aSloganFT;
	Edit			aSloganED;

	FixedText		aStreetFT;
	Edit			aStreetED;
	FixedText		aZipCityFT;
	Edit			aZipED;
	Edit			aCityED;
	FixedText		aCountryStateFT;
	Edit			aCountryED;
	Edit			aStateED;

	FixedText		aPositionFT;
	Edit			aPositionED;

	FixedText		aPhoneFT;
	Edit			aPhoneED;
	Edit 			aMobilePhoneED;
	FixedText		aFaxFT;
	Edit			aFaxED;

	FixedText		aWWWMailFT;
	Edit			aHomePageED;
	Edit			aMailED;

	SwBusinessDataPage(Window* pParent, const SfxItemSet& rSet);
	~SwBusinessDataPage();

    using TabPage::ActivatePage;
    using TabPage::DeactivatePage;

public:

	static SfxTabPage* Create(Window* pParent, const SfxItemSet& rSet);

	virtual void ActivatePage(const SfxItemSet& rSet);
	virtual int  DeactivatePage(SfxItemSet* pSet = 0);
	virtual sal_Bool FillItemSet(SfxItemSet& rSet);
	virtual void Reset(const SfxItemSet& rSet);
};

#endif

