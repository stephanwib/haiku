PROGS = listsem listport listarea ps

CC ?= cc
CFLAGS ?= -Wall -Wextra -O2

LDLIBS += -lroot

# programs that need libbe
CFLAGS.lbe  += -I${.CURDIR}/../headers/os
LDLIBS.lbe  += -lbe

all: ${PROGS}

.for p in ${PROGS}
${p}: ${p}.c
	${CC} ${CFLAGS} ${CFLAGS.${p}} \
	      ${LDFLAGS} \
	      -o ${p} ${p}.c \
	      ${LDLIBS} ${LDLIBS.${p}}
.endfor

clean:
	rm -f ${PROGS}

.PHONY: all clean
