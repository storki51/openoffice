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
#include "precompiled_extensions.hxx"
#include <cstdarg>

#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <osl/file.hxx>
#include <osl/thread.h>
#include <rtl/bootstrap.hxx>

#include <plugin/impl.hxx>

int UnxPluginComm::nConnCounter = 0;

UnxPluginComm::UnxPluginComm(
                             const String& /*mimetype*/,
                             const String& library,
                             XLIB_Window aParent,
                             int nDescriptor1,
                             int nDescriptor2
                             ) :
        PluginComm( ::rtl::OUStringToOString( library, osl_getThreadTextEncoding() ), false ),
        PluginConnector( nDescriptor2 )
{
    char pDesc[32];
	char pWindow[32];
	sprintf( pWindow, "%d", (int)aParent );
    sprintf( pDesc, "%d", nDescriptor1 );
	ByteString aLib( library, osl_getThreadTextEncoding() );
    rtl::OString path;
    if (!getPluginappPath(&path)) {
        fprintf( stderr, "cannot construct path to pluginapp.bin\n" );
        m_nCommPID = -1;
        return;
    }

	char const* pArgs[5];
	pArgs[0] = path.getStr();
	pArgs[1] = pDesc;
	pArgs[2] = aLib.GetBuffer();
	pArgs[3] = pWindow;
	pArgs[4] = NULL;

#if OSL_DEBUG_LEVEL > 1
	m_nCommPID = 10;
	fprintf( stderr, "Try to launch: %s %s %s %s, descriptors are %d, %d\n", pArgs[0], pArgs[1], pArgs[2], pArgs[3], nDescriptor1, nDescriptor2 );
#endif

	if( ! ( m_nCommPID = fork() ) )
  	{
 		execvp( pArgs[0], const_cast< char ** >(pArgs) );
  		fprintf( stderr, "Error: could not exec %s\n", pArgs[0] );
  		_exit(255);
  	}

	if( m_nCommPID != -1 )
	{
		// wait for pluginapp.bin to start up
		if( ! WaitForMessage( 5000 ) )
		{
			fprintf( stderr, "Timeout on command: %s %s %s %s\n", pArgs[0], pArgs[1], pArgs[2], pArgs[3] );
			invalidate();
		}
		else
		{
			MediatorMessage* pMessage = GetNextMessage( sal_True );
			Respond( pMessage->m_nID,
					 const_cast<char*>("init ack"),8,
					 NULL );
			delete pMessage;
			NPP_Initialize();
		}
	}
}

UnxPluginComm::~UnxPluginComm()
{
	NPP_Shutdown();
	if( m_nCommPID != -1 && m_nCommPID != 0 )
    {
        int status = 16777216;
        pid_t nExit = waitpid( m_nCommPID, &status, WUNTRACED );
#if OSL_DEBUG_LEVEL > 1
        fprintf( stderr, "child %d (plugin app child %d) exited with status %d\n", (int)nExit, (int)m_nCommPID, (int)WEXITSTATUS(status) );
#else
        (void)nExit;
#endif
    }
}

bool UnxPluginComm::getPluginappPath(rtl::OString * path) {
    OSL_ASSERT(path != NULL);
    rtl::OUString p(
        RTL_CONSTASCII_USTRINGPARAM("$OOO_BASE_DIR/program/pluginapp.bin"));
    rtl::Bootstrap::expandMacros(p);
    return
        (osl::FileBase::getSystemPathFromFileURL(p, p) ==
         osl::FileBase::E_None) &&
        p.convertToString(
            path, osl_getThreadTextEncoding(),
            (RTL_UNICODETOTEXT_FLAGS_UNDEFINED_ERROR |
             RTL_UNICODETOTEXT_FLAGS_INVALID_ERROR));
}
