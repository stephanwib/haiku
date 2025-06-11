
#LIBRARY_HEADERS= icon
PRIVATE_HEADERS= support input print tracker
OS_HEADERS= locale

.PATH: ${.CURDIR}/../../kits/interface \
       ${.CURDIR}/../../kits/interface/layouter \
       ${.CURDIR}/../../kits/interface/textview_support

SRCS+=    AboutWindow.cpp AbstractLayout.cpp AbstractLayoutItem.cpp AbstractSpinner.cpp \
          AffineTransform.cpp Alert.cpp Alignment.cpp BMCPrivate.cpp Bitmap.cpp Box.cpp \
          Button.cpp CardLayout.cpp CardView.cpp ChannelControl.cpp ChannelSlider.cpp \
          CheckBox.cpp ColorControl.cpp ColorConversion.cpp ColorMenuItem.cpp \
          ColumnListView.cpp ColumnTypes.cpp Control.cpp ControlLook.cpp DecimalSpinner.cpp \
          DecorInfo.cpp Deskbar.cpp Dragger.cpp Font.cpp Gradient.cpp GradientConic.cpp \
          GradientDiamond.cpp GradientLinear.cpp GradientRadial.cpp GradientRadialFocus.cpp \
          GraphicsDefs.cpp GridLayout.cpp GridLayoutBuilder.cpp GridView.cpp GroupLayout.cpp \
          GroupLayoutBuilder.cpp GroupView.cpp HaikuControlLook.cpp Icon.cpp Input.cpp \
          InterfaceDefs.cpp Layout.cpp LayoutContext.cpp LayoutItem.cpp LayoutUtils.cpp \
          ListItem.cpp ListView.cpp Menu.cpp MenuBar.cpp MenuField.cpp MenuItem.cpp MenuItemPrivate.cpp \
          MenuPrivate.cpp MenuWindow.cpp OptionControl.cpp OptionPopUp.cpp OutlineListView.cpp \
          Picture.cpp PictureButton.cpp PictureDataWriter.cpp PicturePlayer.cpp Point.cpp Polygon.cpp \
          PopUpMenu.cpp PrintJob.cpp PrivateScreen.cpp RadioButton.cpp Rect.cpp Region.cpp RegionSupport.cpp \
          Screen.cpp ScrollBar.cpp ScrollView.cpp SeparatorItem.cpp SeparatorView.cpp Shape.cpp Shelf.cpp \
          Size.cpp Slider.cpp SpaceLayoutItem.cpp Spinner.cpp SplitLayout.cpp SplitLayoutBuilder.cpp \
          SplitView.cpp StatusBar.cpp StringItem.cpp StringView.cpp TabView.cpp TextControl.cpp \
          TextInput.cpp TextView.cpp ToolTip.cpp ToolTipManager.cpp TwoDimensionalLayout.cpp \
          View.cpp ViewLayoutItem.cpp ViewPort.cpp Window.cpp WindowStack.cpp ZombieReplicantView.cpp

# Issues:

CPPFLAGS+= "-I${.CURDIR}/../../../headers/private"
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/add-ons/graphics"


.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= -I${.CURDIR}/../../../headers/private/${HEADER}
.endfor

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor
