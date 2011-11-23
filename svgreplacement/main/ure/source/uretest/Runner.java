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



package test.java.runner;

import java.net.URL;
import com.sun.star.lib.unoloader.UnoLoader;

public final class Runner {
    public static void main(String[] arguments) throws Exception {
        String[] args = new String[arguments.length - 2];
        System.arraycopy(arguments, 2, args, 0, args.length);
        UnoLoader.execute(new URL(arguments[0]), new URL(arguments[1]), args);
    }

    private Runner() {}
}
