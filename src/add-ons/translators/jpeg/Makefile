.include <bsd.own.mk>

.PATH: ${.CURDIR}/../shared

LIB=	JPEGTranslator

SRCS=  be_jdatadst.cpp be_jdatasrc.cpp be_jerror.cpp exif_parser.cpp JPEGTranslator.cpp

# shared
SRCS+=  BaseTranslator.cpp StreamBuffer.cpp TranslatorSettings.cpp TranslatorWindow.cpp


CXXFLAGS= -g -Wno-multichar -Wno-old-style-cast -Wno-shadow
CPPFLAGS+= -I${.CURDIR} -I${.CURDIR}/../shared

LDFLAGS= -L/usr/pkg/lib -L${.CURDIR}/../../libs/libbe -lroot -lbe -ljpeg
LDFLAGS+= -Wl,-e,main  # Library can also be used as an executable


.include <bsd.lib.mk>
