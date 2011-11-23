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



#include <documentfragment.hxx>

namespace DOM
{
    CDocumentFragment::CDocumentFragment(
            CDocument const& rDocument, ::osl::Mutex const& rMutex,
            xmlNodePtr const pNode)
        : CDocumentFragment_Base(rDocument, rMutex,
                NodeType_DOCUMENT_FRAGMENT_NODE, pNode)
    {
    }

    bool CDocumentFragment::IsChildTypeAllowed(NodeType const nodeType)
    {
        switch (nodeType) {
            case NodeType_ELEMENT_NODE:
            case NodeType_PROCESSING_INSTRUCTION_NODE:
            case NodeType_COMMENT_NODE:
            case NodeType_TEXT_NODE:
            case NodeType_CDATA_SECTION_NODE:
            case NodeType_ENTITY_REFERENCE_NODE:
                return true;
            default:
                return false;
        }
    }

    OUString SAL_CALL CDocumentFragment::getNodeName()throw (RuntimeException)
    {
        return OUString::createFromAscii("#document-fragment");
    }
    OUString SAL_CALL CDocumentFragment::getNodeValue() throw (RuntimeException)
    {
        return OUString();
    }
}
