PRIVATE_HEADERS=    interface shared
OS_HEADERS=         interface support app storage translation locale add-ons/graphics

PROG=	PackageInstaller


postbuild: ${PROG}

realall: postbuild


SRCS+=      main.cpp BlockingWindow.cpp PackageWindow.cpp PackageView.cpp PackageInfo.cpp PackageItem.cpp \
            PackageInstall.cpp PackageStatus.cpp PackageTextViewer.cpp PackageImageViewer.cpp InstalledPackageInfo.cpp \
            UninstallWindow.cpp UninstallView.cpp


CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow

LDADD+=	-lbe # -licon -lagg -ltracker
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/icon -L${.CURDIR}/../../libs/agg \
          -L${.CURDIR}/../../libs/libtracker -L/usr/pkg/lib

CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers/posix
CPPFLAGS+= -I${.CURDIR}/../../../headers

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.include "${.CURDIR}/../../resources.mk"
.include <bsd.prog.mk>
