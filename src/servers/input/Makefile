PRIVATE_HEADERS=    interface shared app storage kernel system libroot
OS_HEADERS=         interface support app storage translation locale add-ons/input_server

# .PATH: ${.CURDIR}/mime

PROG=	input_server

SRCS+=      	InputServer.cpp InputServerDevice.cpp InputServerFilter.cpp InputServerMethod.cpp AddOnManager.cpp \
              MouseSettings.cpp KeyboardSettings.cpp MethodReplicant.cpp MethodMenuItem.cpp BottomlineWindow.cpp \ 
              PathList.cpp AddOnMonitor.cpp AddOnMonitorHandler.cpp NodeMonitorHandler.cpp


CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow

LDADD+=	-lbe -licon -lagg
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/icon -L${.CURDIR}/../../libs/agg

CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers
CPPFLAGS+= -I${.CURDIR}/mime

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.include <bsd.prog.mk>
