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



#ifndef INCLUDED_DRAWINGLAYER_PRIMITIVE2D_PRIMITIVETYPES2D_HXX
#define INCLUDED_DRAWINGLAYER_PRIMITIVE2D_PRIMITIVETYPES2D_HXX

//////////////////////////////////////////////////////////////////////////////
// define ranges for other libraries

#define	PRIMITIVE2D_ID_RANGE_DRAWINGLAYER			(0 << 16)
#define	PRIMITIVE2D_ID_RANGE_SVX					(1 << 16)
#define	PRIMITIVE2D_ID_RANGE_SD						(2 << 16)
#define	PRIMITIVE2D_ID_RANGE_SW						(3 << 16)
#define	PRIMITIVE2D_ID_RANGE_SC						(4 << 16)

//////////////////////////////////////////////////////////////////////////////
// local primitives

#define PRIMITIVE2D_ID_TRANSPARENCEPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 0)
#define PRIMITIVE2D_ID_ANIMATEDSWITCHPRIMITIVE2D			(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 1)
#define PRIMITIVE2D_ID_ANIMATEDBLINKPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 2)
#define PRIMITIVE2D_ID_ANIMATEDINTERPOLATEPRIMITIVE2D		(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 3)
#define PRIMITIVE2D_ID_BACKGROUNDCOLORPRIMITIVE2D			(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 4)
#define PRIMITIVE2D_ID_BITMAPPRIMITIVE2D					(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 5)
#define PRIMITIVE2D_ID_CONTROLPRIMITIVE2D					(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 6)
#define PRIMITIVE2D_ID_EMBEDDED3DPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 7)
#define PRIMITIVE2D_ID_FILLBITMAPPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 8)
#define PRIMITIVE2D_ID_FILLGRADIENTPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 9)
#define PRIMITIVE2D_ID_FILLHATCHPRIMITIVE2D					(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 10)
#define PRIMITIVE2D_ID_GRAPHICPRIMITIVE2D					(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 11)
#define PRIMITIVE2D_ID_GRIDPRIMITIVE2D						(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 12)
#define PRIMITIVE2D_ID_GROUPPRIMITIVE2D						(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 13)
#define PRIMITIVE2D_ID_HELPLINEPRIMITIVE2D					(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 14)
#define PRIMITIVE2D_ID_MARKERARRAYPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 15)
#define PRIMITIVE2D_ID_MASKPRIMITIVE2D						(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 16)
#define PRIMITIVE2D_ID_MEDIAPRIMITIVE2D						(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 17)
#define PRIMITIVE2D_ID_METAFILEPRIMITIVE2D					(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 18)
#define PRIMITIVE2D_ID_MODIFIEDCOLORPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 19)
#define PRIMITIVE2D_ID_POLYGONHAIRLINEPRIMITIVE2D			(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 20)
#define PRIMITIVE2D_ID_POLYGONMARKERPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 21)
#define PRIMITIVE2D_ID_POLYGONSTROKEPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 22)
#define PRIMITIVE2D_ID_POLYGONSTROKEARROWPRIMITIVE2D		(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 23)
#define PRIMITIVE2D_ID_POLYPOLYGONSTROKEPRIMITIVE2D			(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 24)
#define PRIMITIVE2D_ID_POLYPOLYGONSTROKEARROWPRIMITIVE2D	(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 25)
#define PRIMITIVE2D_ID_POLYPOLYGONCOLORPRIMITIVE2D			(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 26)
#define PRIMITIVE2D_ID_POLYPOLYGONGRADIENTPRIMITIVE2D		(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 27)
#define PRIMITIVE2D_ID_POLYPOLYGONHATCHPRIMITIVE2D			(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 28)
#define PRIMITIVE2D_ID_POLYPOLYGONBITMAPPRIMITIVE2D			(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 29)
#define PRIMITIVE2D_ID_SCENEPRIMITIVE2D						(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 30)
#define PRIMITIVE2D_ID_SHADOWPRIMITIVE2D					(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 31)
#define PRIMITIVE2D_ID_TEXTSIMPLEPORTIONPRIMITIVE2D			(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 32)
#define PRIMITIVE2D_ID_TEXTDECORATEDPORTIONPRIMITIVE2D		(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 33)
#define PRIMITIVE2D_ID_TRANSFORMPRIMITIVE2D					(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 34)
#define PRIMITIVE2D_ID_UNIFIEDTRANSPARENCEPRIMITIVE2D	    (PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 35)
#define PRIMITIVE2D_ID_POINTARRAYPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 36)
#define PRIMITIVE2D_ID_TEXTHIERARCHYFIELDPRIMITIVE2D	    (PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 37)
#define PRIMITIVE2D_ID_TEXTHIERARCHYLINEPRIMITIVE2D         (PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 38)
#define PRIMITIVE2D_ID_TEXTHIERARCHYPARAGRAPHPRIMITIVE2D    (PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 39)
#define PRIMITIVE2D_ID_TEXTHIERARCHYBLOCKPRIMITIVE2D        (PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 40)
#define PRIMITIVE2D_ID_TEXTHIERARCHYEDITPRIMITIVE2D         (PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 41)
#define PRIMITIVE2D_ID_POLYGONWAVEPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 42)
#define PRIMITIVE2D_ID_WRONGSPELLPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 43)
#define PRIMITIVE2D_ID_TEXTEFFECTPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 44)
#define PRIMITIVE2D_ID_TEXTHIERARCHYBULLETPRIMITIVE2D       (PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 45)
#define PRIMITIVE2D_ID_POLYPOLYGONHAIRLINEPRIMITIVE2D		(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 46)
#define PRIMITIVE2D_ID_EXECUTEPRIMITIVE2D		            (PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 47)
#define PRIMITIVE2D_ID_PAGEPREVIEWPRIMITIVE2D		        (PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 48)
#define PRIMITIVE2D_ID_CHARTPRIMITIVE2D						(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 49)
#define PRIMITIVE2D_ID_STRUCTURETAGPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 50)
#define PRIMITIVE2D_ID_BORDERLINEPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 51)
#define PRIMITIVE2D_ID_POLYPOLYGONMARKERPRIMITIVE2D			(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 52)
#define PRIMITIVE2D_ID_HITTESTPRIMITIVE2D                   (PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 53)
#define PRIMITIVE2D_ID_INVERTPRIMITIVE2D                    (PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 54)
#define PRIMITIVE2D_ID_DISCRETEBITMAPPRIMITIVE2D			(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 55)
#define PRIMITIVE2D_ID_WALLPAPERBITMAPPRIMITIVE2D			(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 56)
#define PRIMITIVE2D_ID_TEXTLINEPRIMITIVE2D                  (PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 57)
#define PRIMITIVE2D_ID_TEXTCHARACTERSTRIKEOUTPRIMITIVE2D    (PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 58)
#define PRIMITIVE2D_ID_TEXTGEOMETRYSTRIKEOUTPRIMITIVE2D     (PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 59)
#define PRIMITIVE2D_ID_EPSPRIMITIVE2D						(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 60)
#define PRIMITIVE2D_ID_DISCRETESHADOWPRIMITIVE2D			(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 61)
#define PRIMITIVE2D_ID_HIDDENGEOMETRYPRIMITIVE2D            (PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 62)
#define PRIMITIVE2D_ID_RENDERGRAPHICPRIMITIVE2D				(PRIMITIVE2D_ID_RANGE_DRAWINGLAYER| 63)

//////////////////////////////////////////////////////////////////////////////

#endif // INCLUDED_DRAWINGLAYER_PRIMITIVE2D_PRIMITIVETYPES2D_HXX

//////////////////////////////////////////////////////////////////////////////
// eof
