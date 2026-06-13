#PRIVATE_HEADERS=    app interface locale shared tracker
OS_HEADERS=          storage support #interface  app translation locale kernel add-ons/graphics

postbuild: ${PROG}
realall: postbuild

PROG=       UnitTester

SRCS+=      UnitTester.cpp

CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow

LDADD+=	-lbe -lbetest -licon -lagg -lcppunit
LDFLAGS+= -L${.CURDIR}/../libs/libbe -L${.CURDIR}/../libs/libbetest -L${.CURDIR}/../libs/icon -L${.CURDIR}/../libs/agg -L${.CURDIR}/../libs/cppunit

#LIBDPLIBS+= cppunit ${.CURDIR}/../libs/cppunit
#LIBDO.cppunit = _external

#LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/icon -L${.CURDIR}/../../libs/agg \
#          -L${.CURDIR}/../../libs/libtracker -L/usr/pkg/lib

CPPFLAGS+= -I/usr/pkg/include
CPPFLAGS+= -I${.CURDIR}
CPPFLAGS+= -I${.CURDIR}/../../headers/tools/cppunit
CPPFLAGS+= -I${.CURDIR}/../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../headers

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../headers/os/${HEADER}"
.endfor

.include "${.CURDIR}/../resources.mk"
.include <bsd.prog.mk>
