#LIBRARY_HEADERS=
PRIVATE_HEADERS= storage userlandfs/legacy
OS_HEADERS= add-ons/registrar

.PATH: ${.CURDIR}/../../kits/storage \
       ${.CURDIR}/../../kits/storage/disk_device \
${.CURDIR}/../../kits/storage/disk_device/jobs \
       ${.CURDIR}/../../kits/storage/mime \
       ${.CURDIR}/../../kits/storage/sniffer

SRCS+=    kernel_interface.POSIX.cpp  AddOnMonitor.cpp AddOnMonitorHandler.cpp AppFileInfo.cpp \
          CopyEngine.cpp Directory.cpp DriverSettings.cpp Entry.cpp EntryList.cpp EntryOperationEngineBase.cpp \
          FdIO.cpp File.cpp FileDescriptorIO.cpp FileIO.cpp FindDirectory.cpp MergedDirectory.cpp Mime.cpp \
          MimeType.cpp Node.cpp NodeInfo.cpp NodeMonitor.cpp NodeMonitorHandler.cpp OffsetFile.cpp Path.cpp \
          PathFinder.cpp PathMonitor.cpp Query.cpp QueryPredicate.cpp RemoveEngine.cpp ResourceFile.cpp \
          ResourceItem.cpp ResourceStrings.cpp Resources.cpp ResourcesContainer.cpp Statable.cpp SymLink.cpp \
          Volume.cpp VolumeRoster.cpp storage_support.cpp

# Issues: AddOnImage.cpp

# sniffer
SRCS+=    CharStream.cpp DisjList.cpp Err.cpp Parser.cpp Pattern.cpp PatternList.cpp RPattern.cpp \
          RPatternList.cpp Range.cpp Rule.cpp

# mime
SRCS+=    AppMetaMimeCreator.cpp AssociatedTypes.cpp Database.cpp DatabaseDirectory.cpp DatabaseLocation.cpp \
          InstalledTypes.cpp MimeEntryProcessor.cpp MimeInfoUpdater.cpp MimeSniffer.cpp MimeSnifferAddon.cpp \
          MimeSnifferAddonManager.cpp SnifferRules.cpp Supertype.cpp SupportingApps.cpp TextSnifferAddon.cpp \
          TextSnifferAddon.cpp database_support.cpp

# disk_device
SRCS+=  DiskDevice.cpp DiskDeviceJob.cpp DiskDeviceJobGenerator.cpp DiskDeviceJobQueue.cpp DiskDeviceList.cpp \
	    DiskDevicePrivate.cpp DiskDeviceRoster.cpp DiskDeviceVisitor.cpp DiskSystemAddOn.cpp DiskSystemAddOnManager.cpp \
	    DiskSystem.cpp MutablePartition.cpp Partition.cpp PartitionDelegate.cpp PartitionReference.cpp

# disk_device/jobs
SRCS+=  CreateChildJob.cpp DefragmentJob.cpp DeleteChildJob.cpp InitializeJob.cpp MoveJob.cpp RepairJob.cpp \
	    ResizeJob.cpp SetStringJob.cpp UninitializeJob.cpp


# Issues:

CPPFLAGS+= -I${.CURDIR}/../../../headers/posix
CPPFLAGS+= -I${.CURDIR}/../../kits/storage -I${.CURDIR}/../../kits/storage/disk_device \
           -I${.CURDIR}/../../kits/storage/disk_device/jobs

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= -I${.CURDIR}/../../../headers/private/${HEADER}
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
