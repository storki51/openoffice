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


#ifndef _SVX_DATALISTENER_HXX
#define _SVX_DATALISTENER_HXX

#include <cppuhelper/implbase3.hxx>
#include <com/sun/star/container/XContainerListener.hpp>
#include <com/sun/star/frame/XFrameActionListener.hpp>
#include <com/sun/star/xml/dom/events/XEventListener.hpp>

//............................................................................
namespace svxform
{
//............................................................................

    class DataNavigatorWindow;

    typedef cppu::WeakImplHelper3<
        com::sun::star::container::XContainerListener,
        com::sun::star::frame::XFrameActionListener,
        com::sun::star::xml::dom::events::XEventListener > DataListener_t;

    class DataListener : public DataListener_t
    {
    private:
        DataNavigatorWindow*        m_pNaviWin;

    public:
        DataListener( DataNavigatorWindow* pNaviWin );

    protected:
        ~DataListener();

    public:
        // XContainerListener
        virtual void SAL_CALL elementInserted( const ::com::sun::star::container::ContainerEvent& Event ) throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL elementRemoved( const ::com::sun::star::container::ContainerEvent& Event ) throw (::com::sun::star::uno::RuntimeException);
        virtual void SAL_CALL elementReplaced( const ::com::sun::star::container::ContainerEvent& Event ) throw (::com::sun::star::uno::RuntimeException);

        // XFrameActionListener
        virtual void SAL_CALL frameAction( const ::com::sun::star::frame::FrameActionEvent& Action ) throw (::com::sun::star::uno::RuntimeException);

        // xml::dom::events::XEventListener
        virtual void SAL_CALL handleEvent( const ::com::sun::star::uno::Reference< ::com::sun::star::xml::dom::events::XEvent >& evt ) throw (::com::sun::star::uno::RuntimeException);

        // lang::XEventListener
        virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source ) throw (::com::sun::star::uno::RuntimeException);
    };

//............................................................................
}   // namespace svxform
//............................................................................

#endif // #ifndef _SVX_DATALISTENER_HXX

