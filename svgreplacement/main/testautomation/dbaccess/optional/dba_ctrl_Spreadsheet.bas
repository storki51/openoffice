'encoding UTF-8  Do not remove or change this line!
'**************************************************************************
' DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
' 
' Copyright 2000, 2010 Oracle and/or its affiliates.
'
' OpenOffice.org - a multi-platform office productivity suite
'
' This file is part of OpenOffice.org.
'
' OpenOffice.org is free software: you can redistribute it and/or modify
' it under the terms of the GNU Lesser General Public License version 3
' only, as published by the Free Software Foundation.
'
' OpenOffice.org is distributed in the hope that it will be useful,
' but WITHOUT ANY WARRANTY; without even the implied warranty of
' MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
' GNU Lesser General Public License version 3 for more details
' (a copy is included in the LICENSE file that accompanied this code).
'
' You should have received a copy of the GNU Lesser General Public License
' version 3 along with OpenOffice.org.  If not, see
' <http://www.openoffice.org/license.html>
' for a copy of the LGPLv3 License.
'
'/************************************************************************
'*
'* owner : marc.neumann@oracle.com
'*
'* short description : Spreadsheets Controls
'*
'\***********************************************************************
sub main
    printlog "---------------------------------------------------------------------"
    printlog "-----           S P R E A D S H E E T   C O N T R O L S         -----"
    printlog "---------------------------------------------------------------------"

    use "dbaccess/optional/includes/ctrl_Spreadsheet.inc"
    
    call hStatusIn ("dbaccess" , "dba_ctrl_Spreadsheet.bas" )
	    
	call ctrl_Spreadsheet

	call hStatusOut

end sub


sub LoadIncludeFiles   
   use "dbaccess/tools/dbinit.inc"      	
   Call sDBInit
   Call GetUseFiles
   gApplication   = "WRITER"
end sub
