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



#include <stdio.h>

#include "rtl/ustring.hxx"
#include "rtl/ustrbuf.hxx"
#include "rtl/process.h"

#include "com/sun/star/uno/RuntimeException.hpp"

using namespace ::rtl;
using namespace ::com::sun::star::uno;

namespace unodevtools {

//-------------------------------------------------------------------------------
#if OSL_DEBUG_LEVEL > 1
static void out( const sal_Char * pText )
{
    fprintf( stderr, pText );
}
#endif

//-------------------------------------------------------------------------------
sal_Bool readOption( OUString * pValue, const sal_Char * pOpt,
                     sal_Int32 * pnIndex, const OUString & aArg)
	throw (RuntimeException)
{
	const OUString dash = OUString(RTL_CONSTASCII_USTRINGPARAM("-"));
	if(aArg.indexOf(dash) != 0)
		return sal_False;

	OUString aOpt = OUString::createFromAscii( pOpt );

	if (aArg.getLength() < aOpt.getLength())
		return sal_False;

	if (aOpt.equalsIgnoreAsciiCase( aArg.copy(1) )) {
		// take next argument
		++(*pnIndex);

		rtl_getAppCommandArg(*pnIndex, &pValue->pData);
		if (*pnIndex >= (sal_Int32)rtl_getAppCommandArgCount() ||
            pValue->copy(1).equals(dash))
		{
			OUStringBuffer buf( 32 );
			buf.appendAscii( RTL_CONSTASCII_STRINGPARAM("incomplete option \"-") );
			buf.appendAscii( pOpt );
			buf.appendAscii( RTL_CONSTASCII_STRINGPARAM("\" given!") );
			throw RuntimeException( buf.makeStringAndClear(), Reference< XInterface >() );
		} else {
#if OSL_DEBUG_LEVEL > 1
			out( "\n> identified option -" );
			out( pOpt );
			out( " = " );
			OString tmp = OUStringToOString(*pValue, RTL_TEXTENCODING_ASCII_US);
  			out( tmp.getStr() );
#endif
			++(*pnIndex);
			return sal_True;
		}
	} else if (aArg.indexOf(aOpt) == 1) {
		*pValue = aArg.copy(1 + aOpt.getLength());
#if OSL_DEBUG_LEVEL > 1
		out( "\n> identified option -" );
		out( pOpt );
		out( " = " );
		OString tmp = OUStringToOString(*pValue, RTL_TEXTENCODING_ASCII_US);
		out( tmp.getStr() );
#endif
		++(*pnIndex);

		return sal_True;
	}
	return sal_False;
}

//-------------------------------------------------------------------------------
sal_Bool readOption( sal_Bool * pbOpt, const sal_Char * pOpt,
                     sal_Int32 * pnIndex, const OUString & aArg)
{
	const OUString dashdash(RTL_CONSTASCII_USTRINGPARAM("--"));
	const OUString dash(RTL_CONSTASCII_USTRINGPARAM("-"));
	OUString aOpt = OUString::createFromAscii(pOpt);

	if((aArg.indexOf(dash) == 0 && aOpt.equalsIgnoreAsciiCase(aArg.copy(1))) ||
       (aArg.indexOf(dashdash) == 0 && aOpt.equalsIgnoreAsciiCase(aArg.copy(2))) )
	{
		++(*pnIndex);
		*pbOpt = sal_True;
#if OSL_DEBUG_LEVEL > 1
		out( "\n> identified option --" );
		out( pOpt );
#endif
		return sal_True;
	}
	return sal_False;
}

} // end of namespace unodevtools
