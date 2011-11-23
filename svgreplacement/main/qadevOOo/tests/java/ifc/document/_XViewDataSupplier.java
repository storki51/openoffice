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


package ifc.document;

import com.sun.star.beans.PropertyValue;
import com.sun.star.container.XIndexAccess;
import com.sun.star.container.XIndexContainer;
import com.sun.star.document.XViewDataSupplier;
import com.sun.star.uno.UnoRuntime;
import lib.MultiMethodTest;
import lib.Status;

/**
 * Check the XViewDataSupplier interface.
 * Test idea: take the property values from the index access, change one 
 * property value, put this into the index access and write it back.
 * Get the property value again and check that the change made it.
 */
public class _XViewDataSupplier extends MultiMethodTest {
    public XViewDataSupplier oObj = null;
    XIndexAccess xAccess = null;
    PropertyValue[] newProps = null;
    PropertyValue[] oldProps = null;
    String myview = "myview1";
    
    public void _getViewData() {
        xAccess = oObj.getViewData();
//        util.dbg.printInterfaces(xAccess);
        if (xAccess != null) {
            setViewID(xAccess, myview);
        }
        tRes.tested("getViewData()", true);
    }
    
    public void _setViewData() {
        if (xAccess == null) {
            log.println("No view data to change available");
            tRes.tested("setViewData()", Status.skipped(true));
        } 
        else {
            // 2do: provide an own implementation of the XIndexAccess to set.
            // this will work without "setViewData()", it just checks that a 
            // setViewData can be done.
            oObj.setViewData(xAccess);
            XIndexAccess xAccess2 = oObj.getViewData();
            String newView = getViewID(xAccess2);
            tRes.tested("setViewData()", newView.equals(myview));
        }
    }
    
    private void setViewID(XIndexAccess xAccess, String value) {
        XIndexContainer xIndexContainer = (XIndexContainer)UnoRuntime.queryInterface(XIndexContainer.class, xAccess);
        int count = xAccess.getCount();
        try {
            if (count > 0) {
                oldProps = (PropertyValue[])xAccess.getByIndex(0);
                newProps = new PropertyValue[oldProps.length];
                for (int j=0; j<oldProps.length; j++) {
//                    log.println("Name: " + oldProps[j].Name);
//                    log.println("Value: " + oldProps[j].Value.toString());
                    newProps[j] = new PropertyValue();
                    newProps[j].Name = oldProps[j].Name;
                    newProps[j].Handle = oldProps[j].Handle;
                    newProps[j].State = oldProps[j].State;
                    if (oldProps[j].Name.equals("ViewId")) {
                        newProps[j].Value = value;
                    }

                }
                xIndexContainer.insertByIndex(0, newProps);
            }
        }
        catch(Exception e) {
            e.printStackTrace((java.io.PrintWriter)log);
        }
    }
    
    private String getViewID(XIndexAccess xAccess) {
        String retValue = null;
        int count = xAccess.getCount();
        try {
            if (count > 0) {
                oldProps = (PropertyValue[])xAccess.getByIndex(0);
                for (int j=0; j<oldProps.length; j++) {
//                    log.println("Name: " + oldProps[j].Name);
//                    log.println("Value: " + oldProps[j].Value.toString());
                    if (oldProps[j].Name.equals("ViewId")) {
                        retValue = (String)newProps[j].Value;
                    }

                }
            }
        }
        catch(Exception e) {
            e.printStackTrace((java.io.PrintWriter)log);
        }
        return retValue;
    }
}
