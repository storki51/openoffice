/*************************************************************************
 *
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 * 
 * Copyright 2000, 2010 Oracle and/or its affiliates.
 *
 * OpenOffice.org - a multi-platform office productivity suite
 *
 * This file is part of OpenOffice.org.
 *
 * OpenOffice.org is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License version 3
 * only, as published by the Free Software Foundation.
 *
 * OpenOffice.org is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3 for more details
 * (a copy is included in the LICENSE file that accompanied this code).
 *
 * You should have received a copy of the GNU Lesser General Public License
 * version 3 along with OpenOffice.org.  If not, see
 * <http://www.openoffice.org/license.html>
 * for a copy of the LGPLv3 License.
 *
 ************************************************************************/
#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#pragma warning(disable:4738) // storing 32-bit float result in memory, possible loss of performance
#endif

#include <rtl/memory.h>
#include <osl/diagnose.h>
#include <osl/interlck.h>
#include <rtl/alloc.h>
#include <osl/mutex.h>
#include <osl/doublecheckedlocking.h>
#include <rtl/tencinfo.h>

#include <string.h>
#include <sal/alloca.h>

#include "hash.h"
#include "strimp.h"
#include "surrogates.h"
#include <rtl/ustring.h>

#include "rtl/math.h"
#include "rtl/tencinfo.h"

/* ======================================================================= */

/* static data to be referenced by all empty strings
 * the refCount is predefined to 1 and must never become 0 !
 */
static rtl_uString const aImplEmpty_rtl_uString =
{
    (sal_Int32) (SAL_STRING_INTERN_FLAG|SAL_STRING_STATIC_FLAG|1), /*sal_Int32    refCount; */
    0,                                               /*sal_Int32    length;   */
    { 0 }                                            /*sal_Unicode  buffer[1];*/
};

/* ======================================================================= */

#define IMPL_RTL_STRCODE            sal_Unicode
#define IMPL_RTL_USTRCODE( c )      (c)
#define IMPL_RTL_STRNAME( n )       rtl_ustr_ ## n

#define IMPL_RTL_STRINGNAME( n )    rtl_uString_ ## n
#define IMPL_RTL_STRINGDATA         rtl_uString
#define IMPL_RTL_EMPTYSTRING        aImplEmpty_rtl_uString
#define IMPL_RTL_INTERN
static void internRelease (rtl_uString *pThis);

/* ======================================================================= */

/* Include String/UString template code */

#include "strtmpl.c"

sal_Int32 rtl_ustr_indexOfAscii_WithLength(
    sal_Unicode const * str, sal_Int32 len,
    char const * subStr, sal_Int32 subLen)
{
    if (subLen > 0 && subLen <= len) {
        sal_Int32 i;
        for (i = 0; i <= len - subLen; ++i) {
            if (rtl_ustr_asciil_reverseEquals_WithLength(
                    str + i, subStr, subLen))
            {
                return i;
            }
        }
    }
    return -1;
}

sal_Int32 rtl_ustr_lastIndexOfAscii_WithLength(
    sal_Unicode const * str, sal_Int32 len,
    char const * subStr, sal_Int32 subLen)
{
    if (subLen > 0 && subLen <= len) {
        sal_Int32 i;
        for (i = len - subLen; i >= 0; --i) {
            if (rtl_ustr_asciil_reverseEquals_WithLength(
                    str + i, subStr, subLen))
            {
                return i;
            }
        }
    }
    return -1;
}

sal_Int32 SAL_CALL rtl_ustr_valueOfFloat(sal_Unicode * pStr, float f)
{
    rtl_uString * pResult = NULL;
    sal_Int32 nLen;
    rtl_math_doubleToUString(
        &pResult, 0, 0, f, rtl_math_StringFormat_G,
        RTL_USTR_MAX_VALUEOFFLOAT - RTL_CONSTASCII_LENGTH("-x.E-xxx"), '.', 0,
        0, sal_True);
    nLen = pResult->length;
    OSL_ASSERT(nLen < RTL_USTR_MAX_VALUEOFFLOAT);
    rtl_copyMemory(pStr, pResult->buffer, (nLen + 1) * sizeof(sal_Unicode));
    rtl_uString_release(pResult);
    return nLen;
}

