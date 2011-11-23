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


#ifndef _SDTAIITM_HXX
#define _SDTAIITM_HXX

#include <bf_svtools/bf_solar.h>

#ifndef _SDYNITM_HXX
#include <bf_svx/sdynitm.hxx>
#endif

#ifndef _SVDDEF_HXX //autogen
#include <bf_svx/svddef.hxx>
#endif
namespace binfilter {

class SdrTextAniStartInsideItem: public SdrYesNoItem {
public:
	SdrTextAniStartInsideItem(BOOL bOn=FALSE): SdrYesNoItem(SDRATTR_TEXT_ANISTARTINSIDE,bOn) {}
	SdrTextAniStartInsideItem(SvStream& rIn) : SdrYesNoItem(SDRATTR_TEXT_ANISTARTINSIDE,rIn) {}
};

class SdrTextAniStopInsideItem: public SdrYesNoItem {
public:
	SdrTextAniStopInsideItem(BOOL bOn=FALSE): SdrYesNoItem(SDRATTR_TEXT_ANISTOPINSIDE,bOn) {}
	SdrTextAniStopInsideItem(SvStream& rIn) : SdrYesNoItem(SDRATTR_TEXT_ANISTOPINSIDE,rIn) {}
};

}//end of namespace binfilter
#endif
