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



#ifndef _DXCANVAS_RENDERMODULE_HXX
#define _DXCANVAS_RENDERMODULE_HXX

#include <basegfx/vector/b2ivector.hxx>
#include <basegfx/range/b2irectangle.hxx>
#include <canvas/rendering/irendermodule.hxx>
#include <boost/shared_ptr.hpp>
#include "dx_winstuff.hxx"

class Window;
namespace basegfx
{
    class B2IRange;
    class B2DVector;
}

namespace dxcanvas
{
    /// Specialization of IRenderModule for DirectX
    struct IDXRenderModule : public canvas::IRenderModule
    {
		/** Flip front- and backbuffer, update only given area

			Note: Both update area and offset are ignored for
			fullscreen canvas, that uses page flipping (cannot, by
			definition, do anything else there except displaying the
			full backbuffer instead of the front buffer)

            @param rUpdateArea
            Area to copy from backbuffer to front

            @param rCurrWindowArea
            Current area of VCL window (coordinates relative to VCL
            HWND)
         */
        virtual bool flip( const ::basegfx::B2IRectangle& rUpdateArea,
						   const ::basegfx::B2IRectangle& rCurrWindowArea ) = 0;

        /** Resize backbuffer area for this render module
         */
        virtual void resize( const ::basegfx::B2IRange& rect ) = 0;

        /// Write a snapshot of the screen to disk
        virtual void screenShot() = 0;

		virtual COMReference<surface_type>
			createSystemMemorySurface(
				const ::basegfx::B2IVector& rSize ) = 0;

		virtual void disposing() = 0;
		virtual HWND getHWND() const = 0;
    };

    typedef ::boost::shared_ptr< IDXRenderModule > IDXRenderModuleSharedPtr;


    /** Factory method, to create an IRenderModule instance for the
        given VCL window instance
     */
    IDXRenderModuleSharedPtr createRenderModule( const ::Window& rParent );
}

#endif
