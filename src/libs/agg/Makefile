.include <bsd.own.mk>

#OS_HEADERS= app interface support storage
#PRIVATE_HEADERS= shared

LIB=	agg

.PATH: ${.CURDIR}/src
#       ${.CURDIR}/generic

SRCS+=     agg_arc.cpp agg_arrowhead.cpp agg_bezier_arc.cpp agg_bspline.cpp agg_curves.cpp \
           agg_embedded_raster_fonts.cpp agg_gsv_text.cpp agg_image_filters.cpp agg_line_aa_basics.cpp \
           agg_line_profile_aa.cpp agg_rounded_rect.cpp agg_sqrt_tables.cpp agg_trans_affine.cpp \
           agg_trans_double_path.cpp agg_trans_single_path.cpp agg_trans_warp_magnifier.cpp \
           agg_vcgen_bspline.cpp agg_vcgen_contour.cpp agg_vcgen_dash.cpp agg_vcgen_markers_term.cpp \
           agg_vcgen_smooth_poly1.cpp agg_vcgen_stroke.cpp agg_vpgen_clip_polygon.cpp \
           agg_vpgen_clip_polyline.cpp agg_vpgen_segmentator.cpp

# flat_icon
#SRCS+=     FlatIconFormat.cpp FlatIconImporter.cpp LittleEndianBuffer.cpp PathCommandQueue.cpp

CPPFLAGS+= -I${.CURDIR}/../../../headers/libs/agg

CXXFLAGS= -Wno-multichar -Wno-old-style-cast -Wno-shadow
#CPPFLAGS+= -I${.CURDIR}


.for HEADER in ${OS_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/os/${HEADER}"
.endfor

.for HEADER in ${PRIVATE_HEADERS}
CPPFLAGS+= "-I${.CURDIR}/../../../headers/private/${HEADER}"
.endfor

#LDFLAGS= -L/usr/pkg/lib -rpath=/usr/pkg/lib -lroot -licudata -licui18n -licuio -licuuc -lz -lzstd


WARNS=		5

.include <bsd.lib.mk>
