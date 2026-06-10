PRIVATE_HEADERS=    interface
OS_HEADERS=         interface support app storage translation locale add-ons/graphics

.PATH: ${.CURDIR}/document ${.CURDIR}/document/savers ${.CURDIR}/generic ${.CURDIR}/generic/listener \
       ${.CURDIR}/generic ${.CURDIR}/generic/support ${.CURDIR}/generic/command/ ${.CURDIR}/generic/gui \
       ${.CURDIR}/generic/gui/panel ${.CURDIR}/generic/gui/panel/color_picker ${.CURDIR}/generic/gui/scrollview \
       ${.CURDIR}/generic/gui/stateview ${.CURDIR}/generic/property ${.CURDIR}/generic/property/specific_properties \
       ${.CURDIR}/generic/property/view ${.CURDIR}/generic/property/view/specific_properties

PROG=	Icon-O-Matic


postbuild: ${PROG}

realall: postbuild


SRCS+=      

CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow

LDADD+=	-lbe -licon -lagg -ltracker
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/icon -L${.CURDIR}/../../libs/agg \
          -L${.CURDIR}/../../libs/libtracker -L/usr/pkg/lib

CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers/posix
CPPFLAGS+= -I${.CURDIR}/../../../headers

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.include "${.CURDIR}/../../resources.mk"
.include <bsd.prog.mk>
