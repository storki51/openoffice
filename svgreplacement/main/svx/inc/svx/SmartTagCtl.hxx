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


 
#ifndef _SVX_SMARTTAGSCONTROL_HXX
#define _SVX_SMARTTAGSCONTROL_HXX

// include ---------------------------------------------------------------

#include <tools/link.hxx>
#include <sfx2/mnuitem.hxx>
#include "svx/svxdllapi.h"
#include <com/sun/star/uno/Reference.hxx>

#include <vector>

class SfxBindings;
class SvxSmartTagItem;
class PopupMenu;

namespace com { namespace sun { namespace star { namespace smarttags {
    class XSmartTagAction;
} } } }

namespace com { namespace sun { namespace star { namespace container {
    class XStringKeyMap;
} } } }

// class SvxFontMenuControl ----------------------------------------------

class SVX_DLLPUBLIC SvxSmartTagsControl : public SfxMenuControl
{
private:
    PopupMenu*                  mpMenu;
	Menu&			            mrParent;
    const SvxSmartTagItem*      mpSmartTagItem;
    
    struct InvokeAction
    {
        com::sun::star::uno::Reference< com::sun::star::smarttags::XSmartTagAction > mxAction;
        com::sun::star::uno::Reference< com::sun::star::container::XStringKeyMap > mxSmartTagProperties;
        sal_uInt32 mnActionID;
        InvokeAction( com::sun::star::uno::Reference< com::sun::star::smarttags::XSmartTagAction > xAction,
                      com::sun::star::uno::Reference< com::sun::star::container::XStringKeyMap > xSmartTagProperties,
                      sal_uInt32 nActionID ) : mxAction( xAction ), mxSmartTagProperties( xSmartTagProperties ), mnActionID( nActionID ) {}  
    };

    std::vector< InvokeAction > maInvokeActions;

	void			FillMenu();
    DECL_LINK( MenuSelect, PopupMenu * );
	virtual void	StateChanged( sal_uInt16 nSID, SfxItemState eState,
								  const SfxPoolItem* pState );

public:
	SvxSmartTagsControl( sal_uInt16 nId, Menu&, SfxBindings& );
	~SvxSmartTagsControl();

	virtual PopupMenu*  GetPopup() const;
	SFX_DECL_MENU_CONTROL();
};

#endif