sal_Int32 SAL_CALL rtl_ustr_valueOfDouble(sal_Unicode * pStr, double d)
{
    rtl_uString * pResult = NULL;
    sal_Int32 nLen;
    rtl_math_doubleToUString(
        &pResult, 0, 0, d, rtl_math_StringFormat_G,
        RTL_USTR_MAX_VALUEOFDOUBLE - RTL_CONSTASCII_LENGTH("-x.E-xxx"), '.', 0,
        0, sal_True);
    nLen = pResult->length;
    OSL_ASSERT(nLen < RTL_USTR_MAX_VALUEOFDOUBLE);
    rtl_copyMemory(pStr, pResult->buffer, (nLen + 1) * sizeof(sal_Unicode));
    rtl_uString_release(pResult);
    return nLen;
}

float SAL_CALL rtl_ustr_toFloat(sal_Unicode const * pStr)
{
    return (float) rtl_math_uStringToDouble(pStr,
                                            pStr + rtl_ustr_getLength(pStr),
                                            '.', 0, 0, 0);
}

double SAL_CALL rtl_ustr_toDouble(sal_Unicode const * pStr)
{
    return rtl_math_uStringToDouble(pStr, pStr + rtl_ustr_getLength(pStr), '.',
                                    0, 0, 0);
}

/* ======================================================================= */

sal_Int32 SAL_CALL rtl_ustr_ascii_compare( const sal_Unicode* pStr1,
                                           const sal_Char* pStr2 )
{
    sal_Int32 nRet;
    while ( ((nRet = ((sal_Int32)(*pStr1))-
                     ((sal_Int32)((unsigned char)(*pStr2)))) == 0) &&
            *pStr2 )
    {
        pStr1++;
        pStr2++;
    }

    return nRet;
}

/* ----------------------------------------------------------------------- */

sal_Int32 SAL_CALL rtl_ustr_ascii_compare_WithLength( const sal_Unicode* pStr1,
                                                      sal_Int32 nStr1Len,
                                                      const sal_Char* pStr2 )
{
	sal_Int32 nRet = 0;
    while( ((nRet = (nStr1Len ? (sal_Int32)(*pStr1) : 0)-
                    ((sal_Int32)((unsigned char)(*pStr2)))) == 0) &&
           nStr1Len && *pStr2 )
    {
        pStr1++;
        pStr2++;
        nStr1Len--;
    }

    return nRet;
}

/* ----------------------------------------------------------------------- */

sal_Int32 SAL_CALL rtl_ustr_ascii_shortenedCompare_WithLength( const sal_Unicode* pStr1,
                                                               sal_Int32 nStr1Len,
                                                               const sal_Char* pStr2,
                                                               sal_Int32 nShortenedLength )
{
    const sal_Unicode*  pStr1End = pStr1 + nStr1Len;
    sal_Int32           nRet;
    while ( (nShortenedLength > 0) &&
            (pStr1 < pStr1End) && *pStr2 )
    {
        /* Check ASCII range */
        OSL_ENSURE( (*pStr2 & 0x80) == 0, "Found ASCII char > 127");

        nRet = ((sal_Int32)*pStr1)-
               ((sal_Int32)(unsigned char)*pStr2);
        if ( nRet != 0 )
            return nRet;

        nShortenedLength--;
        pStr1++;
        pStr2++;
    }

    if ( nShortenedLength <= 0 )
        return 0;

    if ( *pStr2 )
    {
        OSL_ENSURE( pStr1 == pStr1End, "pStr1 == pStr1End failed" );
        // first is a substring of the second string => less (negative value)
        nRet = -1;
    }
    else
    {
        // greater or equal
        nRet = pStr1End - pStr1;
    }

    return nRet;
}

