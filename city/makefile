# makefile of swooz-teleoperation project using Visual C++
# Guillaume Gibert / Florian Lance
# lyon sept 2013

!IF "$(CFG)" != "Release" &&  "$(CFG)" != "Debug"
!ERROR Invalid CFG "($CFG)
!ENDIF

!IF "$(ARCH)" != "x86" &&  "$(ARCH)" != "amd64"
!ERROR Invalid ARCH "($ARCH)
!ENDIF

CC=cl
LINK=link

!INCLUDE <./makefile-include>


############################################################################## OBJ LISTS

CITY_LINK_OBJ=\
    $(LIBDIR)/Batiment.obj\
    $(LIBDIR)/box.obj\
    $(LIBDIR)/Building.obj\
    $(LIBDIR)/city.obj\
    $(LIBDIR)/cube.obj\
    $(LIBDIR)/EtageFenetre.obj\
    $(LIBDIR)/exporte.obj\
    $(LIBDIR)/geometry.obj\
    $(LIBDIR)/GiantBuilding.obj\
    $(LIBDIR)/Maison.obj\
    $(LIBDIR)/MaisonClassique.obj\
    $(LIBDIR)/mobilierUrbain.obj\
    $(LIBDIR)/opengl.obj\
    $(LIBDIR)/quartier.obj\
    $(LIBDIR)/quartierCentre.obj\
    $(LIBDIR)/quartierIndustriel.obj\
    $(LIBDIR)/quartierResidentiel.obj\
    $(LIBDIR)/shape.obj\
    $(LIBDIR)/SmallBuilding.obj\
    $(LIBDIR)/Usine.obj\
    $(LIBDIR)/UsineClassique.obj\
    $(LIBDIR)/vector.obj\

############################################################################## Makefile commands

!if "$(ARCH)" == "x86"
all: $(BINDIR)/City.exe
!endif

!if "$(ARCH)" == "amd64"
all: $(BINDIR)/City-x64.exe
!endif

############################################################################## exe files

WIN_CONFIG = $(SETARGV) $(BINMODE) $(WINLIBS)

# exec files to be generated
$(BINDIR)/City.exe: $(CITY_LINK_OBJ) $(LIBS_CITY)
        $(LINK) /OUT:$(BINDIR)/City.exe $(LFLAGS_CITY) $(CITY_LINK_OBJ) $(LIBS_CITY) $(WIN_CONFIG)


$(BINDIR)/City-x64.exe: $(CITY_LINK_OBJ) $(LIBS_CITY)
        $(LINK) /OUT:$(BINDIR)/City-x64.exe $(LFLAGS_CITY) $(CITY_LINK_OBJ) $(LIBS_CITY) $(WIN_CONFIG)

##################################################### devices

$(LIBDIR)/Batiment.obj: ./src/Batiment.cpp
        $(CC) -c ./src/Batiment.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/Batiment.obj"


$(LIBDIR)/box.obj: ./src/box.cpp
        $(CC) -c ./src/box.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/box.obj"


$(LIBDIR)/Building.obj: ./src/Building.cpp
        $(CC) -c ./src/Building.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/Building.obj"


$(LIBDIR)/city.obj: ./src/city.cpp
        $(CC) -c ./src/city.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/city.obj"


$(LIBDIR)/cube.obj: ./src/cube.cpp
        $(CC) -c ./src/cube.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/cube.obj"


$(LIBDIR)/EtageFenetre.obj: ./src/EtageFenetre.cpp
        $(CC) -c ./src/EtageFenetre.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/EtageFenetre.obj"


$(LIBDIR)/exporte.obj: ./src/exporte.cpp
        $(CC) -c ./src/exporte.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/exporte.obj"


$(LIBDIR)/geometry.obj: ./src/geometry.cpp
        $(CC) -c ./src/geometry.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/geometry.obj"


$(LIBDIR)/GiantBuilding.obj: ./src/GiantBuilding.cpp
        $(CC) -c ./src/GiantBuilding.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/GiantBuilding.obj"


$(LIBDIR)/Maison.obj: ./src/Maison.cpp
        $(CC) -c ./src/Maison.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/Maison.obj"


$(LIBDIR)/MaisonClassique.obj: ./src/MaisonClassique.cpp
        $(CC) -c ./src/MaisonClassique.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/MaisonClassique.obj"

$(LIBDIR)/mobilierUrbain.obj: ./src/mobilierUrbain.cpp
        $(CC) -c ./src/mobilierUrbain.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/mobilierUrbain.obj"

$(LIBDIR)/opengl.obj: ./src/opengl.cpp
        $(CC) -c ./src/opengl.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/opengl.obj"

$(LIBDIR)/quartier.obj: ./src/quartier.cpp
        $(CC) -c ./src/quartier.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/quartier.obj"

$(LIBDIR)/quartierCentre.obj: ./src/quartierCentre.cpp
        $(CC) -c ./src/quartierCentre.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/quartierCentre.obj"

$(LIBDIR)/quartierIndustriel.obj: ./src/quartierIndustriel.cpp
        $(CC) -c ./src/quartierIndustriel.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/quartierIndustriel.obj"

$(LIBDIR)/quartierResidentiel.obj: ./src/quartierResidentiel.cpp
        $(CC) -c ./src/quartierResidentiel.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/quartierResidentiel.obj"

$(LIBDIR)/shape.obj: ./src/shape.cpp
        $(CC) -c ./src/shape.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/shape.obj"

$(LIBDIR)/SmallBuilding.obj: ./src/SmallBuilding.cpp
        $(CC) -c ./src/SmallBuilding.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/SmallBuilding.obj"

$(LIBDIR)/Usine.obj: ./src/Usine.cpp
        $(CC) -c ./src/Usine.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/Usine.obj"

$(LIBDIR)/UsineClassique.obj: ./src/UsineClassique.cpp
        $(CC) -c ./src/UsineClassique.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/UsineClassique.obj"

$(LIBDIR)/vector.obj: ./src/vector.cpp
        $(CC) -c ./src/vector.cpp $(CFLAGS_DYN) $(CITY_INC) -Fo"$(LIBDIR)/vector.obj"

