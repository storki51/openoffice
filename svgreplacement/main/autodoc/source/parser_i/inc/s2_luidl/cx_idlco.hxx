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



#ifndef LUIDL_CX_IDLCO_HXX
#define LUIDL_CX_IDLCO_HXX

// USED SERVICES
	// BASE CLASSES
#include <tokens/tkpcont2.hxx>
	// COMPONENTS
#include <tokens/tkpstam2.hxx>
	// PARAMETERS


namespace csi
{
namespace uidl
{

class Token_Receiver;
class Token;

/**
*/
class Context_UidlCode : public TkpContext,
						 private StateMachineContext
{
  public:
	// 	LIFECYCLE
						Context_UidlCode(
							Token_Receiver &	o_rReceiver,
							DYN TkpDocuContext &
												let_drContext_Docu	);
						~Context_UidlCode();
	//	OPERATORS

	//	OPERATIONS
	virtual void		ReadCharChain(
							CharacterSource &	io_rText );
	virtual bool		PassNewToken();

	//	INQUIRY
	virtual TkpContext &
						FollowUpContext();
  private:
	//	SERVICE FUNCTIONS
	void				PerformStatusFunction(
							uintt				i_nStatusSignal,
							UINT16 	      	    i_nTokenId,
							CharacterSource &	io_rText );
	void				SetupStateMachine();

	//	DATA
	StateMachin2		aStateMachine;
	Token_Receiver *	pReceiver;

		// Contexts
	Dyn<TkpDocuContext>	pDocuContext;

	Dyn<TkpContext>    dpContext_MLComment;
	Dyn<TkpContext>    dpContext_SLComment;
	Dyn<TkpContext>    dpContext_Preprocessor;
	Dyn<TkpContext>    dpContext_Assignment;

		// Temporary data, used during ReadCharChain()
	Dyn<Token>			pNewToken;
	::TkpContext *		pFollowUpContext;
};


}   // namespace uidl
}   // namespace csi

#endif
