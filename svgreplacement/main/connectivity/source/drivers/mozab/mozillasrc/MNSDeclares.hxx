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



#ifndef _CONNECTIVITY_MAB_NS_DECLARES_HXX_
#define _CONNECTIVITY_MAB_NS_DECLARES_HXX_ 

#include <sal/types.h>


const	sal_Int32 RowStates_Normal = 0;
const	sal_Int32 RowStates_Inserted = 1;
const	sal_Int32 RowStates_Updated = 2;
const	sal_Int32 RowStates_Deleted  = 4;
const	sal_Int32 RowStates_Error  = 32;

namespace connectivity{
	namespace mozab{
        class OConnection;
	}
}
sal_Bool isProfileLocked(connectivity::mozab::OConnection* _pCon);

class nsIAbDirectory;
sal_Int32 getDirectoryType(const nsIAbDirectory*  directory);


#endif // _CONNECTIVITY_MAB_NS_DECLARES_HXX_ 1

