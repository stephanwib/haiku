PRIVATE_HEADERS=    interface shared
OS_HEADERS=         interface support app storage translation locale add-ons/graphics

PROG=	Poorman

postbuild: ${PROG}
realall: postbuild

.PATH:      ${.CURDIR}/libhttpd

# build special headers
mime_encodings.h: mime_encodings.txt
	rm -f ${.TARGET}
	sed < ${.ALLSRC} > ${.TARGET} \
		-e 's/#.*//' \
		-e 's/[ 	]*$$//' \
		-e '/^$$/d' \
		-e 's/[ 	][ 	]*/", 0, "/' \
		-e 's/^/{ "/' \
		-e 's/$$/", 0 },/'

mime_types.h: mime_types.txt
	rm -f ${.TARGET}
	sed < ${.ALLSRC} > ${.TARGET} \
		-e 's/#.*//' \
		-e 's/[ 	]*$$//' \
		-e '/^$$/d' \
		-e 's/[ 	][ 	]*/", 0, "/' \
		-e 's/^/{ "/' \
		-e 's/$$/", 0 },/'



SRCS+=      PoorManWindow.cpp PoorManView.cpp PoorManAdvancedView.cpp StatusSlider.cpp \
            PoorManServer.cpp PoorManSiteView.cpp PoorManLogger.cpp PoorManLoggingView.cpp \
            PoorManPreferencesWindow.cpp PoorManApplication.cpp constants.cpp

# libhttpd
SRCS+=      libhttpd.c match.c tdate_parse.c


CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow
CFLAGS+=    -Wno-multichar #-Wno-old-style-cast -Wno-shadow
CPPFLAGS+=  -DHAVE_INT64T -DHAVE_SOCKLENT -DHAVE_ATOLL


LDADD+=	-lbe -licon -lagg -ltracker
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/icon -L${.CURDIR}/../../libs/agg \
          -L${.CURDIR}/../../libs/libtracker -L/usr/pkg/lib

CPPFLAGS+= -I${.CURDIR}/libhttpd
CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers/posix
CPPFLAGS+= -I${.CURDIR}/../../../headers

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.include "${.CURDIR}/../../resources.mk"
.include <bsd.prog.mk>
