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



package ifc.container;

import lib.MultiMethodTest;

import com.sun.star.container.XEnumeration;
import com.sun.star.container.XEnumerationAccess;


/**
* Testing <code>com.sun.star.container.XEnumerationAccess</code>
* interface methods. <p>
* Test is multithread compilant. <p>
*/
public class _XEnumerationAccess extends MultiMethodTest{
    public XEnumerationAccess oObj = null;

    /**
    * Test calls the method and checks return value. <p>
    * Has <b> OK </b> status if the method returns not null value. <p>
    */
    public void _createEnumeration(){
        log.println( "createing Enumeration" );
        XEnumeration oEnum = oObj.createEnumeration();
        tRes.tested( "createEnumeration()", oEnum != null );
        return;
    } // end createEnumeration()
}  // finish class _XEnumerationAccess



