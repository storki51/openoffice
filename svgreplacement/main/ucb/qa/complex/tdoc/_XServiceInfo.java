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



package complex.tdoc;

import lib.MultiMethodTest;

import com.sun.star.lang.XServiceInfo;
import share.LogWriter;

/**
* Testing <code>com.sun.star.lang.XServiceInfo</code>
* interface methods :
* <ul>
*  <li><code> getImplementationName()</code></li>
*  <li><code> supportsService()</code></li>
*  <li><code> getSupportedServiceNames()</code></li>
* </ul> <p>
* Test is multithread compilant. <p>
* @see com.sun.star.lang.XServiceInfo
*/
public class _XServiceInfo {
    public static XServiceInfo oObj = null;
    public static String[] names = null;
    public LogWriter log = null;

    /**
    * Just calls the method.<p>
    * Has <b>OK</b> status if no runtime exceptions occured.
    */
    public boolean _getImplementationName() {
        boolean result = true;
        log.println("testing getImplementationName() ... ");

        log.println("The ImplementationName ist "+oObj.getImplementationName());
        result=true;

        return result;

    } // end getImplementationName()


    /**
    * Just calls the method.<p>
    * Has <b>OK</b> status if no runtime exceptions occured.
    */
    public boolean _getSupportedServiceNames() {
        boolean result = true;
        log.println("getting supported Services...");
        names = oObj.getSupportedServiceNames();
        for (int i=0;i<names.length;i++) {
           int k = i+1;
           log.println(k+". Supported Service is "+names[i]);
        }
        result=true;

        return result;

    } // end getSupportedServiceNames()

    /**
    * Gets one of the service names returned by
    * <code>getSupportedServiceNames</code> method and
    * calls the <code>supportsService</code> methos with this
    * name. <p>
    * Has <b>OK</b> status if <code>true</code> value is
    * returned.
    */
    public boolean _supportsService() {
        log.println("testing supportsService");
        names = oObj.getSupportedServiceNames();
        return oObj.supportsService(names[0]);
    } // end supportsService()
}

