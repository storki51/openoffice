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


#ifndef _RSCSFX_HXX
#define _RSCSFX_HXX

// StarView 	(RSC_NOTYPE) bis (RSC_NOTYPE + 0x190)
// Sfx 			(RSC_NOTYPE + 0x200) bis (RSC_NOTYPE + 0x20F)
#define RSC_SFX_STYLE_FAMILIES     (0x100 + 0x201)
#define RSC_SFX_STYLE_FAMILY_ITEM  (0x100 + 0x202)
#define RSC_SFX_SLOT_INFO          (0x100 + 0x203)
// StarMoney	(RSC_NOTYPE + 0x210) bis (RSC_NOTYPE + 0x22F)
// Public   	(RSC_NOTYPE + 0x300) bis (RSC_NOTYPE + 0x3FF)

//========== S F X =======================================
enum SfxStyleFamily { SFX_STYLE_FAMILY_CHAR    = 1,
                      SFX_STYLE_FAMILY_PARA    = 2,
                      SFX_STYLE_FAMILY_FRAME   = 4,
                      SFX_STYLE_FAMILY_PAGE    = 8,
                      SFX_STYLE_FAMILY_PSEUDO  = 16,
                      SFX_STYLE_FAMILY_ALL   = 0x7fff
                      };


// SfxTemplateDialog
#define RSC_SFX_STYLE_ITEM_LIST         0x1
#define RSC_SFX_STYLE_ITEM_BITMAP       0x2
#define RSC_SFX_STYLE_ITEM_TEXT         0x4
#define RSC_SFX_STYLE_ITEM_HELPTEXT     0x8
#define RSC_SFX_STYLE_ITEM_STYLEFAMILY  0x10
#define RSC_SFX_STYLE_ITEM_IMAGE        0x20


// SfxSlotInfo
#define RSC_SFX_SLOT_INFO_SLOTNAME      0x1
#define RSC_SFX_SLOT_INFO_HELPTEXT      0x2


#endif
