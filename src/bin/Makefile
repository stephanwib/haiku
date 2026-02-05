PROGS = listsem listport listarea ps
CPPPROGS = xres

CC   ?= cc
CXX  ?= c++

CFLAGS   ?= -Wall -Wextra -O2
CXXFLAGS ?= -Wall -Wextra -O2
CXXFLAGS += -I${.CURDIR}/../headers

LDLIBS += -lroot

# program specific
#CFLAGS.ps   += -I/usr/local/include
#CXXFLAGS.ps += -I/usr/local/include
#LDLIBS.ps   += -lkvm
#LDFLAGS= -L/usr/pkg/lib
#CPPFLAGS+= "-I${.CURDIR}/../../../headers"

all: ${PROGS}

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
	       ${LDLIBS} ${LDLIBS.${p}}
.endfor

clean:
	rm -f ${PROGS}

.PHONY: all clean
