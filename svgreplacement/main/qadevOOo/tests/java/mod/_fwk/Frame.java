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



package mod._fwk;

import java.io.PrintWriter;

import lib.StatusException;
import lib.TestCase;
import lib.TestEnvironment;
import lib.TestParameters;
import util.SOfficeFactory;

import com.sun.star.frame.XFrame;
import com.sun.star.lang.XMultiServiceFactory;
import com.sun.star.text.XTextDocument;
import com.sun.star.uno.UnoRuntime;
import com.sun.star.uno.XInterface;
import com.sun.star.util.XCloseable;

/**
* Test for object that implements the following interfaces :
* <ul>
*  <li><code>com::sun::star::frame::XDispatchProvider</code></li>
*  <li><code>com::sun::star::frame::XFrame</code></li>
*  <li><code>com::sun::star::frame::XFramesSupplier</code></li>
*  <li><code>com::sun::star::task::XStatusIndicatorFactory</code></li>
*  <li><code>com::sun::star::lang::XComponent</code></li>
* </ul><p>
* @see com.sun.star.frame.XDispatchProvider
* @see com.sun.star.frame.XFrame
* @see com.sun.star.frame.XFramesSupplier
* @see com.sun.star.task.XStatusIndicatorFactory
* @see com.sun.star.lang.XComponent
* @see ifc.frame._XDispatchProvider
* @see ifc.frame._XFrame
* @see ifc.frame._XFramesSupplier
* @see ifc.task._XStatusIndicatorFactory
* @see ifc.lang._XComponent
*/
public class Frame extends TestCase {

    XTextDocument xTextDoc;
    XFrame frame = null;


    /**
    * Creates a text document and obtains a frame of current controller.
    */
    public TestEnvironment createTestEnvironment( TestParameters Param,
        PrintWriter log ) throws StatusException {

        XInterface oObj = null;

        log.println( "creating a test environment" );

        // get a soffice factory object
        SOfficeFactory SOF = SOfficeFactory.getFactory( (XMultiServiceFactory)Param.getMSF());

        try {
            log.println( "creating a text document" );
            xTextDoc = SOF.createTextDoc(null);
        } catch ( com.sun.star.uno.Exception e ) {
            // Some exception occures.FAILED
            e.printStackTrace( log );
            throw new StatusException( "Couldn't create document", e );
        }

        frame = xTextDoc.getCurrentController().getFrame();
        oObj = (XInterface)UnoRuntime.queryInterface(XInterface.class, frame);

        log.println(util.utils.getImplName(oObj));

        TestEnvironment tEnv = new TestEnvironment( oObj );
        
        tEnv.addObjRelation("XDispatchProvider.URL",
            ".uno:SwitchControlDesignMode");

        return tEnv;
    } // finish method getTestEnvironment


    /**
     * Disposes the document created and finally disposes
     * the frame containing the document (for case when the frame
     * contains no model after some interafce manipulations).
     */
    protected void cleanup( TestParameters Param, PrintWriter log) {
        try {
            XCloseable xTextClose = (XCloseable) UnoRuntime.queryInterface(XCloseable.class, xTextDoc);
            xTextClose.close(true);
        } catch(Exception e){}

    }
}
