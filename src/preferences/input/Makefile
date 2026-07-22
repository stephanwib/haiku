PRIVATE_HEADERS=    interface textencoding shared libroot system preferences
OS_HEADERS=         interface support app storage translation locale add-ons/graphics add-ons/input_server

# .PATH: ${.CURDIR}/../../add-ons/accelerants/common

PROG=	Input

SRCS+=      Input.cpp InputDeviceView.cpp InputIcons.cpp InputKeyboard.cpp InputMouse.cpp InputTouchpadPref.cpp \
            InputTouchpadPrefView.cpp InputWindow.cpp KeyboardSettings.cpp KeyboardView.cpp MouseView.cpp \
            MouseSettings.cpp SettingsView.cpp

CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow

LDADD+=	-lbe -licon -lagg -ltracker
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/libtracker -L${.CURDIR}/../../libs/icon -L${.CURDIR}/../../libs/agg  -L/usr/pkg/lib

CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.include <bsd.prog.mk>
