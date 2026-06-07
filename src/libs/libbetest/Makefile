.include <bsd.own.mk>

OS_HEADERS= app interface support storage
PRIVATE_HEADERS= shared

LIB=	betest

.PATH: ${.CURDIR}/../../tools/cppunit

SRCS+=     BTestCase.cpp BTestSuite.cpp SemaphoreSyncObject.cpp TestApp.cpp TestListener.cpp TestShell.cpp \
           TestUtils.cpp ThreadedTestCase.cpp BetestInit.cpp


CXXFLAGS= -Wno-multichar -Wno-old-style-cast -Wno-shadow

CPPFLAGS+= -I/usr/pkg/include
CPPFLAGS+= -I${.CURDIR}/../../tools/cppunit
CPPFLAGS+= -I${.CURDIR}/../../../headers/tools/cppunit
CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers

LDFLAGS= -L/usr/pkg/lib -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/cppunit -rpath=/usr/pkg/lib -lroot -lbe

LIBDPLIBS+= cppunit ${.CURDIR}/../cppunit
LIBDO.cppunit = _external

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

WARNS=		5

.include <bsd.lib.mk>
