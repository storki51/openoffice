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

// ZipException.h: interface for the ZipException class.
//
//////////////////////////////////////////////////////////////////////

#ifndef ZIPEXCPTN_HXX_INCLUDED
#define ZIPEXCPTN_HXX_INCLUDED

#include <stdexcept>

//------------------------------------------
/**
*/
class RuntimeException : public std::exception
{
public:
	RuntimeException(int Error);
	virtual ~RuntimeException() throw();

	int GetErrorCode() const;

private:
	int m_Error;
};

//------------------------------------------
/**
*/
class ZipException : public RuntimeException
{
public:
	ZipException(int Error);

	virtual const char* what() const throw();
};

//------------------------------------------
/**
*/
class Win32Exception : public RuntimeException
{
public:
	Win32Exception(int Error);
	virtual ~Win32Exception() throw();

	virtual const char* what() const throw();

private:
	void* m_MsgBuff;
};

//------------------------------------------
/**
*/
class ZipContentMissException : public ZipException
{
public:
	ZipContentMissException(int Error);
};

//------------------------------------------
/**
*/
class AccessViolationException : public Win32Exception
{
public:
	AccessViolationException(int Error);
};

//------------------------------------------
/**
*/
class IOException : public Win32Exception
{
public:
	IOException(int Error);
};

#endif 
