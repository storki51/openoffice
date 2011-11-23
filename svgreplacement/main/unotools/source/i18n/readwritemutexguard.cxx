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
#include "precompiled_unotools.hxx"
#include "unotools/readwritemutexguard.hxx"
#include <tools/debug.hxx>


namespace utl {

ReadWriteGuard::ReadWriteGuard( ReadWriteMutex& rMutexP,
            sal_Int32 nRequestMode )
        : rMutex( rMutexP )
{
    // don't do anything until a pending write completed (or another
    // ReadWriteGuard leaves the ctor phase)
    ::osl::MutexGuard aGuard( rMutex.pWriteMutex );
    nMode = nRequestMode;
    if ( nMode & ReadWriteGuardMode::nWrite )
    {
        rMutex.pWriteMutex->acquire();
        // wait for any read to complete
// TODO: set up a waiting thread instead of a loop
        sal_Bool bWait = sal_True;
        do
        {
            rMutex.pMutex->acquire();
            bWait = (rMutex.nReadCount != 0);
            if ( nMode & ReadWriteGuardMode::nCriticalChange )
                bWait |= (rMutex.nBlockCriticalCount != 0);
            rMutex.pMutex->release();
        } while ( bWait );
    }
    else if ( nMode & ReadWriteGuardMode::nBlockCritical )
    {
        rMutex.pMutex->acquire();
        ++rMutex.nBlockCriticalCount;
        rMutex.pMutex->release();
    }
    else
    {
        rMutex.pMutex->acquire();
        ++rMutex.nReadCount;
        rMutex.pMutex->release();
    }
}


ReadWriteGuard::~ReadWriteGuard()
{
    if ( nMode & ReadWriteGuardMode::nWrite )
        rMutex.pWriteMutex->release();
    else if ( nMode & ReadWriteGuardMode::nBlockCritical )
    {
        rMutex.pMutex->acquire();
        --rMutex.nBlockCriticalCount;
        rMutex.pMutex->release();
    }
    else
    {
        rMutex.pMutex->acquire();
        --rMutex.nReadCount;
        rMutex.pMutex->release();
    }
}


void ReadWriteGuard::changeReadToWrite()
{
    sal_Bool bOk = !(nMode & (ReadWriteGuardMode::nWrite | ReadWriteGuardMode::nBlockCritical));
    DBG_ASSERT( bOk, "ReadWriteGuard::changeReadToWrite: can't" );
    if ( bOk )
    {
        // MUST release read before acquiring write mutex or dead lock would
        // occur if there was a write in another thread waiting for this read
        // to complete.
        rMutex.pMutex->acquire();
        --rMutex.nReadCount;
        rMutex.pMutex->release();

        rMutex.pWriteMutex->acquire();
        nMode |= ReadWriteGuardMode::nWrite;
        // wait for any other read to complete
// TODO: set up a waiting thread instead of a loop
        sal_Bool bWait = sal_True;
        do
        {
            rMutex.pMutex->acquire();
            bWait = (rMutex.nReadCount != 0);
            rMutex.pMutex->release();
        } while ( bWait );
    }
}

}   // namespace utl
