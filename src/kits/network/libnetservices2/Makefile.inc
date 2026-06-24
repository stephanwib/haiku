

.PATH: ${.CURDIR}/../../kits/network/libnetservices2

#CPPFLAGS.ErrorsExt.cpp+=   "-I${.CURDIR}/../../../headers/private/netservices2"

SRCS+=	ErrorsExt.cpp HttpBuffer.cpp HttpFields.cpp HttpParser.cpp HttpRequest.cpp HttpResult.cpp \
			HttpSerializer.cpp HttpSession.cpp HttpTime.cpp NetServicesMisc.cpp

.for SRC in ${SRCS}
CPPFLAGS.${SRC}+= "-I${.CURDIR}/../../../headers/private/netservices2"
.endfor


#CPPFLAGS+= "-I${.CURDIR}/../../../headers"
#CPPFLAGS+= "-I${.CURDIR}/../../../headers/os"

