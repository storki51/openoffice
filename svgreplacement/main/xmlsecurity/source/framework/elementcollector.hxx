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



#ifndef _ELEMENTCOLLECTOR_HXX
#define _ELEMENTCOLLECTOR_HXX

#include "elementmark.hxx"
#include <com/sun/star/xml/crypto/sax/XReferenceResolvedListener.hpp>
#include <com/sun/star/xml/crypto/sax/ElementMarkPriority.hpp>

class ElementCollector : public ElementMark
/****** elementcollector.hxx/CLASS ElementCollector ***************************
 *
 *   NAME
 *	ElementCollector -- Class to manipulate an element collector
 *
 *   FUNCTION
 *	This class is derived from the ElementMark class. Beyond the function
 *	of the ElementMark class, this class also maintains the priority, and
 *	manages the notify process
 *
 *   HISTORY
 *	05.01.2004 -	implemented
 *
 *   AUTHOR
 *	Michael Mi
 *	Email: michael.mi@sun.com
 ******************************************************************************/
{
private:
	/*
	 * the notify priority, is one of following values:
	 * AFTERMODIFY  - this ElementCollector will notify after all
	 *                    internal modifications have finished.
	 * BEFOREMODIFY - this ElementCollector must notify before any
	 *                    internal modification happens.
	 */
	com::sun::star::xml::crypto::sax::ElementMarkPriority m_nPriority;
	
	/*
	 * the modify flag, representing whether which elementcollector will
	 * modify its data.
	 */
	bool m_bToModify;
	
	/* the notify enable flag, see notifyListener method */
	bool m_bAbleToNotify;
	
	/* whether the listener has been notified */
	bool m_bNotified;
	
	/* the listener to be notified */
	com::sun::star::uno::Reference<
		com::sun::star::xml::crypto::sax::XReferenceResolvedListener > m_xReferenceResolvedListener;
	
public:
	ElementCollector(
		sal_Int32 nSecurityId,
		sal_Int32 nBufferId,
		com::sun::star::xml::crypto::sax::ElementMarkPriority nPriority,
		bool bToModify,
		const com::sun::star::uno::Reference<
			com::sun::star::xml::crypto::sax::XReferenceResolvedListener >&
			xReferenceResolvedListener);
	virtual ~ElementCollector() {};
	
	//bool isInternalNotificationSuppressed() const;
	com::sun::star::xml::crypto::sax::ElementMarkPriority getPriority() const;
	bool getModify() const;
	void notifyListener();
	bool isAbleToNotify() const;
	void setReferenceResolvedListener(
		const com::sun::star::uno::Reference<
			com::sun::star::xml::crypto::sax::XReferenceResolvedListener >&
			referenceResolvedListener);
	void setSecurityId(sal_Int32 nSecurityId);
	void doNotify();
	ElementCollector* clone(
		sal_Int32 nId,
		com::sun::star::xml::crypto::sax::ElementMarkPriority nPriority ) const;
};

#endif

