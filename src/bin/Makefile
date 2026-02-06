PROGS = listsem listport listarea ps
CPPPROGS = xres listres

CC   ?= cc
CXX  ?= c++

CFLAGS   += -Wall -Wextra -O2
CXXFLAGS += -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow -I${.CURDIR}/../../headers/os/storage \
            -I${.CURDIR}/../../headers/os/support -I${.CURDIR}/../../headers/os -I${.CURDIR}/../../headers

LDLIBS += -lroot
LDXXLIBS += -lroot -lbe -L${.CURDIR}/../libs/libbe

LDXXLIBS.xres += -licon -L${.CURDIR}/../libs/icon

# program specific
#CFLAGS.ps   += -I/usr/local/include
#CXXFLAGS.ps += -I/usr/local/include
#LDLIBS.ps   += -lkvm
#LDFLAGS= -L/usr/pkg/lib
#CPPFLAGS+= "-I${.CURDIR}/../../../headers"

all: ${PROGS} ${CPPPROGS}

# C
.for p in ${PROGS}
${p}: ${p}.c
	${CC} ${CFLAGS} ${CFLAGS.${p}} \
	      ${LDFLAGS} \
	      -o ${p} ${p}.c \
	      ${LDLIBS} ${LDLIBS.${p}}
.endfor

# C++
.for p in ${CPPPROGS}
${p}: ${p}.cpp
	${CXX} ${CXXFLAGS} ${CXXFLAGS.${p}} \
	       ${LDFLAGS} \
	       -o ${p} ${p}.cpp \
	       ${LDXXLIBS} ${LDXXLIBS.${p}}
.endfor

clean:
	rm -f ${PROGS} ${CPPPROGS}

.PHONY: all clean
