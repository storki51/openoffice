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



#ifndef SC_TABCONT_HXX
#define SC_TABCONT_HXX

#include "address.hxx"
#include <svtools/tabbar.hxx>
#include <svtools/transfer.hxx>


class ScViewData;

// ---------------------------------------------------------------------------

//	initial size
#define SC_TABBAR_DEFWIDTH		270


class ScTabControl : public TabBar, public DropTargetHelper, public DragSourceHelper
{
private:
	ScViewData*		pViewData;
    sal_uInt16          nMouseClickPageId;      /// Last page ID after mouse button down/up
    sal_uInt16          nSelPageIdByMouse;      /// Selected page ID, if selected with mouse
    sal_Bool            bErrorShown;

	void    		DoDrag( const Region& rRegion );

	sal_uInt16			GetMaxId() const;
	SCTAB			GetPrivatDropPos(const Point& rPos );

protected:
	virtual void	Select();
	virtual void	Command( const CommandEvent& rCEvt );
	virtual void	MouseButtonDown( const MouseEvent& rMEvt );
	virtual void	MouseButtonUp( const MouseEvent& rMEvt );

	virtual sal_Int8 AcceptDrop( const AcceptDropEvent& rEvt );
	virtual sal_Int8 ExecuteDrop( const ExecuteDropEvent& rEvt );

	virtual void	StartDrag( sal_Int8 nAction, const Point& rPosPixel );

	virtual	long	StartRenaming();
	virtual long	AllowRenaming();
	virtual void	EndRenaming();
    virtual void    Mirror();

public:
					ScTabControl( Window* pParent, ScViewData* pData );
					~ScTabControl();

    using TabBar::StartDrag;

	void			UpdateStatus();
	void			ActivateView(sal_Bool bActivate);

    void            SetSheetLayoutRTL( sal_Bool bSheetRTL );
};



#endif
