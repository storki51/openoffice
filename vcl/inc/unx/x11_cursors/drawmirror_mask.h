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


#define drawmirror_mask_width 32
#define drawmirror_mask_height 32
static char drawmirror_mask_bits[] = {
   0x00, 0x00, 0x04, 0x00, 0xfe, 0x0f, 0x0e, 0x00, 0xfe, 0x0f, 0x1f, 0x00,
   0xfe, 0x8f, 0x3f, 0x00, 0xfe, 0x0f, 0x1f, 0x00, 0xfe, 0x8f, 0x0f, 0x00,
   0xbe, 0x8f, 0x0f, 0x00, 0xbe, 0xcf, 0x07, 0x00, 0xbe, 0xcf, 0x87, 0x00,
   0xbe, 0xef, 0xc3, 0x01, 0xbe, 0xef, 0xe3, 0x03, 0xfe, 0xff, 0xf1, 0x07,
   0xfe, 0xff, 0x79, 0x0f, 0xfe, 0xff, 0x3c, 0x1e, 0xfe, 0xff, 0x1e, 0x3c,
   0xfe, 0x7f, 0x0f, 0x1e, 0x00, 0xfc, 0x07, 0x0f, 0x00, 0xfe, 0x83, 0x07,
   0x00, 0xbe, 0xc7, 0x03, 0x00, 0x1f, 0xef, 0x01, 0x00, 0x1f, 0xfe, 0x00,
   0x80, 0x0f, 0x7c, 0x00, 0xc0, 0x1d, 0x38, 0x00, 0x80, 0x0f, 0x10, 0x00,
   0x00, 0x07, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
