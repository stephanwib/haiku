

.include <bsd.own.mk>

LIB=	be

# Notes:
#  Compiler suggests -std=gnu99 due to alloca usage
#  Needs libicu and mapm (Math library) from pkgsrc

CXXFLAGS= -std=c++17 -Wno-multichar -Wno-old-style-cast -Wno-shadow

# XXX Compiler suggests -std=gnu99 due to alloca usage

LDFLAGS= -L/usr/pkg/lib -lroot -licudata -licui18n -licuio -licuuc -lz

WARNS=		5


.include "${.CURDIR}/../../kits/app/Makefile.inc"
.include "${.CURDIR}/../../kits/interface/Makefile.inc"
.include "${.CURDIR}/../../kits/support/Makefile.inc"
.include "${.CURDIR}/../../kits/locale/Makefile.inc"
.include "${.CURDIR}/../../kits/textencoding/Makefile.inc"
.include "${.CURDIR}/../../kits/translation/Makefile.inc"
.include "${.CURDIR}/../../kits/shared/Makefile.inc"
#.include "${.CURDIR}/../../kits/storage/Makefile.inc"

.include <bsd.lib.mk>
