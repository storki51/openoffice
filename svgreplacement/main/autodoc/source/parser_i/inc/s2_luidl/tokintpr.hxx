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



#ifndef ADC_LUIDL_TOKINTPR_HXX
#define ADC_LUIDL_TOKINTPR_HXX



// USED SERVICES
	// BASE CLASSES
	// COMPONENTS
	// PARAMETERS

namespace csi
{
namespace uidl
{


class TokIdentifier;
class TokPunctuation;
class TokBuiltInType;
class TokTypeModifier;
class TokMetaType;
class TokStereotype;
class TokParameterHandling;
class TokAssignment;
class Tok_Documentation;


class TokenInterpreter
{
  public:
	virtual				~TokenInterpreter() {}

	virtual void		Process_Identifier(
							const TokIdentifier &
												i_rToken ) = 0;
	virtual void		Process_NameSeparator() = 0;      // ::
	virtual void		Process_Punctuation(
							const TokPunctuation &
												i_rToken ) = 0;
	virtual void		Process_BuiltInType(
							const TokBuiltInType &
												i_rToken ) = 0;
	virtual void		Process_TypeModifier(
							const TokTypeModifier &
												i_rToken ) = 0;
	virtual void		Process_MetaType(
							const TokMetaType &	i_rToken ) = 0;
	virtual void		Process_Stereotype(
							const TokStereotype &
												i_rToken ) = 0;
	virtual void		Process_ParameterHandling(
							const TokParameterHandling &
												i_rToken ) = 0;
	virtual void		Process_Raises() = 0;
	virtual void		Process_Needs() = 0;
	virtual void		Process_Observes() = 0;
	virtual void		Process_Assignment(
							const TokAssignment &
												i_rToken ) = 0;
	virtual void		Process_EOL() = 0;
};



// IMPLEMENTATION


}   // namespace uidl
}   // namespace csi

#endif
