.include <bsd.own.mk>

OS_HEADERS= support storage app interface
PRIVATE_HEADERS= support

LIB=	supporttest

.PATH: ${.CURDIR}/barchivable ${.CURDIR}/bautolock ${.CURDIR}/bblockcache ${.CURDIR}/blocker ${.CURDIR}/bmemoryio \
       ${.CURDIR}/bstring ${.CURDIR}/pointerlist


SRCS+=     SupportKitTestAddon.cpp ByteOrderTest.cpp

# BArchivable
SRCS+=     ArchivableTest.cpp BArchivableTester.cpp FindInstantiationFuncTester.cpp InstantiateObjectTester.cpp LocalTestObject.cpp \
           ValidateInstantiationTester.cpp
		
# BAutolock
SRCS+=     AutolockTest.cpp AutolockLockerTest.cpp AutolockLooperTest.cpp

# BDateTime
SRCS+=     DateTimeTest.cpp

# BLocker
SRCS+=     LockerTest.cpp BenaphoreLockCountTest1.cpp ConcurrencyTest1.cpp ConcurrencyTest2.cpp ConstructionTest1.cpp \
           DestructionTest1.cpp DestructionTest2.cpp LockerTestCase.cpp SemaphoreLockCountTest1.cpp

# BMemoryIO
SRCS+=     MemoryIOTest.cpp ConstTest.cpp SeekTest.cpp WriteTest.cpp ReadTest.cpp SetSizeTest.cpp

# BMallocIO
SRCS+=     MallocIOTest.cpp MallocSeekTest.cpp MallocWriteTest.cpp MallocBufferLengthTest.cpp

#BString
SRCS+=     StringTest.cpp StringConstructionTest.cpp StringAccessTest.cpp StringAssignTest.cpp \
           StringAppendTest.cpp StringSubCopyTest.cpp StringPrependTest.cpp StringCaseTest.cpp \
           StringInsertTest.cpp StringEscapeTest.cpp StringRemoveTest.cpp StringCompareTest.cpp \
           StringFormatAppendTest.cpp StringCharAccessTest.cpp StringSearchTest.cpp StringReplaceTest.cpp \
           StringSplitTest.cpp

#BBlockCache
SRCS+=     BlockCacheTest.cpp BlockCacheExerciseTest.cpp BlockCacheConcurrencyTest.cpp



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
