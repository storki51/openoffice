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



#include "precompiled_svtools.hxx"

#include <vcl/window.hxx>
#include <vcl/virdev.hxx>

//......................................................................................................................
namespace svt
{
//......................................................................................................................

    class ToolPanelDrawer;
	//==================================================================================================================
	//= DrawerVisualization
	//==================================================================================================================
    /** serves a single purpose - let ZoomText read the drawers ...

        Strange enough, ZoomText does not read the drawers when they get the focus (in none of the combinations
        of AccessibleRoles I tried), except when it does have an AccessibleChild with the role LABEL. To "inject"       
        such a child into the A11Y hierarchy, we use this window here.

        (We could also inject the A11Y component on the A11Y level only, but this would mean additional code. With
        this approach here, VCL/toolkit will take care of creating and maintaining the A11Y component for us.)
    */
    class DrawerVisualization : public Window
    {
    public:
        DrawerVisualization( ToolPanelDrawer& i_rParent );
        ~DrawerVisualization();

    protected:
        // Window overridables
        virtual void Paint( const Rectangle& i_rBoundingBox );

    private:
        ToolPanelDrawer&    m_rDrawer;
    };

	//==================================================================================================================
	//= ToolPanelDrawer
	//==================================================================================================================
	//------------------------------------------------------------------------------------------------------------------
    class ToolPanelDrawer : public Window
    {
    public:
        ToolPanelDrawer( Window& i_rParent, const ::rtl::OUString& i_rTitle );
        ~ToolPanelDrawer();

        long    GetPreferredHeightPixel() const;
        void    SetExpanded( const bool i_bExpanded );
        bool    IsExpanded() const { return m_bExpanded; }

        void    Paint();

    protected:
        // Window overridables
        virtual void GetFocus();
        virtual void LoseFocus();
        virtual void Resize();
        virtual void DataChanged( const DataChangedEvent& i_rEvent );
        virtual void MouseButtonDown( const MouseEvent& i_rMouseEvent );

        virtual ::com::sun::star::uno::Reference< ::com::sun::star::awt::XWindowPeer >
                     GetComponentInterface( sal_Bool i_bCreate );

    private:
        Rectangle   impl_calcTextBoundingBox() const;
        Rectangle   impl_calcTitleBarBox( const Rectangle& i_rTextBox ) const;
        void        impl_paintBackground( const Rectangle& i_rTitleBarBox );
        sal_uInt16      impl_getTextStyle() const;
        void        impl_paintFocusIndicator( const Rectangle& i_rTextBox );
        Rectangle   impl_paintExpansionIndicator( const Rectangle& i_rTextBox );
        Image       impl_getExpansionIndicator() const;

        // don't expose SetText. Our text is used as AccessibleName/Desc, and those are not expected to change.
        using Window::SetText;
        using Window::Paint;

    private:
        ::std::auto_ptr< VirtualDevice >    m_pPaintDevice;
        DrawerVisualization                 m_aVisualization;
        bool                                m_bFocused;
        bool                                m_bExpanded;
    };

//......................................................................................................................
} // namespace svt
//......................................................................................................................
