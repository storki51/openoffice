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



#ifndef INCLUDED_UNOTOOLS_SYSLOCALE_HXX
#define INCLUDED_UNOTOOLS_SYSLOCALE_HXX

#include "unotools/unotoolsdllapi.h"
#include <unotools/localedatawrapper.hxx>
#include <unotools/charclass.hxx>
#include <sal/types.h>
#include <i18npool/lang.h>
#include <rtl/textenc.h>

class SvtSysLocale_Impl;
class SvtSysLocaleOptions;

namespace osl { class Mutex; }
class LocaleDataWrapper;

/**
    SvtSysLocale provides a refcounted single instance of an application wide
    <type>LocaleDataWrapper</type> and <type>CharClass</type> which always
    follow the locale as it is currently configured by the user. You may use
    it anywhere to access the locale data elements like decimal separator and
    simple date formatting and so on. Contructing and destructing a
    SvtSysLocale is not expensive as long as there is at least one instance
    left.
 */
class UNOTOOLS_DLLPUBLIC SvtSysLocale
{
    friend class SvtSysLocale_Impl;     // access to mutex

    static  SvtSysLocale_Impl*  pImpl;
    static  sal_Int32           nRefCount;

    UNOTOOLS_DLLPRIVATE static  ::osl::Mutex&               GetMutex();

public:
                                        SvtSysLocale();
                                        ~SvtSysLocale();

            const LocaleDataWrapper&    GetLocaleData() const;
            const CharClass&            GetCharClass() const;

    /** It is safe to store the pointers locally and use them AS LONG AS THE
        INSTANCE OF SvtSysLocale LIVES!
        It is a faster access but be sure what you do!
     */
            const LocaleDataWrapper*    GetLocaleDataPtr() const;
            const CharClass*            GetCharClassPtr() const;
			SvtSysLocaleOptions&		GetOptions() const;
			com::sun::star::lang::Locale GetLocale() const;
			LanguageType				GetLanguage() const;
			com::sun::star::lang::Locale GetUILocale() const;
			LanguageType				GetUILanguage() const;

    /** Get the best MIME encoding matching the system locale, or if that isn't
        determinable one that matches the UI locale, or UTF8 if everything else
        fails.
     */
    static  rtl_TextEncoding    GetBestMimeEncoding();
};

#endif  // INCLUDED_SVTOOLS_SYSLOCALE_HXX