/* ----------------------------------------------------------------------- */

sal_Int32 SAL_CALL rtl_ustr_asciil_reverseCompare_WithLength( const sal_Unicode* pStr1,
                                                              sal_Int32 nStr1Len,
                                                              const sal_Char* pStr2,
                                                              sal_Int32 nStr2Len )
{
    const sal_Unicode*  pStr1Run = pStr1+nStr1Len;
    const sal_Char*     pStr2Run = pStr2+nStr2Len;
    sal_Int32           nRet;
    while ( (pStr1 < pStr1Run) && (pStr2 < pStr2Run) )
    {
        pStr1Run--;
        pStr2Run--;
        nRet = ((sal_Int32)*pStr1Run)-((sal_Int32)*pStr2Run);
        if ( nRet )
            return nRet;
    }

    return nStr1Len - nStr2Len;
}

/* ----------------------------------------------------------------------- */

sal_Bool SAL_CALL rtl_ustr_asciil_reverseEquals_WithLength( const sal_Unicode* pStr1,
                                                              const sal_Char* pStr2,
                                                              sal_Int32 nStrLen )
{
    const sal_Unicode*  pStr1Run = pStr1+nStrLen;
    const sal_Char*     pStr2Run = pStr2+nStrLen;
    while ( pStr1 < pStr1Run )
    {
        pStr1Run--;
        pStr2Run--;
		if( *pStr1Run != (sal_Unicode)*pStr2Run )
			return sal_False;
    }

    return sal_True;
}

/* ----------------------------------------------------------------------- */

sal_Int32 SAL_CALL rtl_ustr_ascii_compareIgnoreAsciiCase( const sal_Unicode* pStr1,
                                                          const sal_Char* pStr2 )
{
    sal_Int32   nRet;
    sal_Int32   c1;
    sal_Int32   c2;
    do
    {
        /* If character between 'A' and 'Z', than convert it to lowercase */
        c1 = (sal_Int32)*pStr1;
        c2 = (sal_Int32)((unsigned char)*pStr2);
        if ( (c1 >= 65) && (c1 <= 90) )
            c1 += 32;
        if ( (c2 >= 65) && (c2 <= 90) )
            c2 += 32;
        nRet = c1-c2;
        if ( nRet != 0 )
            return nRet;

        pStr1++;
        pStr2++;
    }
    while ( c2 );

    return 0;
}

/* ----------------------------------------------------------------------- */

sal_Int32 SAL_CALL rtl_ustr_ascii_compareIgnoreAsciiCase_WithLength( const sal_Unicode* pStr1,
                                                                     sal_Int32 nStr1Len,
                                                                     const sal_Char* pStr2 )
{
    sal_Int32   nRet;
    sal_Int32   c1;
    sal_Int32   c2;
    do
    {
        if ( !nStr1Len )
            return *pStr2 == '\0' ? 0 : -1;

        /* If character between 'A' and 'Z', than convert it to lowercase */
        c1 = (sal_Int32)*pStr1;
        c2 = (sal_Int32)((unsigned char)*pStr2);
        if ( (c1 >= 65) && (c1 <= 90) )
            c1 += 32;
        if ( (c2 >= 65) && (c2 <= 90) )
            c2 += 32;
        nRet = c1-c2;
        if ( nRet != 0 )
            return nRet;

        pStr1++;
        pStr2++;
        nStr1Len--;
    }
    while( c2 );

    return 0;
}

