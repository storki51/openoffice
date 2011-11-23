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



#ifndef _CAIROCANVAS_SURFACEPROVIDER_HXX
#define _CAIROCANVAS_SURFACEPROVIDER_HXX

#include <rtl/ref.hxx>
#include <com/sun/star/uno/XInterface.hpp>

#include "cairo_cairo.hxx"

using namespace ::cairo;

class OutputDevice;
class Bitmap;

namespace cairocanvas
{
    class Bitmap;

	/* Definition of RepaintTarget interface */
    
    /** Target interface for XCachedPrimitive implementations

    	This interface must be implemented on all canvas
    	implementations that hand out XCachedPrimitives
     */
    class SurfaceProvider : public ::com::sun::star::uno::XInterface
    {
    public:
        virtual ~SurfaceProvider() {}

        /** Query surface from this provider

            This should return the default surface to render on.
         */
		virtual SurfaceSharedPtr getSurface() = 0;

        /// create new surface in given size
		virtual SurfaceSharedPtr createSurface( const ::basegfx::B2ISize& rSize, 
                                                Content aContent = CAIRO_CONTENT_COLOR_ALPHA ) = 0;
        /// create new surface from given bitmap
        virtual SurfaceSharedPtr createSurface( ::Bitmap& rBitmap ) = 0;

        /** convert surface between alpha and non-alpha
            channel. returns new surface on success, NULL otherwise
        */
		virtual SurfaceSharedPtr changeSurface( bool bHasAlpha, bool bCopyContent ) = 0;

        /** Provides the underlying vcl outputdevice this surface renders on
         */
		virtual OutputDevice* getOutputDevice() = 0;
    };

    typedef ::rtl::Reference< SurfaceProvider > SurfaceProviderRef;
}

#endif
