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


package mod._forms;

import com.sun.star.beans.NamedValue;
import java.io.PrintWriter;

import lib.TestEnvironment;
import lib.TestParameters;
import util.DBTools;



/**
 * Test for object which is represented by service
 * <code>com.sun.star.form.component.PatternField</code>. <p>
 * Object implements the following interfaces :
 * <ul>
 *  <li> <code>com::sun::star::io::XPersistObject</code></li>
 *  <li> <code>com::sun::star::form::XReset</code></li>
 *  <li> <code>com::sun::star::form::XBoundComponent</code></li>
 *  <li> <code>com::sun::star::form::FormComponent</code></li>
 *  <li> <code>com::sun::star::beans::XFastPropertySet</code></li>
 *  <li> <code>com::sun::star::beans::XMultiPropertySet</code></li>
 *  <li> <code>com::sun::star::form::component::PatternField</code></li>
 *  <li> <code>com::sun::star::form::DataAwareControlModel</code></li>
 *  <li> <code>com::sun::star::form::XUpdateBroadcaster</code></li>
 *  <li> <code>com::sun::star::awt::UnoControlPatternFieldModel</code></li>
 *  <li> <code>com::sun::star::form::component::DatabasePatternField</code></li>
 *  <li> <code>com::sun::star::form::FormControlModel</code></li>
 *  <li> <code>com::sun::star::beans::XPropertyState</code></li>
 *  <li> <code>com::sun::star::container::XNamed</code></li>
 *  <li> <code>com::sun::star::lang::XComponent</code></li>
 *  <li> <code>com::sun::star::lang::XEventListener</code></li>
 *  <li> <code>com::sun::star::beans::XPropertyAccess</code></li>
*  <li> <code>com::sun::star::beans::XPropertyContainer</code></li>
*  <li> <code>com::sun::star::beans::XPropertySet</code></li>
 *  <li> <code>com::sun::star::form::XLoadListener</code></li>
 *  <li> <code>com::sun::star::container::XChild</code></li>
 * </ul> <p>
 *
 * This object test <b> is NOT </b> designed to be run in several
 * threads concurently.
 *
 * @see com.sun.star.io.XPersistObject
 * @see com.sun.star.form.XReset
 * @see com.sun.star.form.XBoundComponent
 * @see com.sun.star.form.FormComponent
 * @see com.sun.star.beans.XFastPropertySet
 * @see com.sun.star.beans.XMultiPropertySet
 * @see com.sun.star.form.component.PatternField
 * @see com.sun.star.form.DataAwareControlModel
 * @see com.sun.star.form.XUpdateBroadcaster
 * @see com.sun.star.awt.UnoControlPatternFieldModel
 * @see com.sun.star.form.component.DatabasePatternField
 * @see com.sun.star.form.FormControlModel
 * @see com.sun.star.beans.XPropertyState
 * @see com.sun.star.container.XNamed
 * @see com.sun.star.lang.XComponent
 * @see com.sun.star.lang.XEventListener
 * @see com.sun.star.beans.XPropertyAccess
* @see com.sun.star.beans.XPropertyContainer
* @see com.sun.star.beans.XPropertySet
 * @see com.sun.star.form.XLoadListener
 * @see com.sun.star.container.XChild
 * @see ifc.io._XPersistObject
 * @see ifc.form._XReset
 * @see ifc.form._XBoundComponent
 * @see ifc.form._FormComponent
 * @see ifc.beans._XFastPropertySet
 * @see ifc.beans._XMultiPropertySet
 * @see ifc.form.component._PatternField
 * @see ifc.form._DataAwareControlModel
 * @see ifc.form._XUpdateBroadcaster
 * @see ifc.awt._UnoControlPatternFieldModel
 * @see ifc.form.component._DatabasePatternField
 * @see ifc.form._FormControlModel
 * @see ifc.beans._XPropertyState
 * @see ifc.container._XNamed
 * @see ifc.lang._XComponent
 * @see ifc.lang._XEventListener
 * @see ifc.beans._XPropertySet
 * @see ifc.form._XLoadListener
 * @see ifc.container._XChild
 */
public class OPatternModel extends GenericModelTest {
    /**
     * Set some member variable of the super class <CODE>GenericModelTest</CODE>:
     * <pre>
     *    super.m_ChangePropertyName = "Text";
     *    super.m_kindOfControl="PatternField";
     *    super.m_ObjectName = "stardiv.one.form.component.PatternField";
     *    NamedValue DataField = new NamedValue();
     *    DataField.Name = "DataField";
     *    DataField.Value = DBTools.TST_STRING_F;
     *    super.m_propertiesToSet.add(DataField);
     *
     *    super.m_LCShape_Type = "FixedText";
     * </pre>
     * Then <CODE>super.initialize()</CODE> was called.
     * @param tParam the test parameter
     * @param log the log writer
     */
    protected void initialize(TestParameters tParam, PrintWriter log) {
        
        super.initialize(tParam, log);

        super.m_ChangePropertyName = "Text";
        
        super.m_kindOfControl="PatternField";
        
        super.m_ObjectName = "stardiv.one.form.component.PatternField";

        NamedValue DataField = new NamedValue(); 
        DataField.Name = "DataField"; 
        DataField.Value = DBTools.TST_STRING_F; 
        super.m_propertiesToSet.add(DataField);
        
        super.m_LCShape_Type = "FixedText";

    }    /**
     * calls <CODE>cleanup()</CODE> from it's super class
     * @param tParam the test parameter
     * @param log the log writer
     */
    protected void cleanup(TestParameters tParam, PrintWriter log) {
        super.cleanup(tParam, log);
    }
    

    /**
     * calls <CODE>createTestEnvironment()</CODE> from it's super class
     * @param Param the test parameter
     * @param log the log writer
     * @return lib.TestEnvironment
     */
    protected synchronized TestEnvironment createTestEnvironment(TestParameters Param, 
                                                                 PrintWriter log) {
        return super.createTestEnvironment(Param, log);
    }

} // finish class OPatternModel
