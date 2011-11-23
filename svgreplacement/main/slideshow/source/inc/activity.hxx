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



#ifndef INCLUDED_SLIDESHOW_ACTIVITY_HXX
#define INCLUDED_SLIDESHOW_ACTIVITY_HXX

#include <sal/types.h>

#include <boost/shared_ptr.hpp>

#include "disposable.hxx"


/* Definition of Activity interface */

namespace slideshow
{
    namespace internal
    {

        class Activity : public Disposable
        {
        public:
            /** Perform the activity associated with this interface's
                implementation.

                @return true, if activity continues, or false, if activity has
                ended.
            */
            virtual bool perform() = 0;

            /** Calculates whether the activity lags time.

            	If this method returns a time lag greater than 0.0,
            	the ActivitiesQueue will adjust the global slideshow
            	time, by subtracting the given amount of lag.
                
                @return time lag or 0.0. Value must be greater or
                equal than zero.
            */
            virtual double calcTimeLag() const = 0;
            
            /** Query whether this activity is still continuing

	            @return true, if this activity still
	            continues. Returns false, if activity has ended. It is
	            required that operator() returns false, when
	            isActive() returns false. Furthermore, it is required
	            that the inactive state is persistent; an activity
	            that has become inactive (i.e. isActive() once
	            returned false) must stay in that state eternally.
            */
            virtual bool isActive() const = 0;

            /** Notifies the Activity that it has now left the
                ActivitiesQueue

                Use this method to react on the queue removal
                event. For animated shapes, this is e.g. used to
                switch back to the non-sprite presentation mode of the
                shape.
             */
            virtual void dequeued() = 0;
            
            /** Forces this activity deactivate and get to its end state
                (if possible), but does _not_ dispose.
            */
            virtual void end() = 0;
        };

        typedef ::boost::shared_ptr< Activity > ActivitySharedPtr;

    }
}

#endif /* INCLUDED_SLIDESHOW_ACTIVITY_HXX */
