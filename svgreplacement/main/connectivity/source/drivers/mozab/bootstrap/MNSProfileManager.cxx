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



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_connectivity.hxx"

#include "MNSProfileManager.hxx"
#include "MNSProfile.hxx"

#ifndef MAXPATHLEN
#define MAXPATHLEN 1024
#endif
#include <MNSFolders.hxx>
#include <MNSINIParser.hxx>

static ::sal_Int32 nInitCounter=0;
namespace connectivity
{
	namespace mozab
	{

		ProfileManager::~ProfileManager()
		{
		}
		ProfileManager::ProfileManager()
			:m_CurrentProduct(MozillaProductType_Mozilla)
			,aProfile(NULL)
		{
		}
			::sal_Int32 ProfileManager::bootupProfile( ::com::sun::star::mozilla::MozillaProductType product, const ::rtl::OUString& profileName ) throw (::com::sun::star::uno::RuntimeException)
			{
				if (!aProfile)
				{
					aProfile=new nsProfile();
					aProfile->StartupWithArgs(NULL,sal_False);
				}

				setCurrentProfile(product,profileName);
				return ++nInitCounter;
			}
			::sal_Int32 ProfileManager::shutdownProfile(  ) throw (::com::sun::star::uno::RuntimeException)
			{
				return --nInitCounter;
			}
			::com::sun::star::mozilla::MozillaProductType ProfileManager::getCurrentProduct(  ) throw (::com::sun::star::uno::RuntimeException)
			{
				return m_CurrentProduct;
			}
			::rtl::OUString ProfileManager::getCurrentProfile(  ) throw (::com::sun::star::uno::RuntimeException)
			{
				nsresult rv;
				nsCOMPtr<nsIProfile> theProfile(do_GetService(NS_PROFILE_CONTRACTID,&rv));
				     if (NS_FAILED(rv)) return ::rtl::OUString();
				nsXPIDLString currentProfileStr;
				//call GetCurrentProfile before call SetCurrentProfile will get the default profile
				rv = theProfile->GetCurrentProfile(getter_Copies(currentProfileStr));
			    if (NS_FAILED(rv) || currentProfileStr.get() == nsnull)
					return ::rtl::OUString();
				// PRUnichar != sal_Unicode in mingw
				return ::rtl::OUString(reinterpret_cast_mingw_only<const sal_Unicode *>(currentProfileStr.get()));
			}
			::rtl::OUString ProfileManager::setCurrentProfile( ::com::sun::star::mozilla::MozillaProductType product, const ::rtl::OUString& profileName ) throw (::com::sun::star::uno::RuntimeException)
			{
				::rtl::OUString currentProfile = getCurrentProfile();
				//if profileName not given, then skip and return curernt profile
				if (!profileName.getLength() && m_CurrentProduct == product)
					return currentProfile;

				if (m_CurrentProduct == product && profileName.equals(currentProfile))
					return currentProfile;
				//set current product
				m_CurrentProduct = product;

				//get profile mozilla profile service
				nsresult rv;
				nsCOMPtr<nsIProfile> theProfile(do_GetService(NS_PROFILE_CONTRACTID,&rv));
                if (NS_FAILED(rv)) return ::rtl::OUString();

				// PRUnichar != sal_Unicode in mingw
				const PRUnichar* pUsedProfile = reinterpret_cast_mingw_only<const PRUnichar *>(profileName.getStr());
				//set current profile
				rv = theProfile->SetCurrentProfile( pUsedProfile );
				if (NS_FAILED(rv)) return ::rtl::OUString();
				return currentProfile;
			}


	}
}
