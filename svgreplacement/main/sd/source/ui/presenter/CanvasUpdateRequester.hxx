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



#ifndef SD_PRESENTER_CANVAS_UPDATE_REQUESTER_HEADER
#define SD_PRESENTER_CANVAS_UPDATE_REQUESTER_HEADER

#include "precompiled_sd.hxx"

#include <com/sun/star/rendering/XSpriteCanvas.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <sal/types.h>
#include <tools/solar.h>
#include <tools/link.hxx>
#include <vector>

namespace css = ::com::sun::star;

namespace sd { namespace presenter {

/** Each UpdateRequester handles update requests (calls to
    XCanvas::updateScreen()) for one shared canvas (a canvas that has one or
    more PresenterCanvas wrappers).  Multiple calls are collected and lead
    to a single call to updateScreen.
*/
class CanvasUpdateRequester : private ::boost::noncopyable
{
public:
    /** Return the Canvas UpdateRequester object for the given shared
        canvas.  A new object is created when it does not already exist.
    */
    static ::boost::shared_ptr<CanvasUpdateRequester> Instance (
        const css::uno::Reference<css::rendering::XSpriteCanvas>& rxCanvas);

    void RequestUpdate (const sal_Bool bUpdateAll);
    
private:
    CanvasUpdateRequester (const css::uno::Reference<css::rendering::XSpriteCanvas>& rxCanvas);
    ~CanvasUpdateRequester (void);
    class Deleter; friend class Deleter;
    
    typedef ::std::vector<
        ::std::pair<
            css::uno::Reference<css::rendering::XSpriteCanvas>, 
           ::boost::shared_ptr<CanvasUpdateRequester> > > RequesterMap;
    static RequesterMap maRequesterMap;
    
    css::uno::Reference<css::rendering::XSpriteCanvas> mxCanvas;
    sal_uLong mnUserEventId;
    sal_Bool mbUpdateFlag;
    DECL_LINK(Callback, void*);
};

} } // end of namespace ::sd::presenter

#endif
