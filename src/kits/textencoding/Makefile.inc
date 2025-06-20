LIBRARY_HEADERS=
PRIVATE_HEADERS= textencoding
OS_HEADERS=

.PATH: ${.CURDIR}/../../kits/textencoding

SRCS+=      CharacterSet.cpp CharacterSetRoster.cpp character_sets.cpp utf8_conversions.cpp

# Issues:

CPPFLAGS+= -I${.CURDIR}/../../kits/textencoding
#CPPFLAGS+= "-I${.CURDIR}/../../../headers"
#CPPFLAGS+= "-I${.CURDIR}/../../../headers/os"

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
