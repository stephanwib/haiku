PRIVATE_HEADERS= interface mount shared storage support tracker
OS_HEADERS= interface support app storage kernel locale translation add-ons input_server filters add-ons/graphics

.PATH: ${.CURDIR}/../../kits/tracker ${.CURDIR}/../../kits/tracker/infowindow

SRCS+=	AttributeStream.cpp AutoMounterSettings.cpp BackgroundImage.cpp Bitmaps.cpp ContainerWindow.cpp \
        CountView.cpp DeskWindow.cpp DesktopPoseView.cpp DraggableContainerIcon.cpp DialogPane.cpp \
        DirMenu.cpp EntryIterator.cpp FBCPadding.cpp FSClipboard.cpp FSUndoRedo.cpp FSUtils.cpp FavoritesMenu.cpp \
        FilePanel.cpp FilePanelPriv.cpp FindPanel.cpp GroupedMenu.cpp IconCache.cpp IconMenuItem.cpp LiveMenu.cpp \
        MimeTypeList.cpp MiniMenuField.cpp Model.cpp MountMenu.cpp Navigator.cpp NavMenu.cpp NodePreloader.cpp \
        NodeWalker.cpp OpenWithWindow.cpp OverrideAlert.cpp PendingNodeMonitorCache.cpp Pose.cpp PoseList.cpp \
        PoseView.cpp PoseViewScripting.cpp QueryContainerWindow.cpp QueryPoseView.cpp RecentItems.cpp RegExp.cpp \
        SelectionWindow.cpp Settings.cpp SettingsViews.cpp Shortcuts.cpp SlowMenu.cpp StatusWindow.cpp TaskLoop.cpp \
        TemplatesMenu.cpp Tests.cpp TextWidget.cpp Thumbnails.cpp TitleView.cpp Tracker.cpp TrackerInitialState.cpp \
        TrackerScripting.cpp TrackerSettings.cpp TrackerSettingsWindow.cpp TrackerString.cpp TrashWatcher.cpp Utilities.cpp \
        ViewState.cpp VirtualDirectoryEntryList.cpp VirtualDirectoryManager.cpp VirtualDirectoryPoseView.cpp \
        VirtualDirectoryWindow.cpp WidgetAttributeText.cpp

# infowindow
SRCS+=  AttributesView.cpp FilePermissionsView.cpp GeneralInfoView.cpp HeaderView.cpp InfoWindow.cpp

CPPFLAGS+= -I${.CURDIR}/../../kits/tracker -I${.CURDIR}/../../kits/tracker/infowindow -I${.CURDIR}/../../../headers \
           -I${.CURDIR}/../../../headers/os -I${.CURDIR}/../../../headers/private -I${.CURDIR}/../../../headers/posix

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
