#LIBRARY_HEADERS=
PRIVATE_HEADERS=
OS_HEADERS=

.PATH: ${.CURDIR}/../../kits/shared

SRCS+=    AboutMenuItem.cpp ArgumentVector.cpp AttributeUtilities.cpp BarberPole.cpp BitmapButton.cpp \
          CalendarView.cpp ColorItem.cpp ColorListView.cpp ColorPreview.cpp ColorQuantizer.cppC ommandPipe.cpp \
          DateTimeEdit.cpp DragTrackingFilter.cpp DriverSettingsMessageAdapter.cpp ExpressionParser.cpp

# Issues:

#CPPFLAGS+= -I${.CURDIR}/../../../headers/private
#CPPFLAGS+= -I${.CURDIR}/../../kits/support

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= -I${.CURDIR}/../../../headers/private/${HEADER}
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
