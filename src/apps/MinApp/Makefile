PRIVATE_HEADERS=    interface
OS_HEADERS=         interface app # support storage translation locale add-ons/graphics

PROG=	MinApp

SRCS+=      MinApp.cpp

CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow

LDADD+=	-lbe
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L/usr/pkg/lib

CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.include <bsd.prog.mk>
