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



package ifc.text;

import com.sun.star.container.XNameAccess;
import com.sun.star.text.XBookmarksSupplier;
import lib.MultiMethodTest;


/**
 * Testing <code>com.sun.star.text.XBookmarksSupplier</code>
 * interface methods :
 * <ul>
 *  <li><code> getBookmarks()</code></li>
 * </ul> <p>
 * Test is <b> NOT </b> multithread compilant. <p>
 * @see com.sun.star.text.XBookmarksSupplier
 */
public class _XBookmarksSupplier extends MultiMethodTest {

    public static XBookmarksSupplier oObj = null;

    /**
     * Test calls the method. <p>
     * Has <b> OK </b> status if the collection returned has at least
     * one element.
     */
    public void _getBookmarks() {
        boolean res = false;

        XNameAccess the_bookmarks = oObj.getBookmarks();
        log.println("Found: ");
        util.dbg.printArray(the_bookmarks.getElementNames());
        res = the_bookmarks.getElementNames().length>0;

        tRes.tested("getBookmarks()",res);
    }

}  // finish class _XBookmarksSupplier
