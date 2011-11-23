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



#ifndef _STOC_TDMGR_COMMON_HXX
#define _STOC_TDMGR_COMMON_HXX

#include <rtl/unload.h>

#include "com/sun/star/reflection/XTypeDescription.hpp"

#define OUSTR(x) ::rtl::OUString( RTL_CONSTASCII_USTRINGPARAM(x) )
#define ARLEN(x) (sizeof (x) / sizeof *(x))


namespace css = ::com::sun::star;

namespace stoc_tdmgr
{
    extern rtl_StandardModuleCount g_moduleCount;

struct IncompatibleTypeException
{
    ::rtl::OUString m_cause;
    IncompatibleTypeException( ::rtl::OUString const & cause )
        : m_cause( cause ) {}
};

void check(
    css::uno::Reference<css::reflection::XTypeDescription> const & xNewTD,
    css::uno::Reference<css::reflection::XTypeDescription> const & xExistingTD,
    ::rtl::OUString const & context = ::rtl::OUString() );
/* throw (css::uno::RuntimeException, IncompatibleTypeException) */

} // namespace stoc_tdmgr

#endif /* _STOC_TDMGR_COMMON_HXX */
