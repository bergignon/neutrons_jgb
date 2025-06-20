# $Id: GNUmakefile,v 1.15 2010-09-23 05:02:14 mkelsey Exp $
# -----------------------------------------------------------
# GNUmakefile for hadronic library.  Gabriele Cosmo, 18/9/96.
#
# Map user environment/GMake variables onto preprocessor debugging flags
#
# 20100922 J. Yarba -- Add include directories for pre-compound model
# -----------------------------------------------------------

name := G4hadronic_inclxx_interface

ifndef G4INSTALL
  G4INSTALL = ../../../../../..
endif
include $(G4INSTALL)/config/architecture.gmk

CPPFLAGS += -DG4HADRONIC_ALLOC_EXPORT
CPPFLAGS += -I$(G4BASE)/global/management/include \
            -I$(G4BASE)/global/HEPRandom/include \
            -I$(G4BASE)/global/HEPNumerics/include \
            -I$(G4BASE)/global/HEPGeometry/include \
            -I$(G4BASE)/track/include \
            -I$(G4BASE)/geometry/volumes/include \
            -I$(G4BASE)/geometry/management/include \
            -I$(G4BASE)/processes/management/include \
            -I$(G4BASE)/processes/hadronic/management/include/ \
            -I$(G4BASE)/processes/hadronic/util/include \
            -I$(G4BASE)/processes/hadronic/processes/include \
            -I$(G4BASE)/processes/hadronic/cross_sections/include \
	    -I$(G4BASE)/processes/hadronic/models/management/include \
	    -I$(G4BASE)/processes/hadronic/models/util/include \
            -I$(G4BASE)/processes/hadronic/models/pre_equilibrium/exciton_model/include/ \
            -I$(G4BASE)/processes/hadronic/models/de_excitation/multifragmentation/include/ \
            -I$(G4BASE)/processes/hadronic/models/de_excitation/fermi_breakup/include/ \
            -I$(G4BASE)/processes/hadronic/models/de_excitation/photon_evaporation/include/ \
            -I$(G4BASE)/processes/hadronic/models/de_excitation/management/include/ \
            -I$(G4BASE)/processes/hadronic/models/de_excitation/evaporation/include/ \
            -I$(G4BASE)/processes/hadronic/models/de_excitation/handler/include/ \
            -I$(G4BASE)/processes/hadronic/models/de_excitation/util/include/ \
	    -I$(G4BASE)/processes/hadronic/models/inclxx/incl_physics/include \
	    -I$(G4BASE)/processes/hadronic/models/inclxx/utils/include \
	    -I$(G4BASE)/processes/hadronic/models/binary_cascade/include/ \
	    -I$(G4BASE)/processes/hadronic/models/im_r_matrix/include/ \
	    -I$(G4BASE)/particles/management/include \
            -I$(G4BASE)/particles/leptons/include \
            -I$(G4BASE)/particles/bosons/include \
            -I$(G4BASE)/particles/hadrons/mesons/include \
            -I$(G4BASE)/particles/hadrons/barions/include \
            -I$(G4BASE)/particles/hadrons/ions/include \
            -I$(G4BASE)/particles/shortlived/include \
            -I$(G4BASE)/materials/include \
            -I$(G4BASE)/intercoms/include

include $(G4INSTALL)/config/common.gmk

