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


package com.sun.star.report;

/**
 * Making this enumeration typesafe and fully defined here would
 * be nice, wouldn't it?
 */
public class ReportEngineParameterNames
{

    public static final String CONTENT_TYPE = "content-type";
    public static final String INPUT_NAME = "input.name";
    public static final String INPUT_REPOSITORY = "input.repository";
    public static final String OUTPUT_NAME = "output.name";
    public static final String OUTPUT_REPOSITORY = "output.repository";
    public static final String INPUT_DATASOURCE_FACTORY = "input.datasource-factory";
    public static final String IMAGE_SERVICE = "ImageService";
    public static final String INPUT_REPORTJOB_FACTORY = "input.reportjob-factory";
    public static final String INPUT_MASTER_COLUMNS = "input.master-columns";
    public static final String INPUT_MASTER_VALUES = "input.master-values";
    public static final String INPUT_DETAIL_COLUMNS = "input.detail-columns";
    public static final String MIMETYPE = "output.mimetype";
    public static final String AUTHOR = "Author";
    public static final String TITLE = "Title";
    public static final String MAXROWS = "MaxRows";

    private ReportEngineParameterNames()
    {
    }
}
