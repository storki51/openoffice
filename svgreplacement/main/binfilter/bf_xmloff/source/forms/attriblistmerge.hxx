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



#ifndef _XMLOFF_FORMS_ATTRIBLISTMERGE_HXX_
#define _XMLOFF_FORMS_ATTRIBLISTMERGE_HXX_

#ifndef _COMPHELPER_STLTYPES_HXX_
#include <comphelper/stl_types.hxx>
#endif
#ifndef _CPPUHELPER_IMPLBASE1_HXX_
#include <cppuhelper/implbase1.hxx>
#endif
#ifndef _COM_SUN_STAR_XML_SAX_XATTRIBUTELIST_HPP_
#include <com/sun/star/xml/sax/XAttributeList.hpp>
#endif
namespace binfilter {

//.........................................................................
namespace xmloff
{
//.........................................................................

	//=====================================================================
	//= OAttribListMerger
	//=====================================================================
	typedef ::cppu::WeakImplHelper1	<	::com::sun::star::xml::sax::XAttributeList
									>	OAttribListMerger_Base;
	/** implements the XAttributeList list by merging different source attribute lists

		<p>Currently, the time behavious is O(n), though it would be possible to change it to O(log n).</p>
	*/
	class OAttribListMerger : public OAttribListMerger_Base
	{
	protected:
		::osl::Mutex		m_aMutex;
		DECLARE_STL_VECTOR( ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >, AttributeListArray );
		AttributeListArray	m_aLists;

		~OAttribListMerger() { }

	public:
		OAttribListMerger() { }

		// attribute list handling
		// (very thinn at the moment ... only adding lists is allowed ... add more if you need it :)
		void addList(const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& _rList);

		// XAttributeList
		virtual sal_Int16 SAL_CALL getLength(  ) throw(::com::sun::star::uno::RuntimeException);
		virtual ::rtl::OUString SAL_CALL getNameByIndex( sal_Int16 i ) throw(::com::sun::star::uno::RuntimeException);
		virtual ::rtl::OUString SAL_CALL getTypeByIndex( sal_Int16 i ) throw(::com::sun::star::uno::RuntimeException);
		virtual ::rtl::OUString SAL_CALL getTypeByName( const ::rtl::OUString& aName ) throw(::com::sun::star::uno::RuntimeException);
		virtual ::rtl::OUString SAL_CALL getValueByIndex( sal_Int16 i ) throw(::com::sun::star::uno::RuntimeException);
		virtual ::rtl::OUString SAL_CALL getValueByName( const ::rtl::OUString& aName ) throw(::com::sun::star::uno::RuntimeException);

	protected:
		sal_Bool seekToIndex(sal_Int16 _nGlobalIndex, ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& _rSubList, sal_Int16& _rLocalIndex);
		sal_Bool seekToName(const ::rtl::OUString& _rName, ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList >& _rSubList, sal_Int16& _rLocalIndex);
	};


//.........................................................................
}	// namespace xmloff
//.........................................................................

}//end of namespace binfilter
#endif // _XMLOFF_FORMS_ATTRIBLISTMERGE_HXX_

