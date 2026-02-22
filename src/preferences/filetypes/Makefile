PRIVATE_HEADERS=    interface textencoding shared libroot system
OS_HEADERS=         interface support app storage translation locale add-ons/graphics

PROG=	Filetypes

SRCS+=      	ApplicationTypeWindow.cpp AttributeWindow.cpp FileTypeWindow.cpp IconView.cpp PreferredAppMenu.cpp \
              ApplicationTypesWindow.cpp DropTargetListView.cpp FileTypes.cpp MimeTypeListView.cpp StringView.cpp \
              AttributeListView.cpp ExtensionWindow.cpp FileTypesWindow.cpp NewFileTypeWindow.cpp TypeListWindow.cpp


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
