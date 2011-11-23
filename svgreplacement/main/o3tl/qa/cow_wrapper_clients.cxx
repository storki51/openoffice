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



#include "cow_wrapper_clients.hxx"

namespace o3tltests {

class cow_wrapper_client2_impl
{
public:
    cow_wrapper_client2_impl() : mnValue(0) {}
    explicit cow_wrapper_client2_impl( int nVal ) : mnValue(nVal) {}
    void setValue( int nVal ) { mnValue = nVal; }
    int  getValue() const { return mnValue; }

    bool operator==( const cow_wrapper_client2_impl& rRHS ) const { return mnValue == rRHS.mnValue; }
    bool operator!=( const cow_wrapper_client2_impl& rRHS ) const { return mnValue != rRHS.mnValue; }
    bool operator<( const cow_wrapper_client2_impl& rRHS ) const { return mnValue < rRHS.mnValue; }

private:
    int mnValue;
};

cow_wrapper_client2::cow_wrapper_client2() : maImpl()
{
}

cow_wrapper_client2::cow_wrapper_client2( int nVal ) : 
    maImpl( cow_wrapper_client2_impl(nVal) )
{
}

cow_wrapper_client2::~cow_wrapper_client2()
{
}

cow_wrapper_client2::cow_wrapper_client2( const cow_wrapper_client2& rSrc ) : 
    maImpl(rSrc.maImpl)
{
}

cow_wrapper_client2& cow_wrapper_client2::operator=( const cow_wrapper_client2& rSrc )
{
    maImpl = rSrc.maImpl;

	return *this;
}

void cow_wrapper_client2::modify( int nVal )
{
    maImpl->setValue( nVal );
}

int  cow_wrapper_client2::queryUnmodified() const
{
    return maImpl->getValue();
}

void cow_wrapper_client2::makeUnique() 
{ 
    maImpl.make_unique(); 
}
bool cow_wrapper_client2::is_unique() const 
{ 
    return maImpl.is_unique(); 
}
oslInterlockedCount cow_wrapper_client2::use_count() const
{ 
    return maImpl.use_count(); 
}
void cow_wrapper_client2::swap( cow_wrapper_client2& r )
{ 
    o3tl::swap(maImpl, r.maImpl); 
} 

bool cow_wrapper_client2::operator==( const cow_wrapper_client2& rRHS ) const
{ 
    return maImpl == rRHS.maImpl; 
}
bool cow_wrapper_client2::operator!=( const cow_wrapper_client2& rRHS ) const
{ 
    return maImpl != rRHS.maImpl; 
}
bool cow_wrapper_client2::operator<( const cow_wrapper_client2& rRHS ) const 
{ 
    return maImpl < rRHS.maImpl; 
}

// ---------------------------------------------------------------------------

cow_wrapper_client3::cow_wrapper_client3() : maImpl()
{
}

cow_wrapper_client3::cow_wrapper_client3( int nVal ) : 
    maImpl( cow_wrapper_client2_impl(nVal) )
{
}

cow_wrapper_client3::~cow_wrapper_client3()
{
}

cow_wrapper_client3::cow_wrapper_client3( const cow_wrapper_client3& rSrc ) : 
    maImpl(rSrc.maImpl)
{
}

cow_wrapper_client3& cow_wrapper_client3::operator=( const cow_wrapper_client3& rSrc )
{
    maImpl = rSrc.maImpl;

	return *this;
}

void cow_wrapper_client3::modify( int nVal )
{
    maImpl->setValue( nVal );
}

int  cow_wrapper_client3::queryUnmodified() const
{
    return maImpl->getValue();
}

void cow_wrapper_client3::makeUnique() 
{ 
    maImpl.make_unique(); 
}
bool cow_wrapper_client3::is_unique() const 
{ 
    return maImpl.is_unique(); 
}
oslInterlockedCount cow_wrapper_client3::use_count() const
{ 
    return maImpl.use_count(); 
}
void cow_wrapper_client3::swap( cow_wrapper_client3& r )
{ 
    o3tl::swap(maImpl, r.maImpl); 
} 

bool cow_wrapper_client3::operator==( const cow_wrapper_client3& rRHS ) const
{ 
    return maImpl == rRHS.maImpl; 
}
bool cow_wrapper_client3::operator!=( const cow_wrapper_client3& rRHS ) const
{ 
    return maImpl != rRHS.maImpl; 
}
bool cow_wrapper_client3::operator<( const cow_wrapper_client3& rRHS ) const 
{ 
    return maImpl < rRHS.maImpl; 
}

} // namespace o3tltests
