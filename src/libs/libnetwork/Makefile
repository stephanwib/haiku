.include <bsd.own.mk>

LIB=	netapi

CXXFLAGS= -g -Wno-multichar -Wno-old-style-cast -Wno-shadow
# -std=c++17 

LDFLAGS= -L/usr/pkg/lib -rpath=/usr/pkg/lib -lroot

WARNS=		5


.include "${.CURDIR}/../../kits/network/libnetapi/Makefile.inc"


.include <bsd.lib.mk>
