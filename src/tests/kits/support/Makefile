.include <bsd.own.mk>

OS_HEADERS= support storage app interface
PRIVATE_HEADERS= support

LIB=	supporttest

.PATH: ${.CURDIR}/barchivable ${.CURDIR}/bautolock ${.CURDIR}/bblockcache ${.CURDIR}/blocker ${.CURDIR}/bmemoryio \
       ${.CURDIR}/bstring ${.CURDIR}/pointerlist

SRCS+=     SupportKitTestAddon.cpp ByteOrderTest.cpp ArchivableTest.cpp AutolockTest.cpp DateTimeTest.cpp \
            MemoryIOTest.cpp MallocIOTest.cpp StopWatchTest.cpp StringAccessTest.cpp \
           StringAppendTest.cpp StringAssignTest.cpp StringCaseTest.cpp StringCompareTest.cpp StringConstructionTest.cpp \
           StringEscapeTest.cpp StringFormatAppendTest.cpp StringInsertTest.cpp StringPrependTest.cpp StringRemoveTest.cpp \
           StringReplaceTest.cpp StringSearchTest.cpp StringSplitTest.cpp StringSubCopyTest.cpp StringUTF8Test.cpp \
           BlockCacheExerciseTest.cpp BlockCacheConcurrencyTest.cpp PointerListTest.cpp



CXXFLAGS= -Wno-multichar -Wno-old-style-cast -Wno-shadow -D_NETBSD_SOURCE
#CPPFLAGS+= -I${.CURDIR}

CPPFLAGS+= -I${.CURDIR}/../../../../headers
CPPFLAGS+= -I${.CURDIR}/../../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../../headers/tools/cppunit

LDFLAGS= -lroot -lbe -lcppunit -lbetest -L${.CURDIR}/../../../libs/libbe -L${.CURDIR}/../../../libs/cppunit -L${.CURDIR}/../../../libs/libbetest

#LDFLAGS= -L/usr/pkg/lib -rpath=/usr/pkg/lib -lroot -licudata -licui18n -licuio -licuuc -lz -lzstd

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../../headers/os/${HEADER}"
.endfor

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../../headers/private/${HEADER}"
.endfor



WARNS=		5

.include <bsd.lib.mk>
