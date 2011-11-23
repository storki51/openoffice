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



// autogenerated file with codegen.pl

#include <basegfx/vector/b2isize.hxx>
#include <basegfx/point/b2ipoint.hxx>

#include <basebmp/color.hxx>
#include <basebmp/bitmapdevice.hxx>

using namespace ::basebmp;

int countPixel( const BitmapDeviceSharedPtr& rDevice,
                Color                        checkColor )
{
    int count(0);
    const basegfx::B2ISize& rSize( rDevice->getSize() );
    for( sal_Int32 y=0; y<rSize.getY(); ++y )
        for( sal_Int32 x=0; x<rSize.getX(); ++x )
            if( rDevice->getPixel( basegfx::B2IPoint(x,y) ) == checkColor )
                ++count;

    return count;
}
