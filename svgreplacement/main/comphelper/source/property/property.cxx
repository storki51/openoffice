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



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_comphelper.hxx"


#include <comphelper/property.hxx>
#include <comphelper/sequence.hxx>
#include <comphelper/types.hxx>
#include <osl/diagnose.h>

#if OSL_DEBUG_LEVEL > 0
    #include <rtl/strbuf.hxx>
    #include <cppuhelper/exc_hlp.hxx>
    #include <osl/thread.h>
    #include <com/sun/star/lang/XServiceInfo.hpp>
    #include <typeinfo>
#endif
#include <com/sun/star/beans/PropertyAttribute.hpp>
#include <com/sun/star/lang/IllegalArgumentException.hpp>
#include <com/sun/star/uno/genfunc.h>

#include <algorithm>
#include <boost/bind.hpp>

//.........................................................................
namespace comphelper
{

    /** === begin UNO using === **/
    using ::com::sun::star::uno::Reference;
    using ::com::sun::star::beans::XPropertySet;
    using ::com::sun::star::beans::XPropertySetInfo;
    using ::com::sun::star::beans::Property;
    using ::com::sun::star::uno::Sequence;
    using ::com::sun::star::uno::Exception;
    using ::com::sun::star::uno::Any;
    using ::com::sun::star::uno::Type;
    using ::com::sun::star::uno::cpp_queryInterface;
    using ::com::sun::star::uno::cpp_acquire;
    using ::com::sun::star::uno::cpp_release;
#if OSL_DEBUG_LEVEL > 0
    using ::com::sun::star::lang::XServiceInfo;
#endif
    using ::com::sun::star::uno::UNO_QUERY;
    /** === end UNO using === **/
    namespace PropertyAttribute = ::com::sun::star::beans::PropertyAttribute;

//------------------------------------------------------------------
void copyProperties(const Reference<XPropertySet>& _rxSource,
					const Reference<XPropertySet>& _rxDest)
{
	if (!_rxSource.is() || !_rxDest.is())
	{
		OSL_ENSURE(sal_False, "copyProperties: invalid arguments !");
        return;
	}

	Reference< XPropertySetInfo > xSourceProps = _rxSource->getPropertySetInfo();
	Reference< XPropertySetInfo > xDestProps = _rxDest->getPropertySetInfo();

	Sequence< Property > aSourceProps = xSourceProps->getProperties();
	const Property* pSourceProps = aSourceProps.getConstArray();
	Property aDestProp;
	for (sal_Int32 i=0; i<aSourceProps.getLength(); ++i, ++pSourceProps)
	{
		if ( xDestProps->hasPropertyByName(pSourceProps->Name) )
		{
			try
			{
				aDestProp = xDestProps->getPropertyByName(pSourceProps->Name);
				if (0 == (aDestProp.Attributes & PropertyAttribute::READONLY) )
                {
                    const Any aSourceValue = _rxSource->getPropertyValue(pSourceProps->Name);
                    if ( 0 != (aDestProp.Attributes & PropertyAttribute::MAYBEVOID) || aSourceValue.hasValue() )
					    _rxDest->setPropertyValue(pSourceProps->Name, aSourceValue);
                }
			}
			catch (Exception&)
			{
#if OSL_DEBUG_LEVEL > 0
                ::rtl::OStringBuffer aBuffer;
                aBuffer.append( "::comphelper::copyProperties: could not copy property '" );
                aBuffer.append( ::rtl::OString( pSourceProps->Name.getStr(), pSourceProps->Name.getLength(), RTL_TEXTENCODING_ASCII_US ) );
                aBuffer.append( "' to the destination set (a '" );

                Reference< XServiceInfo > xSI( _rxDest, UNO_QUERY );
                if ( xSI.is() )
                {
                    aBuffer.append( ::rtl::OUStringToOString( xSI->getImplementationName(), osl_getThreadTextEncoding() ) );
                }
                else
                {
                    aBuffer.append( typeid( *_rxDest.get() ).name() );
                }
                aBuffer.append( "' implementation).\n" );

                Any aException( ::cppu::getCaughtException() );
                aBuffer.append( "Caught an exception of type '" );
                ::rtl::OUString sExceptionType( aException.getValueTypeName() );
                aBuffer.append( ::rtl::OString( sExceptionType.getStr(), sExceptionType.getLength(), RTL_TEXTENCODING_ASCII_US ) );
                aBuffer.append( "'" );

                Exception aBaseException;
                if ( ( aException >>= aBaseException ) && aBaseException.Message.getLength() )
                {
                    aBuffer.append( ", saying '" );
                    aBuffer.append( ::rtl::OString( aBaseException.Message.getStr(), aBaseException.Message.getLength(), osl_getThreadTextEncoding() ) );
                    aBuffer.append( "'" );
                }
                aBuffer.append( "." );

                OSL_ENSURE( sal_False, aBuffer.getStr() );
#endif
			}
		}
	}
}

//------------------------------------------------------------------
sal_Bool hasProperty(const rtl::OUString& _rName, const Reference<XPropertySet>& _rxSet)
{
	if (_rxSet.is())
	{
		//	XPropertySetInfoRef xInfo(rxSet->getPropertySetInfo());
		return _rxSet->getPropertySetInfo()->hasPropertyByName(_rName);
	}
	return sal_False;
}

//------------------------------------------------------------------
bool findProperty(Property&              o_rProp, 
                  Sequence<Property>&    i_seqProps, 
                  const ::rtl::OUString& i_rPropName)
{
    const Property* pAry(i_seqProps.getConstArray());
    const sal_Int32 nLen(i_seqProps.getLength());
    const Property* pRes(
        std::find_if(pAry,pAry+nLen,
                     boost::bind(PropertyStringEqualFunctor(),
                                 _1,
                                 boost::cref(i_rPropName))));
    if( pRes == pAry+nLen )
        return false;

    o_rProp = *pRes;
    return true;
}

//------------------------------------------------------------------
void RemoveProperty(Sequence<Property>& _rProps, const rtl::OUString& _rPropName)
{
	sal_Int32 nLen = _rProps.getLength();

	// binaere Suche
	const Property* pProperties = _rProps.getConstArray();
	const Property* pResult = ::std::lower_bound(pProperties, pProperties + nLen, _rPropName,PropertyStringLessFunctor());

	// gefunden ?
	if ( pResult && (pResult != pProperties + nLen) && (pResult->Name == _rPropName) )
	{
		OSL_ENSURE(pResult->Name.equals(_rPropName), "::RemoveProperty Properties nicht sortiert");
		removeElementAt(_rProps, pResult - pProperties);
	}
}

//------------------------------------------------------------------
void ModifyPropertyAttributes(Sequence<Property>& seqProps, const ::rtl::OUString& sPropName, sal_Int16 nAddAttrib, sal_Int16 nRemoveAttrib)
{
	sal_Int32 nLen = seqProps.getLength();

	// binaere Suche
	Property* pProperties = seqProps.getArray();
	Property* pResult = ::std::lower_bound(pProperties, pProperties + nLen,sPropName, PropertyStringLessFunctor());

	// gefunden ?
	if ( pResult && (pResult != pProperties + nLen) && (pResult->Name == sPropName) )
	{
		pResult->Attributes |= nAddAttrib;
		pResult->Attributes &= ~nRemoveAttrib;
	}
}

//------------------------------------------------------------------
sal_Bool tryPropertyValue(Any& _rConvertedValue, Any& _rOldValue, const Any& _rValueToSet, const Any& _rCurrentValue, const Type& _rExpectedType)
{
	sal_Bool bModified(sal_False);
	if (_rCurrentValue.getValue() != _rValueToSet.getValue())
	{
        if ( _rValueToSet.hasValue() && ( !_rExpectedType.equals( _rValueToSet.getValueType() ) ) )
        {
            _rConvertedValue = Any( NULL, _rExpectedType.getTypeLibType() );

            if  ( !uno_type_assignData(
                    const_cast< void* >( _rConvertedValue.getValue() ), _rConvertedValue.getValueType().getTypeLibType(),
                    const_cast< void* >( _rValueToSet.getValue() ), _rValueToSet.getValueType().getTypeLibType(),
                    reinterpret_cast< uno_QueryInterfaceFunc >(
                        cpp_queryInterface),
                    reinterpret_cast< uno_AcquireFunc >(cpp_acquire),
                    reinterpret_cast< uno_ReleaseFunc >(cpp_release)
                  )
                )
                throw starlang::IllegalArgumentException();
        }
        else
            _rConvertedValue = _rValueToSet;

		if ( _rCurrentValue != _rConvertedValue )
		{
			_rOldValue = _rCurrentValue;
			bModified = sal_True;
		}
	}
	return bModified;
}

//.........................................................................
}
//.........................................................................

