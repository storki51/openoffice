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



#ifndef INCLUDED_SLIDESHOW_CURSORMANAGER_HXX
#define INCLUDED_SLIDESHOW_CURSORMANAGER_HXX

#include <sal/types.h>
#include <boost/shared_ptr.hpp>


/* Definition of CursorManager interface */

namespace slideshow
{
    namespace internal
    {

        /** Interface for handling the view cursor.

        	Classes implementing this interface interact with the
        	View, arbitrating access to the mouse cursor shape.
         */
        class CursorManager
        {
        public:
            virtual ~CursorManager() {}
            
            /** Request different cursor shape.

            	@param nCursorShape
                Shape ID of the new mouse cursor
             */
            virtual bool requestCursor( sal_Int16 nCursorShape ) = 0;

            /** Reset cursor to default one.

                This method resets the cursor to whatever default to
                manager deems appropriate.
             */
            virtual void resetCursor() = 0;
        };

        typedef ::boost::shared_ptr< CursorManager > CursorManagerSharedPtr;

    }
}

#endif /* INCLUDED_SLIDESHOW_CURSORMANAGER_HXX */
