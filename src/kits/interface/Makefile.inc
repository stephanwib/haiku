
#LIBRARY_HEADERS= icon
#PRIVATE_HEADERS=
OS_HEADERS= locale

.PATH: ${.CURDIR}/../../kits/interface

SRCS+=    AboutWindow.cpp AbstractLayout.cpp AbstractLayoutItem.cpp AbstractSpinner.cpp \
          AffineTransform.cpp Alert.cpp Alignment.cpp BMCPrivate.cpp Bitmap.cpp Box.cpp

# Issues:

CPPFLAGS+= "-I${.CURDIR}/../../../headers/private"
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/add-ons/graphics"


.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= -I${.CURDIR}/../../../headers/private/${HEADER}
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
