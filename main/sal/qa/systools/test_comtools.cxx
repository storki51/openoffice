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
#include "precompiled_sal.hxx"
// autogenerated file with codegen.pl

#include "gtest/gtest.h"
#include <systools/win32/comtools.hxx>

class COMObject : public IUnknown
{
public:
    COMObject() : ref_count_(0)
    {
    }

    ~COMObject()
    {
    }

    ULONG __stdcall AddRef()
    {
        ref_count_++;
        return ref_count_;
    }

    ULONG __stdcall Release()
    {
        ULONG cnt = --ref_count_;
        if (cnt == 0)
            delete this;
        return cnt;
    }

    HRESULT __stdcall QueryInterface(REFIID riid, LPVOID* ppv)
    {
        if (riid == IID_IUnknown)
        {
            AddRef();
            *ppv = this;
            return S_OK;
        }
        return E_NOINTERFACE;
    }

    ULONG GetRefCount() const
    {
        return ref_count_;
    }

private:
    ULONG ref_count_;
};

sal::systools::COMReference<IUnknown> comObjectSource()
{
    return sal::systools::COMReference<IUnknown>(new COMObject);
}

bool comObjectSink(sal::systools::COMReference<IUnknown> r, ULONG expectedRefCountOnReturn)
{
    r = sal::systools::COMReference<IUnknown>();
    COMObject* p = reinterpret_cast<COMObject*>(r.get());
    if (p)
        return (p->GetRefCount() == expectedRefCountOnReturn);
    else
        return (0 == expectedRefCountOnReturn);
}

void comObjectSource2(LPVOID* ppv)
{
    COMObject* p = new COMObject;
    p->AddRef();
    *ppv = p;
}

namespace test_comtools
{

    class test_COMReference : public ::testing::Test
    {
    };

    /// test of COMReference<IUnknown> r;
    TEST_F(test_COMReference, default_ctor)
    {
        sal::systools::COMReference<IUnknown> r;
        ASSERT_TRUE(r.get() == NULL) << "COMReference should be empty";
    }

    TEST_F(test_COMReference, test_ctor_manual_AddRef)
    {
        COMObject* p = new COMObject;
        p->AddRef();
        sal::systools::COMReference<IUnknown> r(p, false);
        ASSERT_TRUE(reinterpret_cast<COMObject*>(r.get())->GetRefCount() == 1) << "Wrong reference count 1 is expected";
    }

    TEST_F(test_COMReference, test_copy_ctor)
    {
        sal::systools::COMReference<IUnknown> r(comObjectSource());
        ASSERT_TRUE(reinterpret_cast<COMObject*>(r.get())->GetRefCount() == 1) << "Wrong reference count 1 is expected";
    }

    TEST_F(test_COMReference, test_copy_assignment)
    {
        sal::systools::COMReference<IUnknown> r;
        ASSERT_TRUE(r.get() == NULL) << "COMReference should be empty";

        r = comObjectSource();
        ASSERT_TRUE(r.get() != NULL) << "COMReference should be empty";
        ASSERT_TRUE(reinterpret_cast<COMObject*>(r.get())->GetRefCount() == 1) << "Wrong reference count 1 is expected";
    }

    TEST_F(test_COMReference, test_ref_to_ref_assignment)
    {
        sal::systools::COMReference<IUnknown> r1 = comObjectSource();
        sal::systools::COMReference<IUnknown> r2 = r1;
        ASSERT_TRUE(reinterpret_cast<COMObject*>(r2.get())->GetRefCount() == 2) << "Wrong reference count 2 is expected";
    }

    TEST_F(test_COMReference, test_pointer_to_ref_assignment)
    {
        sal::systools::COMReference<IUnknown> r;
        r = new COMObject;
        ASSERT_TRUE(reinterpret_cast<COMObject*>(r.get())->GetRefCount() == 1) << "Wrong reference count 1 is expected";
    }

    TEST_F(test_COMReference, test_pointer_to_ref_assignment2)
    {
        sal::systools::COMReference<IUnknown> r = comObjectSource();
        r = new COMObject;
        ASSERT_TRUE(reinterpret_cast<COMObject*>(r.get())->GetRefCount() == 1) << "Wrong reference count 1 is expected";
    }

    TEST_F(test_COMReference, test_source_sink)
    {
        ASSERT_TRUE(comObjectSink(comObjectSource(), 0)) << "Wrong reference count, 0 is expected";
    }

    TEST_F(test_COMReference, test_address_operator)
    {
        sal::systools::COMReference<IUnknown> r;
        comObjectSource2(reinterpret_cast<LPVOID*>(&r));
        ASSERT_TRUE(reinterpret_cast<COMObject*>(r.get())->GetRefCount() == 1) << "Wrong reference count, 1 is expected";
    }

    TEST_F(test_COMReference, test_address_operator2)
    {
        sal::systools::COMReference<IUnknown> r1 = comObjectSource();
        sal::systools::COMReference<IUnknown> r2 = r1;
        ASSERT_TRUE(reinterpret_cast<COMObject*>(r2.get())->GetRefCount() == 2) << "Wrong reference count 2 is expected";
        comObjectSource2(reinterpret_cast<LPVOID*>(&r1));
        ASSERT_TRUE(reinterpret_cast<COMObject*>(r1.get())->GetRefCount() == 1) << "Wrong reference count 1 is expected";
        ASSERT_TRUE(reinterpret_cast<COMObject*>(r2.get())->GetRefCount() == 1) << "Wrong reference count 1 is expected";
    }

    TEST_F(test_COMReference, test_clear)
    {
        sal::systools::COMReference<IUnknown> r = comObjectSource();
        ASSERT_TRUE(reinterpret_cast<COMObject*>(r.get())->GetRefCount() == 1) << "Wrong reference count 1 is expected";
        r.clear();
        ASSERT_TRUE(!r.is()) << "Expect reference to be empty";
    }

    TEST_F(test_COMReference, test_query_interface)
    {
        try
        {
            sal::systools::COMReference<IUnknown> r1 = comObjectSource();
            sal::systools::COMReference<IUnknown> r2 = r1.QueryInterface<IUnknown>(IID_IUnknown);
            ASSERT_TRUE(reinterpret_cast<COMObject*>(r2.get())->GetRefCount() == 2) << "Wrong reference count, 2 is expected";
        }
        catch(sal::systools::ComError& ex)
        {
            ASSERT_TRUE(false) << "Exception should not have been thrown";
        }
    }

    TEST_F(test_COMReference, test_query_interface_throw)
    {
        try
        {
            sal::systools::COMReference<IUnknown> r1 = comObjectSource();
            sal::systools::COMReference<IPersistFile> r2 = r1.QueryInterface<IPersistFile>(IID_IPersistFile);
        }
        catch(sal::systools::ComError& ex)
        {
            return;
        }
        ASSERT_TRUE(false) << "Exception should have been thrown";
    }

} // namespace rtl_OUString

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
