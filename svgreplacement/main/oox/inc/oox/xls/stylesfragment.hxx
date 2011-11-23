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



#ifndef OOX_XLS_STYLESFRAGMENT_HXX
#define OOX_XLS_STYLESFRAGMENT_HXX

#include "oox/xls/excelhandlers.hxx"
#include "oox/xls/stylesbuffer.hxx"

namespace oox {
namespace xls {

// ============================================================================

class IndexedColorsContext : public WorkbookContextBase
{
public:
    explicit            IndexedColorsContext( WorkbookFragmentBase& rFragment );

protected:
    virtual ::oox::core::ContextHandlerRef onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs );
    virtual ::oox::core::ContextHandlerRef onCreateRecordContext( sal_Int32 nRecId, SequenceInputStream& rStrm );
};

// ============================================================================

class FontContext : public WorkbookContextBase
{
public:
    template< typename ParentType >
    inline explicit     FontContext( ParentType& rParent, const FontRef& rxFont ) :
                            WorkbookContextBase( rParent ), mxFont( rxFont ) {}

protected:
    virtual ::oox::core::ContextHandlerRef onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs );

private:
    FontRef             mxFont;
};

// ============================================================================

class BorderContext : public WorkbookContextBase
{
public:
    template< typename ParentType >
    inline explicit     BorderContext( ParentType& rParent, const BorderRef& rxBorder ) :
                            WorkbookContextBase( rParent ), mxBorder( rxBorder ) {}

protected:
    virtual void        onStartElement( const AttributeList& rAttribs );
    virtual ::oox::core::ContextHandlerRef onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs );

private:
    BorderRef           mxBorder;
};

// ============================================================================

class FillContext : public WorkbookContextBase
{
public:
    template< typename ParentType >
    inline explicit     FillContext( ParentType& rParent, const FillRef& rxFill ) :
                            WorkbookContextBase( rParent ), mxFill( rxFill ), mfGradPos( -1.0 ) {}

protected:
    virtual ::oox::core::ContextHandlerRef onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs );

private:
    FillRef             mxFill;
    double              mfGradPos;      /// Gradient color position.
};

// ============================================================================

class XfContext : public WorkbookContextBase
{
public:
    template< typename ParentType >
    inline explicit     XfContext( ParentType& rParent, const XfRef& rxXf, bool bCellXf ) :
                            WorkbookContextBase( rParent ), mxXf( rxXf ), mbCellXf( bCellXf ) {}

protected:
    virtual void        onStartElement( const AttributeList& rAttribs );
    virtual ::oox::core::ContextHandlerRef onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs );

private:
    XfRef               mxXf;
    bool                mbCellXf;       /// True = cell XF, false = style XF.
};

// ============================================================================

class DxfContext : public WorkbookContextBase
{
public:
    template< typename ParentType >
    inline explicit     DxfContext( ParentType& rParent, const DxfRef& rxDxf ) :
                            WorkbookContextBase( rParent ), mxDxf( rxDxf ) {}

protected:
    virtual ::oox::core::ContextHandlerRef onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs );

private:
    DxfRef              mxDxf;
};

// ============================================================================

class StylesFragment : public WorkbookFragmentBase
{
public:
    explicit            StylesFragment(
                            const WorkbookHelper& rHelper,
                            const ::rtl::OUString& rFragmentPath );

protected:
    virtual ::oox::core::ContextHandlerRef onCreateContext( sal_Int32 nElement, const AttributeList& rAttribs );
    virtual ::oox::core::ContextHandlerRef onCreateRecordContext( sal_Int32 nRecId, SequenceInputStream& rStrm );

    virtual const ::oox::core::RecordInfo* getRecordInfos() const;
    virtual void        finalizeImport();
};

// ============================================================================

} // namespace xls
} // namespace oox

#endif
