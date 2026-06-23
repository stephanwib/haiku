.include <bsd.own.mk>

LIB=	netapi

CXXFLAGS= -g -std=c++17 -Wno-multichar -Wno-old-style-cast -Wno-shadow
# -std=c++17 

LDFLAGS= -L/usr/pkg/lib -rpath=/usr/pkg/lib -lroot

WARNS=		5

CPPFLAGS+= -I.

.include "${.CURDIR}/../../kits/network/libnetapi/Makefile.inc"
.include "${.CURDIR}/../../kits/network/libnetservices/Makefile.inc"
.include "${.CURDIR}/../../kits/network/libnetservices2/Makefile.inc"

.include <bsd.lib.mk>

