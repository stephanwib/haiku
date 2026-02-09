PRIVATE_HEADERS=    app interface locale shared tracker
OS_HEADERS=         interface support app storage translation locale kernel add-ons/graphics

PROG=       Deskbar

SRCS+=      BarApp.cpp BarMenuBar.cpp BarMenuTitle.cpp BarView.cpp BarWindow.cpp CalendarMenuWindow.cpp DeskbarMenu.cpp \
            DeskbarUtils.cpp ExpandoMenuBar.cpp InlineScrollView.cpp PreferencesWindow.cpp \
            ShowHideMenuItem.cpp StatusView.cpp StatusViewShelf.cpp TeamMenu.cpp TeamMenuItem.cpp \
            TimeView.cpp TruncatableMenuItem.cpp WindowMenu.cpp WindowMenuItem.cpp ResourceSet.cpp \
            Switcher.cpp

CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow -DDB_ADDONS

LDADD+=	-lbe -licon -lagg -ltracker
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/icon -L${.CURDIR}/../../libs/agg \
          -L${.CURDIR}/../../libs/libtracker -L/usr/pkg/lib

CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers
CPPFLAGS+= -I${.CURDIR}/../../kits/tracker

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.include <bsd.prog.mk>
