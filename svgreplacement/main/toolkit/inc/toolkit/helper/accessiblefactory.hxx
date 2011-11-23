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



#ifndef TOOLKIT_HELPER_ACCESSIBLE_FACTORY_HXX
#define TOOLKIT_HELPER_ACCESSIBLE_FACTORY_HXX

#ifndef _COM_SUN_STAR_UNO_REFERENCE_HXX
#include <com/sun/star/uno/Reference.hxx>
#endif

#ifndef _RTL_REF_HXX
#include <rtl/ref.hxx>
#endif

namespace com { namespace sun { namespace star { namespace accessibility {
    class XAccessible;
    class XAccessibleContext;
} } } }
class VCLXButton;
class VCLXCheckBox;
class VCLXRadioButton;
class VCLXListBox;
class VCLXFixedHyperlink;
class VCLXFixedText;
class VCLXScrollBar;
class VCLXEdit;
class VCLXComboBox;
class VCLXToolBox;
class VCLXWindow;
class Menu;

//........................................................................
namespace toolkit
{
//........................................................................

    /** a function which is able to create a factory for the standard Accessible/Context
        components needed for standard toolkit controls

        The returned pointer denotes an instance of the IAccessibleFactory, which has been acquired
        <em>once</em>. The caller is responsible for holding this reference as long as it needs the
        factory, and release it afterwards.
    */
    typedef void* (SAL_CALL * GetStandardAccComponentFactory)( );

    //================================================================
	//= IAccessibleFactory
	//================================================================
    class IAccessibleFactory : public ::rtl::IReference
    {
    public:
        /** creates an accessible context for a button window
        */
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleContext >
            createAccessibleContext( VCLXButton* _pXWindow ) = 0;

        /** creates an accessible context for a checkbox window
        */
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleContext >
            createAccessibleContext( VCLXCheckBox* _pXWindow ) = 0;

        /** creates an accessible context for a radio button window
        */
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleContext >
            createAccessibleContext( VCLXRadioButton* _pXWindow ) = 0;

        /** creates an accessible context for a listbox window
        */
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleContext >
            createAccessibleContext( VCLXListBox* _pXWindow ) = 0;

        /** creates an accessible context for a fixed hyperlink window
        */
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleContext >
            createAccessibleContext( VCLXFixedHyperlink* _pXWindow ) = 0;

        /** creates an accessible context for a fixed text window
        */
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleContext >
            createAccessibleContext( VCLXFixedText* _pXWindow ) = 0;

        /** creates an accessible context for a scrollbar window
        */
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleContext >
            createAccessibleContext( VCLXScrollBar* _pXWindow ) = 0;

        /** creates an accessible context for a edit window
        */
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleContext >
            createAccessibleContext( VCLXEdit* _pXWindow ) = 0;

        /** creates an accessible context for a combo box window
        */
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleContext >
            createAccessibleContext( VCLXComboBox* _pXWindow ) = 0;

        /** creates an accessible context for a toolbox window
        */
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleContext >
            createAccessibleContext( VCLXToolBox* _pXWindow ) = 0;

        /** creates an accessible context for a generic window
        */
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessibleContext >
            createAccessibleContext( VCLXWindow* _pXWindow ) = 0;

        /** creates an accessible component for the given menu
        */
        virtual ::com::sun::star::uno::Reference< ::com::sun::star::accessibility::XAccessible >
            createAccessible( Menu* _pMenu, sal_Bool _bIsMenuBar ) = 0;
    };

//........................................................................
}   // namespace toolkit
//........................................................................

#endif // TOOLKIT_HELPER_ACCESSIBLE_FACTORY_HXX
