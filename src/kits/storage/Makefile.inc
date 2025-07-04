#LIBRARY_HEADERS=
PRIVATE_HEADERS= storage userlandfs/legacy
OS_HEADERS=

.PATH: ${.CURDIR}/../../kits/storage \
       ${.CURDIR}/../../kits/storage/disk_device \
       ${.CURDIR}/../../kits/storage/mime \
       ${.CURDIR}/../../kits/storage/sniffer

SRCS+=    kernel_interface.POSIX.cpp AddOnImage.cpp AddOnMonitor.cpp AddOnMonitorHandler.cpp AppFileInfo.cpp \
          CopyEngine.cpp Directory.cpp DriverSettings.cpp Entry.cpp EntryList.cpp EntryOperationEngineBase.cpp \
          FdIO.cpp File.cpp FileDescriptorIO.cpp FileIO.cpp FindDirectory.cpp MergedDirectory.cpp Mime.cpp \
          MimeType.cpp Node.cpp NodeInfo.cpp NodeMonitor.cpp NodeMonitorHandler.cpp OffsetFile.cpp Path.cpp \
          PathFinder.cpp PathMonitor.cpp Query.cpp QueryPredicate.cpp RemoveEngine.cpp ResourceFile.cpp \
          ResourceItem.cpp ResourceStrings.cpp Resources.cpp ResourcesContainer.cpp Statable.cpp SymLink.cpp \
          Volume.cpp VolumeRoster.cpp storage_support.cpp

# Issues: 

# disk_device
SRCS+=    

# mime
SRCS+=    AppMetaMimeCreator.cpp AssociatedTypes.cpp Database.cpp DatabaseDirectory.cpp DatabaseLocation.cpp \
          InstalledTypes.cpp MimeEntryProcessor.cpp MimeInfoUpdater.cpp MimeSniffer.cpp MimeSnifferAddon.cpp \
          MimeSnifferAddonManager.cpp SnifferRules.cpp Supertype.cpp SupportingApps.cpp TextSnifferAddon.cpp \
          TextSnifferAddon.cpp database_support.cpp

# sniffer
SRCS+=  

# Issues:

CPPFLAGS+= -I${.CURDIR}/../../../headers/posix
CPPFLAGS+= -I${.CURDIR}/../../kits/storage

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= -I${.CURDIR}/../../../headers/private/${HEADER}
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
