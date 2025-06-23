#LIBRARY_HEADERS=
PRIVATE_HEADERS= storage
OS_HEADERS=

.PATH: ${.CURDIR}/../../kits/storage \
       ${.CURDIR}/../../kits/storage/disk_device \
       ${.CURDIR}/../../kits/storage/mime \
       ${.CURDIR}/../../kits/storage/sniffer

SRCS+=    AddOnImage.cpp AddOnMonitor.cpp AddOnMonitorHandler.cpp AppFileInfo.cpp \
          CopyEngine.cpp  DriverSettings.cpp Entry.cpp EntryList.cpp

# Issues: Directory.cpp

# disk_device
SRCS+=    

# mime
SRCS+=    

# sniffer
SRCS+=  

# Issues:

#CPPFLAGS+= "-I${.CURDIR}/../../../headers/private"

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= -I${.CURDIR}/../../../headers/private/${HEADER}
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
