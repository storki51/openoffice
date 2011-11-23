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



#ifndef _DXCANVAS_SPRITEDEVICEHELPER_HXX
#define _DXCANVAS_SPRITEDEVICEHELPER_HXX

#include <com/sun/star/awt/Rectangle.hpp>
#include <com/sun/star/rendering/XGraphicDevice.hpp>
#include <com/sun/star/rendering/XBufferController.hpp>

#include "dx_rendermodule.hxx"
#include "dx_surfacebitmap.hxx"
#include "dx_devicehelper.hxx"

#include <canvas/rendering/isurfaceproxymanager.hxx>

#include <boost/utility.hpp>


namespace dxcanvas
{
    class SpriteCanvas;
    class SpriteCanvasHelper;

    class SpriteDeviceHelper : public DeviceHelper
    {
    public:
        SpriteDeviceHelper();

        void init( Window&                                  rWindow,
                   SpriteCanvas&                            rSpriteCanvas,
                   const ::com::sun::star::awt::Rectangle&	rRect,
                   bool                                     bFullscreen );

        /// Dispose all internal references
        void disposing();

        // partial override XWindowGraphicDevice
        ::com::sun::star::uno::Reference< ::com::sun::star::rendering::XBitmap > createCompatibleBitmap(
            const ::com::sun::star::uno::Reference< ::com::sun::star::rendering::XGraphicDevice >& 	rDevice,
            const ::com::sun::star::geometry::IntegerSize2D& 										size );
        ::com::sun::star::uno::Reference< ::com::sun::star::rendering::XVolatileBitmap > createVolatileBitmap(
            const ::com::sun::star::uno::Reference< ::com::sun::star::rendering::XGraphicDevice >& 	rDevice,
            const ::com::sun::star::geometry::IntegerSize2D& 										size );
        ::com::sun::star::uno::Reference< ::com::sun::star::rendering::XBitmap > createCompatibleAlphaBitmap(
            const ::com::sun::star::uno::Reference< ::com::sun::star::rendering::XGraphicDevice >& 	rDevice,
            const ::com::sun::star::geometry::IntegerSize2D& 										size );
        ::com::sun::star::uno::Reference< ::com::sun::star::rendering::XVolatileBitmap > createVolatileAlphaBitmap(
            const ::com::sun::star::uno::Reference< ::com::sun::star::rendering::XGraphicDevice >& 	rDevice,
            const ::com::sun::star::geometry::IntegerSize2D& 										size );

        sal_Bool hasFullScreenMode(  );
        sal_Bool enterFullScreenMode( sal_Bool bEnter );

        ::sal_Int32 createBuffers( ::sal_Int32 nBuffers );
        void 		destroyBuffers(  );
        ::sal_Bool  showBuffer( bool bIsVisible, ::sal_Bool bUpdateAll );
        ::sal_Bool  switchBuffer( bool bIsVisible, ::sal_Bool bUpdateAll );

        const IDXRenderModuleSharedPtr& getRenderModule() const { return mpRenderModule; }
        const DXSurfaceBitmapSharedPtr&	getBackBuffer() const { return mpBackBuffer; }
		const ::canvas::ISurfaceProxyManagerSharedPtr &getSurfaceProxy() const { return mpSurfaceProxyManager; }

        ::com::sun::star::uno::Any isAccelerated() const;

        void notifySizeUpdate( const ::com::sun::star::awt::Rectangle& rBounds );

        /** called when DumpScreenContent property is enabled on
            XGraphicDevice, and writes out bitmaps of current screen.
         */
        void dumpScreenContent() const;

    private:
        void resizeBackBuffer( const ::basegfx::B2ISize& rNewSize );
        HWND getHwnd() const;

        /// Pointer to sprite canvas (owner of this helper), needed to create bitmaps
        SpriteCanvas*                           mpSpriteCanvas;

        DXSurfaceBitmapSharedPtr                mpBackBuffer;

		/// Instance passing out HW textures
        ::canvas::ISurfaceProxyManagerSharedPtr mpSurfaceProxyManager;

        /// Our encapsulation interface to DirectX
        IDXRenderModuleSharedPtr                mpRenderModule;
    };
}

#endif /* _DXCANVAS_SPRITEDEVICEHELPER_HXX */
