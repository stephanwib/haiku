PRIVATE_HEADERS=    
OS_HEADERS=         

PROG=	appserver

SRCS+=      Angle.cpp AppServer.cpp BitmapManager.cpp ClientMemoryAllocator.cpp CursorData.cpp \
            CursorManager.cpp CursorSet.cpp Canvas.cpp DrawState.cpp DelayedMessage.cpp Desktop.cpp \
            DesktopSettings.cpp DesktopListener.cpp DirectWindowInfo.cpp EventDispatcher.cpp \
            EventStream.cpp InputManager.cpp IntPoint.cpp IntRect.cpp Layer.cpp MessageLooper.cpp

CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow

LDADD+=	-lbe
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/icon -L${.CURDIR}/../../libs/agg -L/usr/pkg/lib

CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.include <bsd.prog.mk>
