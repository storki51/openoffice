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


#ifndef _MACROPG_HXX
#define _MACROPG_HXX

#include <sfx2/basedlgs.hxx>
#include <sfx2/tabdlg.hxx>

#include <com/sun/star/container/XNameReplace.hpp>
#include <com/sun/star/util/XModifiable.hpp>
#include <com/sun/star/beans/PropertyValue.hpp>
#include <com/sun/star/uno/Reference.hxx>
#include <svl/macitem.hxx>
#ifndef _LSTBOX_HXX //autogen
#include <vcl/lstbox.hxx>
#endif
#include <rtl/ustring.hxx>

#include <hash_map>
#include <vector>

typedef ::std::hash_map< ::rtl::OUString, ::std::pair< ::rtl::OUString, ::rtl::OUString >, ::rtl::OUStringHash, ::std::equal_to< ::rtl::OUString > > EventsHash;

struct EventDisplayName
{
    const sal_Char* pAsciiEventName;
    sal_uInt16          nEventResourceID;
    EventDisplayName() : pAsciiEventName( NULL ), nEventResourceID(0) { }
    EventDisplayName( const sal_Char* _pAsciiName, const sal_uInt16 _nResId )
        : pAsciiEventName( _pAsciiName )
        , nEventResourceID( _nResId )
    {
    }
};
typedef ::std::vector< EventDisplayName >   EventDisplayNames;

class _SvxMacroTabPage;
class SvStringsDtor;
class SvTabListBox;
class Edit;
class String;

class _HeaderTabListBox;
class _SvxMacroTabPage_Impl;


class _SvxMacroTabPage : public SfxTabPage
{
#if _SOLAR__PRIVATE
	DECL_STATIC_LINK( _SvxMacroTabPage, SelectEvent_Impl, SvTabListBox * );
	DECL_STATIC_LINK( _SvxMacroTabPage, AssignDeleteHdl_Impl, PushButton * );
	DECL_STATIC_LINK( _SvxMacroTabPage, DoubleClickHdl_Impl, SvTabListBox * );

	static long GenericHandler_Impl( _SvxMacroTabPage* pThis, PushButton* pBtn );

#endif
protected:
	_SvxMacroTabPage_Impl*		mpImpl;
    ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameReplace > m_xAppEvents;
    ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameReplace > m_xDocEvents;
    ::com::sun::star::uno::Reference< ::com::sun::star::util::XModifiable > m_xModifiable;
	EventsHash m_appEventsHash;
	EventsHash m_docEventsHash;
	bool bReadOnly, bDocModified, bAppEvents, bInitialized;
    EventDisplayNames aDisplayNames;

								_SvxMacroTabPage( Window* pParent, const ResId& rId, const SfxItemSet& rItemSet );

	void						EnableButtons();
	::com::sun::star::uno::Any 	GetPropsByName( const ::rtl::OUString& eventName, EventsHash& eventsHash );
	::std::pair< ::rtl::OUString, ::rtl::OUString > GetPairFromAny( ::com::sun::star::uno::Any aAny );

public:

	virtual						~_SvxMacroTabPage();
    void                        InitResources();

	void						InitAndSetHandler( ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameReplace > xAppEvents, ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameReplace > xDocEvents, ::com::sun::star::uno::Reference< ::com::sun::star::util::XModifiable > xModifiable );
	virtual	sal_Bool				FillItemSet( SfxItemSet& rSet );
	
	using SfxTabPage::Reset;
	virtual	void				Reset();

	void						DisplayAppEvents( bool appEvents);
	void						SetReadOnly( sal_Bool bSet );
	sal_Bool						IsReadOnly() const;
};

class SvxMacroTabPage : public _SvxMacroTabPage
{
public:
	SvxMacroTabPage(
        Window* pParent,
        const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XFrame >& _rxDocumentFrame,
        const SfxItemSet& rSet,
        ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameReplace > xNameReplace,
        sal_uInt16 nSelectedIndex
    );
	virtual ~SvxMacroTabPage();
};

// class SvxMacroAssignDlg --------------------------------------------------

typedef sal_uInt16*	(*GetTabPageRanges)(); // liefert internationale Which-Werte

class SvxMacroAssignSingleTabDialog : public SfxModalDialog
{
public:
	SvxMacroAssignSingleTabDialog( Window* pParent, const SfxItemSet& rOptionsSet, sal_uInt16 nUniqueId );

	virtual             ~SvxMacroAssignSingleTabDialog();

	void				SetTabPage( SfxTabPage* pTabPage );
	// SfxTabPage*			GetTabPage() const { return pPage; }

	// OKButton*			GetOKButton() const { return pOKBtn; }
	// CancelButton*		GetCancelButton() const { return pCancelBtn; }

private:
	SfxViewFrame*       pFrame;

	FixedLine*			pFixedLine;

	OKButton*			pOKBtn;
	CancelButton*		pCancelBtn;
	HelpButton*			pHelpBtn;

	SfxTabPage*			pPage;
	const SfxItemSet*	pOptions;
	SfxItemSet*			pOutSet;

#if _SOLAR__PRIVATE
	DECL_DLLPRIVATE_LINK( OKHdl_Impl, Button * );
#endif
};


class SvxMacroAssignDlg : public SvxMacroAssignSingleTabDialog
{
public:
	SvxMacroAssignDlg(
        Window* pParent,
        const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XFrame >& _rxDocumentFrame,
        const SfxItemSet& rSet,
        const ::com::sun::star::uno::Reference< ::com::sun::star::container::XNameReplace >& xNameReplace,
        sal_uInt16 nSelectedIndex
    );
	virtual	~SvxMacroAssignDlg();
};

#endif
