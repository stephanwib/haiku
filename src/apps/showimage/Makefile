PRIVATE_HEADERS=    interface
OS_HEADERS=         interface support app storage translation locale add-ons/graphics

PROG=	Showimage

SRCS+=      	Filter.cpp ImageCache.cpp ImageFileNavigator.cpp PrintOptionsWindow.cpp \
              ShowImageApp.cpp ShowImageSettings.cpp ShowImageStatusView.cpp ShowImageView.cpp \
              ShowImageWindow.cpp SupportingAppsMenu.cpp ToolBarIcons.cpp ProgressWindow.cpp \
              SelectionBox.cpp


CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow

LDADD+=	-lbe -licon -lagg
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/icon -L${.CURDIR}/../../libs/agg  -L/usr/pkg/lib

CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.include <bsd.prog.mk>
