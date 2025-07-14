.include <bsd.own.mk>

OS_HEADERS= support

LIB=	icon

.PATH: ${.CURDIR}/flat_icon \
       ${.CURDIR}/generic \
       ${.CURDIR}/message \
       ${.CURDIR}/shape \
       ${.CURDIR}/style \
       ${.CURDIR}/transformable \
       ${.CURDIR}/transformer

SRCS+=     Icon.cpp IconRenderer.cpp IconUtils.cpp

# flat_icon
SRCS+=     

# generic
SRCS+=     

# message
SRCS+=     

# shape
SRCS+=     

# style
SRCS+=     

# transformable
SRCS+=     

# transformer
SRCS+=     

CXXFLAGS= -Wno-multichar -Wno-old-style-cast -Wno-shadow
CPPFLAGS+= -I${.CURDIR}
CPPFLAGS+= -I${.CURDIR}/generic
CPPFLAGS+= -I${.CURDIR}/flat_icon
CPPFLAGS+= -I${.CURDIR}/shape
CPPFLAGS+= -I${.CURDIR}/message
CPPFLAGS+= -I${.CURDIR}/transformable
CPPFLAGS+= -I${.CURDIR}/transformer

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

#LDFLAGS= -L/usr/pkg/lib -rpath=/usr/pkg/lib -lroot -licudata -licui18n -licuio -licuuc -lz -lzstd


WARNS=		5


#.include "${.CURDIR}/../../kits/app/Makefile.inc"


.include <bsd.lib.mk>
