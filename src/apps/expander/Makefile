PRIVATE_HEADERS=    interface
OS_HEADERS=         interface support app storage translation locale add-ons/graphics

PROG=	Expander

SRCS+=      ExpanderApp.cpp ExpanderWindow.cpp ExpanderThread.cpp GenericThread.cpp ExpanderSettings.cpp \
            ExpanderPreferences.cpp DirectoryFilePanel.cpp ExpanderRules.cpp PasswordAlert.cpp

CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow

LDADD+=	-lbe -licon -lagg -ltracker
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/icon -L${.CURDIR}/../../libs/agg \
          -L${.CURDIR}/../../libs/libtracker -L/usr/pkg/lib

CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers/posix
CPPFLAGS+= -I${.CURDIR}/../../../headers

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.include <bsd.prog.mk>
