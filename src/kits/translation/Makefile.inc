LIBRARY_HEADERS=
PRIVATE_HEADERS= system
OS_HEADERS= translation drivers

.PATH: ${.CURDIR}/../../kits/translation

SRCS=      BitmapStream.cpp FuncTranslator.cpp TranslationUtils.cpp Translator.cpp TranslatorRoster.cpp

# Issues:

#CPPFLAGS+= "-I${.CURDIR}/../../../headers"
#CPPFLAGS+= "-I${.CURDIR}/../../../headers/os"

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
