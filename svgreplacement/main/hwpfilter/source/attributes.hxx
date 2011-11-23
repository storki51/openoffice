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




#ifndef _CONFIGMGR_MISC_ATTRIBUTES_HXX_
#define _CONFIGMGR_MISC_ATTRIBUTES_HXX_

#include <com/sun/star/xml/sax/XAttributeList.hpp>
#include <cppuhelper/implbase1.hxx>

/*----------------------------------------
*
* 	Attributlist implementation
*
*----------------------------------------*/

using namespace ::cppu;
using namespace ::rtl;
using namespace ::com::sun::star::xml::sax;
using namespace ::com::sun::star::uno;

struct AttributeListImpl_impl;
class AttributeListImpl : public WeakImplHelper1< XAttributeList >
{
protected:
	~AttributeListImpl();

public:
	AttributeListImpl();
	AttributeListImpl( const AttributeListImpl & );
	
public:
    virtual sal_Int16 SAL_CALL getLength(void) throw (RuntimeException);
    virtual OUString  SAL_CALL getNameByIndex(sal_Int16 i) throw (RuntimeException);
    virtual OUString  SAL_CALL getTypeByIndex(sal_Int16 i) throw (RuntimeException);
    virtual OUString  SAL_CALL getTypeByName(const OUString& aName) throw (RuntimeException);
    virtual OUString  SAL_CALL getValueByIndex(sal_Int16 i) throw (RuntimeException);
    virtual OUString  SAL_CALL getValueByName(const OUString& aName) throw (RuntimeException);

public:
	void addAttribute( const OUString &sName , const OUString &sType , const OUString &sValue );
	void clear();

private:
	struct AttributeListImpl_impl *m_pImpl;
};

#endif // _CONFIGMGR_MISC_ATTRIBUTES_HXX_


