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



#ifndef _REPORT_RPTUICLIP_HXX
#define _REPORT_RPTUICLIP_HXX

#include <svtools/transfer.hxx>
#include <com/sun/star/beans/NamedValue.hpp>

namespace rptui
{
//============================================================================
// OReportExchange
//============================================================================
/** \class OReportExchange 
 * \brief defines a clipboard fromat for copying selection elements.
 * \ingroup reportdesign_source_ui_report
 *
 *
 */
class OReportExchange : public TransferableHelper
{
public:
    typedef ::com::sun::star::uno::Sequence< ::com::sun::star::beans::NamedValue > TSectionElements;

    /** Constructs a new exchange object with section elements
    *
    * \param _rCopyElements the elements to copy. Each section is one entry. The value must be a sequence of elements.
    * \return 
    */
    OReportExchange( const TSectionElements& _rCopyElements);

    /** checks whether or not a descriptor can be extracted from the data flavor vector given
    *
    * \param _rFlavors 
            available flavors
    * \return 
    */
	static sal_Bool         canExtract(const DataFlavorExVector& _rFlavors);

    /** extract the section elements
    *
    * \param _rData the clipboard data
    * \return the copied elements
    */
    static TSectionElements extractCopies(const TransferableDataHelper& _rData);

    /** returns the format id.
    *
    * \return the registered format id
    */
    static sal_uInt32	    getDescriptorFormatId();

protected:
	// TransferableHelper overridables
	virtual void		AddSupportedFormats();
	virtual sal_Bool	GetData( const ::com::sun::star::datatransfer::DataFlavor& rFlavor );	
private:
    TSectionElements	m_aCopyElements;
};
}
#endif // _REPORT_RPTUICLIP_HXX
