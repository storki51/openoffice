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


#ifndef _CHART_STRIPE_HXX
#define _CHART_STRIPE_HXX

#include <com/sun/star/drawing/Position3D.hpp>
#include <com/sun/star/drawing/Direction3D.hpp>
#include <com/sun/star/uno/Any.h>

//.............................................................................
namespace chart
{
//.............................................................................

//-----------------------------------------------------------------------------
/** A Stripe represents a 2 dimensional foursquare plane in a 3 dimaensional room.

@todo could: it is not necessary to have 4 point members here; it would be sufficient to have one point and 2 directions
*/

class Stripe
{
public:
    Stripe( const ::com::sun::star::drawing::Position3D& rPoint1
        , const ::com::sun::star::drawing::Direction3D& rDirectionToPoint2
        , const ::com::sun::star::drawing::Direction3D& rDirectionToPoint4 );

    Stripe( const ::com::sun::star::drawing::Position3D& rPoint1
        , const ::com::sun::star::drawing::Position3D& rPoint2
        , double fDepth );

    Stripe( const ::com::sun::star::drawing::Position3D& rPoint1
        , const ::com::sun::star::drawing::Position3D& rPoint2
        , const ::com::sun::star::drawing::Position3D& rPoint3
        , const ::com::sun::star::drawing::Position3D& rPoint4 );

    void SetManualNormal( const ::com::sun::star::drawing::Direction3D& rNormal );
    ::com::sun::star::drawing::Direction3D getNormal() const;

    void InvertNormal( bool bInvertNormal );

    ::com::sun::star::uno::Any      getPolyPolygonShape3D() const;
    ::com::sun::star::uno::Any      getNormalsPolygon() const;
    ::com::sun::star::uno::Any      getTexturePolygon( short nRotatedTexture ) const; //0 to 7 are the different possibilities

    ::com::sun::star::drawing::Position3D GetPosition1() const { return m_aPoint1; }
    ::com::sun::star::drawing::Position3D GetPosition2() const { return m_aPoint2; }
    ::com::sun::star::drawing::Position3D GetPosition3() const { return m_aPoint3; }
    ::com::sun::star::drawing::Position3D GetPosition4() const { return m_aPoint4; }

private:
    ::com::sun::star::drawing::Position3D m_aPoint1;
    ::com::sun::star::drawing::Position3D m_aPoint2;
    ::com::sun::star::drawing::Position3D m_aPoint3;
    ::com::sun::star::drawing::Position3D m_aPoint4;

    bool m_bInvertNormal;
    bool m_bManualNormalSet;
    ::com::sun::star::drawing::Direction3D m_aManualNormal;
};

//.............................................................................
} //namespace chart
//.............................................................................
#endif
