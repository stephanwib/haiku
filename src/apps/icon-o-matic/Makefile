PRIVATE_HEADERS=    interface shared
OS_HEADERS=         interface support app storage translation locale add-ons/graphics

.PATH: ${.CURDIR}/document ${.CURDIR}/document/savers ${.CURDIR}/generic ${.CURDIR}/generic/listener \
       ${.CURDIR}/generic ${.CURDIR}/generic/support ${.CURDIR}/generic/command/ ${.CURDIR}/generic/gui \
       ${.CURDIR}/generic/gui/panel ${.CURDIR}/generic/gui/panel/color_picker ${.CURDIR}/generic/gui/scrollview \
       ${.CURDIR}/generic/gui/stateview ${.CURDIR}/generic/property ${.CURDIR}/generic/property/specific_properties \
       ${.CURDIR}/generic/property/view ${.CURDIR}/generic/property/view/specific_properties ${.CURDIR}/ ${.CURDIR}/generic/selection \
       ${.CURDIR}/generic/property/view/specific_properties ${.CURDIR}/transformable ${.CURDIR}/gui \
       ${.CURDIR}/import_export ${.CURDIR}/import_export/bitmap ${.CURDIR}/import_export/flat_icon \
       ${.CURDIR}/import_export/message ${.CURDIR}/ ${.CURDIR}/import_export/styled_text ${.CURDIR}/import_export/svg \
       ${.CURDIR}/shape ${.CURDIR}/shape/commands ${.CURDIR}/style

PROG=	Icon-O-Matic


postbuild: ${PROG}

realall: postbuild


SRCS+=      main.cpp MainWindow.cpp Util.cpp IconEditorApp.cpp CanvasView.cpp

CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow -D__HAIKU__ -DICON_O_MATIC=1


LDADD+=	-lbe -licon -lagg #-ltracker
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/icon -L${.CURDIR}/../../libs/agg \
          -L${.CURDIR}/../../libs/libtracker -L/usr/pkg/lib


CPPFLAGS+=  -I${.CURDIR}/../../libs/icon -I${.CURDIR}/../../libs/icon/generic \
            -I${.CURDIR}/../../libs/icon/flat_icon -I${.CURDIR}/../../libs/icon/message -I${.CURDIR}/../../libs/icon/transformer \
            -I${.CURDIR}/../../libs/icon/transformable -I${.CURDIR}/../../libs/icon/style -I${.CURDIR}/../../libs/icon/shape

CPPFLAGS+=  -I${.CURDIR}/gui

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor


CPPFLAGS+= -I${.CURDIR} -I${.CURDIR}/document -I${.CURDIR}/document/savers -I${.CURDIR}/generic -I${.CURDIR}/generic/listener \
       -I${.CURDIR}/generic -I${.CURDIR}/generic/support -I${.CURDIR}/generic/command/ -I${.CURDIR}/generic/gui \
       -I${.CURDIR}/generic/gui/panel -I${.CURDIR}/generic/gui/panel/color_picker -I${.CURDIR}/generic/gui/scrollview \
       -I${.CURDIR}/generic/gui/stateview -I${.CURDIR}/generic/property -I${.CURDIR}/generic/property/specific_properties \
       -I${.CURDIR}/generic/property/view -I${.CURDIR}/generic/property/view/specific_properties -I${.CURDIR}/generic/selection \
       -I${.CURDIR}/generic/property/view/specific_properties -I${.CURDIR}/transformable -I${.CURDIR}/gui \
       -I${.CURDIR}/import_export -I${.CURDIR}/import_export/bitmap -I${.CURDIR}/import_export/flat_icon \
       -I${.CURDIR}/import_export/message ${.CURDIR}/ -I${.CURDIR}/import_export/styled_text -I${.CURDIR}/import_export/svg \
       -I${.CURDIR}/shape -I${.CURDIR}/shape/commands -I${.CURDIR}/style \
       -I${.CURDIR}/../../../headers/libs/agg


CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers/posix
CPPFLAGS+= -I${.CURDIR}/../../../headers



.include "${.CURDIR}/../../resources.mk"
.include <bsd.prog.mk>
