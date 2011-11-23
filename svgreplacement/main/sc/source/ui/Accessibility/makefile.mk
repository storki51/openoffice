#*************************************************************************
#
# DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
# 
# Copyright 2000, 2010 Oracle and/or its affiliates.
#
# OpenOffice.org - a multi-platform office productivity suite
#
# This file is part of OpenOffice.org.
#
# OpenOffice.org is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License version 3
# only, as published by the Free Software Foundation.
#
# OpenOffice.org is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License version 3 for more details
# (a copy is included in the LICENSE file that accompanied this code).
#
# You should have received a copy of the GNU Lesser General Public License
# version 3 along with OpenOffice.org.  If not, see
# <http://www.openoffice.org/license.html>
# for a copy of the LGPLv3 License.
#
#*************************************************************************

PRJ=..$/..$/..

PRJNAME=sc
TARGET=accessibility

# --- Settings -----------------------------------------------------

.INCLUDE :  scpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sc.mk
.INCLUDE :  $(PRJ)$/util$/makefile.pmk

# --- Files --------------------------------------------------------

SLOFILES =  										\
		$(SLO)$/AccessibleContextBase.obj			\
		$(SLO)$/AccessibleTableBase.obj				\
		$(SLO)$/AccessibleDocument.obj				\
		$(SLO)$/AccessibleGlobal.obj				\
		$(SLO)$/AccessibleSpreadsheet.obj			\
		$(SLO)$/AccessibleCell.obj					\
		$(SLO)$/AccessibilityHints.obj				\
		$(SLO)$/AccessibleDocumentBase.obj			\
		$(SLO)$/AccessibleCellBase.obj				\
		$(SLO)$/AccessibleDocumentPagePreview.obj	\
		$(SLO)$/AccessibleFilterMenu.obj	\
		$(SLO)$/AccessibleFilterMenuItem.obj	\
		$(SLO)$/AccessibleFilterTopWindow.obj	\
		$(SLO)$/AccessiblePreviewTable.obj			\
		$(SLO)$/AccessiblePreviewCell.obj			\
		$(SLO)$/AccessiblePreviewHeaderCell.obj		\
		$(SLO)$/AccessiblePageHeader.obj			\
		$(SLO)$/AccessibleText.obj					\
		$(SLO)$/AccessiblePageHeaderArea.obj		\
		$(SLO)$/DrawModelBroadcaster.obj			\
		$(SLO)$/AccessibleEditObject.obj			\
		$(SLO)$/AccessibleDataPilotControl.obj		\
		$(SLO)$/AccessibleCsvControl.obj

EXCEPTIONSFILES=									\
		$(SLO)$/AccessibleContextBase.obj			\
		$(SLO)$/AccessibleTableBase.obj				\
		$(SLO)$/AccessibleDocument.obj				\
		$(SLO)$/AccessibleGlobal.obj				\
		$(SLO)$/AccessibleSpreadsheet.obj			\
		$(SLO)$/AccessibleCell.obj					\
		$(SLO)$/AccessibleDocumentBase.obj			\
		$(SLO)$/AccessibleCellBase.obj				\
		$(SLO)$/AccessibleDocumentPagePreview.obj	\
		$(SLO)$/AccessibleFilterMenu.obj	\
		$(SLO)$/AccessibleFilterMenuItem.obj	\
		$(SLO)$/AccessibleFilterTopWindow.obj	\
		$(SLO)$/AccessiblePreviewTable.obj			\
		$(SLO)$/AccessiblePreviewCell.obj			\
		$(SLO)$/AccessiblePreviewHeaderCell.obj		\
		$(SLO)$/AccessiblePageHeader.obj			\
		$(SLO)$/AccessiblePageHeaderArea.obj		\
		$(SLO)$/DrawModelBroadcaster.obj			\
		$(SLO)$/AccessibleEditObject.obj			\
		$(SLO)$/AccessibleDataPilotControl.obj		\
		$(SLO)$/AccessibleCsvControl.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk


