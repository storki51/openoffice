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



#ifndef _FTP_FTPCONTENTPROVIDER_HXX_
#define _FTP_FTPCONTENTPROVIDER_HXX_

#include <vector>
#include <osl/mutex.hxx>
#include <ucbhelper/macros.hxx>
#include <ucbhelper/proxydecider.hxx>
#include <ucbhelper/providerhelper.hxx>
#include <com/sun/star/ucb/XContentProviderManager.hpp>
#include "ftphandleprovider.hxx"
#include "ftpurl.hxx"

// UNO service name for the provider. This name will be used by the UCB to
// create instances of the provider.

#define FTP_CONTENT_PROVIDER_SERVICE_NAME "com.sun.star.ucb.FTPContentProvider"
#define FTP_CONTENT_TYPE "application/ftp-content"


/**
 *  Definition of ftpcontentprovider
 */



namespace ftp {
	

	class FTPLoaderThread;
	
	
	class FTPContentProvider:
		public ::ucbhelper::ContentProviderImplHelper,
		public FTPHandleProvider
	{
	public:
		
		FTPContentProvider(
            const com::sun::star::uno::Reference<
            com::sun::star::lang::XMultiServiceFactory>& xMSF );

		~FTPContentProvider();

		// XInterface
		XINTERFACE_DECL()
			
		// XTypeProvider
		XTYPEPROVIDER_DECL()

		// XServiceInfo
		XSERVICEINFO_DECL()

		// XContentProvider
		virtual com::sun::star::uno::Reference< com::sun::star::ucb::XContent > SAL_CALL
		queryContent(
			const com::sun::star::uno::Reference< com::sun::star::ucb::XContentIdentifier >& Identifier )
			throw( com::sun::star::ucb::IllegalIdentifierException,
				   com::sun::star::uno::RuntimeException );
		
		// FTPHandleProvider.
		
		virtual CURL* handle();
        
        virtual bool forHost(const rtl::OUString& host,
                             const rtl::OUString& port,
                             const rtl::OUString& username,
                             rtl::OUString& password,
                             rtl::OUString& account);
        
        virtual bool setHost(const rtl::OUString& host,
                             const rtl::OUString& port,
                             const rtl::OUString& username,
                             const rtl::OUString& password,
                             const rtl::OUString& account);
        
        
        struct ServerInfo {
            rtl::OUString host;
            rtl::OUString port;
            rtl::OUString username;
            rtl::OUString password;
            rtl::OUString account;
        };

	private:
		
		osl::Mutex m_aMutex;
		FTPLoaderThread *m_ftpLoaderThread;
		ucbhelper::InternetProxyDecider *m_pProxyDecider;
		std::vector<ServerInfo> m_ServerInfo;
		
		void init();
		
		com::sun::star::uno::Reference<com::sun::star::ucb::XContentProvider>
		getHttpProvider()
			throw(com::sun::star::uno::RuntimeException);		
		
	};  // end class FTPContentProvider
	
}       // end namespace ftp

#endif

