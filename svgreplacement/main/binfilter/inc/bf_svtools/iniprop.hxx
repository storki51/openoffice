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


#ifndef _SFXINIPROP_HXX
#define _SFXINIPROP_HXX

#include <limits.h>

#ifndef _RTTI_HXX //autogen
#include <tools/rtti.hxx>
#endif
#ifndef _APP_HXX
#include <vcl/svapp.hxx>
#endif

namespace binfilter
{

class SfxIniManager;

//------------------------------------------------------------------------

class SfxAppIniManagerProperty: public ApplicationProperty

//	fuer Application::Property(), um von ueberall an den AppIniManger zu kommen

{
	SfxIniManager*		_pIniManager;

public:
						TYPEINFO();
						SfxAppIniManagerProperty()
						:	_pIniManager(0)
						{}
						~SfxAppIniManagerProperty();

	SfxIniManager*		GetIniManager() const { return _pIniManager; }
	void				SetIniManager( SfxIniManager *pIniManager )
						{ _pIniManager = pIniManager; }
};

}

#endif

