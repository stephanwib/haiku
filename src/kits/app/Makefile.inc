
LIBRARY_HEADERS= icon
PRIVATE_HEADERS= shared app interface kernel libroot locale notification
OS_HEADERS= app support storage interface

.PATH: ${.CURDIR}/../../kits/app

SRCS=	AppDefs.cpp AppMisc.cpp AppServerLink.cpp

CPPFLAGS+= "-I${.CURDIR}/../../../headers"
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os"


.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
