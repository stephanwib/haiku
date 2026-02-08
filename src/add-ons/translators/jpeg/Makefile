.include <bsd.own.mk>

PRIVATE_HEADERS=    interface
OS_HEADERS=         interface support app storage translation locale add-ons/graphics

.PATH: ${.CURDIR}/../shared

LIB=	JPEGTranslator

SRCS=  be_jdatadst.cpp be_jdatasrc.cpp be_jerror.cpp exif_parser.cpp JPEGTranslator.cpp

# shared
SRCS+=  BaseTranslator.cpp StreamBuffer.cpp TranslatorSettings.cpp TranslatorWindow.cpp


CXXFLAGS= -g -Wno-multichar -Wno-old-style-cast -Wno-shadow
CPPFLAGS+= -I${.CURDIR} -I${.CURDIR}/../shared

LDFLAGS= -L/usr/pkg/lib -L${.CURDIR}/../../../libs/libbe -lroot -lbe -ljpeg
LDFLAGS+= -Wl,-e,main  # Library can also be used as an executable


CPPFLAGS+= -I${.CURDIR}/../../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../../headers
CPPFLAGS+= -I/usr/pkg/include

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../../headers/os/${HEADER}"
.endfor


.include <bsd.lib.mk>
