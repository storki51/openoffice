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



#ifndef INCLUDED_CODEMAKER_SOURCE_CPPUMAKER_INCLUDES_HXX
#define INCLUDED_CODEMAKER_SOURCE_CPPUMAKER_INCLUDES_HXX

#include "codemaker/dependencies.hxx"
#include "rtl/ustring.hxx"

class FileStream;
class TypeManager;

namespace codemaker { namespace cppumaker {

class Includes {
public:
    Includes(
        TypeManager const & manager,
        codemaker::Dependencies const & dependencies, bool hpp);

    ~Includes();

    void add(rtl::OString const & registryType);

    void addAny() { m_includeAny = true; }

    void addReference() { m_includeReference = true; }

    void addSequence() { m_includeSequence = true; }

    void addType() { m_includeType = true; }

    void addCppuMacrosHxx() { m_includeCppuMacrosHxx = true; }

    void addCppuUnotypeHxx() { m_includeCppuUnotypeHxx = true; }

    void addOslDoublecheckedlockingH()
    { m_includeOslDoublecheckedlockingH = true; }

    void addOslMutexHxx() { m_includeOslMutexHxx = true; }

    void addRtlStrbufHxx() { m_includeRtlStrbufHxx = true; }

    void addRtlStringH() { m_includeRtlStringH = true; }

    void addRtlTextencH() { m_includeRtlTextencH = true; }

    void addRtlUstrbufHxx() { m_includeRtlUstrbufHxx = true; }

    void addRtlUstringH() { m_includeRtlUstringH = true; }

    void addRtlUstringHxx() { m_includeRtlUstringHxx = true; }

    void addSalTypesH() { m_includeSalTypesH = true; }

    void addTypelibTypeclassH() { m_includeTypelibTypeclassH = true; }

    void addTypelibTypedescriptionH()
    { m_includeTypelibTypedescriptionH = true; }

    void dump(FileStream & out, rtl::OString const * companionHdl);

    static void dumpInclude(
        FileStream & out, rtl::OString const & registryType, bool hpp,
        rtl::OString const & suffix = rtl::OString());

private:
    Includes(Includes &); // not implemented
    void operator =(Includes); // not implemented;

    bool isInterfaceType(rtl::OString const & registryType) const;

    TypeManager const & m_manager;
    codemaker::Dependencies::Map m_map;
    bool m_hpp;
    bool m_includeAny;
    bool m_includeReference;
    bool m_includeSequence;
    bool m_includeType;
    bool m_includeCppuMacrosHxx;
    bool m_includeCppuUnotypeHxx;
    bool m_includeOslDoublecheckedlockingH;
    bool m_includeOslMutexHxx;
    bool m_includeRtlStrbufHxx;
    bool m_includeRtlStringH;
    bool m_includeRtlTextencH;
    bool m_includeRtlUstrbufHxx;
    bool m_includeRtlUstringH;
    bool m_includeRtlUstringHxx;
    bool m_includeSalTypesH;
    bool m_includeTypelibTypeclassH;
    bool m_includeTypelibTypedescriptionH;
};

} }

#endif // INCLUDED_CODEMAKER_SOURCE_CPPUMAKER_INCLUDES_HXX
