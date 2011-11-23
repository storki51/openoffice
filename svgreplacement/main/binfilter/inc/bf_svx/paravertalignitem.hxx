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


#ifndef _SVX_PARAVERTALIGNITEM_HXX
#define _SVX_PARAVERTALIGNITEM_HXX

// include ---------------------------------------------------------------

#ifndef _SFXINTITEM_HXX
#include <bf_svtools/intitem.hxx>
#endif
#ifndef _SVX_SVXIDS_HRC
#include <bf_svx/svxids.hrc>
#endif
namespace binfilter {

// class SvxParaVertAlignItem ----------------------------------------------

/* [Description]

	This item defines the character alignment in the lines of a paragraph.
 	Currently the alignment can be none (i.e. baseline), top, center or bottom.

*/

class SvxParaVertAlignItem : public SfxUInt16Item
{
public:
	enum { AUTOMATIC, BASELINE, TOP, CENTER, BOTTOM };
	TYPEINFO();

	SvxParaVertAlignItem( sal_uInt16 nValue = 0,
					   const sal_uInt16 nId = ITEMID_PARAVERTALIGN );

	virtual USHORT			GetVersion( USHORT nFileVersion ) const;



	inline SvxParaVertAlignItem& operator=( const SvxParaVertAlignItem& rItem )
	{
		SetValue( rItem.GetValue() );
		return *this;
	}


};

}//end of namespace binfilter
#endif

