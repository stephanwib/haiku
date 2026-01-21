PRIVATE_HEADERS= app net shared storage support
OS_HEADERS= net support app storage interface

.PATH: ${.CURDIR}/../../kits/tracker ${.CURDIR}/../../kits/tracker/infowindow

SRCS+=	


CPPFLAGS+= "-I${.CURDIR}/../../../headers"
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os"

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