sal_Int32 rtl_ustr_ascii_compareIgnoreAsciiCase_WithLengths(
    sal_Unicode const * first, sal_Int32 firstLen,
    char const * second, sal_Int32 secondLen)
{
    sal_Int32 i;
    sal_Int32 len = firstLen < secondLen ? firstLen : secondLen;
    for (i = 0; i < len; ++i) {
        sal_Int32 c1 = *first++;
        sal_Int32 c2 = (unsigned char) *second++;
        sal_Int32 d;
        if (c1 >= 65 && c1 <= 90) {
            c1 += 32;
        }
        if (c2 >= 65 && c2 <= 90) {
            c2 += 32;
        }
        d = c1 - c2;
        if (d != 0) {
            return d;
        }
    }
    return firstLen - secondLen;
}

/* ----------------------------------------------------------------------- */

sal_Int32 SAL_CALL rtl_ustr_ascii_shortenedCompareIgnoreAsciiCase_WithLength( const sal_Unicode* pStr1,
                                                                              sal_Int32 nStr1Len,
                                                                              const sal_Char* pStr2,
                                                                              sal_Int32 nShortenedLength )
{
    const sal_Unicode*  pStr1End = pStr1 + nStr1Len;
    sal_Int32           nRet;
    sal_Int32           c1;
    sal_Int32           c2;
    while ( (nShortenedLength > 0) &&
            (pStr1 < pStr1End) && *pStr2 )
    {
        /* Check ASCII range */
        OSL_ENSURE( (*pStr2 & 0x80) == 0, "Found ASCII char > 127");

        /* If character between 'A' and 'Z', than convert it to lowercase */
        c1 = (sal_Int32)*pStr1;
        c2 = (sal_Int32)((unsigned char)*pStr2);
        if ( (c1 >= 65) && (c1 <= 90) )
            c1 += 32;
        if ( (c2 >= 65) && (c2 <= 90) )
            c2 += 32;
        nRet = c1-c2;
        if ( nRet != 0 )
            return nRet;

        nShortenedLength--;
        pStr1++;
        pStr2++;
    }

    if ( nShortenedLength <= 0 )
        return 0;

    if ( *pStr2 )
    {
        OSL_ENSURE( pStr1 == pStr1End, "pStr1 == pStr1End failed" );
        // first is a substring of the second string => less (negative value)
        nRet = -1;
    }
    else
    {
        // greater or equal
        nRet = pStr1End - pStr1;
    }

    return nRet;
}

/* ----------------------------------------------------------------------- */

void SAL_CALL rtl_uString_newFromAscii( rtl_uString** ppThis,
                                        const sal_Char* pCharStr )
{
    sal_Int32 nLen;

    if ( pCharStr )
    {
        const sal_Char* pTempStr = pCharStr;
        while( *pTempStr )
            pTempStr++;
        nLen = pTempStr-pCharStr;
    }
    else
        nLen = 0;

    if ( !nLen )
    {
        IMPL_RTL_STRINGNAME( new )( ppThis );
        return;
    }

    if ( *ppThis )
        IMPL_RTL_STRINGNAME( release )( *ppThis );

    *ppThis = IMPL_RTL_STRINGNAME( ImplAlloc )( nLen );
    OSL_ASSERT(*ppThis != NULL);
    if ( (*ppThis) )
    {
        IMPL_RTL_STRCODE* pBuffer = (*ppThis)->buffer;
        do
        {
            /* Check ASCII range */
            OSL_ENSURE( ((unsigned char)*pCharStr) <= 127,
                        "rtl_uString_newFromAscii() - Found ASCII char > 127" );

            *pBuffer = *pCharStr;
            pBuffer++;
            pCharStr++;
        }
        while ( *pCharStr );
    }
}

