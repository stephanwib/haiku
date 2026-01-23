PRIVATE_HEADERS=    interface textencoding shared libroot system
OS_HEADERS=         interface support app storage translation locale add-ons/graphics

PROG=	Terminal

SRCS+=      	ActiveProcessInfo.cpp AppearPrefView.cpp Arguments.cpp BasicTerminalBuffer.cpp \
              Colors.cpp FindWindow.cpp Globals.cpp HistoryBuffer.cpp HyperLink.cpp InlineInput.cpp \
              PatternEvaluator.cpp PrefHandler.cpp PrefWindow.cpp SetTitleDialog.cpp Shell.cpp \
              ShellInfo.cpp ShellParameters.cpp SmartTabView.cpp TermApp.cpp TermConst.cpp \
              TerminalBuffer.cpp TerminalCharClassifier.cpp TerminalRoster.cpp TermParse.cpp \
              TermScrollView.cpp TermView.cpp TermViewHighlight.cpp TermViewStates.cpp TermWindow.cpp \
              ThemeView.cpp ThemeWindow.cpp TitlePlaceholderMapper.cpp VTKeyTbl.c VTPrsTbl.c


CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow

LDADD+=	-lbe -licon -lagg
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/icon -L${.CURDIR}/../../libs/agg  -L/usr/pkg/lib

CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.include <bsd.prog.mk>
