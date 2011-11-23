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
TARGET=lotus

PROJECTPCH4DLL=TRUE
PROJECTPCH=filt_pch
PROJECTPCHSOURCE=..\pch\filt_pch

AUTOSEG=true

VISIBILITY_HIDDEN=TRUE

# --- Settings -----------------------------------------------------

.INCLUDE :  scpre.mk
.INCLUDE :  settings.mk
.INCLUDE :  sc.mk

# --- Files --------------------------------------------------------

SLOFILES =						\
		$(SLO)$/filter.obj		\
		$(SLO)$/lotus.obj		\
		$(SLO)$/lotimpop.obj	\
		$(SLO)$/lotread.obj		\
		$(SLO)$/lotform.obj		\
		$(SLO)$/memory.obj		\
		$(SLO)$/op.obj			\
		$(SLO)$/optab.obj		\
		$(SLO)$/tool.obj		\
		$(SLO)$/expop.obj		\
		$(SLO)$/export.obj		\
		$(SLO)$/lotattr.obj

EXCEPTIONSFILES =				\
		$(SLO)$/op.obj

# --- Tagets -------------------------------------------------------

.INCLUDE :  target.mk

