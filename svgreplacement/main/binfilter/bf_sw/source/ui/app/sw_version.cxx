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




#ifdef _MSC_VER
#pragma hdrstop
#endif

#define _VERSION_CXX

#ifndef _STRING_HXX //autogen
#include <tools/string.hxx>
#endif
#ifndef _TOOLS_RESID_HXX //autogen
#include <tools/resid.hxx>
#endif
#ifndef _SFX_HRC
#include <bf_sfx2/sfx.hrc>
#endif

#include "swtypes.hxx"
namespace binfilter {


/*N*/ String GetSWGVersion()
/*N*/ {
/*N*/ 	String aStr( '(' );
/*N*/ 	aStr += SW_RESSTR( RID_BUILDVERSION );
/*N*/ 	aStr += ']';
/*N*/ 
/*N*/ 	return aStr;
/*N*/ }

}
