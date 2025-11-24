
PRIVATE_HEADERS= app net shared storage support
OS_HEADERS= net support

.PATH: ${.CURDIR}/../../kits/network/libnetapi

SRCS+=	DynamicBuffer.cpp NetEndpoint.cpp NetAddress.cpp NetBuffer.cpp NetDebug.cpp Certificate.cpp \
        NetworkAddress.cpp NetworkAddressResolver.cpp NetworkDevice.cpp NetworkInterface.cpp \
        NetworkRoster.cpp NetworkRoute.cpp NetworkSettings.cpp AbstractSocket.cpp DatagramSocket.cpp \
			  ProxySecureSocket.cpp SecureSocket.cpp Socket.cpp SocketMessenger.cpp notifications.cpp


CPPFLAGS+= "-I${.CURDIR}/../../../headers"
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os"

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
