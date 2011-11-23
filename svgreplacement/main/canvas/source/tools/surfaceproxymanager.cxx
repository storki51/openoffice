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



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_canvas.hxx"

#include <canvas/rendering/isurfaceproxymanager.hxx>
#include <canvas/rendering/isurfaceproxy.hxx>
#include "surfaceproxy.hxx"

namespace canvas
{

	//////////////////////////////////////////////////////////////////////////////////
	// SurfaceProxyManager
	//////////////////////////////////////////////////////////////////////////////////

	class SurfaceProxyManager : public ISurfaceProxyManager
	{
    public:

        SurfaceProxyManager( const IRenderModuleSharedPtr pRenderModule ) :
            mpPageManager( new PageManager(pRenderModule) )
        {
        }

        /** the whole idea is build around the concept that you create
            some arbitrary buffer which contains the image data and
            tell the texture manager about it.  from there on you can
            draw this image using any kind of graphics api you want.
            in the technical sense we allocate some space in local
            videomemory or AGP memory which will be filled on demand,
            which means if there exists any rendering operation that
            needs to read from this memory location.  this method
            creates a logical hardware surface object which uses the
            given color buffer as the image source.  internally this
            texture may be distributed to several real hardware
            surfaces.
        */
        virtual ISurfaceProxySharedPtr createSurfaceProxy( const IColorBufferSharedPtr& pBuffer ) const
        {
            // not much to do for now, simply allocate a new surface
            // proxy from our internal pool and initialize this thing
            // properly. we *don't* create a hardware surface for now.
            return SurfaceProxySharedPtr(new SurfaceProxy(pBuffer,mpPageManager));
        }

    private:    
        PageManagerSharedPtr mpPageManager;
	};

	//////////////////////////////////////////////////////////////////////////////////
	// createSurfaceProxyManager
	//////////////////////////////////////////////////////////////////////////////////

	ISurfaceProxyManagerSharedPtr createSurfaceProxyManager( const IRenderModuleSharedPtr& rRenderModule )
    {
        return ISurfaceProxyManagerSharedPtr(
			new SurfaceProxyManager(
				rRenderModule));
	}
}
