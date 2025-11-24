.include <bsd.own.mk>

OS_HEADERS= support interface
PRIVATE_HEADERS= shared

LIB=	linprog

.PATH: ${.CURDIR}/src

SRCS+=     ActiveSetSolver.cpp Constraint.cpp LayoutOptimizer.cpp LinearSpec.cpp \
           Summand.cpp Variable.cpp


CPPFLAGS+= -I${.CURDIR} -I${.CURDIR}/../../../headers/libs/linprog
CXXFLAGS= -Wno-multichar -Wno-old-style-cast -Wno-shadow
#LDFLAGS= -L/usr/pkg/lib -rpath=/usr/pkg/lib -lroot -licudata -licui18n -licuio -licuuc -lz -lzstd


.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor


WARNS=		5

.include <bsd.lib.mk>
