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



package ifc.drawing;

import lib.MultiMethodTest;
import util.FormTools;

import com.sun.star.awt.XControlModel;
import com.sun.star.drawing.XControlShape;
import com.sun.star.lang.XComponent;
import com.sun.star.uno.UnoRuntime;
import com.sun.star.uno.XInterface;

/**
* Testing <code>com.sun.star.drawing.XControlShape</code>
* interface methods :
* <ul>
*  <li><code> getControl()</code></li>
*  <li><code> setControl()</code></li>
* </ul> <p>
* This test needs the following object relations :
* <ul>
*  <li> <code>'xDoc'</code> (of type <code>XComponent</code>):
*   the document where shape tested is situated. This document
*   must also implement <code>XMultiServiceFactory</code> interface
*   to create some control model. </li>
* <ul> <p>
* Test is <b> NOT </b> multithread compilant. <p>
* @see com.sun.star.drawing.XControlShape
*/
public class _XControlShape extends MultiMethodTest {

    public XControlShape oObj = null;

    XControlModel model = null;

    /**
    * Test calls the method. <p>
    * Has <b> OK </b> status if the method successfully returns
    * and no exceptions were thrown. <p>
    */
    public void _getControl() {
        model = oObj.getControl() ;

        tRes.tested("getControl()", true) ;
    }

    /**
    * With the help of document passed as relation, a new button control
    * model is created and set as a control. <p>
    * Has <b> OK </b> status if <code>getControl()</code> method returns
    * the same control as was set. <p>
    * The following method tests are to be completed successfully before :
    * <ul>
    *  <li> <code> getControl() </code>  </li>
    * </ul>
    */
    public void _setControl() {
        requiredMethod("getControl()") ;

        XInterface oNewControl = FormTools.createControl
            ((XComponent)tEnv.getObjRelation("xDoc"), "ComboBox") ;

        XControlModel xControl = (XControlModel) UnoRuntime.queryInterface
            (XControlModel.class, oNewControl) ;

        oObj.setControl(xControl) ;

        XControlModel gControl = oObj.getControl() ;

        if (oNewControl.equals(gControl))
            tRes.tested("setControl()", true) ;
        else {
            log.println("Control set is not equal to control get") ;
            tRes.tested("setControl()", false) ;
        }
    }

}  // finish class _XControlShape


