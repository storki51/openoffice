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

PRJ=..$/..
PRJNAME=basegfx
TARGET=tuple

#UNOUCRRDB=$(SOLARBINDIR)$/applicat.rdb
#ENABLE_EXCEPTIONS=FALSE
#USE_DEFFILE=TRUE

# --- Settings ----------------------------------

.INCLUDE :  	settings.mk

# --- Files -------------------------------------

SLOFILES= \
				$(SLO)$/b2dtuple.obj		\
				$(SLO)$/b3dtuple.obj		\
				$(SLO)$/b2ituple.obj		\
				$(SLO)$/b3ituple.obj		\
				$(SLO)$/b2i64tuple.obj		\
				$(SLO)$/b3i64tuple.obj

# --- Targets ----------------------------------

.INCLUDE : target.mk
