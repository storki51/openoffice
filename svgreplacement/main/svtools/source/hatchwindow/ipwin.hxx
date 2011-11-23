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



#ifndef _IPWIN_HXX
#define _IPWIN_HXX

#include <tools/gen.hxx>
#include <vcl/window.hxx>
#include <tools/svborder.hxx>

/********************** SvResizeHelper ***********************************
*************************************************************************/
class SvResizeHelper
{
	Size        aBorder;
	Rectangle   aOuter;
	short       nGrab; // -1 kein Grab,  0 - 7, 8 = Move, siehe FillHandle...
	Point       aSelPos;
	sal_Bool		bResizeable;
public:
				SvResizeHelper();

	void		SetResizeable( sal_Bool b ) { bResizeable = b; }
	short       GetGrab() const { return nGrab; }
	void        SetBorderPixel( const Size & rBorderP )
				{ aBorder = rBorderP; }
	const Size & GetBorderPixel() const { return aBorder; }
	const Rectangle & GetOuterRectPixel() const
				{ return aOuter; }
	void        SetOuterRectPixel( const Rectangle & rRect )
				{ aOuter = rRect; }
	Rectangle   GetInnerRectPixel() const
				{
					Rectangle aRect( aOuter );
					aRect.Top()    += aBorder.Height();
					aRect.Left()   += aBorder.Width();
					aRect.Bottom() -= aBorder.Height();
					aRect.Right()  -= aBorder.Width();
					return aRect;
				}
				// Im Uhrzeigersinn, beginnend bei Linksoben
	void        FillHandleRectsPixel( Rectangle aRects[ 8 ] ) const;
	void        FillMoveRectsPixel( Rectangle aRects[ 4 ] ) const;
	void        Draw( OutputDevice * );
	void        InvalidateBorder( Window * );
	sal_Bool        SelectBegin( Window *, const Point & rPos );
	short       SelectMove( Window * pWin, const Point & rPos );
	Point       GetTrackPosPixel( const Rectangle & rRect ) const;
	Rectangle	GetTrackRectPixel( const Point & rTrackPos ) const;
	void        ValidateRect( Rectangle & rValidate ) const;
	sal_Bool        SelectRelease( Window *, const Point & rPos, Rectangle & rOutPosSize );
	void        Release( Window * pWin );
};

/********************** SvResizeWindow ***********************************
*************************************************************************/
class VCLXHatchWindow;
class SvResizeWindow : public Window
{
	Pointer         m_aOldPointer;
	short           m_nMoveGrab;  // Letzer Pointertyp
	SvResizeHelper  m_aResizer;
    sal_Bool        m_bActive;

	VCLXHatchWindow* m_pWrapper;
public:
	SvResizeWindow( Window* pParent, VCLXHatchWindow* pWrapper );

	void    SetHatchBorderPixel( const Size & rSize );

	void    SelectMouse( const Point & rPos );
	virtual void    MouseButtonUp( const MouseEvent & rEvt );
	virtual void    MouseMove( const MouseEvent & rEvt );
	virtual void    MouseButtonDown( const MouseEvent & rEvt );
	virtual void    KeyInput( const KeyEvent & rEvt );
	virtual void    Resize();
	virtual void    Paint( const Rectangle & );
    virtual long    Notify( NotifyEvent& rNEvt );
    virtual long    PreNotify( NotifyEvent& rNEvt );

	void	QueryObjAreaPixel( Rectangle & );
	void    RequestObjAreaPixel( const Rectangle & );
};

#endif // _IPWIN_HXX

