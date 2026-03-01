.include <bsd.own.mk>


RC= ${.CURDIR}/../../bin/rc/rc 
XRES= ${.CURDIR}/../../bin/xres

RESOURCES=      libtracker TrackerIcons
RESPATH=        ${.CURDIR}/../../kits/tracker

RSRCFILES=      ${RESOURCES:S/$/.rsrc/}
CLEANFILES+=    ${RSRCFILES}

.SUFFIXES: .rdef .rsrc
.rdef.rsrc:
	${RC} ${.IMPSRC} -o ${.TARGET} -I ${RESPATH}


LIB=	tracker

# Notes:
#  Compiler suggests -std=gnu99 due to alloca usage
#  Needs zstd, icu and mapm (Math library) from pkgsrc

CXXFLAGS= -g -std=c++17 -Wno-multichar -Wno-old-style-cast -Wno-shadow -D_NETBSD_SOURCE

# XXX Compiler suggests -std=gnu99 due to alloca usage

LDFLAGS= -L/usr/pkg/lib -L${.CURDIR}/../../libs/libbe -lroot -lbe
# -rpath=/usr/pkg/lib

WARNS=		5


.include "${.CURDIR}/../../kits/tracker/Makefile.inc"

.include <bsd.lib.mk>



${_LIB.so.full}.res : ${_LIB.so.full}
	${XRES} -o ${.TARGET} ${RSRCFILES}

