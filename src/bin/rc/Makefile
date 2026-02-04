PRIVATE_HEADERS=    
OS_HEADERS=      storage support app os interface

PROG=	rc

SRCS+=      compile.cpp decompile.cpp rc.cpp rdef.cpp

# generated
SRCS+=      lexer.cpp parser.cpp

parser.cpp : parser.y
	flex -o parser.cpp parser.y

lexer.cpp lexer.hpp : lexer.l
	bison lexer.l --defines=lexer.hpp --output=lexer.cpp

CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow

#LDADD+=	-lbe
#LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L/usr/pkg/lib

CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.include <bsd.prog.mk>
