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


#ifndef CHART2_SHAPECONTROLLER_HXX
#define CHART2_SHAPECONTROLLER_HXX

#include "FeatureCommandDispatchBase.hxx"
#include <tools/link.hxx>

class AbstractSvxNameDialog;
class SdrObject;

//.............................................................................
namespace chart
{
//.............................................................................

class ChartController;

/** This is a CommandDispatch implementation for shapes.
 */
class ShapeController: public FeatureCommandDispatchBase
{
    friend class ControllerCommandDispatch;

public:
    ShapeController( const ::com::sun::star::uno::Reference<
        ::com::sun::star::uno::XComponentContext >& rxContext, ChartController* pController );
	virtual ~ShapeController();

    // late initialisation, especially for adding as listener
    virtual void initialize();

protected:
    // WeakComponentImplHelperBase
    virtual void SAL_CALL disposing();

    // XEventListener
    virtual void SAL_CALL disposing( const ::com::sun::star::lang::EventObject& Source )
        throw (::com::sun::star::uno::RuntimeException);

	// state of a feature
    virtual FeatureState getState( const ::rtl::OUString& rCommand );

    // execute a feature
    virtual void execute( const ::rtl::OUString& rCommand, const ::com::sun::star::uno::Sequence< ::com::sun::star::beans::PropertyValue>& rArgs );

    // all the features which should be handled by this class
    virtual void describeSupportedFeatures();

private:
    DECL_LINK( CheckNameHdl, AbstractSvxNameDialog* );

    void executeDispatch_FormatLine();
    void executeDispatch_FormatArea();
    void executeDispatch_TextAttributes();
    void executeDispatch_TransformDialog();
    void executeDispatch_ObjectTitleDescription();
    void executeDispatch_RenameObject();
    void executeDispatch_ChangeZOrder( sal_uInt16 nId );
    void executeDispatch_FontDialog();
    void executeDispatch_ParagraphDialog();

    SdrObject* getFirstAdditionalShape();
    SdrObject* getLastAdditionalShape();
    bool       isBackwardPossible();
    bool       isForwardPossible();

    ChartController* m_pChartController;
};

//.............................................................................
} //  namespace chart
//.............................................................................

// CHART2_SHAPECONTROLLER_HXX
#endif
