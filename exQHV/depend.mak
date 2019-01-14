HSO.i: HSO.c quickhvolume.h point.h macros.h HSO.h
counterHash.i: counterHash.c counterHash.h point.h macros.h
division.i: division.c division.h divisionStruct.c
divisionStruct.i: divisionStruct.c
dominant.i: dominant.c dominant.h point.h macros.h
inexclusion.i: inexclusion.c point.h macros.h quickhvolume.h subsets.h \
  inexclusion.h
main.i: main.c point.h macros.h quickhvolume.h splitter.h division.h \
  subsets.h unionFilter.h naiverandom.h HSO.h inexclusion.h
naiverandom.i: naiverandom.c naiverandom.h point.h macros.h
point.i: point.c point.h macros.h
quickhvolume.i: quickhvolume.c quickhvolume.h point.h macros.h HSO.h \
  subsets.h division.h splitter.h inexclusion.h
splitter.i: splitter.c point.h macros.h splitter.h division.h \
  divisionStruct.c arrayList.h counterHash.h unionFilter.h subsets.h \
  dominant.h
subsets.i: subsets.c macros.h subsets.h
unionFilter.i: unionFilter.c unionFilter.h counterHash.h arrayList.h \
  macros.h
