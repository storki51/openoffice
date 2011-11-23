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



#if ! defined INCLUDED_SLIDESHOW_IRISWIPE_HXX
#define INCLUDED_SLIDESHOW_IRISWIPE_HXX

#include <basegfx/polygon/b2dpolypolygon.hxx>
#include "parametricpolypolygon.hxx"
#include "transitiontools.hxx"


namespace slideshow {
namespace internal {

/// Generate a iris wipe
class IrisWipe : public ParametricPolyPolygon
{
public:
    IrisWipe() : m_unitRect( createUnitRect() ) {}
    virtual ::basegfx::B2DPolyPolygon operator()( double x );
private:
    const ::basegfx::B2DPolyPolygon m_unitRect;
};

}
}

#endif /* INCLUDED_SLIDESHOW_IRISWIPE_HXX */
