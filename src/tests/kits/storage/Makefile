.include <bsd.own.mk>

OS_HEADERS= support storage
#PRIVATE_HEADERS= shared

LIB=	storagetest

# .PATH: ${.CURDIR}

SRCS+=     BasicTest.cpp DataIOTest.cpp

CXXFLAGS= -Wno-multichar -Wno-old-style-cast -Wno-shadow -D_NETBSD_SOURCE
#CPPFLAGS+= -I${.CURDIR}

CPPFLAGS+= -I${.CURDIR}/../../../../headers
CPPFLAGS+= -I${.CURDIR}/../../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../../headers/tools/cppunit

#LDFLAGS= -L/usr/pkg/lib -rpath=/usr/pkg/lib -lroot -licudata -licui18n -licuio -licuuc -lz -lzstd

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../../headers/os/${HEADER}"
.endfor

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../../headers/private/${HEADER}"
.endfor



WARNS=		5

.include <bsd.lib.mk>
