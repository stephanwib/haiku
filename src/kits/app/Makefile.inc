
LIBRARY_HEADERS= icon
PRIVATE_HEADERS= shared app interface kernel libroot locale notification
OS_HEADERS= app support storage interface kernel

.PATH: ${.CURDIR}/../../kits/app

SRCS=	AppDefs.cpp AppMisc.cpp AppServerLink.cpp Application.cpp Clipboard.cpp Cursor.cpp \
      DesktopLink.cpp DirectMessageTarget.cpp Handler.cpp InitTerminateLibBe.cpp Invoker.cpp \
      Key.cpp KeyStore.cpp LaunchRoster.cpp LinkReceiver.cpp Looper.cpp LooperList.cpp \
      Message.cpp MessageAdapter.cpp MessageFilter.cpp MessageQueue.cpp MessageRunner.cpp \
      MessageUtils.cpp Messenger.cpp PortLink.cpp PropertyInfo.cpp RegistrarDefs.cpp Roster.cpp \
      RosterPrivate.cpp Server.cpp ServerLink.cpp 

# Issues:
# LinkSender.cpp -- missing syscalls.h, kern_transfer_area()
# Notification.cpp -- kernel realted? Not included in Cosmoe as well

CPPFLAGS+= "-I${.CURDIR}/../../../headers"
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os"


.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
