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




#include <com/sun/star/uno/XComponentContext.hpp>

#include <rtl/ref.hxx>
#include <rtl/ustring.hxx>
#include <osl/conditn.hxx>
#include <osl/file.h>

struct DownloadInteractionHandler : public rtl::IReference
{
    virtual bool checkDownloadDestination(const rtl::OUString& rFileName) = 0;

    // called if the destination file already exists, but resume is false
    virtual bool downloadTargetExists(const rtl::OUString& rFileName) = 0;
    
    // called when curl reports an error
    virtual void downloadStalled(const rtl::OUString& rErrorMessage) = 0;
    
    // progress handler
    virtual void downloadProgressAt(sal_Int8 nPercent) = 0;
    
    // called on first progress notification
    virtual void downloadStarted(const rtl::OUString& rFileName, sal_Int64 nFileSize) = 0;

    // called when download has been finished
    virtual void downloadFinished(const rtl::OUString& rFileName) = 0;
};


class Download
{
public:
    Download(const com::sun::star::uno::Reference< com::sun::star::uno::XComponentContext >& xContext,
             const rtl::Reference< DownloadInteractionHandler >& rHandler) : m_xContext(xContext), m_aHandler(rHandler) {};

    // returns true when the content of rURL was successfully written to rLocalFile
    bool start(const rtl::OUString& rURL, const rtl::OUString& rFile, const rtl::OUString& rDestinationDir);
    
    // stops the download after the next write operation
    void stop();
    
    // returns true if the stop condition is set
    bool isStopped() const
        { return sal_True == const_cast <Download *> (this)->m_aCondition.check(); };
    
protected:

    // Determines the appropriate proxy settings for the given URL. Returns true if a proxy should be used
    void getProxyForURL(const rtl::OUString& rURL, rtl::OString& rHost, sal_Int32& rPort) const;
        
private:
    osl::Condition m_aCondition;
    const com::sun::star::uno::Reference< com::sun::star::uno::XComponentContext >& m_xContext;
    const rtl::Reference< DownloadInteractionHandler > m_aHandler;
};


