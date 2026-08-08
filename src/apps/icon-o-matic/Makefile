PRIVATE_HEADERS=    interface shared
OS_HEADERS=         interface support app storage translation locale add-ons/graphics kernel

.PATH: ${.CURDIR}/document ${.CURDIR}/document/savers ${.CURDIR}/generic ${.CURDIR}/generic/listener \
       ${.CURDIR}/generic ${.CURDIR}/generic/support ${.CURDIR}/generic/command/ ${.CURDIR}/generic/gui \
       ${.CURDIR}/generic/gui/panel ${.CURDIR}/generic/gui/panel/color_picker ${.CURDIR}/generic/gui/scrollview \
       ${.CURDIR}/generic/gui/stateview ${.CURDIR}/generic/property ${.CURDIR}/generic/property/specific_properties \
       ${.CURDIR}/generic/property/view ${.CURDIR}/generic/property/view/specific_properties ${.CURDIR}/ ${.CURDIR}/generic/selection \
       ${.CURDIR}/generic/property/view/specific_properties ${.CURDIR}/transformable ${.CURDIR}/gui \
       ${.CURDIR}/import_export ${.CURDIR}/import_export/bitmap ${.CURDIR}/import_export/flat_icon \
       ${.CURDIR}/import_export/message ${.CURDIR}/ ${.CURDIR}/import_export/styled_text ${.CURDIR}/import_export/svg \
       ${.CURDIR}/shape ${.CURDIR}/shape/commands ${.CURDIR}/style

PROG=	Icon-O-Matic


postbuild: ${PROG}

realall: postbuild


SRCS+=      main.cpp MainWindow.cpp Util.cpp IconEditorApp.cpp CanvasView.cpp

SRCS+=      Document.cpp IconObject.cpp SetPropertiesCommand.cpp

# document/savers
SRCS+=      AttributeSaver.cpp BitmapSetSaver.cpp DocumentSaver.cpp FileSaver.cpp MessengerSaver.cpp NativeSaver.cpp \
            SimpleFileSaver.cpp

# generic/command
SRCS+=      Command.cpp CommandStack.cpp CompoundCommand.cpp

# generic/gui
SRCS+=      Group.cpp InputTextView.cpp NummericalTextView.cpp StringTextView.cpp ListViews.cpp SwatchView.cpp


# generic/gui/panel
SRCS+=      Panel.cpp

# generic/gui/panel/color_picker
SRCS+=      AlphaSlider.cpp ColorField.cpp ColorPickerPanel.cpp ColorPickerView.cpp ColorPreview.cpp ColorSlider.cpp


# generic/gui/popup_control

# generic/gui/scrollview
SRCS+=      Scrollable.cpp Scroller.cpp ScrollView.cpp

# generic/gui/stateview
SRCS+=      Manipulator.cpp MultipleManipulatorState.cpp StateView.cpp ViewState.cpp

# generic/listener
SRCS+=      Observable.cpp Observer.cpp

# generic/property
SRCS+=      CommonPropertyIDs.cpp Property.cpp PropertyObject.cpp

# generic/property/specific_properties
SRCS+=      ColorProperty.cpp IconProperty.cpp Int64Property.cpp OptionProperty.cpp

# generic/property/view
SRCS+=      PropertyEditorFactory.cpp PropertyEditorView.cpp PropertyItemView.cpp \
            PropertyListView.cpp

# generic/property/view/specific_properties
SRCS+=      BoolValueView.cpp ColorValueView.cpp FloatValueView.cpp IconValueView.cpp \
            Int64ValueView.cpp IntValueView.cpp OptionValueView.cpp \
            StringValueView.cpp SwatchValueView.cpp TextInputValueView.cpp

# generic/selection
SRCS+=      Selectable.cpp Selection.cpp

# generic/support
SRCS+=      support.cpp support_ui.cpp support_settings.cpp

# gui
SRCS+=      GradientControl.cpp IconObjectListView.cpp PathListView.cpp \
            SavePanel.cpp ShapeListView.cpp StyleListView.cpp StyleView.cpp \
            SwatchGroup.cpp TransformerListView.cpp

# import_export
SRCS+=      Exporter.cpp Importer.cpp

# import_export/bitmap
SRCS+=      BitmapExporter.cpp

# import_export/flat_icon
SRCS+=      FlatIconExporter.cpp RDefExporter.cpp SourceExporter.cpp

# import_export/message
SRCS+=      MessageExporter.cpp

# import_export/styled_text
SRCS+=      StyledTextImporter.cpp

# import_export/svg
SRCS+=      DocumentBuilder.cpp SVGExporter.cpp SVGImporter.cpp

# shape
SRCS+=      PathManipulator.cpp

# shape/commands
SRCS+=      AddPathsCommand.cpp AddPointCommand.cpp AddShapesCommand.cpp \
            AddTransformersCommand.cpp ChangePointCommand.cpp \
            CleanUpPathCommand.cpp FlipPointsCommand.cpp \
            FreezeTransformationCommand.cpp InsertPointCommand.cpp \
            MoveShapesCommand.cpp MovePathsCommand.cpp \
            MoveTransformersCommand.cpp NudgePointsCommand.cpp \
            PathCommand.cpp RemovePathsCommand.cpp RemovePointsCommand.cpp \
            RemoveShapesCommand.cpp RemoveTransformersCommand.cpp \
            ReversePathCommand.cpp RotatePathIndicesCommand.cpp \
            SplitPointsCommand.cpp TransformPointsCommand.cpp \
            UnassignPathCommand.cpp

