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



#ifndef _SVX_ACCESSIBILITY_IACCESSIBLE_VIEW_FORWARDER_LISTENER_HXX
#define _SVX_ACCESSIBILITY_IACCESSIBLE_VIEW_FORWARDER_LISTENER_HXX

#ifndef _SAL_TYPES_H_
#include <sal/types.h>
#endif

namespace binfilter {

namespace accessibility {

class IAccessibleViewForwarder;

/**	<p>The purpose of this interface is to notify a user of an
    IAccessibleViewForwarder when that view forwarder changes its
    properties.  Such a change may be one of the following:
    <ul>
    <li>Change of the coordinate transformation.</li>
    <li>Change of the visible area (which in turn results in a change of the
    coordinate transformation.</li>
    <li>Change of the validity state of the view forwarder.</li>
*/
class IAccessibleViewForwarderListener
{
public:
    /** Enumeration of the different change types.
    */
    enum ChangeType {TRANSFORMATION, VISIBLE_AREA, STATE};

    /** This method is called to indicate a change of the specified view
        forwarder. 
        @param aChangeType
            The type of the change.  TRANSFORMATION indicates a change of
            the coordinate transformation with a constant visible area.  If
            the visible area changes, just use VISIBLE_AREA.  This changes
            the transformation implicitly.  The value STATE indicates a
            change of the validity state.  Check the IsValid method of the
            view forwarder before doing further calls.
        @param pViewForwarder
            The modified view forwarder.  It is specified just in case that
            there is more than one view forwarder in use at the same time.
    */
	virtual void ViewForwarderChanged (ChangeType aChangeType,
        const IAccessibleViewForwarder* pViewForwarder) = 0;
};

} // end of namespace accessibility

}//end of namespace binfilter
#endif
