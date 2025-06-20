#LIBRARY_HEADERS=
PRIVATE_HEADERS= shared
#OS_HEADERS=

.PATH: ${.CURDIR}/../../kits/shared

SRCS+=    AboutMenuItem.cpp ArgumentVector.cpp AttributeUtilities.cpp BarberPole.cpp BitmapButton.cpp \
          CalendarView.cpp ColorItem.cpp ColorListView.cpp ColorPreview.cpp ColorQuantizer.cpp CommandPipe.cpp \
          DateTimeEdit.cpp DragTrackingFilter.cpp DriverSettingsMessageAdapter.cpp ExpressionParser.cpp \
          HSL.cpp HashString.cpp IconButton.cpp IconView.cpp Json.cpp JsonEvent.cpp JsonEventListener.cpp \
          JsonMessageWriter.cpp JsonTextWriter.cpp JsonWriter.cpp Keymap.cpp LongAndDragTrackingFilter.cpp \
          MemoryRingIO.cpp MessageBuilder.cpp NaturalCompare.cpp PromptWindow.cpp QueryFile.cpp RWLockManager.cpp \
          RWLocker.cpp RegExp.cpp SettingsHandler.cpp SettingsMessage.cpp ShakeTrackingFilter.cpp StatusView.cpp \
          StringForRate.cpp StringForSize.cpp StripeView.cpp TextTable.cpp Thread.cpp ToolBar.cpp Variant.cpp \
          WeakReferenceable.cpp md5.cpp

# Issues:

CPPFLAGS+= -I${.CURDIR}/../../kits/tracker


.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= -I${.CURDIR}/../../../headers/private/${HEADER}
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