void SAL_CALL rtl_uString_newFromCodePoints(
    rtl_uString ** newString, sal_uInt32 const * codePoints,
    sal_Int32 codePointCount)
{
    sal_Int32 n;
    sal_Int32 i;
    sal_Unicode * p;
    OSL_ASSERT(
        newString != NULL &&
        (codePoints != NULL || codePointCount == 0) &&
        codePointCount >= 0);
    if (codePointCount == 0) {
        rtl_uString_new(newString);
        return;
    }
    if (*newString != NULL) {
        rtl_uString_release(*newString);
    }
    n = codePointCount;
    for (i = 0; i < codePointCount; ++i) {
        OSL_ASSERT(codePoints[i] <= 0x10FFFF);
        if (codePoints[i] >= 0x10000) {
            ++n;
        }
    }
    /* Builds on the assumption that sal_Int32 uses 32 bit two's complement
       representation with wrap around (the necessary number of UTF-16 code
       units will be no larger than 2 * SAL_MAX_INT32, represented as
       sal_Int32 -2): */
    if (n < 0) {
        *newString = NULL;
        return;
    }
    *newString = rtl_uString_ImplAlloc(n);
    if (*newString == NULL) {
        return;
    }
    p = (*newString)->buffer;
    for (i = 0; i < codePointCount; ++i) {
        sal_uInt32 c = codePoints[i];
        if (c < 0x10000) {
            *p++ = (sal_Unicode) c;
        } else {
            c -= 0x10000;
            *p++ = (sal_Unicode) ((c >> 10) | SAL_RTL_FIRST_HIGH_SURROGATE);
            *p++ = (sal_Unicode) ((c & 0x3FF) | SAL_RTL_FIRST_LOW_SURROGATE);
        }
    }
}

/* ======================================================================= */

static int rtl_ImplGetFastUTF8UnicodeLen( const sal_Char* pStr, sal_Int32 nLen )
{
    int             n;
    sal_uChar       c;
    const sal_Char* pEndStr;

    n = 0;
    pEndStr  = pStr+nLen;
    while ( pStr < pEndStr )
    {
        c = (sal_uChar)*pStr;

        if ( !(c & 0x80) )
            pStr++;
        else if ( (c & 0xE0) == 0xC0 )
            pStr += 2;
        else if ( (c & 0xF0) == 0xE0 )
            pStr += 3;
        else if ( (c & 0xF8) == 0xF0 )
            pStr += 4;
        else if ( (c & 0xFC) == 0xF8 )
            pStr += 5;
        else if ( (c & 0xFE) == 0xFC )
            pStr += 6;
        else
            pStr++;

        n++;
    }

    return n;
}

/* ----------------------------------------------------------------------- */

