#PRIVATE_HEADERS=    app interface locale shared tracker
OS_HEADERS=          storage support #interface  app translation locale kernel add-ons/graphics

RC= ${.CURDIR}/../../bin/rc/rc 
XRES= ${.CURDIR}/../../bin/xres

PROG=       UnitTester
#RESOURCES=      

RSRCFILES=      ${RESOURCES:S/$/.rsrc/}
CLEANFILES+=    ${RSRCFILES}

.SUFFIXES: .rdef .rsrc
.rdef.rsrc:
	${RC} ${.IMPSRC} -o ${.TARGET} -I .

postbuild: ${PROG} ${RSRCFILES}
	${XRES} -o ${PROG} ${RSRCFILES}

realall: postbuild

SRCS+=      UnitTester.cpp

CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow

LDADD+=	-lbe
#LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/icon -L${.CURDIR}/../../libs/agg \
#          -L${.CURDIR}/../../libs/libtracker -L/usr/pkg/lib

CPPFLAGS+= -I/usr/pkg/include
CPPFLAGS+= -I${.CURDIR}
CPPFLAGS+= -I${.CURDIR}/../../headers/tools/cppunit
CPPFLAGS+= -I${.CURDIR}/../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../headers

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../headers/os/${HEADER}"
.endfor

.include <bsd.prog.mk>
