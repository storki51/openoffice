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



#ifndef SC_OPTUNO_HXX
#define SC_OPTUNO_HXX

#include "docuno.hxx"
#include "docoptio.hxx"

#define PROP_UNO_CALCASSHOWN    1
#define PROP_UNO_DEFTABSTOP     2
#define PROP_UNO_IGNORECASE     3
#define PROP_UNO_ITERENABLED    4
#define PROP_UNO_ITERCOUNT      5
#define PROP_UNO_ITEREPSILON    6
#define PROP_UNO_LOOKUPLABELS   7
#define PROP_UNO_MATCHWHOLE     8
#define PROP_UNO_NULLDATE       9
#define PROP_UNO_SPELLONLINE    10
#define PROP_UNO_STANDARDDEC    11
#define PROP_UNO_REGEXENABLED   12


class ScDocOptionsHelper
{
public:
    static const SfxItemPropertyMapEntry* GetPropertyMap();

	static sal_Bool setPropertyValue( ScDocOptions& rOptions,
                                    const SfxItemPropertyMap& rPropMap, 
									const ::rtl::OUString& aPropertyName,
									const ::com::sun::star::uno::Any& aValue );
	static ::com::sun::star::uno::Any getPropertyValue(
									const ScDocOptions& rOptions,
                                    const SfxItemPropertyMap& rPropMap, 
									const ::rtl::OUString& PropertyName );
};


//	empty doc object to supply only doc options

class ScDocOptionsObj : public ScModelObj
{
private:
	ScDocOptions	aOptions;

public:
							ScDocOptionsObj( const ScDocOptions& rOpt );
	virtual					~ScDocOptionsObj();

	// get/setPropertyValue overloaded to used stored options instead of document

	virtual void SAL_CALL	setPropertyValue( const ::rtl::OUString& aPropertyName,
									const ::com::sun::star::uno::Any& aValue )
								throw(::com::sun::star::beans::UnknownPropertyException,
									::com::sun::star::beans::PropertyVetoException,
									::com::sun::star::lang::IllegalArgumentException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);
	virtual ::com::sun::star::uno::Any SAL_CALL getPropertyValue(
									const ::rtl::OUString& PropertyName )
								throw(::com::sun::star::beans::UnknownPropertyException,
									::com::sun::star::lang::WrappedTargetException,
									::com::sun::star::uno::RuntimeException);
};


#endif

