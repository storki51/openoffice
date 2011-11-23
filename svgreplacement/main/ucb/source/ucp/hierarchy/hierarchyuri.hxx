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



#ifndef _HIERARCHYURI_HXX
#define _HIERARCHYURI_HXX

#include <rtl/ustring.hxx>

namespace hierarchy_ucp {

//=========================================================================

#define HIERARCHY_URL_SCHEME          "vnd.sun.star.hier"
#define HIERARCHY_URL_SCHEME_LENGTH   17

//=========================================================================

class HierarchyUri
{
	mutable ::rtl::OUString m_aUri;
	mutable ::rtl::OUString m_aParentUri;
    mutable ::rtl::OUString m_aService;
	mutable ::rtl::OUString m_aPath;
	mutable ::rtl::OUString m_aName;
    mutable bool            m_bValid;

private:
	void init() const;

public:
    HierarchyUri() : m_bValid( false ) {}
    HierarchyUri( const ::rtl::OUString & rUri )
    : m_aUri( rUri ), m_bValid( false ) {}

    sal_Bool isValid() const
    { init(); return m_bValid; }

	const ::rtl::OUString & getUri() const
	{ init(); return m_aUri; }

    void setUri( const ::rtl::OUString & rUri )
    { m_aPath = ::rtl::OUString(); m_aUri = rUri; m_bValid = false; }

	const ::rtl::OUString & getParentUri() const
	{ init(); return m_aParentUri; }

    const ::rtl::OUString & getService() const
    { init(); return m_aService; }

	const ::rtl::OUString & getPath() const
	{ init(); return m_aPath; }

	const ::rtl::OUString & getName() const
	{ init(); return m_aName; }

    inline sal_Bool isRootFolder() const;
};

inline sal_Bool HierarchyUri::isRootFolder() const
{
    init();
    return ( ( m_aPath.getLength() == 1 ) &&
             ( m_aPath.getStr()[ 0 ] == sal_Unicode( '/' ) ) );
}
}

#endif
