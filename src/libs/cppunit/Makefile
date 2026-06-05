.include <bsd.own.mk>

LIB=	cppunit

.PATH: ${.CURDIR}/../../tools/cppunit/cppunit

SRCS+=    Asserter.cpp SynchronizedObject.cpp TestResultCollector.cpp TextTestProgressListener.cpp \
          CompilerOutputter.cpp TestAssert.cpp TestRunner.cpp TextTestResult.cpp \
          Exception.cpp TestCase.cpp TestSetUp.cpp TypeInfoHelper.cpp \
          NotEqualException.cpp TestFactoryRegistry.cpp TestSucessListener.cpp   XmlOutputter.cpp \
          RepeatedTest.cpp TestFailure.cpp TestSuite.cpp SourceLine.cpp TestResult.cpp TextOutputter.cpp


CPPFLAGS+= -I${.CURDIR}/../../../headers/tools/cppunit

CXXFLAGS= -g -fPIC -std=c++03 -DBUILDING_CPPUNIT

#-std=c++17 -Wno-multichar -Wno-old-style-cast -Wno-shadow -D_NETBSD_SOURCE -D_SUPPORTS_RESOURCES

# XXX Compiler suggests -std=gnu99 due to alloca usage

#LDFLAGS= -L/usr/pkg/lib -L${.CURDIR}/../../libs/libbe -lroot -lbe
# -rpath=/usr/pkg/lib

WARNS=		5


.include <bsd.lib.mk>

