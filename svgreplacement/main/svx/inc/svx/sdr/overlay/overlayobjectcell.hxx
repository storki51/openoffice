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



#ifndef _SDR_OVERLAY_OVERLAYOBJECTCELL_HXX
#define _SDR_OVERLAY_OVERLAYOBJECTCELL_HXX

#include <svx/sdr/overlay/overlayobject.hxx>

#include <vector>

//////////////////////////////////////////////////////////////////////////////

// #114409#
namespace sdr
{
	namespace overlay
	{
		enum CellOverlayType { CELL_OVERLAY_INVERT, CELL_OVERLAY_TRANSPARENT };

        // OverlayObjectCell - used for cell cursor, selection and AutoFill handle

        class SVX_DLLPUBLIC OverlayObjectCell : public OverlayObject
        {
        public:
            typedef ::std::vector< basegfx::B2DRange > RangeVector;

        private:
            CellOverlayType mePaintType;
            RangeVector     maRectangles;

			// geometry creation for OverlayObject
			virtual drawinglayer::primitive2d::Primitive2DSequence createOverlayObjectPrimitive2DSequence();

        public:
            OverlayObjectCell( CellOverlayType eType, const Color& rColor, const RangeVector& rRects);
            virtual ~OverlayObjectCell();
        };

	} // end of namespace overlay
} // end of namespace sdr

//////////////////////////////////////////////////////////////////////////////

#endif //_SDR_OVERLAY_OVERLAYLINE_HXX

// eof