static void rtl_string2UString_status( rtl_uString** ppThis,
                                       const sal_Char* pStr,
                                       sal_Int32 nLen,
                                       rtl_TextEncoding eTextEncoding,
                                       sal_uInt32 nCvtFlags,
                                       sal_uInt32 *pInfo )
{
    OSL_ENSURE(rtl_isOctetTextEncoding(eTextEncoding),
               "rtl_string2UString_status() - Wrong TextEncoding" );

    if ( !nLen )
    {
        rtl_uString_new( ppThis );
        if (pInfo != NULL) {
            *pInfo = 0;
        }
    }
    else
    {
        if ( *ppThis )
            IMPL_RTL_STRINGNAME( release )( *ppThis );

        /* Optimization for US-ASCII */
        if ( eTextEncoding == RTL_TEXTENCODING_ASCII_US )
        {
            IMPL_RTL_STRCODE* pBuffer;
            *ppThis = IMPL_RTL_STRINGNAME( ImplAlloc )( nLen );
            if (*ppThis == NULL) {
                if (pInfo != NULL) {
                    *pInfo = RTL_TEXTTOUNICODE_INFO_ERROR |
                        RTL_TEXTTOUNICODE_INFO_DESTBUFFERTOSMALL;
                }
                return;
            }
            pBuffer = (*ppThis)->buffer;
            do
            {
                /* Check ASCII range */
                OSL_ENSURE( ((unsigned char)*pStr) <= 127,
                            "rtl_string2UString_status() - Found char > 127 and RTL_TEXTENCODING_ASCII_US is specified" );

                *pBuffer = *pStr;
                pBuffer++;
                pStr++;
                nLen--;
            }
            while ( nLen );
            if (pInfo != NULL) {
                *pInfo = 0;
            }
        }
        else
        {
            rtl_uString*                pTemp;
            rtl_uString*                pTemp2 = NULL;
            rtl_TextToUnicodeConverter  hConverter;
            sal_uInt32                  nInfo;
            sal_Size                    nSrcBytes;
            sal_Size                    nDestChars;
            sal_Size                    nNewLen;

            /* Optimization for UTF-8 - we try to calculate the exact length */
            /* For all other encoding we try the maximum - and reallocate
               the buffer if needed */
            if ( eTextEncoding == RTL_TEXTENCODING_UTF8 )
            {
                nNewLen = rtl_ImplGetFastUTF8UnicodeLen( pStr, nLen );
                /* Includes the string only ASCII, then we could copy
                   the buffer faster */
                if ( nNewLen == (sal_Size)nLen )
                {
                    IMPL_RTL_STRCODE* pBuffer;
                    *ppThis = IMPL_RTL_STRINGNAME( ImplAlloc )( nLen );
                    if (*ppThis == NULL)
                    {
                        if (pInfo != NULL) {
                            *pInfo = RTL_TEXTTOUNICODE_INFO_ERROR |
                                RTL_TEXTTOUNICODE_INFO_DESTBUFFERTOSMALL;
                        }
                        return;
                    }
                    pBuffer = (*ppThis)->buffer;
                    do
                    {
                        /* Check ASCII range */
                        OSL_ENSURE( ((unsigned char)*pStr) <= 127,
                                    "rtl_string2UString_status() - UTF8 test encoding is wrong" );

                        *pBuffer = *pStr;
                        pBuffer++;
                        pStr++;
                        nLen--;
                    }
                    while ( nLen );
                    if (pInfo != NULL) {
                        *pInfo = 0;
                    }
                    return;
                }
            }
            else
                nNewLen = nLen;

            nCvtFlags |= RTL_TEXTTOUNICODE_FLAGS_FLUSH;
            hConverter = rtl_createTextToUnicodeConverter( eTextEncoding );

            pTemp = IMPL_RTL_STRINGNAME( ImplAlloc )( nNewLen );
            if (pTemp == NULL) {
                if (pInfo != NULL) {
                    *pInfo = RTL_TEXTTOUNICODE_INFO_ERROR |
                        RTL_TEXTTOUNICODE_INFO_DESTBUFFERTOSMALL;
                }
                return;
            }
            nDestChars = rtl_convertTextToUnicode( hConverter, 0,
                                                   pStr, nLen,
                                                   pTemp->buffer, nNewLen,
                                                   nCvtFlags,
                                                   &nInfo, &nSrcBytes );

            /* Buffer not big enough, try again with enough space */
            /* Shouldn't be the case, but if we get textencoding which
               could results in more unicode characters we have this
               code here. Could be the case for apple encodings */
            while ( nInfo & RTL_TEXTTOUNICODE_INFO_DESTBUFFERTOSMALL )
            {
                rtl_freeMemory( pTemp );
                nNewLen += 8;
                pTemp = IMPL_RTL_STRINGNAME( ImplAlloc )( nNewLen );
                if (pTemp == NULL) {
                    if (pInfo != NULL) {
                        *pInfo = RTL_TEXTTOUNICODE_INFO_ERROR |
                            RTL_TEXTTOUNICODE_INFO_DESTBUFFERTOSMALL;
                    }
                    return;
                }
                nDestChars = rtl_convertTextToUnicode( hConverter, 0,
                                                       pStr, nLen,
                                                       pTemp->buffer, nNewLen,
                                                       nCvtFlags,
                                                       &nInfo, &nSrcBytes );
            }

            if (pInfo)
                *pInfo = nInfo;

            /* Set the buffer to the correct size or if there is too
               much overhead, reallocate to the correct size */
            if ( nNewLen > nDestChars+8 )
            {
                pTemp2 = IMPL_RTL_STRINGNAME( ImplAlloc )( nDestChars );
            }
            if (pTemp2 != NULL)
            {
                rtl_str_ImplCopy(pTemp2->buffer, pTemp->buffer, nDestChars);
                rtl_freeMemory(pTemp);
                pTemp = pTemp2;
            }
            else
            {
                pTemp->length = nDestChars;
                pTemp->buffer[nDestChars] = 0;
            }

            rtl_destroyTextToUnicodeConverter( hConverter );
            *ppThis = pTemp;

            /* Results the conversion in an empty buffer -
               create an empty string */
            if ( pTemp && !nDestChars )
                rtl_uString_new( ppThis );
        }
    }
}

