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



#ifndef DBACCESS_DOCERRORHANDLING_HXX
#define DBACCESS_DOCERRORHANDLING_HXX

/** === begin UNO includes === **/
#include <com/sun/star/frame/XModel.hpp>
#include <com/sun/star/task/XInteractionHandler.hpp>
/** === end UNO includes === **/

namespace comphelper {
    class ComponentContext;
}

#include <memory>

//........................................................................
namespace dbmm
{
//........................................................................

	//====================================================================
	//= DocumentErrorHandling
	//====================================================================
    struct InteractionHandler_Data;
    /** wraps common operations with an interaction handler.
    */
    class InteractionHandler
    {
    public:
        /** creates an interaction handler by instantiating a css.task.InteractionHandler
            component at the given component context, or using the given document's interaction handler,
            if one is specified in the document's media descriptor.
        */
        InteractionHandler( const ::comphelper::ComponentContext& _rContext, const ::com::sun::star::uno::Reference< ::com::sun::star::frame::XModel >& _rxDocument );

        /** destructor
        */
        ~InteractionHandler();

        /** requests a document password
            @param _rDocumentName
                the document name
            @param _io_rPassword    
                the initial password on method entry, the password as entered by the user on method leave
            @return
                <TRUE/> if and only if the user entered a password, and confirmed with OK, <FALSE/>
                if the user aborted the request.
        */
        bool    requestDocumentPassword(
                    const ::rtl::OUString& _rDocumentName,
                          ::rtl::OUString& _io_rPassword
                );

        /** reports the given error (usually an exception caught on the caller's side)
            to the user
        */
        void    reportError(
                    const ::com::sun::star::uno::Any& _rError
                );

    private:
        ::std::auto_ptr< InteractionHandler_Data >  m_pData;
    };

//........................................................................
} // namespace dbmm
//........................................................................

#endif // DBACCESS_DOCERRORHANDLING_HXX
