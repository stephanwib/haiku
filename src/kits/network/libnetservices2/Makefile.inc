PRIVATE_HEADERS= app net shared storage support
OS_HEADERS= net support app storage interface

.PATH: ${.CURDIR}/../../kits/network/libnetservices2

SRCS+=	ErrorsExt.cpp HttpBuffer.cpp HttpFields.cpp HttpParser.cpp HttpRequest.cpp HttpResult.cpp \
			HttpSerializer.cpp HttpSession.cpp HttpTime.cpp NetServicesMisc.cpp


CPPFLAGS.HttpParser.o+=  "-I${.CURDIR}/../../../headers/private/netservices2"

CPPFLAGS+= "-I${.CURDIR}/../../../headers"
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os"

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
