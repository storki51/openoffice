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



package mod._rdbtdp;

import java.io.PrintWriter;

import lib.Status;
import lib.StatusException;
import lib.TestCase;
import lib.TestEnvironment;
import lib.TestParameters;

import com.sun.star.beans.XPropertySet;
import com.sun.star.container.XEnumeration;
import com.sun.star.container.XEnumerationAccess;
import com.sun.star.lang.XMultiServiceFactory;
import com.sun.star.uno.AnyConverter;
import com.sun.star.uno.Type;
import com.sun.star.uno.UnoRuntime;
import com.sun.star.uno.XComponentContext;
import com.sun.star.uno.XInterface;

/**
* Test for object which is represented by service
* <code>com.sun.star.reflection.TypeDescriptionProvider</code>. <p>
* Object implements the following interfaces :
* <ul>
*  <li> <code>com::sun::star::container::XHierarchicalNameAccess</code></li>
*  <li> <code>com::sun::star::lang::XComponent</code></li>
* </ul>
* This object test <b> is NOT </b> designed to be run in several
* threads concurently.
* @see com.sun.star.container.XHierarchicalNameAccess
* @see com.sun.star.lang.XComponent
* @see com.sun.star.reflection.TypeDescriptionProvider
* @see ifc.container._XHierarchicalNameAccess
* @see ifc.lang._XComponent
*/
public class RegistryTypeDescriptionProvider extends TestCase {

    protected void initialize ( TestParameters Param, PrintWriter log) {

    }

    /**
    * Creating a Testenvironment for the interfaces to be tested.
    * Creates an instance of the service
    * <code>com.sun.star.reflection.TypeDescriptionProvider</code>.
    *     Object relations created :
    * <ul>
    *  <li> <code>'ElementName'</code> for
    *      {@link ifc.container._XHierarchicalNameAccess} :
    *      name of the existing element. Here it type name for
    *      <code>com.sun.star.uno.XInterface</code> interface.</li>
    * </ul>
    */
    public TestEnvironment createTestEnvironment( TestParameters Param,
                                                  PrintWriter log )
                                                    throws StatusException {
        XInterface oObj = null;
        Object oInterface = null;

        try {
            XMultiServiceFactory xMSF = (XMultiServiceFactory)Param.getMSF();
            XPropertySet xProp = (XPropertySet)UnoRuntime.queryInterface(
                                                XPropertySet.class, xMSF);
            // get context
            XComponentContext xContext = (XComponentContext)
                            UnoRuntime.queryInterface(XComponentContext.class,
                            xProp.getPropertyValue("DefaultContext"));
            // get the type description manager
            Object o = xContext.getValueByName("/singletons/" +
                        "com.sun.star.reflection.theTypeDescriptionManager");
            // the manager contains all providers
            XEnumerationAccess aProviderAccess = (XEnumerationAccess)
                        UnoRuntime.queryInterface(XEnumerationAccess.class, o);
            // collect enumeration
            XEnumeration xProviderEnum;
            if (aProviderAccess.hasElements())
                xProviderEnum = aProviderAccess.createEnumeration();
            else
                throw new lib.StatusException(Status.failed(
                                        "No TypeDescriptionProvider given"));
            // take the first registry type description provider
            oInterface = xProviderEnum.nextElement();
            oObj = (XInterface) AnyConverter.toObject(
                            new Type(XInterface.class),oInterface);
        }
        catch( com.sun.star.uno.Exception e ) {
            log.println("Service not available" );
        }

        //oObj = (XInterface) oInterface;

        log.println( "    creating a new environment for object" );
        TestEnvironment tEnv = new TestEnvironment( oObj );

        // adding relation for XHierarchicalNameAccess
        tEnv.addObjRelation("ElementName", "com.sun.star.uno.XInterface") ;
        tEnv.addObjRelation("SearchString", "com.sun.star.loader");

        return tEnv;
    } // finish method getTestEnvironment

}

