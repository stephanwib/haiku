RC?=        ${.CURDIR}/../../bin/rc/rc
XRES?=      ${.CURDIR}/../../bin/xres

.PATH.rdef: ${RESPATH}

RSRCFILES=  ${RESOURCES:S/$/.rsrc/}

CLEANFILES+= ${RSRCFILES}

#
# .rdef -> .rsrc
#

.SUFFIXES: .rdef .rsrc

.rdef.rsrc:
	${RC} ${.IMPSRC} -o ${.TARGET} -I ${RESPATH}


.if defined(PROG) && !empty(RSRCFILES)
${PROG}: ${RSRCFILES}
	${XRES} -o ${.TARGET} ${RSRCFILES}
.endif


.if defined(LIB) && defined(SHLIB_MAJOR) && !empty(RSRCFILES)

.if defined(SHLIB_MINOR)
FULLSHLIB= lib${LIB}.so.${SHLIB_MAJOR}.${SHLIB_MINOR}
.else
FULLSHLIB= lib${LIB}.so.${SHLIB_MAJOR}
.endif

${FULLSHLIB}: ${RSRCFILES}
	${XRES} -o ${.TARGET} ${RSRCFILES}

.endif
