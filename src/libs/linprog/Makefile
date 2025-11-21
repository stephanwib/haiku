.include <bsd.own.mk>

OS_HEADERS=
PRIVATE_HEADERS=

LIB=	linprog

.PATH: ${.CURDIR}/src

SRCS+=     

CPPFLAGS+= -I${.CURDIR}

CXXFLAGS= -Wno-multichar -Wno-old-style-cast -Wno-shadow


.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

#LDFLAGS= -L/usr/pkg/lib -rpath=/usr/pkg/lib -lroot -licudata -licui18n -licuio -licuuc -lz -lzstd


WARNS=		5

.include <bsd.lib.mk>
