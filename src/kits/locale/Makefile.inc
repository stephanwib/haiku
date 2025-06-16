#LIBRARY_HEADERS= 
#PRIVATE_HEADERS= 
#OS_HEADERS= 

.PATH: ${.CURDIR}/../../kits/locale

SRCS+=    Catalog.cpp CatalogData.cpp CatalogStub.cpp Collator.cpp Country.cpp \
          DateFormat.cpp DateTimeFormat.cpp DefaultCatalog.cpp DurationFormat.cpp \
          EditableCatalog.cpp Format.cpp FormattingConventions.cpp HashMapCatalog.cpp \
          InitLocaleKit.cpp Language.cpp Locale.cpp LocaleRoster.cpp LocaleRosterData.cpp \
          MutableLocaleRoster.cpp NumberFormat.cpp RelativeDateTimeFormat.cpp StringFormat.cpp \
          TextEncoding.cpp TimeFormat.cpp TimeUnitFormat.cpp TimeZone.cpp UnicodeChar.cpp

# Issues:

CPPFLAGS+= -I/usr/pkg/include
#CPPFLAGS+= -I${.CURDIR}/../../../headers/private
#CPPFLAGS+= -I${.CURDIR}/../../kits/support

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= -I${.CURDIR}/../../../headers/private/${HEADER}
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
