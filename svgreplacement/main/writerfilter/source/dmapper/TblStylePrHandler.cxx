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

#include <TblStylePrHandler.hxx>
#include <PropertyMap.hxx>
#include <ooxml/resourceids.hxx>
#include <dmapperLoggers.hxx>
#include <resourcemodel/QNameToString.hxx>

#include "dmapperLoggers.hxx"

namespace writerfilter {
namespace dmapper {

TblStylePrHandler::TblStylePrHandler( DomainMapper & rDMapper ) :
LoggedProperties(dmapper_logger, "TblStylePrHandler"),
m_rDMapper( rDMapper ), 
m_pTablePropsHandler( new TablePropertiesHandler( true ) ),
m_nType( TBL_STYLE_UNKNOWN ),
m_pProperties( new PropertyMap )
{
}

TblStylePrHandler::~TblStylePrHandler( )
{
    delete m_pTablePropsHandler, m_pTablePropsHandler = NULL;
}

void TblStylePrHandler::lcl_attribute(Id rName, Value & rVal)
{
#ifdef DEBUG_DOMAINMAPPER
    dmapper_logger->startElement("TblStylePrHandler.attribute");
    dmapper_logger->attribute("name", (*QNameToString::Instance())(rName));
    dmapper_logger->chars(rVal.toString());
    dmapper_logger->endElement("TblStylePrHandler.attribute");
#endif

    switch ( rName )
    {
        case NS_ooxml::LN_CT_TblStyleOverrideType:
            {
                // The tokenid should be the same in the model.xml than
                // in the TblStyleType enum
                m_nType = TblStyleType( rVal.getInt( ) );
            }
            break;
    }
}

void TblStylePrHandler::lcl_sprm(Sprm & rSprm)
{
#ifdef DEBUG_DOMAINMAPPER
    dmapper_logger->startElement("TblStylePrHandler.sprm");
    dmapper_logger->attribute("sprm", rSprm.toString());
#endif

    Value::Pointer_t pValue = rSprm.getValue();
    switch ( rSprm.getId( ) )
    {
        case NS_ooxml::LN_CT_PPrBase:
        case NS_ooxml::LN_EG_RPrBase:
        case NS_ooxml::LN_CT_TblPrBase:
        case NS_ooxml::LN_CT_TrPrBase: 
        case NS_ooxml::LN_CT_TcPrBase:
            resolveSprmProps( rSprm );
            break;
        default:
            // Tables specific properties have to handled here
            m_pTablePropsHandler->SetProperties( m_pProperties );
            bool bRet = m_pTablePropsHandler->sprm( rSprm );

            if ( !bRet )
            {
                // The DomainMapper can handle some of the properties
                m_rDMapper.PushStyleSheetProperties( m_pProperties, true );
                m_rDMapper.sprm( rSprm );
                m_rDMapper.PopStyleSheetProperties( true );
            }
    }
    
#ifdef DEBUG_DOMAINMAPPER
    dmapper_logger->endElement("TblStylePrHandler.sprm");
#endif
}

void TblStylePrHandler::resolveSprmProps(Sprm & rSprm)
{
    writerfilter::Reference<Properties>::Pointer_t pProperties = rSprm.getProps();
    if( pProperties.get())
        pProperties->resolve(*this);
}

}}
