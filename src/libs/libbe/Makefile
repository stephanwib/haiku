

.include <bsd.own.mk>

LIB=	be

#LIBDPLIBS+=	root /lib

CXXFLAGS+= -Wno-multichar
CXXFLAGS+= -Wno-old-style-cast
CXXFLAGS+= -Wno-shadow
CXXFLAGS+= -lroot

WARNS=		5


.include "${.CURDIR}/../../kits/app/Makefile.inc"

.include <bsd.lib.mk>
