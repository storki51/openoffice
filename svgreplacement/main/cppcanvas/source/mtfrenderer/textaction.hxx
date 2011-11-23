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



#ifndef _CPPCANVAS_TEXTACTION_HXX
#define _CPPCANVAS_TEXTACTION_HXX

#include <com/sun/star/uno/Sequence.hxx>

#include <action.hxx>
#include <cppcanvas/canvas.hxx>
#include <cppcanvas/renderer.hxx>
#include <tools/poly.hxx>
#include <tools/gen.hxx>

class VirtualDevice;
class Point;
class Color;
class String;


/* Definition of internal::TextActionFactory class */

namespace cppcanvas 
{ 
    namespace internal
    {
        struct OutDevState;

        /** Creates encapsulated converters between GDIMetaFile and
            XCanvas. The Canvas argument is deliberately placed at the
            constructor, to force reconstruction of this object for a
            new canvas. This considerably eases internal state
            handling, since a lot of the internal state (e.g. fonts,
            text layout) is Canvas-dependent.
         */
        class TextActionFactory
        {
        public: 
            /** Create text action, optionally shadow/relief effect

            	Note that this method accepts all coordinates in
            	logical coordinates.

            	@param pDXArray
                Pointer to array of logical character offsets (or NULL)

            	@param bSubsettable
                When this parameter is set to true, the generated
                action might consume slightly more memory, but is
                subsettable (Action::render( Subset ) works on
                characters)
             */
            static ActionSharedPtr createTextAction( const ::Point&					rStartPoint,  
                                                     const ::Size&					rReliefOffset,  
                                                     const ::Color&					rReliefColor,
                                                     const ::Size&					rShadowOffset,
                                                     const ::Color&					rShadowColor,
                                                     const ::String& 				rText,
                                                     sal_Int32 						nStartPos,
                                                     sal_Int32 						nLen,
                                                     const sal_Int32*				pDXArray,
                                                     VirtualDevice&					rVDev,
                                                     const CanvasSharedPtr&			rCanvas, 
                                                     const OutDevState& 			rState,
                                                     const Renderer::Parameters& 	rParms,
                                                     bool							bSubsettable );

        private:
            // static factory, disable big four
            TextActionFactory();
            ~TextActionFactory();
            TextActionFactory(const TextActionFactory&);
            TextActionFactory& operator=( const TextActionFactory& );
        };
    } 
}

#endif /* _CPPCANVAS_TEXTACTION_HXX */
