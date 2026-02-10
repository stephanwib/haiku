PRIVATE_HEADERS= app net shared storage support
OS_HEADERS= net support app storage interface

.PATH: ${.CURDIR}/../../kits/network/libnetservices

SRCS+=	DataRequest.cpp
			HttpAuthentication.cpp HttpHeaders.cpp HttpForm.cpp HttpRequest.cpp HttpResult.cpp FileRequest.cpp \
      GopherRequest.cpp Geolocation.cpp HttpTime.cpp NetworkCookie.cpp NetworkCookieJar.cpp NetworkRequest.cpp \
			UrlContext.cpp UrlProtocolAsynchronousListener.cpp UrlProtocolDispatchingListener.cpp UrlProtocolListener.cpp \
			UrlProtocolRoster.cpp UrlRequest.cpp UrlResult.cpp UrlSynchronousRequest.cpp


CPPFLAGS+= "-I${.CURDIR}/../../../headers"
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os"

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
