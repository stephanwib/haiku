.include <bsd.own.mk>

#OS_HEADERS= app interface support storage
#PRIVATE_HEADERS= shared

LIB=	agg

.PATH: ${.CURDIR}/src
#       ${.CURDIR}/generic

SRCS+=     agg_arc.cpp agg_arrowhead.cpp agg_bezier_arc.cpp agg_bspline.cpp agg_curves.cpp

# flat_icon
#SRCS+=     FlatIconFormat.cpp FlatIconImporter.cpp LittleEndianBuffer.cpp PathCommandQueue.cpp

CPPFLAGS+= -I${.CURDIR}/../../../headers/libs/agg

CXXFLAGS= -Wno-multichar -Wno-old-style-cast -Wno-shadow
#CPPFLAGS+= -I${.CURDIR}


.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

#LDFLAGS= -L/usr/pkg/lib -rpath=/usr/pkg/lib -lroot -licudata -licui18n -licuio -licuuc -lz -lzstd


WARNS=		5

.include <bsd.lib.mk>
