PRIVATE_HEADERS=    app graphics graphics/common input interface kernel shared storage support
OS_HEADERS=         interface app support storage add-ons/graphics kernel game drivers net

.PATH:      ${.CURDIR}/decorator ${.CURDIR}/drawing ${.CURDIR}/font ${.CURDIR}/stackandtile \
            ${.CURDIR}/drawing/Painter ${.CURDIR}/drawing/Painter/bitmap_painter \
            ${.CURDIR}/drawing/Painter/drawing_modes ${.CURDIR}/drawing/interface/remote
            
PROG=	appserver

SRCS+=      Angle.cpp AppServer.cpp BitmapManager.cpp ClientMemoryAllocator.cpp CursorData.cpp \
            CursorManager.cpp CursorSet.cpp Canvas.cpp DrawState.cpp DelayedMessage.cpp Desktop.cpp \
            DesktopSettings.cpp DesktopListener.cpp DirectWindowInfo.cpp EventDispatcher.cpp \
            EventStream.cpp InputManager.cpp IntPoint.cpp IntRect.cpp Layer.cpp MessageLooper.cpp \
            MultiLocker.cpp OffscreenWindow.cpp OffscreenServerWindow.cpp ProfileMessageSupport.cpp \
            PictureBoundingBoxPlayer.cpp RegionPool.cpp RGBColor.cpp ScreenManager.cpp ServerApp.cpp \
            ServerBitmap.cpp ServerCursor.cpp ServerFont.cpp ServerPicture.cpp Screen.cpp ServerWindow.cpp \
            SystemPalette.cpp ScreenConfigurations.cpp View.cpp VirtualScreen.cpp Window.cpp \
            WindowList.cpp Workspace.cpp WorkspacesView.cpp

# decorator
SRCS+=      Decorator.cpp DecorManager.cpp DefaultDecorator.cpp DefaultWindowBehaviour.cpp MagneticBorder.cpp \
            TabDecorator.cpp WindowBehaviour.cpp

# drawing
SRCS+=      AlphaMask.cpp AlphaMaskCache.cpp BitmapDrawingEngine.cpp BitmapBuffer.cpp BBitmapBuffer.cpp \
            BitmapHWInterface.cpp DrawingEngine.cpp drawing_support.cpp HWInterface.cpp Overlay.cpp \
            PatternHandler.cpp UpdateQueue.cpp

# drawing/Painter
SRCS+=      AGGTextRenderer.cpp GlobalSubpixelSettings.cpp Painter.cpp Transformable.cpp 

# drawing/Painter/drawing_modes
SRCS+=      PixelFormat.cpp

# drawing/Painter/bitmap_painter
SRCS+=      BitmapPainter.cpp

# drawing/interface/remote
SRCS+=      NetReceiver.cpp NetSender.cpp RemoteDrawingEngine.cpp RemoteEventStream.cpp \
            RemoteHWInterface.cpp RemoteMessage.cpp StreamingRingBuffer.cpp

# font
SRCS+=      AppFontManager.cpp FontCache.cpp FontManager.cpp FontFamily.cpp FontStyle.cpp \
            FontCacheEntry.cpp FontEngine.cpp GlobalFontManager.cpp

# stackandtile
SRCS+=      SATDecorator.cpp SATGroup.cpp SATWindow.cpp StackAndTile.cpp Stacking.cpp Tiling.cpp



CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow

LDADD+=	-lbe -lagg -licon -lfreetype -llinprog
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/agg -L${.CURDIR}/../../libs/icon \
          -L${.CURDIR}/../../libs/linprog -L/usr/pkg/lib

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

CPPFLAGS+= -I${.CURDIR} -I${.CURDIR}/decorator -I${.CURDIR}/drawing -I${.CURDIR}/drawing/Painter \
           -I${.CURDIR}/drawing/Painter/drawing_modes -I${.CURDIR}/drawing/Painter/bitmap_painter \
           -I${.CURDIR}/drawing/interface/remote -I${.CURDIR}/drawing/interface/local \
           -I${.CURDIR}/stackandtile -I${.CURDIR}/font -I${.CURDIR}/../../../headers/libs/linprog

CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers
CPPFLAGS+= -I${.CURDIR}/../../../headers/libs/agg
CPPFLAGS+= -I/usr/pkg/include/freetype2

.include <bsd.prog.mk>
