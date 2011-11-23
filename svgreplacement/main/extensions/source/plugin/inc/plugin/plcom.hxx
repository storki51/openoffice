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


#ifndef __PLUGIN_INC_PLCOM_HXX
#define __PLUGIN_INC_PLCOM_HXX

#include <tools/string.hxx>
#include <list>

class XPlugin_Impl;

class PluginComm
{
protected:
	int							m_nRefCount;
	::rtl::OString				m_aLibName;
	std::list< String >			m_aFilesToDelete;
public:
	PluginComm( const ::rtl::OString& rLibName, bool bReusable = true );
	virtual ~PluginComm();

	int getRefCount() { return m_nRefCount; }
	void addRef() { m_nRefCount++; }
	void decRef() { m_nRefCount--; if( ! m_nRefCount ) delete this; }

	const ::rtl::OString& getLibName() { return m_aLibName; }
	void setLibName( const ::rtl::OString& rName ) { m_aLibName = rName; }

	void addFileToDelete( const String& filename )
		{ m_aFilesToDelete.push_back( filename ); }

	virtual NPError NPP_Destroy( NPP instance, NPSavedData** save ) = 0;
	virtual NPError NPP_DestroyStream( NPP instance, NPStream* stream,
							   NPError reason ) = 0;
	virtual void* NPP_GetJavaClass() = 0;
	virtual NPError NPP_Initialize() = 0;
	virtual NPError NPP_New( NPMIMEType pluginType, NPP instance,
							 uint16 mode, int16 argc,
							 char* argn[], char* argv[],
							 NPSavedData *saved ) = 0;
	virtual NPError NPP_NewStream( NPP instance, NPMIMEType type,
								   NPStream* stream,
								   NPBool seekable, uint16* stype ) = 0;
	virtual void NPP_Print( NPP instance, NPPrint* platformPrint ) = 0;
	virtual NPError NPP_SetWindow( NPP instance, NPWindow* window ) = 0;
	virtual void NPP_Shutdown() = 0;
	virtual void NPP_StreamAsFile( NPP instance, NPStream* stream,
								   const char* fname ) = 0;
	virtual void NPP_URLNotify( NPP instance, const char* url,
								NPReason reason, void* notifyData ) = 0;
	virtual int32 NPP_Write( NPP instance, NPStream* stream, int32 offset,
							 int32 len, void* buffer ) = 0;
	virtual int32 NPP_WriteReady( NPP instance, NPStream* stream ) = 0;
	virtual NPError NPP_GetValue( NPP instance, NPPVariable  variable, void* value ) = 0;
	virtual NPError NPP_SetValue( NPP instance, NPNVariable variable,
								 void *value) = 0;
    
    virtual NPError NPP_SetWindow( XPlugin_Impl* );
    virtual NPError NPP_Destroy( XPlugin_Impl*, NPSavedData** save );
};

#endif
