#############################################################################
##
##  FougTools
##  Copyright FougSys (1 Mar. 2011)
##  contact@fougsys.fr
##
## This software is a computer program whose purpose is to provide utility
## tools for the C++ language, the Qt and OpenCascade toolkits.
##
## This software is governed by the CeCILL-C license under French law and
## abiding by the rules of distribution of free software.  You can  use,
## modify and/ or redistribute the software under the terms of the CeCILL-C
## license as circulated by CEA, CNRS and INRIA at the following URL
## "http://www.cecill.info".
##
## As a counterpart to the access to the source code and  rights to copy,
## modify and redistribute granted by the license, users are provided only
## with a limited warranty  and the software's author,  the holder of the
## economic rights,  and the successive licensors  have only  limited
## liability.
##
## In this respect, the user's attention is drawn to the risks associated
## with loading,  using,  modifying and/or developing or reproducing the
## software by the user in light of its specific status of free software,
## that may mean  that it is complicated to manipulate,  and  that  also
## therefore means  that it is reserved for developers  and  experienced
## professionals having in-depth computer knowledge. Users are therefore
## encouraged to load and test the software's suitability as regards their
## requirements in conditions enabling the security of their systems and/or
## data to be ensured and,  more generally, to use and operate it in the
## same conditions as regards security.
##
## The fact that you are presently reading this means that you have had
## knowledge of the CeCILL-C license and that you accept its terms.
##
#############################################################################

include(../../3rdparty/occ.pri)

INCLUDEPATH *= $$BOOST_ROOT

HEADERS += $$PWD/io.h \
           $$PWD/occtools.h \
           $$PWD/ais_text.h \
           $$PWD/handle_ais_text.h \
           $$PWD/brep_point_on_faces_projection.h \
           $$PWD/gcpnts_uniform_abscissa_const_iterator.h \
           $$PWD/make_wire_from_edges.h \
           $$PWD/point_on_faces_projector.h \
           $$PWD/pnt_vec_traits.h \
           $$PWD/utils.h \
           $$PWD/utils.impl.h \
           $$PWD/ui/view.h \
           $$PWD/ui/view_controller.h \
           $$PWD/ui/view_controller_delegate.h \
           $$PWD/qt_occ.h

SOURCES += \
           $$PWD/io.cpp \
           $$PWD/ais_text.cpp \
           $$PWD/brep_point_on_faces_projection.cpp \
           $$PWD/gcpnts_uniform_abscissa_const_iterator.cpp \
           $$PWD/point_on_faces_projector.cpp \
           $$PWD/utils.cpp \
           $$PWD/ui/view.cpp \
           $$PWD/ui/view_controller.cpp \
           $$PWD/ui/view_controller_delegate.cpp \
           $$PWD/qt_occ.cpp

LIBS += -lTKBRep -lTKernel -lTKG2d -lTKG3d -lTKGeomAlgo -lTKGeomBase \
        -lTKIGES -lTKMath -lTKMesh -lTKOpenGl -lTKPrim  -lTKService \
        -lTKSTEP -lTKSTEPAttr -lTKSTEPBase -l$$OCC_TKSTEP -lTKSTL -lTKTopAlgo \
        -lTKV2d -lTKV3d -lTKXSBase
