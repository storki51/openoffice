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



#ifndef INCLUDED_BINARYURP_SOURCE_CACHE_HXX
#define INCLUDED_BINARYURP_SOURCE_CACHE_HXX

#include "sal/config.h"

#include <cstddef>
#include <map>

#include "boost/noncopyable.hpp"
#include "osl/diagnose.h"
#include "sal/types.h"

namespace binaryurp {

namespace cache {

enum { size = 256, ignore = 0xFFFF };

}

template< typename T > class Cache: private boost::noncopyable {
public:
    explicit Cache(std::size_t size):
        size_(size), first_(map_.end()), last_(map_.end())
    {
        OSL_ASSERT(size < cache::ignore);
    }

    sal_uInt16 add(T const & content, bool * found) {
        OSL_ASSERT(found != 0);
        typename Map::iterator i(map_.find(content));
        *found = i != map_.end();
        if (i == map_.end()) {
            typename Map::size_type n = map_.size();
            if (n < size_) {
                i =
                    (map_.insert(
                        typename Map::value_type(
                            content,
                            Entry(
                                static_cast< sal_uInt16 >(n), map_.end(),
                                first_)))).
                    first;
                if (first_ == map_.end()) {
                    last_ = i;
                } else {
                    first_->second.prev = i;
                }
                first_ = i;
            } else if (last_ != map_.end()) {
                i =
                    (map_.insert(
                        typename Map::value_type(
                            content,
                            Entry(last_->second.index, map_.end(), first_)))).
                    first;
                first_->second.prev = i;
                first_ = i;
                typename Map::iterator j(last_);
                last_ = last_->second.prev;
                last_->second.next = map_.end();
                map_.erase(j);
            } else {
                // Reached iff size_ == 0:
                return cache::ignore;
            }
        } else if (i != first_) {
            // Move to front (reached only if size_ > 1):
            i->second.prev->second.next = i->second.next;
            if (i->second.next == map_.end()) {
                last_ = i->second.prev;
            } else {
                i->second.next->second.prev = i->second.prev;
            }
            i->second.prev = map_.end();
            i->second.next = first_;
            first_->second.prev = i;
            first_ = i;
        }
        return i->second.index;
    }

private:
    struct Entry;

    typedef std::map< T, Entry > Map;

    struct Entry {
        sal_uInt16 index;
        typename Map::iterator prev;
        typename Map::iterator next;

        Entry(
            sal_uInt16 theIndex, typename Map::iterator thePrev,
            typename Map::iterator theNext):
            index(theIndex), prev(thePrev), next(theNext) {}
    };

    std::size_t size_;
    Map map_;
    typename Map::iterator first_;
    typename Map::iterator last_;
};

}

#endif
