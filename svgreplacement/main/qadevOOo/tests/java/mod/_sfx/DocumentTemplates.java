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



package mod._sfx;

import java.io.PrintWriter;

import lib.StatusException;
import lib.TestCase;
import lib.TestEnvironment;
import lib.TestParameters;

import com.sun.star.frame.XStorable;
import com.sun.star.lang.XMultiServiceFactory;
import com.sun.star.text.XTextDocument;
import com.sun.star.uno.UnoRuntime;
import com.sun.star.uno.XInterface;

/**
 * Test for object which is represented by service
 * <code>com.sun.star.frame.DocumentTemplates</code>. <p>
 *
 * Object implements the following interfaces :
 * <ul>
 *  <li> <code>com::sun::star::frame::XDocumentTemplates</code></li>
 * </ul> <p>
 *
 */
public class DocumentTemplates extends TestCase {

    XTextDocument xTextDoc;

    protected void initialize( TestParameters tParam, PrintWriter log ) {
        String aURL=util.utils.getFullTestURL("report2.stw");
        xTextDoc = util.WriterTools.loadTextDoc((XMultiServiceFactory)tParam.getMSF(),aURL);
    }

    protected void cleanup( TestParameters tParam, PrintWriter log ) {
        log.println( "    disposing xTextDoc " );
        xTextDoc.dispose();
    }

    /**
     * Creating a Testenvironment for the interfaces to be tested.
     * Creates an instance of the service
     * <code>com.sun.star.frame.DocumentTemplates</code>.
    */
    protected TestEnvironment createTestEnvironment
            (TestParameters tParam, PrintWriter log) {

        XMultiServiceFactory xMSF = (XMultiServiceFactory)tParam.getMSF();
        XInterface oObj = null;
        XStorable store = null;

        try {
            oObj = (XInterface)xMSF.createInstance
                ("com.sun.star.frame.DocumentTemplates");
            store = (XStorable) UnoRuntime.queryInterface
                (XStorable.class,xTextDoc);
        } catch (com.sun.star.uno.Exception e) {
            e.printStackTrace(log);
            throw new StatusException("Unexpected exception", e);
        }

        String Iname = util.utils.getImplName(oObj);
        log.println("Implementation Name: "+Iname);
        TestEnvironment tEnv = new TestEnvironment(oObj);
        tEnv.addObjRelation("Store",store);
        return tEnv;
    }

}    // finish class TestCase

