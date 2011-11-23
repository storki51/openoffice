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


#ifndef SC_VBA_CHART_HXX
#define SC_VBA_CHART_HXX
#include <cppuhelper/implbase1.hxx>
#include <com/sun/star/uno/XComponentContext.hpp>
#include <com/sun/star/table/XTableChart.hpp>
#include <com/sun/star/chart/XChartDocument.hpp>
#include <com/sun/star/chart/XAxisXSupplier.hpp>
#include <com/sun/star/chart/XAxisYSupplier.hpp>
#include <com/sun/star/chart/XAxisZSupplier.hpp>
#include <com/sun/star/chart/XTwoAxisXSupplier.hpp>
#include <com/sun/star/chart/XTwoAxisYSupplier.hpp>
#include <ooo/vba/excel/XChart.hpp>
#include <ooo/vba/excel/XDataLabels.hpp>
#include <ooo/vba/excel/XSeries.hpp>
#include <vbahelper/vbahelperinterface.hxx>

typedef InheritedHelperInterfaceImpl1<ov::excel::XChart > ChartImpl_BASE;

class ScVbaChart : public ChartImpl_BASE
{		
friend class ScVbaAxis;

	css::uno::Reference< css::chart::XChartDocument > mxChartDocument;
	css::uno::Reference< css::table::XTableChart > mxTableChart;
	css::uno::Reference< css::beans::XPropertySet > mxDiagramPropertySet;
	css::uno::Reference< css::beans::XPropertySet > mxChartPropertySet;
	css::uno::Reference< css::chart::XAxisXSupplier > xAxisXSupplier;
	css::uno::Reference< css::chart::XAxisYSupplier> xAxisYSupplier;
	css::uno::Reference< css::chart::XAxisZSupplier > xAxisZSupplier;
	css::uno::Reference< css::chart::XTwoAxisXSupplier > xTwoAxisXSupplier;
	css::uno::Reference< css::chart::XTwoAxisYSupplier > xTwoAxisYSupplier;

	css::uno::Sequence< rtl::OUString > getDefaultSeriesDescriptions( sal_Int32 nCount );
	css::uno::Sequence< css::uno::Sequence< double > > dblValues;
	void setDefaultChartType()throw ( css::script::BasicErrorException ) ;
	void setDiagram( const rtl::OUString& _sDiagramType) throw( css::script::BasicErrorException );
	bool isStacked() throw ( css::uno::RuntimeException );
	bool is100PercentStacked() throw ( css::uno::RuntimeException );
	sal_Int32 getStackedType( sal_Int32 _nStacked, sal_Int32 _n100PercentStacked, sal_Int32 _nUnStacked ) throw ( css::uno::RuntimeException );
	sal_Int32 getSolidType(sal_Int32 _nDeep, sal_Int32 _nVertiStacked, sal_Int32 _nVerti100PercentStacked, sal_Int32 _nVertiUnStacked, sal_Int32 _nHoriStacked, sal_Int32 _nHori100PercentStacked, sal_Int32 _nHoriUnStacked) throw ( css::script::BasicErrorException );
	sal_Int32 getStockUpDownValue(sal_Int32 _nUpDown, sal_Int32 _nNotUpDown) throw (css::script::BasicErrorException);
	bool hasMarkers() throw ( css::script::BasicErrorException );
	sal_Int32 getMarkerType(sal_Int32 _nWithMarkers, sal_Int32 _nWithoutMarkers) throw ( css::script::BasicErrorException ); 
	void assignDiagramAttributes();
	void setDefaultSeriesDescriptionLabels(){}
public:
	ScVbaChart( const css::uno::Reference< ov::XHelperInterface >& _xParent, const css::uno::Reference< css::uno::XComponentContext >& _xContext, const css::uno::Reference< css::lang::XComponent >& _xChartComponent, const css::uno::Reference< css::table::XTableChart >& _xTableChart );

