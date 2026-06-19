.include <bsd.own.mk>

OS_HEADERS= support storage app interface
PRIVATE_HEADERS= support

LIB=	appkittest

.PATH: ${.CURDIR}/bapplication ${.CURDIR}/bclipboard ${.CURDIR}/bcursor ${.CURDIR}/bhandler ${.CURDIR}/blooper  \
       ${.CURDIR}/bmessage ${.CURDIR}/bmessagequeue ${.CURDIR}/bmessagerunner ${.CURDIR}/bmessenger ${.CURDIR}/bpropertyinfo \
       ${.CURDIR}/broster ${.CURDIR}/common ${.CURDIR}/messaging

SRCS+=     ApplicationTest.cpp AppQuitRequestedTester.cpp AppQuitTester.cpp AppRunTester.cpp BApplicationTester.cpp

# BClipboard
SRCS+=     BClipboardTester.cpp ClipboardTest.cpp CountTester.cpp LockTester.cpp ReadWriteTester.cpp

# BCursor
SRCS+=     BCursorTester.cpp CursorTest.cpp

# BHandler 
SRCS+=     HandlerTest.cpp AddFilterTest.cpp BHandlerTester.cpp IsWatchedTest.cpp LockLooperTest.cpp LockLooperTestCommon.cpp \
           LockLooperWithTimeoutTest.cpp HandlerLooperTest.cpp NextHandlerTest.cpp RemoveFilterTest.cpp SetFilterListTest.cpp \
           SetNextHandlerTest.cpp UnlockLooperTest.cpp

# BLooper
SRCS+=     LooperTest.cpp AddHandlerTest.cpp CountHandlersTest.cpp HandlerAtTest.cpp IndexOfTest.cpp IsMessageWaitingTest.cpp \
           RemoveHandlerTest.cpp PerformTest.cpp RunTest.cpp LooperForThreadTest.cpp AddCommonFilterTest.cpp RemoveCommonFilterTest.cpp \
           LooperSizeTest.cpp SetCommonFilterListTest.cpp QuitTest.cpp

# BMessageQueue
SRCS+=     MessageQueueTest.cpp AddMessageTest1.cpp AddMessageTest2.cpp ConcurrencyTest1.cpp ConcurrencyTest2.cpp \
           FindMessageTest1.cpp MessageQueueTestCase.cpp


# BMessageRunner
SRCS+=     MessageRunnerTest.cpp BMessageRunnerTester.cpp BroadcastTester.cpp GetInfoTester.cpp MessageRunnerTestHelpers.cpp \
           SetCountTester.cpp SetIntervalTester.cpp

# BMessenger
SRCS+=     MessengerTest.cpp BMessengerTester.cpp LockTargetTester.cpp LockTargetWithTimeoutTester.cpp MessengerAssignmentTester.cpp \
           MessengerComparissonTester.cpp SendMessageTester.cpp SMInvoker.cpp SMLooper.cpp SMReplyTarget.cpp SMTarget.cpp \
           TargetTester.cpp


CXXFLAGS= -Wno-multichar -Wno-old-style-cast -Wno-shadow -D_NETBSD_SOURCE
CPPFLAGS+= -I${.CURDIR}/common

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
