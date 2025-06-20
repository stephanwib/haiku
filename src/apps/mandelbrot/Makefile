PRIVATE_HEADERS=    interface
OS_HEADERS=         interface

PROG=	mandelbrot

SRCS+=      Mandelbrot.cpp FractalEngine.cpp	

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.include <bsd.prog.mk>