# style
SRCS+=      AddStylesCommand.cpp AssignStyleCommand.cpp CurrentColor.cpp \
            MoveStylesCommand.cpp RemoveStylesCommand.cpp \
            SetColorCommand.cpp SetGradientCommand.cpp

# transformable
SRCS+=      CanvasTransformBox.cpp ChannelTransform.cpp PerspectiveBox.cpp \
            PerspectiveBoxStates.cpp PerspectiveCommand.cpp \
            ResetTransformationCommand.cpp TransformBox.cpp \
            TransformBoxStates.cpp TransformCommand.cpp \
            TransformGradientBox.cpp TransformGradientCommand.cpp \
            TransformObjectsCommand.cpp TransformPointsBox.cpp \
            TransformShapesBox.cpp



# ====== libicon files ========
# These are built with ICON_O_MATIC=1 defined, making them different to those in libicon
# =============================

.PATH:      ${.CURDIR}/../../libs/icon ${.CURDIR}/../../libs/icon/generic \
            ${.CURDIR}/../../libs/icon/flat_icon ${.CURDIR}/../../libs/icon/message ${.CURDIR}/../../libs/icon/transformer \
            ${.CURDIR}/../../libs/icon/transformable ${.CURDIR}/../../libs/icon/style ${.CURDIR}/../../libs/icon/shape

# icon/flat_icon
SRCS+=      FlatIconFormat.cpp FlatIconImporter.cpp \
            LittleEndianBuffer.cpp PathCommandQueue.cpp

# icon/message
SRCS+=      Defines.cpp MessageImporter.cpp

# icon/shape
SRCS+=      PathSourceShape.cpp ReferenceImage.cpp Shape.cpp \
            VectorPath.cpp

# icon/style
SRCS+=      GradientTransformable.cpp Style.cpp

# icon/transformable
SRCS+=      Transformable.cpp

# icon/transformer
SRCS+=      AffineTransformer.cpp CompoundStyleTransformer.cpp \
            ContourTransformer.cpp PathSource.cpp \
            PerspectiveTransformer.cpp StrokeTransformer.cpp \
            StyleTransformer.cpp TransformerFactory.cpp

# icon
SRCS+=      Icon.cpp IconRenderer.cpp



CXXFLAGS=   -fPIE -Wno-multichar -Wno-old-style-cast -Wno-shadow -D__HAIKU__ -DICON_O_MATIC=1


LDADD+=	-lbe -licon -lagg -ltracker
LDFLAGS+= -L${.CURDIR}/../../libs/libbe -L${.CURDIR}/../../libs/icon -L${.CURDIR}/../../libs/agg \
          -L${.CURDIR}/../../libs/libtracker -L/usr/pkg/lib





CPPFLAGS+=  

.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

CPPFLAGS+=  -I${.CURDIR}/gui

CPPFLAGS+=  -I${.CURDIR}/../../libs/icon -I${.CURDIR}/../../libs/icon/generic \
            -I${.CURDIR}/../../libs/icon/flat_icon -I${.CURDIR}/../../libs/icon/message -I${.CURDIR}/../../libs/icon/transformer \
            -I${.CURDIR}/../../libs/icon/transformable -I${.CURDIR}/../../libs/icon/style -I${.CURDIR}/../../libs/icon/shape

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor




CPPFLAGS+= -I${.CURDIR} -I${.CURDIR}/document -I${.CURDIR}/document/savers -I${.CURDIR}/generic -I${.CURDIR}/generic/listener \
       -I${.CURDIR}/generic -I${.CURDIR}/generic/support -I${.CURDIR}/generic/command/ -I${.CURDIR}/generic/gui \
       -I${.CURDIR}/generic/gui/panel -I${.CURDIR}/generic/gui/panel/color_picker \
       -I${.CURDIR}/generic/gui/stateview -I${.CURDIR}/generic/property -I${.CURDIR}/generic/property/specific_properties \
       -I${.CURDIR}/generic/property/view -I${.CURDIR}/generic/property/view/specific_properties -I${.CURDIR}/generic/selection \
       -I${.CURDIR}/generic/property/view/specific_properties -I${.CURDIR}/transformable -I${.CURDIR}/gui -I${.CURDIR}/generic/gui/scrollview \
       -I${.CURDIR}/import_export -I${.CURDIR}/import_export/bitmap -I${.CURDIR}/import_export/flat_icon \
       -I${.CURDIR}/import_export/message ${.CURDIR}/ -I${.CURDIR}/import_export/styled_text -I${.CURDIR}/import_export/svg \
       -I${.CURDIR}/shape -I${.CURDIR}/shape/commands -I${.CURDIR}/style \
       -I${.CURDIR}/../../../headers/libs/agg

CPPFLAGS+= -I${.CURDIR}/../../../headers/libs/icon
CPPFLAGS+= -I${.CURDIR}/../../../headers/os
CPPFLAGS+= -I${.CURDIR}/../../../headers/posix
CPPFLAGS+= -I${.CURDIR}/../../../headers



.include "${.CURDIR}/../../resources.mk"
.include <bsd.prog.mk>
