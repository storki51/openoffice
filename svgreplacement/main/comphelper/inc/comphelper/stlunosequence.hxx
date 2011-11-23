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



#ifndef _COMPHELPER_STLUNOITERATOR_HXX
#define _COMPHELPER_STLUNOITERATOR_HXX

#include <com/sun/star/uno/Sequence.hxx>
#include <sal/types.h>


namespace comphelper
{
    /**
    @short stl-container-like access to an existing ::com::sun::star::uno::Sequence
    @descr These template functions allows using an existing
    ::com::sun::star::uno::Sequence using stl algorithms. They provides
    standard-compliant mutable random access iterators. Because random access
    iterators are the most generic iterators defined by the stl, any stl algorithm
    can be applied to the Sequence (excluding algorithms requiring output
    iterators).
    <p>
    Example: (creating a ::std::list from a ::com::sun::star::uno::Sequence)
    <code>
    ::com::sun::star::uno::Sequence<sal_Int32> aSeq(10);
    ::std::list stl_list(stl_begin(aSeq), stl_end(aSeq));
    </code>
    <p>
    Example: (sorting ::com::sun::star::uno::Sequence inplace)
    <code>
    ::com::sun::star::uno::Sequence<sal_Int32> aSeq(10);
    ::std::sort(stl_begin(aSeq), stl_seq.end(aSeq));
    </code>
    <p>
    Example: (counting occurrences of 4711 in a ::com::sun::star::uno::Sequence)
    <code>
    ::com::sun::star::uno::Sequence<sal_Int32> aSeq(10);
    sal_Int32 count = 0;
    ::std::count(stl_begin(aSeq), stl_end(aSeq), 4711, count);
    </code>
    <p>

    @see http://www.sgi.com/tech/stl/Container.html
    @see http://www.sgi.com/tech/stl/Sequence.html
    @see http://www.sgi.com/tech/stl/RandomAccessIterator.html
    */

    template <typename V>
    V* stl_begin(::com::sun::star::uno::Sequence<V>& rSeq)
        { return rSeq.getArray(); }

    template <typename V>
    V* stl_end(::com::sun::star::uno::Sequence<V>& rSeq)
        { return rSeq.getArray() + rSeq.getLength(); }

    template <typename V>
    const V* stl_begin(const ::com::sun::star::uno::Sequence<V>& rSeq)
        { return rSeq.getConstArray(); }

    template <typename V>
    const V* stl_end(const ::com::sun::star::uno::Sequence<V>& rSeq)
        { return rSeq.getConstArray() + rSeq.getLength(); }
}
#endif
