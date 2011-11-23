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



#include "precompiled_configmgr.hxx"
#include "sal/config.h"

#include "rtl/ref.hxx"
#include "rtl/ustring.hxx"

#include "data.hxx"
#include "groupnode.hxx"
#include "node.hxx"
#include "nodemap.hxx"

namespace configmgr {

GroupNode::GroupNode(
    int layer, bool extensible, rtl::OUString const & templateName):
    Node(layer), extensible_(extensible), templateName_(templateName),
    mandatory_(Data::NO_LAYER)
{}

rtl::Reference< Node > GroupNode::clone(bool keepTemplateName) const {
    return new GroupNode(*this, keepTemplateName);
}

NodeMap & GroupNode::getMembers() {
    return members_;
}

rtl::OUString GroupNode::getTemplateName() const {
    return templateName_;
}

void GroupNode::setMandatory(int layer) {
    mandatory_ = layer;
}

int GroupNode::getMandatory() const {
    return mandatory_;
}

bool GroupNode::isExtensible() const {
    return extensible_;
}

GroupNode::GroupNode(GroupNode const & other, bool keepTemplateName):
    Node(other), extensible_(other.extensible_), mandatory_(other.mandatory_)
{
    cloneNodeMap(other.members_, &members_);
    if (keepTemplateName) {
        templateName_ = other.templateName_;
    }
}

GroupNode::~GroupNode() {}

Node::Kind GroupNode::kind() const {
    return KIND_GROUP;
}

void GroupNode::clear() {
    members_.clear();
}

}
