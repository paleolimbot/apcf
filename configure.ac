dnl Process this file with autoconf to produce a configure script.
dnl copied largely (w/o proj) from sf (https://github.com/r-spatial/sf)
dnl which in turn made use of GDAL stuff from rgdal, (c) Roger Bivand
AC_INIT(src/rand_dists_ratios.cpp)


#------------------------------------------------------------------------------
#  R
#------------------------------------------------------------------------------
: ${R_HOME=`R RHOME`}
if test -z "${R_HOME}"; then
  echo "could not determine R_HOME"
  exit 1
fi

RBIN="${R_HOME}/bin/R"
# RVER=`"${RBIN}" --version | head -1 | cut -f3 -d" "`
RSCRIPT="${R_HOME}/bin/Rscript"
RVER=`"${RSCRIPT}" -e 'writeLines(paste(sep=".", base::version$major, base::version$minor))'`

RVER_MAJOR=`echo ${RVER} | cut  -f1 -d"."`
RVER_MINOR=`echo ${RVER} | cut  -f2 -d"."`
RVER_PATCH=`echo ${RVER} | cut  -f3 -d"."`

if test [$RVER_MAJOR = "development"]; then
    CXX11=`"${RBIN}" CMD config CXX11`
    CXX11STD=`"${RBIN}" CMD config CXX11STD`
else
    if test [$RVER_MAJOR -lt 3] -o [$RVER_MAJOR -eq 3 -a $RVER_MINOR -lt 3]; then
        AC_MSG_ERROR([apcf is not compatible with R versions before 3.3.0])
    else
        if test [$RVER_MINOR -eq 3]; then
            CXX11=`"${RBIN}" CMD config CXX1X`
            CXX11STD=`"${RBIN}" CMD config CXX1XSTD`
        else
            CXX11=`"${RBIN}" CMD config CXX11`
            CXX11STD=`"${RBIN}" CMD config CXX11STD`
        fi
    fi
fi

# pick all flags for testing from R
: ${CC=`"${RBIN}" CMD config CC`}
: ${CXX=${CXX11} ${CXX11STD}}
: ${CFLAGS=`"${RBIN}" CMD config CFLAGS`}
: ${CPPFLAGS=`"${RBIN}" CMD config CPPFLAGS`}
: ${CXXFLAGS=`"${RBIN}" CMD config CXXFLAGS`}
: ${LDFLAGS=`"${RBIN}" CMD config LDFLAGS`}
# AC_SUBST([CC],["clang"])
# AC_SUBST([CXX],["clang++"])
AC_MSG_NOTICE([CC: ${CC}])
AC_MSG_NOTICE([CXX: ${CXX}])

# AC_MSG_NOTICE([${PACKAGE_NAME}: ${PACKAGE_VERSION}])


#------------------------------------------------------------------------------
#  GDAL
#------------------------------------------------------------------------------
GDAL_CONFIG="gdal-config"

GDAL_CONFIG_SET="no"

AC_ARG_WITH([gdal-config],
    AC_HELP_STRING([--with-gdal-config=GDAL_CONFIG],
           [the location of gdal-config]),
           [gdal_config=$withval])
if test [ -n "$gdal_config" ] ; then
    GDAL_CONFIG_SET="yes"
    AC_SUBST([GDAL_CONFIG],["${gdal_config}"])
    AC_MSG_NOTICE(gdal-config set to $GDAL_CONFIG)
fi

if test ["$GDAL_CONFIG_SET" = "no"] ; then
  AC_PATH_PROG([GDAL_CONFIG], ["$GDAL_CONFIG"],["no"])
  if test ["$GDAL_CONFIG" = "no"] ; then
    AC_MSG_RESULT(no)
    AC_MSG_ERROR([gdal-config not found or not executable.])
  fi
else
  AC_MSG_CHECKING(gdal-config exists)
  if test -r "${GDAL_CONFIG}"; then
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
    AC_MSG_ERROR([gdal-config not found - configure argument error.])
  fi
  AC_MSG_CHECKING(gdal-config executable)
  if test -x "${GDAL_CONFIG}"; then
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
    AC_MSG_ERROR([gdal-config not executable.])
  fi
fi


AC_MSG_CHECKING(gdal-config usability)
if test `${GDAL_CONFIG} --version`;
then
	GDAL_CPPFLAGS=`${GDAL_CONFIG} --cflags`
	GDAL_VERSION=`${GDAL_CONFIG} --version`
	GDAL_LIBS=`${GDAL_CONFIG} --libs`
	GDAL_DEP_LIBS=`${GDAL_CONFIG} --dep-libs`
	GDAL_DATADIR=`${GDAL_CONFIG} --datadir`
	AC_MSG_RESULT(yes)
else
	AC_MSG_RESULT(no)
	echo "Error: gdal-config not found"
	echo "The gdal-config script distributed with GDAL could not be found."
	echo "If you have not installed the GDAL libraries, you can"
	echo "download the source from  https://gdal.org"
	echo "If you have installed the GDAL libraries, then make sure that"
	echo "gdal-config is in your path. Try typing gdal-config at a"
	echo "shell prompt and see if it runs. If not, use:"
	echo " --configure-args='--with-gdal-config=/usr/local/bin/gdal-config'"
	echo "with appropriate values for your installation."
	echo ""

	exit 1
fi

AC_MSG_NOTICE([GDAL: ${GDAL_VERSION}])
AC_MSG_CHECKING([GDAL version >= 2.0.1])

GDAL_MAJ_VER=`echo $GDAL_VERSION | cut -d "." -f1`
if test ${GDAL_MAJ_VER} -lt 2 ; then
  AC_MSG_RESULT(no)
  AC_MSG_ERROR([apcf is not compatible with GDAL versions below 2.0.1])
else
   AC_MSG_RESULT(yes)
fi

INLIBS="${LIBS}"
INCPPFLAGS="${CPPFLAGS}"
INPKG_CPPFLAGS="${PKG_CPPFLAGS}"
INPKG_LIBS="${PKG_LIBS}"

AC_SUBST([PKG_CPPFLAGS], ["${INPKG_CPPFLAGS} ${GDAL_CPPFLAGS}"])
AC_SUBST([PKG_LIBS], ["${INPKG_LIBS} ${GDAL_LIBS}"])

# honor PKG_xx overrides
# for CPPFLAGS we will superfluously double R's flags
# since we'll set PKG_CPPFLAGS with this, but that shouldn't hurt
CPPFLAGS="${INCPPFLAGS} ${PKG_CPPFLAGS}"

gdalok=yes
AC_CHECK_HEADERS(gdal.h,,gdalok=no)
if test "${gdalok}" = no; then
   AC_MSG_ERROR([gdal.h not found in given locations.])
fi

NEED_DEPS=no
LIBS="${INLIBS} ${PKG_LIBS}"
[cat > gdal_test.cpp <<_EOCONF
#include <gdal.h>
#ifdef __cplusplus
extern "C" {
#endif
int main() {
GDALAllRegister();
}
#ifdef __cplusplus
}
#endif
_EOCONF]

AC_MSG_CHECKING(GDAL: linking with --libs only)
${CXX} ${CPPFLAGS} -o gdal_test gdal_test.cpp ${LIBS} 2> errors.txt
if test `echo $?` -ne 0 ; then
gdalok=no
AC_MSG_RESULT(no)
else
AC_MSG_RESULT(yes)
fi

if test "${gdalok}" = no; then
AC_MSG_CHECKING(GDAL: linking with --libs and --dep-libs)
LIBS="${LIBS} ${GDAL_DEP_LIBS}"
gdalok=yes
${CXX} ${CPPFLAGS} -o gdal_test gdal_test.cpp ${LIBS} 2>> errors.txt
if test `echo $?` -ne 0 ; then
gdalok=no
fi
if test "${gdalok}" = yes; then
    NEED_DEPS=yes
    AC_MSG_RESULT(yes)
else
    AC_MSG_RESULT(no)
fi
fi

if test "${gdalok}" = no; then
   cat errors.txt
   AC_MSG_NOTICE([Install failure: compilation and/or linkage problems.])
   AC_MSG_ERROR([GDALAllRegister not found in libgdal.])
fi

rm -f gdal_test errors.txt gdal_test.cpp

GDAL_GE_250="no"
GDAL_MAJ_VER=`echo $GDAL_VERSION | cut -d "." -f1`
GDAL_MOD_VER=`echo $GDAL_VERSION | cut -d "." -f2`
if test "${GDAL_MAJ_VER}" = 2 ; then
  if test "${GDAL_MOD_VER}" -ge 5 ; then
    GDAL_GE_250="yes"
  fi
else
  if test "${GDAL_MAJ_VER}" -ge 3 ; then
    GDAL_GE_250="yes"
  fi
fi

GDAL_DATA_TEST_FILE="${GDAL_DATADIR}/pcs.csv"
AC_MSG_CHECKING(GDAL: ${GDAL_DATADIR}/pcs.csv readable)
if test -r "${GDAL_DATA_TEST_FILE}" ; then
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
  if test "${GDAL_GE_250}" = "no" ; then
    AC_MSG_ERROR([pcs.csv not found in GDAL data directory.])
  fi
fi

# Optional local copy of GDAL datadir -----------------------------------------
data_copy=no
AC_ARG_WITH([data-copy],
    AC_HELP_STRING([--with-data-copy=yes/no],
               [local copy of data directories in package, default no]),
               [data_copy=$withval])
if test "${data_copy}" = "yes" ; then
AC_MSG_NOTICE([Copy data for:])
  if test -d "${GDAL_DATADIR}" ; then
    cp -r "${GDAL_DATADIR}" "${R_PACKAGE_DIR}"
    AC_MSG_NOTICE([  GDAL: ${GDAL_DATADIR}])
  else
    AC_MSG_ERROR([GDAL data files not found.])
  fi
fi

# test whether PROJ is available to gdal --------------------------------------
gdal_has_proj=no
[cat > gdal_proj.cpp <<_EOCONF
#include <gdal.h>
#include <ogr_srs_api.h>
#include <ogr_spatialref.h>
int main(int argc, char *argv[]) {
	OGRSpatialReference *dest = new OGRSpatialReference;
	OGRSpatialReference *src = new OGRSpatialReference;
    src->importFromEPSG(4326);
    dest->importFromEPSG(3857);
	OGRCoordinateTransformation *ct = OGRCreateCoordinateTransformation(src, dest);
	return(ct == NULL); // signals PROJ is not available through gdal
}
_EOCONF]

AC_MSG_CHECKING(GDAL: checking whether PROJ is available for linking:)
${CXX} ${CPPFLAGS} -o gdal_proj gdal_proj.cpp ${LIBS} 2> errors.txt
if test `echo $?` -ne 0 ; then
gdal_has_proj=no
AC_MSG_RESULT(no)
else
gdal_has_proj=yes
AC_MSG_RESULT(yes)
fi

if test "${gdal_has_proj}" = no; then
   cat errors.txt
   AC_MSG_NOTICE([Install failure: compilation and/or linkage problems.])
   AC_MSG_ERROR([cannot link projection code])
fi

AC_MSG_CHECKING(GDAL: checking whether PROJ is available fur running:)
./gdal_proj
if test `echo $?` -ne 0 ; then
gdal_has_proj=no
AC_MSG_RESULT(no)
else
gdal_has_proj=yes
AC_MSG_RESULT(yes)
fi
if test "${gdal_has_proj}" = no; then
   AC_MSG_ERROR([OGRCoordinateTransformation() does not return a coord.trans: PROJ not available?])
fi
rm -fr errors.txt gdal_proj.cpp gdal_proj
AC_MSG_NOTICE([GDAL: ${GDAL_VERSION}])


#------------------------------------------------------------------------------
#  GEOS
#------------------------------------------------------------------------------
GEOS_CONFIG="geos-config"

GEOS_CONFIG_SET="no"

AC_ARG_WITH([geos-config],
    AC_HELP_STRING([--with-geos-config=GEOS_CONFIG],
           [the location of geos-config]),
           [geos_config=$withval])
if test [ -n "$geos_config" ] ; then
    GEOS_CONFIG_SET="yes"
    AC_SUBST([GEOS_CONFIG],["${geos_config}"])
    AC_MSG_NOTICE(geos-config set to $GEOS_CONFIG)
fi

if test ["$GEOS_CONFIG_SET" = "no"] ; then
  AC_PATH_PROG([GEOS_CONFIG], ["$GEOS_CONFIG"],["no"])
  if test ["$GEOS_CONFIG" = "no"] ; then
    AC_MSG_RESULT(no)
    AC_MSG_ERROR([geos-config not found or not executable.])
  fi
else
  AC_MSG_CHECKING(geos-config exists)
  if test -r "${GEOS_CONFIG}"; then
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
    AC_MSG_ERROR([geos-config not found - configure argument error.])
  fi
  AC_MSG_CHECKING(geos-config executable)
  if test -x "${GEOS_CONFIG}"; then
    AC_MSG_RESULT(yes)
  else
    AC_MSG_RESULT(no)
    AC_MSG_ERROR([geos-config not executable.])
  fi
fi

AC_MSG_CHECKING(geos-config usability)
if test `${GEOS_CONFIG} --version`
then
  GEOS_CLIBS="`${GEOS_CONFIG} --clibs`"
  #GEOS_DEP_CLIBS=`geos-config --static-clibs` -- this gives -m instead of -lm, which breaks clang
  # fixed in 3.7.0 at https://github.com/libgeos/libgeos/pull/73#issuecomment-262208677
  GEOS_DEP_CLIBS=`${GEOS_CONFIG} --static-clibs | sed 's/-m/-lm/g'`
  GEOS_CPPFLAGS=`${GEOS_CONFIG} --cflags`
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
  AC_MSG_ERROR([${GEOS_CONFIG} not usable])
fi

GEOS_VERSION=`${GEOS_CONFIG} --version`
AC_MSG_NOTICE([GEOS: ${GEOS_VERSION}])
AC_MSG_CHECKING([GEOS version >= 3.4.0]) # GDAL 2.0.1 requires GEOS 3.1.0
GEOS_VER_DOT=`echo $GEOS_VERSION | tr -d ".[[:alpha:]]"`
if test ${GEOS_VER_DOT} -lt 340 ; then
  AC_MSG_RESULT(no)
  AC_MSG_ERROR([upgrade GEOS to 3.4.0 or later])
else
  AC_MSG_RESULT(yes)
fi

AC_SUBST([PKG_CPPFLAGS], ["${INPKG_CPPFLAGS} ${PROJ_CPPFLAGS} ${GDAL_CPPFLAGS} ${GEOS_CPPFLAGS}"])
AC_SUBST([PKG_LIBS], ["${INPKG_LIBS} ${GDAL_LIBS}"])
if test "${NEED_DEPS}" = yes; then
   AC_SUBST([PKG_LIBS], ["${PKG_LIBS} ${GDAL_DEP_LIBS}"])
fi

# honor PKG_xx overrides
# for CPPFLAGS we will superfluously double R's flags
# since we'll set PKG_CPPFLAGS with this, but that shouldn't hurt
CPPFLAGS="${CPPFLAGS} ${PKG_CPPFLAGS}"
LIBS="${LIBS} ${PKG_LIBS}"

geosok=yes
AC_CHECK_HEADERS(geos_c.h,,geosok=no)
if test "${geosok}" = no; then
   AC_MSG_ERROR([geos_c.h not found in given locations.])
fi

[cat > geos_test.cpp <<_EOCONF
#include <geos_c.h>
#ifdef __cplusplus
extern "C" {
#endif
static void __errorHandler(const char *fmt, ...) {
    return;
}
static void __warningHandler(const char *fmt, ...) {
    return;
}
int main() {
    GEOSContextHandle_t r = initGEOS_r((GEOSMessageHandler) __warningHandler, (GEOSMessageHandler) __errorHandler);
    finishGEOS_r(r);
}
#ifdef __cplusplus
}
#endif
_EOCONF]

#echo "${CXX} ${CPPFLAGS} -o geos_test geos_test.cpp ${LIBS}"
AC_MSG_CHECKING(geos: linking with ${GEOS_CLIBS})
${CXX} ${CPPFLAGS} -o geos_test geos_test.cpp ${GEOS_CLIBS} 2> errors.txt
if test `echo $?` -ne 0 ; then
 geosok=no
 AC_MSG_RESULT(no)
else
 AC_SUBST([PKG_LIBS], ["${PKG_LIBS} ${GEOS_CLIBS}"])
 AC_MSG_RESULT(yes)
fi

if test "${geosok}" = no; then
  AC_MSG_CHECKING(geos: linking with ${GEOS_DEP_CLIBS})
  ${CXX} ${CPPFLAGS} -o geos_test geos_test.cpp ${GEOS_DEP_CLIBS} 2> errors.txt
  if test `echo $?` -ne 0 ; then
    geosok=no
    AC_MSG_RESULT(no)
    cat errors.txt
    AC_MSG_NOTICE([Install failure: compilation and/or linkage problems.])
    AC_MSG_ERROR([initGEOS_r not found in libgeos_c.])
  else
    AC_SUBST([PKG_LIBS], ["${PKG_LIBS} ${GEOS_DEP_CLIBS}"])
    AC_MSG_RESULT(yes)
  fi
fi

rm -f geos_test errors.txt geos_test.cpp


#------------------------------------------------------------------------------
#  Concluding Substitutions
#------------------------------------------------------------------------------
AC_MSG_NOTICE([Package CPP flags: ${PKG_CPPFLAGS}])
AC_MSG_NOTICE([Package LIBS: ${PKG_LIBS}])

AC_CONFIG_FILES(src/Makevars)
AC_OUTPUT
