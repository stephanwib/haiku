PRIVATE_HEADERS=    
OS_HEADERS=      storage support app os interface

PROG=	rc

# generated
SRCS+=      parser.cpp lexer.cpp

SRCS+=      compile.cpp decompile.cpp rc.cpp rdef.cpp

lexer.cpp lexer.hpp : lexer.l
	flex -o lexer.cpp lexer.l

parser.cpp parser.hpp : parser.y
	bison parser.y --defines=parser.hpp --output=parser.cpp

CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow

LDADD+=	-lbe
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L/usr/pkg/lib

CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.include <bsd.prog.mk>
