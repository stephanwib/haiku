#LIBRARY_HEADERS= 
#PRIVATE_HEADERS= 
OS_HEADERS= mail

.PATH: ${.CURDIR}/../../kits/support
      
SRCS+=    Architecture.cpp Archivable.cpp ArchivingManagers.cpp Base64.cpp Beep.cpp


# Issues:

CPPFLAGS+= "-I${.CURDIR}/../../../headers/private"

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= -I${.CURDIR}/../../../headers/private/${HEADER}
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
