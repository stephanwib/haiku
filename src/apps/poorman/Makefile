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


libhttpd.c : mime_encodings.h mime_types.h

SRCS+=      PoorManWindow.cpp PoorManView.cpp PoorManAdvancedView.cpp StatusSlider.cpp \
            PoorManServer.cpp PoorManSiteView.cpp PoorManLogger.cpp PoorManLoggingView.cpp \
            PoorManPreferencesWindow.cpp PoorManApplication.cpp constants.cpp

# libhttpd
SRCS+=      libhttpd.c match.c tdate_parse.c


CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow
CFLAGS+=    -Wno-multichar -Wno-stringop-overflow #-Wno-old-style-cast -Wno-shadow
CPPFLAGS+=  -DHAVE_INT64T -DHAVE_SOCKLENT -DHAVE_ATOLL -DHAVE__PROGNAME -DHAVE_FCNTL -DHAVE_POLL_H \
            -DHAVE_SYS_POLL_H -DHAVE_DIRENT_H -DHAVE_STRERROR -DHAVE_WAITPID -DHAVE_VSNPRINTF -DHAVE_SETSID \
            -DHAVE_UNISTD_H -DHAVE_MMAP -DHAVE_SELECT -DHAVE_SOCKLENT

# HAVE__PROGNAME=1 HAVE_FCNTL_H=1 HAVE_GRP_H=1 HAVE_MEMORY_H=1 HAVE_POLL_H=1 HAVE_SYS_POLL_H=1 TIME_WITH_SYS_TIME=1 HAVE_DIRENT_H=1 HAVE_STRERROR=1 HAVE_WAITPID=1 HAVE_VSNPRINTF=1 HAVE_SETSID=1 HAVE_SIGSET=1 HAVE_ATOLL=1 HAVE_UNISTD_H=1 HAVE_GETPAGESIZE=1 HAVE_MMAP=1 HAVE_SELECT=1 HAVE_POLL=1 HAVE_TM_GMTOFF=1 HAVE_SOCKLENT=1 HAVE_INT64T=1 


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
