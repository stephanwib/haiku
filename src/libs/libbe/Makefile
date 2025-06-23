

.include <bsd.own.mk>

LIB=	be

#LIBDPLIBS+=	root /lib

CXXFLAGS= -std=c++17 -Wno-multichar -Wno-old-style-cast -Wno-shadow

# XXX Compiler suggests -std=gnu99 due to alloca usage

LDFLAGS= -lroot -licudata

WARNS=		5


.include "${.CURDIR}/../../kits/app/Makefile.inc"
.include "${.CURDIR}/../../kits/interface/Makefile.inc"
.include "${.CURDIR}/../../kits/support/Makefile.inc"
.include "${.CURDIR}/../../kits/locale/Makefile.inc"
.include "${.CURDIR}/../../kits/textencoding/Makefile.inc"
.include "${.CURDIR}/../../kits/translation/Makefile.inc"
.include "${.CURDIR}/../../kits/shared/Makefile.inc"

.include <bsd.lib.mk>
