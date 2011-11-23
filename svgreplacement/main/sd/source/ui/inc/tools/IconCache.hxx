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



#ifndef SD_ICON_CACHE_HXX
#define SD_ICON_CACHE_HXX

#include "SdGlobalResourceContainer.hxx"
#include <vcl/image.hxx>

namespace sd {

/** This simple class stores frequently used icons so that the classes that
    use the icons do not have to store them in every one of their
    instances.

    Icons are adressed over their resource id and are loaded on demand.

    This cache acts like a singleton with a lifetime equal to that of the sd
    module.
*/
class IconCache
    : public SdGlobalResource
{
public:
    /** The lifetime of the returned reference is limited to that of the sd
        module. 
    */
    static IconCache& Instance (void);

    /** Return the icon with the given resource id.
        @return
            The returned Image may be empty when there is no icon for the
            given id or an error occured.  Should not happen under normal
            circumstances.
    */
    Image GetIcon (sal_uInt16 nResourceId);

private:
    class Implementation;
    ::std::auto_ptr<Implementation> mpImpl;

    /** The constructor creates the one instance of the cache and registers
        it at the SdGlobalResourceContainer to limit is lifetime to that of
        the sd module.
    */
    IconCache (void);

    /** This destructor is called by SdGlobalResourceContainer.
    */
    virtual ~IconCache (void);
};

} // end of namespace sd

#endif
