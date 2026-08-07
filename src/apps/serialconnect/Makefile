PRIVATE_HEADERS=    interface shared
OS_HEADERS=         interface support app storage translation locale add-ons/graphics

PROG=	SerialConnect


postbuild: ${PROG}

realall: postbuild

.PATH: ${.CURDIR}/libvterm

SRCS+=      CustomRateWindow.cpp FileSender.cpp SerialApp.cpp SerialWindow.cpp TermView.cpp XModem.cpp \
            encoding.c input.c parser.c pen.c screen.c state.c unicode.c vterm.c


CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow

LDADD+=	-lbe -licon -lagg -ltracker
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/icon -L${.CURDIR}/../../libs/agg \
          -L${.CURDIR}/../../libs/libtracker -L/usr/pkg/lib

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
