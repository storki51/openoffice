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
#include "precompiled_ucb.hxx"
#include "filtask.hxx"
#include "filglob.hxx"

/******************************************************************************/
/*                                                                            */
/*                              TaskHandling                                  */
/*                                                                            */
/******************************************************************************/


using namespace fileaccess;
using namespace com::sun::star;
using namespace com::sun::star::uno;
using namespace com::sun::star::ucb;



TaskManager::TaskManager()
    : m_nCommandId( 0 )
{
}



TaskManager::~TaskManager()
{
}



void SAL_CALL
TaskManager::startTask(
    sal_Int32 CommandId,
    const uno::Reference< XCommandEnvironment >& xCommandEnv )
    throw( DuplicateCommandIdentifierException )
{
    osl::MutexGuard aGuard( m_aMutex );
    TaskMap::iterator it = m_aTaskMap.find( CommandId );
    if( it != m_aTaskMap.end() )
    {
        throw DuplicateCommandIdentifierException(
            ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM( OSL_LOG_PREFIX ) ),
            uno::Reference< uno::XInterface >() );
    }
    m_aTaskMap[ CommandId ] = TaskHandling( xCommandEnv );
}



void SAL_CALL
TaskManager::endTask( sal_Int32 CommandId,
                      const rtl::OUString& aUncPath,
                      BaseContent* pContent)
{
    osl::MutexGuard aGuard( m_aMutex );
    TaskMap::iterator it = m_aTaskMap.find( CommandId );
    if( it == m_aTaskMap.end() )
        return;

    sal_Int32 ErrorCode = it->second.getInstalledError();
    sal_Int32 MinorCode = it->second.getMinorErrorCode();
    bool isHandled = it->second.isHandled();

    Reference< XCommandEnvironment > xComEnv
        = it->second.getCommandEnvironment();

    m_aTaskMap.erase( it );

    if( ErrorCode != TASKHANDLER_NO_ERROR )
        throw_handler(
            ErrorCode,
            MinorCode,
            xComEnv,
            aUncPath,
            pContent,
            isHandled);
}



void SAL_CALL
TaskManager::abort( sal_Int32 CommandId )
{
    if( CommandId )
    {
        osl::MutexGuard aGuard( m_aMutex );
        TaskMap::iterator it = m_aTaskMap.find( CommandId );
        if( it == m_aTaskMap.end() )
            return;
        else
            it->second.abort();
    }
}


void SAL_CALL TaskManager::clearError( sal_Int32 CommandId )
{
    osl::MutexGuard aGuard( m_aMutex );
    TaskMap::iterator it = m_aTaskMap.find( CommandId );
    if( it != m_aTaskMap.end() )
        it->second.clearError();
}


void SAL_CALL TaskManager::retrieveError( sal_Int32 CommandId,
                                          sal_Int32 &ErrorCode,
                                          sal_Int32 &minorCode)
{
    osl::MutexGuard aGuard( m_aMutex );
    TaskMap::iterator it = m_aTaskMap.find( CommandId );
    if( it != m_aTaskMap.end() )
    {
        ErrorCode = it->second.getInstalledError();
        minorCode = it->second. getMinorErrorCode();
    }
}



void SAL_CALL TaskManager::installError( sal_Int32 CommandId,
                                         sal_Int32 ErrorCode,
                                         sal_Int32 MinorCode )
{
    osl::MutexGuard aGuard( m_aMutex );
    TaskMap::iterator it = m_aTaskMap.find( CommandId );
    if( it != m_aTaskMap.end() )
        it->second.installError( ErrorCode,MinorCode );
}



sal_Int32 SAL_CALL
TaskManager::getCommandId( void )
{
    osl::MutexGuard aGuard( m_aMutex );
    return ++m_nCommandId;
}



void SAL_CALL TaskManager::handleTask(
    sal_Int32 CommandId,
    const uno::Reference< task::XInteractionRequest >& request )
{
    osl::MutexGuard aGuard( m_aMutex );
    TaskMap::iterator it = m_aTaskMap.find( CommandId );
    uno::Reference< task::XInteractionHandler > xInt;
    if( it != m_aTaskMap.end() )
    {
        xInt = it->second.getInteractionHandler();
        if( xInt.is() )
            xInt->handle( request );
        it->second.setHandled();
    }
}
