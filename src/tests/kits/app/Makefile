.include <bsd.own.mk>

OS_HEADERS= support storage app interface
PRIVATE_HEADERS= support

LIB=	appkittest

.PATH: ${.CURDIR}/bapplication ${.CURDIR}/bclipboard ${.CURDIR}/bcursor ${.CURDIR}/bhandler ${.CURDIR}/blooper  \
       ${.CURDIR}/bmessage ${.CURDIR}/bmessagequeue ${.CURDIR}/bmessagerunner ${.CURDIR}/bmessenger ${.CURDIR}/bpropertyinfo \
       ${.CURDIR}/broster ${.CURDIR}/common ${.CURDIR}/messaging

SRCS+=     ApplicationTest.cpp AppQuitRequestedTester.cpp AppQuitTester.cpp AppRunTester.cpp BApplicationTester.cpp


CXXFLAGS= -Wno-multichar -Wno-old-style-cast -Wno-shadow -D_NETBSD_SOURCE
CPPFLAGS+= -I${.CURDIR}

CPPFLAGS+= -I${.CURDIR}/../../../../headers
CPPFLAGS+= -I${.CURDIR}/../../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../../headers/tools/cppunit

LDFLAGS= -lroot -lbe -lcppunit -lbetest -L${.CURDIR}/../../../libs/libbe -L${.CURDIR}/../../../libs/cppunit -L${.CURDIR}/../../../libs/libbetest

#LDFLAGS= -L/usr/pkg/lib -rpath=/usr/pkg/lib -lroot -licudata -licui18n -licuio -licuuc -lz -lzstd

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../../headers/os/${HEADER}"
.endfor

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../../headers/private/${HEADER}"
.endfor



WARNS=		5

.include <bsd.lib.mk>
