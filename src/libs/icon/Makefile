.include <bsd.own.mk>

OS_HEADERS= app interface support storage
PRIVATE_HEADERS= shared

LIB=	icon

.PATH: ${.CURDIR}/flat_icon \
       ${.CURDIR}/generic \
       ${.CURDIR}/message \
       ${.CURDIR}/shape \
       ${.CURDIR}/style \
       ${.CURDIR}/transformable \
       ${.CURDIR}/transformer

SRCS+=     Icon.cpp IconRenderer.cpp IconUtils.cpp

# flat_icon
SRCS+=     FlatIconFormat.cpp FlatIconImporter.cpp LittleEndianBuffer.cpp PathCommandQueue.cpp
 
# message
SRCS+=     Defines.cpp MessageImporter.cpp

# shape
SRCS+=     PathSourceShape.cpp ReferenceImage.cpp Shape.cpp VectorPath.cpp

# style
SRCS+=     GradientTransformable.cpp Style.cpp

# transformable
SRCS+=     Transformable.cpp

# transformer
SRCS+=     AffineTransformer.cpp CompoundStyleTransformer.cpp ContourTransformer.cpp PathSource.cpp \
           PerspectiveTransformer.cpp StrokeTransformer.cpp StyleTransformer.cpp TransformerFactory.cpp


CXXFLAGS= -Wno-multichar -Wno-old-style-cast -Wno-shadow
CPPFLAGS+= -I${.CURDIR}
CPPFLAGS+= -I${.CURDIR}/generic
CPPFLAGS+= -I${.CURDIR}/flat_icon
CPPFLAGS+= -I${.CURDIR}/shape
CPPFLAGS+= -I${.CURDIR}/style
CPPFLAGS+= -I${.CURDIR}/message
CPPFLAGS+= -I${.CURDIR}/transformable
CPPFLAGS+= -I${.CURDIR}/transformer
CPPFLAGS+= -I${.CURDIR}/../../../headers
CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers/libs/agg

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

#LDFLAGS= -L/usr/pkg/lib -rpath=/usr/pkg/lib -lroot -licudata -licui18n -licuio -licuuc -lz -lzstd


WARNS=		5


#.include "${.CURDIR}/../../kits/app/Makefile.inc"


.include <bsd.lib.mk>
