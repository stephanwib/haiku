# Programme, die gebaut werden sollen
PROGS = listsem listport listarea ps

# Compiler und Flags
CC ?= cc
CFLAGS ?= -Wall -Wextra -O2

# Linker-Optionen
LDLIBS += -lroot
# Falls libroot nicht im Standardpfad liegt, z.B.:
# LDFLAGS += -L/usr/local/lib

# Standardziel
all: ${PROGS}

# Regel: prog -> prog.c
.for p in ${PROGS}
${p}: ${p}.c
	${CC} ${CFLAGS} ${LDFLAGS} -o ${p} ${p}.c ${LDLIBS}
.endfor

# Aufräumen
clean:
	rm -f ${PROGS}

.PHONY: all clean
