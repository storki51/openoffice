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



#ifndef INCLUDED_OUTPUT_WITH_DEPTH
#define INCLUDED_OUTPUT_WITH_DEPTH

#include <vector>
#include <iostream>

namespace writerfilter
{

using namespace ::std;

template <typename T>
class OutputWithDepth
{
    typedef ::std::vector<T> Group_t;
    Group_t mGroup;
    
    unsigned int mnCurrentDepth;
    unsigned int mnGroupDepth;

    T mOpenTag;
    T mCloseTag;

protected:
    virtual void output(const T & aItem) const = 0;
    void outputGroup();
    void finalize();

public:
    OutputWithDepth(const T & aOpenTag, const T & aCloseTag);
    virtual ~OutputWithDepth();

    void openGroup();
    void closeGroup();
    void addItem(const T & aItem);
    void setDepth(unsigned int nDepth);
};

template <typename T>
OutputWithDepth<T>::OutputWithDepth(const T & aOpenTag, const T & aEndTag)
: mOpenTag(aOpenTag), mCloseTag(aEndTag)
{
}

template <typename T>
OutputWithDepth<T>::~OutputWithDepth()
{
}

template <typename T>
void OutputWithDepth<T>::finalize()
{
    outputGroup();
}

template <typename T>
void OutputWithDepth<T>::openGroup()
{
    outputGroup();
    mnGroupDepth = 0;
}

template <typename T>
void OutputWithDepth<T>::closeGroup()
{
    if (mnGroupDepth > mnCurrentDepth)
        for (unsigned int i = 0; i < mnGroupDepth - mnCurrentDepth; ++i)
            output(mOpenTag);
    else if (mnGroupDepth < mnCurrentDepth)
        for (unsigned int i = 0; i < mnCurrentDepth - mnGroupDepth; ++i)
            output(mCloseTag);

    outputGroup();

    mnCurrentDepth = mnGroupDepth;
}

template <typename T>
void OutputWithDepth<T>::addItem(const T & aItem)
{
    mGroup.push_back(aItem);
}

template <typename T>
void OutputWithDepth<T>::setDepth(unsigned int nDepth)
{
    mnGroupDepth = nDepth;
}

template <typename T>
void OutputWithDepth<T>::outputGroup()
{
    typename Group_t::iterator aItEnd = mGroup.end();
    
    for (typename Group_t::iterator aIt = mGroup.begin(); aIt != aItEnd; aIt++)
    {
        output(*aIt);
    }

    mGroup.clear();
}
}
#endif // INCLUDED_OUTPUT_WITH_DEPTH
