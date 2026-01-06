# Programme, die gebaut werden sollen
PROGS = listsem listport listarea ps

# Compiler und Flags
CC ?= cc
CFLAGS ?= -Wall -Wextra -O2

# Standardziel
all: ${PROGS}

# Regel: prog -> prog.c
.for p in ${PROGS}
${p}: ${p}.c
	${CC} ${CFLAGS} -o ${p} ${p}.c
.endfor

# Aufräumen
clean:
	rm -f ${PROGS}

.PHONY: all clean
