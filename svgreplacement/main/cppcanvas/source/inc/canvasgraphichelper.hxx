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



#ifndef _CPPCANVAS_CANVASGRAPHICHELPER_HXX
#define _CPPCANVAS_CANVASGRAPHICHELPER_HXX

#include <com/sun/star/rendering/RenderState.hpp>
#include <basegfx/polygon/b2dpolypolygon.hxx>

#include <cppcanvas/canvasgraphic.hxx>

#include <boost/optional.hpp>

namespace com { namespace sun { namespace star { namespace rendering 
{
    class  XGraphicDevice;
} } } }


/* Definition of CanvasGraphicHelper class */

namespace cppcanvas
{

    namespace internal
    {
        
        class CanvasGraphicHelper : public virtual CanvasGraphic
        {
        public:
            CanvasGraphicHelper( const CanvasSharedPtr& rParentCanvas );

            // CanvasGraphic implementation
            virtual void 						     setTransformation( const ::basegfx::B2DHomMatrix& rMatrix );
            virtual ::basegfx::B2DHomMatrix          getTransformation() const;
            virtual void                             setClip( const ::basegfx::B2DPolyPolygon& rClipPoly );
            virtual void                             setClip();
            virtual ::basegfx::B2DPolyPolygon const* getClip() const;
            virtual void                             setRGBAColor( Color::IntSRGBA );
            virtual Color::IntSRGBA                  getRGBAColor() const;
            virtual void                             setCompositeOp( CompositeOp aOp );
            virtual CompositeOp                      getCompositeOp() const;

        protected:
            // for our clients
            // ===============
            CanvasSharedPtr																	getCanvas() const;
            ::com::sun::star::uno::Reference< ::com::sun::star::rendering::XGraphicDevice >	getGraphicDevice() const;
            const ::com::sun::star::rendering::RenderState&                                 getRenderState() const;

        private:
            mutable ::com::sun::star::rendering::RenderState 								maRenderState;

            boost::optional<basegfx::B2DPolyPolygon>                                        maClipPolyPolygon;
            CanvasSharedPtr 																mpCanvas;
            ::com::sun::star::uno::Reference< ::com::sun::star::rendering::XGraphicDevice > mxGraphicDevice;
        };

    }
}

#endif /* _CPPCANVAS_CANVASGRAPHICHELPER_HXX */
