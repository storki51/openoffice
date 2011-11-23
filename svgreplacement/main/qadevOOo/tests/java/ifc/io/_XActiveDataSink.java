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



package ifc.io;

import lib.MultiMethodTest;

import com.sun.star.io.XActiveDataSink;
import com.sun.star.io.XInputStream;
import com.sun.star.uno.UnoRuntime;
import com.sun.star.uno.XInterface;

/**
* Testing <code>com.sun.star.io.XActiveDataSink</code>
* interface methods :
* <ul>
*  <li><code> setInputStream()</code></li>
*  <li><code> getInputStream()</code></li>
* </ul> <p>
* Test is <b> NOT </b> multithread compilant. <p>
*
* This test needs the following object relations :
* <ul>
*  <li> <code>'InputStream'</code>
*  (of type <code>com.sun.star.io.XInputStream</code>):
*   acceptable input stream which can be set by <code>setInputStream</code> </li>
* <ul> <p>
*
* After test completion object environment has to be recreated.
* @see com.sun.star.io.XActiveDataSink
*/
public class _XActiveDataSink extends MultiMethodTest {

    public XActiveDataSink oObj = null;

    private XInputStream iStream = null;

        /**
        * Take the XInputStream from the environment for setting and getting
    */
    public void before() {
            XInterface x = (XInterface)tEnv.getObjRelation("InputStream");
            iStream = (XInputStream) UnoRuntime.queryInterface
                    (XInputStream.class, x) ;
    }

    /**
    * Just sets new input stream. <p>
    * Has <b>OK</b> status if no runtime exceptions occured.
    */
    public void _setInputStream() {
        oObj.setInputStream(iStream) ;

        tRes.tested("setInputStream()", true) ;
    }

    /**
    * First retrieves current input stream, then sets to new
    * input stream (if old was <code>null</code>) or to null.
    * Then input stream retrieved again and checked to be not
    * equal to the old one. <p>
    * Has <b>OK</b> status if old and new streams retrieved are
    * not equal. <p>
    * The following method tests are to be completed successfully before :
    * <ul>
    *  <li> <code> setInputStream() </code> : to be sure the method
    *   works without exceptions. </li>
    * </ul>
    */
    public void _getInputStream() {
        requiredMethod("setInputStream()") ;

        Object oldStream = oObj.getInputStream() ;
        XInputStream newStream = oldStream == null ? iStream : null ;

        oObj.setInputStream(newStream) ;
        Object getStream = oObj.getInputStream() ;

                tRes.tested("getInputStream()", getStream != oldStream) ;
    }

    public void after() {
        this.disposeEnvironment() ;
    }
}


