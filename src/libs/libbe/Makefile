

.include <bsd.own.mk>

LIB=	be

#LIBDPLIBS+=	root /lib

CXXFLAGS= -std=c++17 -Wno-multichar -Wno-old-style-cast -Wno-shadow

LDFLAGS= -lroot

WARNS=		5


.include "${.CURDIR}/../../kits/app/Makefile.inc"
.include "${.CURDIR}/../../kits/interface/Makefile.inc"
.include "${.CURDIR}/../../kits/support/Makefile.inc"
.include "${.CURDIR}/../../kits/locale/Makefile.inc"
.include "${.CURDIR}/../../kits/translation/Makefile.inc"
.include "${.CURDIR}/../../kits/textencoding/Makefile.inc"

.include <bsd.lib.mk>