	// Non-interface
	css::uno::Reference< css::beans::XPropertySet > xDiagramPropertySet() { return mxDiagramPropertySet; }
	bool isSeriesIndexValid(sal_Int32 _seriesindex) throw( css::script::BasicErrorException );
	bool areIndicesValid(sal_Int32 _seriesindex, sal_Int32 _valindex) throw ( css::script::BasicErrorException );
	void setSeriesName(sal_Int32 _index, rtl::OUString _sname) throw ( css::script::BasicErrorException );
	sal_Int32 getSeriesIndex(rtl::OUString _sseriesname) throw ( css::script::BasicErrorException );
	sal_Int32 getSeriesCount() throw ( css::script::BasicErrorException );
	rtl::OUString getSeriesName(sal_Int32 _index) throw ( css::script::BasicErrorException );
	double getValue(sal_Int32 _seriesIndex, sal_Int32 _valindex) throw ( css::script::BasicErrorException );
	sal_Int32 getValuesCount(sal_Int32 _seriesIndex) throw ( css::script::BasicErrorException );
	css::uno::Reference< ov::excel::XDataLabels > DataLabels( const css::uno::Reference< ov::excel::XSeries > _oSeries ) throw ( css::script::BasicErrorException );
	bool getHasDataCaption( const css::uno::Reference< css::beans::XPropertySet >& _xPropertySet )throw ( css::script::BasicErrorException );
	void setHasDataCaption( const css::uno::Reference< css::beans::XPropertySet >& _xPropertySet, bool _bHasDataLabels )throw ( css::script::BasicErrorException );
	bool is3D() throw ( css::uno::RuntimeException );
	css::uno::Reference< css::beans::XPropertySet > getAxisPropertySet(sal_Int32 _nAxisType, sal_Int32 _nAxisGroup) throw ( css::script::BasicErrorException );
	// Methods
	virtual ::rtl::OUString SAL_CALL getName() throw (css::uno::RuntimeException);
	virtual css::uno::Any SAL_CALL SeriesCollection(const css::uno::Any&) throw (css::uno::RuntimeException);
	virtual ::sal_Int32 SAL_CALL getChartType() throw ( css::uno::RuntimeException, css::script::BasicErrorException);
	virtual void SAL_CALL setChartType( ::sal_Int32 _charttype ) throw ( css::uno::RuntimeException, css::script::BasicErrorException);
	virtual void SAL_CALL Activate(  ) throw (css::script::BasicErrorException, css::uno::RuntimeException); 
	virtual void SAL_CALL setSourceData( const css::uno::Reference< ::ooo::vba::excel::XRange >& range, const css::uno::Any& PlotBy ) throw (css::script::BasicErrorException, css::uno::RuntimeException);
	virtual ::sal_Int32 SAL_CALL Location(  ) throw (css::script::BasicErrorException, css::uno::RuntimeException);
	virtual ::sal_Int32 SAL_CALL getLocation(  ) throw (css::script::BasicErrorException, css::uno::RuntimeException);
	virtual void SAL_CALL setLocation( ::sal_Int32 where, const css::uno::Any& Name ) throw (css::script::BasicErrorException, css::uno::RuntimeException);
	virtual ::sal_Bool SAL_CALL getHasTitle(  ) throw (css::script::BasicErrorException, css::uno::RuntimeException);
	virtual void SAL_CALL setHasTitle( ::sal_Bool bTitle ) throw (css::script::BasicErrorException, css::uno::RuntimeException);
	virtual ::sal_Bool SAL_CALL getHasLegend(  ) throw (css::script::BasicErrorException, css::uno::RuntimeException);
	virtual void SAL_CALL setHasLegend( ::sal_Bool bLegend ) throw (css::script::BasicErrorException, css::uno::RuntimeException);
	virtual void SAL_CALL setPlotBy( ::sal_Int32 xlRowCol ) throw (css::script::BasicErrorException, css::uno::RuntimeException);
	virtual ::sal_Int32 SAL_CALL getPlotBy(  ) throw (css::script::BasicErrorException, css::uno::RuntimeException);
	virtual css::uno::Reference< ov::excel::XChartTitle > SAL_CALL getChartTitle(  ) throw (css::script::BasicErrorException, css::uno::RuntimeException);
	virtual css::uno::Any SAL_CALL Axes( const css::uno::Any& Type, const css::uno::Any& AxisGroup ) throw (css::script::BasicErrorException, css::uno::RuntimeException);
	// XHelperInterface
	virtual rtl::OUString& getServiceImplName();
	virtual css::uno::Sequence<rtl::OUString> getServiceNames();

};

#endif //SC_VBA_WINDOW_HXX