void SAL_CALL rtl_string2UString( rtl_uString** ppThis,
                                  const sal_Char* pStr,
                                  sal_Int32 nLen,
                                  rtl_TextEncoding eTextEncoding,
                                  sal_uInt32 nCvtFlags )
{
    rtl_string2UString_status( ppThis, pStr, nLen, eTextEncoding,
                               nCvtFlags, NULL );
}

/* ----------------------------------------------------------------------- */

typedef enum {
    CANNOT_RETURN,
    CAN_RETURN = 1
} StrLifecycle;

static oslMutex
getInternMutex()
{
    static oslMutex pPoolGuard = NULL;
    if( !pPoolGuard )
    {
        oslMutex pGlobalGuard;
        pGlobalGuard = *osl_getGlobalMutex();
        osl_acquireMutex( pGlobalGuard );
        if( !pPoolGuard )
        {
            oslMutex p = osl_createMutex();
            OSL_DOUBLE_CHECKED_LOCKING_MEMORY_BARRIER();
            pPoolGuard = p;
        }
        osl_releaseMutex( pGlobalGuard );
    }
    else
    {
        OSL_DOUBLE_CHECKED_LOCKING_MEMORY_BARRIER();
    }

    return pPoolGuard;
}

/* returns true if we found a dup in the pool */
static void rtl_ustring_intern_internal( rtl_uString ** newStr,
                                         rtl_uString  * str,
                                         StrLifecycle   can_return )
{
    oslMutex pPoolMutex;

    pPoolMutex = getInternMutex();

    osl_acquireMutex( pPoolMutex );

    *newStr = rtl_str_hash_intern (str, can_return);

    osl_releaseMutex( pPoolMutex );

    if( can_return && *newStr != str )
    { /* we dupped, then found a match */
        rtl_freeMemory( str );
    }
}

void SAL_CALL rtl_uString_intern( rtl_uString ** newStr,
                                  rtl_uString  * str)
{
    if (SAL_STRING_IS_INTERN(str))
    {
        IMPL_RTL_AQUIRE( str );
        *newStr = str;
    }
    else
    {
        rtl_uString *pOrg = *newStr;
        *newStr = NULL;
        rtl_ustring_intern_internal( newStr, str, CANNOT_RETURN );
        if (pOrg)
            rtl_uString_release (pOrg);
    }
}

