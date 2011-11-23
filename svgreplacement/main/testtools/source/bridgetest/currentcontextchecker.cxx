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
#include "precompiled_testtools.hxx"

#include "sal/config.h"

#include "currentcontextchecker.hxx"

#include "com/sun/star/uno/Any.hxx"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/RuntimeException.hpp"
#include "com/sun/star/uno/XCurrentContext.hpp"
#include "cppu/unotype.hxx"
#include "cppuhelper/implbase1.hxx"
#include "osl/diagnose.h"
#include "osl/diagnose.hxx"
#include "rtl/string.h"
#include "rtl/ustring.hxx"
#include "sal/types.h"
#include "test/testtools/bridgetest/XCurrentContextChecker.hpp"
#include "uno/current_context.hxx"

namespace {

namespace css = ::com::sun::star;

static char const KEY[] = "testtools.bridgetest.Key";
static char const VALUE[] = "good";

class CurrentContext:
    public ::osl::DebugBase< CurrentContext >,
    public ::cppu::WeakImplHelper1< css::uno::XCurrentContext >
{
public:
    CurrentContext();

    virtual ~CurrentContext();

    virtual css::uno::Any SAL_CALL getValueByName(::rtl::OUString const & Name)
        throw (css::uno::RuntimeException);

private:
    CurrentContext(CurrentContext &); // not defined
    void operator =(CurrentContext &); // not defined
};

CurrentContext::CurrentContext() {}

CurrentContext::~CurrentContext() {}

css::uno::Any CurrentContext::getValueByName(::rtl::OUString const & Name)
    throw (css::uno::RuntimeException)
{
    return Name.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM(KEY))
        ? css::uno::makeAny(::rtl::OUString::createFromAscii(VALUE))
        : css::uno::Any();
}

}

testtools::bridgetest::CurrentContextChecker::CurrentContextChecker() {}

testtools::bridgetest::CurrentContextChecker::~CurrentContextChecker() {}

::sal_Bool testtools::bridgetest::CurrentContextChecker::perform(
    css::uno::Reference<
        ::test::testtools::bridgetest::XCurrentContextChecker > const & other,
    ::sal_Int32 setSteps, ::sal_Int32 checkSteps)
    throw (css::uno::RuntimeException)
{
    if (setSteps == 0) {
        css::uno::ContextLayer layer(new CurrentContext);
        return performCheck(other, setSteps, checkSteps);
    } else {
        return performCheck(other, setSteps, checkSteps);
    }
}

bool testtools::bridgetest::CurrentContextChecker::performCheck(
    css::uno::Reference<
        ::test::testtools::bridgetest::XCurrentContextChecker > const & other,
    ::sal_Int32 setSteps, ::sal_Int32 checkSteps)
{
    OSL_ASSERT(other.is() && checkSteps >= 0);
    if (checkSteps == 0) {
        css::uno::Reference< css::uno::XCurrentContext > context(
            css::uno::getCurrentContext());
        if (!context.is()) {
            return false;
        }
        css::uno::Any a(
            context->getValueByName(::rtl::OUString::createFromAscii(KEY)));
        if (a.getValueType() != ::cppu::UnoType< ::rtl::OUString >::get()) {
            return false;
        }
        ::rtl::OUString s;
        OSL_VERIFY(a >>= s);
        return s.equalsAsciiL(RTL_CONSTASCII_STRINGPARAM(VALUE));
    } else {
        return other->perform(
            this, setSteps >= 0 ? setSteps - 1 : -1, checkSteps - 1);
    }
}
