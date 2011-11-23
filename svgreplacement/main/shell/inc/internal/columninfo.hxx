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


 
#ifndef COLUMNINFO_HXX_INCLUDED
#define COLUMNINFO_HXX_INCLUDED

#if defined _MSC_VER
#pragma warning(push, 1)
#pragma warning(disable:4917)
#endif
#include <shlobj.h>
#if defined _MSC_VER
#pragma warning(pop)
#endif 


class CColumnInfo : public IColumnProvider  
{
public:
	CColumnInfo(long RefCnt = 1);
	virtual ~CColumnInfo();

	//-----------------------------
	// IUnknown methods
	//-----------------------------

	virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
            REFIID riid,
            void __RPC_FAR *__RPC_FAR *ppvObject);
        
    virtual ULONG STDMETHODCALLTYPE AddRef( void);
        
    virtual ULONG STDMETHODCALLTYPE Release( void);

	//-----------------------------
	// IColumnProvider
	//-----------------------------

    virtual HRESULT STDMETHODCALLTYPE Initialize(LPCSHCOLUMNINIT psci);

    virtual HRESULT STDMETHODCALLTYPE GetColumnInfo(DWORD dwIndex, SHCOLUMNINFO *psci);

    virtual HRESULT STDMETHODCALLTYPE GetItemData(
		LPCSHCOLUMNID pscid, LPCSHCOLUMNDATA pscd, VARIANT *pvarData);

private:
	bool IsOOFileExtension(wchar_t* Extension) const;

private:
	long	m_RefCnt;	
};

#endif 
