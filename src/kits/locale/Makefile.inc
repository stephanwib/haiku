#LIBRARY_HEADERS= 
#PRIVATE_HEADERS= 
#OS_HEADERS= 

.PATH: ${.CURDIR}/../../kits/locale

SRCS+=    Catalog.cpp CatalogData.cpp CatalogStub.cpp Collator.cpp Country.cpp

# Issues:

#CPPFLAGS+= -I${.CURDIR}/../../../headers/private
#CPPFLAGS+= -I${.CURDIR}/../../kits/support

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= -I${.CURDIR}/../../../headers/private/${HEADER}
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
