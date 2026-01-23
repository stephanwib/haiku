

.include <bsd.own.mk>

LIB=	tracker

# Notes:
#  Compiler suggests -std=gnu99 due to alloca usage
#  Needs zstd, icu and mapm (Math library) from pkgsrc

CXXFLAGS= -g -std=c++17 -Wno-multichar -Wno-old-style-cast -Wno-shadow

# XXX Compiler suggests -std=gnu99 due to alloca usage

LDFLAGS= -L/usr/pkg/lib -rpath=/usr/pkg/lib -lroot -lbe


WARNS=		5


.include "${.CURDIR}/../../kits/tracker/Makefile.inc"

.include <bsd.lib.mk>

