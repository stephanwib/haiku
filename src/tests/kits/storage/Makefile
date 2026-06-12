.include <bsd.own.mk>

OS_HEADERS= support storage app interface
PRIVATE_HEADERS= storage

LIB=	storagetest

# .PATH: ${.CURDIR}

SRCS+=     BasicTest.cpp DataIOTest.cpp DirectoryTest.cpp EntryTest.cpp FileTest.cpp FindDirectoryTest.cpp \
           NodeInfoTest.cpp NodeTest.cpp PathTest.cpp ResourcesTest.cpp ResourceStringsTest.cpp StatableTest.cpp \
           StorageKitTestAddon.cpp SymLinkTest.cpp TestApp.cpp VolumeTest.cpp

CXXFLAGS= -Wno-multichar -Wno-old-style-cast -Wno-shadow -D_NETBSD_SOURCE
#CPPFLAGS+= -I${.CURDIR}

CPPFLAGS+= -I${.CURDIR}/../../../../headers
CPPFLAGS+= -I${.CURDIR}/../../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../../headers/tools/cppunit

LDFLAGS= -lroot -lbe -L${.CURDIR}/../../../libs/libbe

#LDFLAGS= -L/usr/pkg/lib -rpath=/usr/pkg/lib -lroot -licudata -licui18n -licuio -licuuc -lz -lzstd

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../../headers/os/${HEADER}"
.endfor

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../../headers/private/${HEADER}"
.endfor



WARNS=		5

.include <bsd.lib.mk>
