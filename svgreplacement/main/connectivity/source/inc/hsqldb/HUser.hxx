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



#ifndef _CONNECTIVITY_HSQLDB_USER_HXX_
#define _CONNECTIVITY_HSQLDB_USER_HXX_

#include "connectivity/sdbcx/VUser.hxx"
#include "com/sun/star/sdbc/XConnection.hpp"

namespace connectivity
{
	namespace hsqldb
	{
		typedef connectivity::sdbcx::OUser OUser_TYPEDEF;

		class OHSQLUser : public OUser_TYPEDEF
		{
			::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection > m_xConnection;

			::rtl::OUString getPrivilegeString(sal_Int32 nRights) const;
			// return the privileges and additional the grant rights
			void findPrivilegesAndGrantPrivileges(const ::rtl::OUString& objName, sal_Int32 objType,sal_Int32& nRights,sal_Int32& nRightsWithGrant) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
		public:
			virtual void refreshGroups();
		public:
			OHSQLUser(  const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >& _xConnection);
            OHSQLUser(  const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >& _xConnection,const ::rtl::OUString& _Name);

			// XUser
            virtual void SAL_CALL changePassword( const ::rtl::OUString& objPassword, const ::rtl::OUString& newPassword ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
			// XAuthorizable
			virtual sal_Int32 SAL_CALL getPrivileges( const ::rtl::OUString& objName, sal_Int32 objType ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
			virtual sal_Int32 SAL_CALL getGrantablePrivileges( const ::rtl::OUString& objName, sal_Int32 objType ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
			virtual void SAL_CALL grantPrivileges( const ::rtl::OUString& objName, sal_Int32 objType, sal_Int32 objPrivileges ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
			virtual void SAL_CALL revokePrivileges( const ::rtl::OUString& objName, sal_Int32 objType, sal_Int32 objPrivileges ) throw(::com::sun::star::sdbc::SQLException, ::com::sun::star::uno::RuntimeException);
		};

		class OUserExtend;
		typedef ::comphelper::OPropertyArrayUsageHelper<OUserExtend> OUserExtend_PROP;

		class OUserExtend : public OHSQLUser,
							public OUserExtend_PROP
		{
		protected:
			::rtl::OUString	m_Password;
			// OPropertyArrayUsageHelper
			virtual ::cppu::IPropertyArrayHelper* createArrayHelper() const;
			// OPropertySetHelper
			virtual ::cppu::IPropertyArrayHelper & SAL_CALL getInfoHelper();
		public:
			OUserExtend(const ::com::sun::star::uno::Reference< ::com::sun::star::sdbc::XConnection >& _xConnection);

			virtual void construct();
		};
	}
}
#endif // _CONNECTIVITY_HSQLDB_USER_HXX_

