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

import com.sun.star.script.provider.XScriptContext;

import com.sun.star.uno.UnoRuntime;
import com.sun.star.frame.XComponentLoader;
import com.sun.star.lang.XComponent;
import com.sun.star.text.XTextDocument;
import com.sun.star.text.XTextRange;
import com.sun.star.text.XText;
import com.sun.star.beans.PropertyValue;
import com.sun.star.awt.ActionEvent;

public class SayHello
{
    public static void start(XScriptContext ctxt, ActionEvent e)
        throws Exception
    {
        SayHello.start(ctxt);
    }
    
    public static void start(XScriptContext ctxt)
        throws Exception
    {
        // getting the text document object
        XTextDocument xTextDocument = createDocument(ctxt);

        XText xText = xTextDocument.getText();
        XTextRange xTextRange = xText.getEnd();
        xTextRange.setString("Hello");
    }

    private static XTextDocument createDocument(XScriptContext ctxt)
        throws Exception
    {
        XComponentLoader loader = (XComponentLoader)
            UnoRuntime.queryInterface(
                XComponentLoader.class, ctxt.getDesktop());

        XComponent comp = loader.loadComponentFromURL(
            "private:factory/swriter", "_blank", 4, new PropertyValue[0]);

        XTextDocument doc = (XTextDocument)
            UnoRuntime.queryInterface( XTextDocument.class, comp);

        return doc;
    }
}
