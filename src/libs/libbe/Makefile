

.include <bsd.own.mk>


RC= ${.CURDIR}/../../bin/rc/rc 
XRES= ${.CURDIR}/../../bin/xres

RESOURCES=      libbe_version Icons CountryFlags LanguageFlags

RSRCFILES=      ${RESOURCES:S/$/.rsrc/}
CLEANFILES+=    ${RSRCFILES}

.SUFFIXES: .rdef .rsrc
.rdef.rsrc:
	${RC} ${.IMPSRC} -o ${.TARGET} -I .

${_LIB}.so: ${RSRCFILES}
	${XRES} -o ${.TARGET} ${RSRCFILES}


LIB=	be

# Notes:
#  Compiler suggests -std=gnu99 due to alloca usage
#  Needs zstd, icu and mapm (Math library) from pkgsrc

CXXFLAGS= -g -std=c++17 -Wno-multichar -Wno-old-style-cast -Wno-shadow -D_NETBSD_SOURCE


# XXX Compiler suggests -std=gnu99 due to alloca usage

LDFLAGS= -L/usr/pkg/lib -rpath=/usr/pkg/lib -lroot -licudata -licui18n -licuio -licuuc -lz -lzstd

LIBDPLIBS+= mapm /usr/pkg/lib
LIBDO.mapm = _external

WARNS=		5


.include "${.CURDIR}/../../kits/app/Makefile.inc"
.include "${.CURDIR}/../../kits/interface/Makefile.inc"
.include "${.CURDIR}/../../kits/support/Makefile.inc"
.include "${.CURDIR}/../../kits/locale/Makefile.inc"
.include "${.CURDIR}/../../kits/textencoding/Makefile.inc"
.include "${.CURDIR}/../../kits/translation/Makefile.inc"
.include "${.CURDIR}/../../kits/shared/Makefile.inc"
.include "${.CURDIR}/../../kits/storage/Makefile.inc"

.include <bsd.lib.mk>





