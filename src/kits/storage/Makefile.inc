#LIBRARY_HEADERS=
PRIVATE_HEADERS= storage userlandfs/legacy
OS_HEADERS=

.PATH: ${.CURDIR}/../../kits/storage \
       ${.CURDIR}/../../kits/storage/disk_device \
       ${.CURDIR}/../../kits/storage/mime \
       ${.CURDIR}/../../kits/storage/sniffer

SRCS+=    kernel_interface.POSIX.cpp AddOnImage.cpp AddOnMonitor.cpp AddOnMonitorHandler.cpp AppFileInfo.cpp \
          CopyEngine.cpp Directory.cpp DriverSettings.cpp Entry.cpp EntryList.cpp

# Issues: 

# disk_device
SRCS+=    

# mime
SRCS+=    

# sniffer
SRCS+=  

# Issues:

CPPFLAGS+= -I${.CURDIR}/../../../headers/posix
CPPFLAGS+= -I${.CURDIR}/../../../headers/build/os/storage

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= -I${.CURDIR}/../../../headers/private/${HEADER}
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
