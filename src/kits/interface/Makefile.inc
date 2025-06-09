
#LIBRARY_HEADERS= icon
#PRIVATE_HEADERS= shared app interface kernel libroot locale notification
#OS_HEADERS= app support storage interface kernel

.PATH: ${.CURDIR}/../../kits/interface

SRCS=	AboutWindow.cpp

# Issues:

#CPPFLAGS+= "-I${.CURDIR}/../../../headers"
#CPPFLAGS+= "-I${.CURDIR}/../../../headers/os"


.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