void SAL_CALL rtl_uString_internConvert( rtl_uString   ** newStr,
                                         const sal_Char * str,
                                         sal_Int32        len,
                                         rtl_TextEncoding eTextEncoding,
                                         sal_uInt32       convertFlags,
                                         sal_uInt32     * pInfo )
{
    rtl_uString *scratch;

    if (*newStr)
    {
        rtl_uString_release (*newStr);
        *newStr = NULL;
    }

    if ( len < 256 )
    { // try various optimisations
        if ( len < 0 )
            len = strlen( str );
        if ( eTextEncoding == RTL_TEXTENCODING_ASCII_US )
        {
            int i;
            rtl_uString *pScratch;
            pScratch = alloca( sizeof( rtl_uString )
                               + len * sizeof (IMPL_RTL_STRCODE ) );
            for (i = 0; i < len; i++)
            {
                /* Check ASCII range */
                OSL_ENSURE( ((unsigned char)str[i]) <= 127,
                            "rtl_ustring_internConvert() - Found char > 127 and RTL_TEXTENCODING_ASCII_US is specified" );
                pScratch->buffer[i] = str[i];
            }
            pScratch->length = len;
            rtl_ustring_intern_internal( newStr, pScratch, CANNOT_RETURN );
            return;
        }
        /* FIXME: we want a nice UTF-8 / alloca shortcut here */
    }

    scratch = NULL;
    rtl_string2UString_status( &scratch, str, len, eTextEncoding, convertFlags,
                               pInfo );
    if (!scratch) {
        return;
    }
    rtl_ustring_intern_internal( newStr, scratch, CAN_RETURN );
}

static void
internRelease (rtl_uString *pThis)
{
    oslMutex pPoolMutex;

    rtl_uString *pFree = NULL;
    if ( SAL_STRING_REFCOUNT(
             osl_decrementInterlockedCount( &(pThis->refCount) ) ) == 0)
    {
        pPoolMutex = getInternMutex();
        osl_acquireMutex( pPoolMutex );

        rtl_str_hash_remove (pThis);

        /* May have been separately acquired */
        if ( SAL_STRING_REFCOUNT(
                 osl_incrementInterlockedCount( &(pThis->refCount) ) ) == 1 )
        {
            /* we got the last ref */
            pFree = pThis;
        }
        else /* very unusual */
        {
            internRelease (pThis);
        }

        osl_releaseMutex( pPoolMutex );
    }
    if (pFree)
        rtl_freeMemory (pFree);
}

sal_uInt32 SAL_CALL rtl_uString_iterateCodePoints(
    rtl_uString const * string, sal_Int32 * indexUtf16,
    sal_Int32 incrementCodePoints)
{
    sal_Int32 n;
    sal_Unicode cu;
    sal_uInt32 cp;
    OSL_ASSERT(string != NULL && indexUtf16 != NULL);
    n = *indexUtf16;
    OSL_ASSERT(n >= 0 && n <= string->length);
    while (incrementCodePoints < 0) {
        OSL_ASSERT(n > 0);
        cu = string->buffer[--n];
        if (SAL_RTL_IS_LOW_SURROGATE(cu) && n != 0 &&
            SAL_RTL_IS_HIGH_SURROGATE(string->buffer[n - 1]))
        {
            --n;
        }
        ++incrementCodePoints;
    }
    OSL_ASSERT(n >= 0 && n < string->length);
    cu = string->buffer[n];
    if (SAL_RTL_IS_HIGH_SURROGATE(cu) && string->length - n >= 2 &&
        SAL_RTL_IS_LOW_SURROGATE(string->buffer[n + 1]))
    {
        cp = SAL_RTL_COMBINE_SURROGATES(cu, string->buffer[n + 1]);
    } else {
        cp = cu;
    }
    while (incrementCodePoints > 0) {
        OSL_ASSERT(n < string->length);
        cu = string->buffer[n++];
        if (SAL_RTL_IS_HIGH_SURROGATE(cu) && n != string->length &&
            SAL_RTL_IS_LOW_SURROGATE(string->buffer[n]))
        {
            ++n;
        }
        --incrementCodePoints;
    }
    OSL_ASSERT(n >= 0 && n <= string->length);
    *indexUtf16 = n;
    return cp;
}

sal_Bool rtl_convertStringToUString(
    rtl_uString ** target, char const * source, sal_Int32 length,
    rtl_TextEncoding encoding, sal_uInt32 flags) SAL_THROW_EXTERN_C()
{
    sal_uInt32 info;
    rtl_string2UString_status(target, source, length, encoding, flags, &info);
    return (sal_Bool) ((info & RTL_TEXTTOUNICODE_INFO_ERROR) == 0);
}
