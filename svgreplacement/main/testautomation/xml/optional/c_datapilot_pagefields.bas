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
'* owner : oliver.craemer@Sun.COM
'*
'* short description  :  Lookup for correct attributes of datapilot pagefields
'*
'\***********************************************************************

sub main       
    Printlog "--------------------------------------------------"
    Printlog "---      Datapilot pagefields attributes       ---"
    Printlog "--------------------------------------------------"

    use "xml/optional/includes/c_datapilot_pagefields.inc"
    use "xml/tools/includes/xmltool1.inc"
    
    Call hStatusIn("XML", "c_datapilot_pagefields.bas")
        call hEnablePrettyPrinting(1)     
        call subPageFields
    Call hStatusOut

end sub
'
'-------------------------------------------------------------------------------
'
sub LoadIncludeFiles
    use "global/system/includes/master.inc"
    use "global/system/includes/gvariabl.inc"
    use "global/tools/includes/required/t_tools1.inc"
    gApplication   = "CALC"
    call GetUseFiles        
end sub
