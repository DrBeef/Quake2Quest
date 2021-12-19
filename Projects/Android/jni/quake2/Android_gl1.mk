LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := yquake2_gl1

LOCAL_CFLAGS :=  -DUSE_GLES1 -DIOAPI_NO_64 -DYQ2OSTYPE=\"Linux\" -DYQ2ARCH=\"Arm\"


BASE_DIR := engine

LOCAL_C_INCLUDES :=     $(SDL_INCLUDE_PATHS)  \
                        $(TOP_DIR) \
                        $(SUPPORT_LIBS)/jpeg8d \
                        $(GL4ES_PATH)

# ----------

REFGL1_OBJS_ := \
	src/client/refresh/gl1/qgl.o \
	src/client/refresh/gl1/gl1_draw.o \
	src/client/refresh/gl1/gl1_image.o \
	src/client/refresh/gl1/gl1_light.o \
	src/client/refresh/gl1/gl1_lightmap.o \
	src/client/refresh/gl1/gl1_main.o \
	src/client/refresh/gl1/gl1_mesh.o \
	src/client/refresh/gl1/gl1_misc.o \
	src/client/refresh/gl1/gl1_model.o \
	src/client/refresh/gl1/gl1_scrap.o \
	src/client/refresh/gl1/gl1_surf.o \
	src/client/refresh/gl1/gl1_warp.o \
	src/client/refresh/gl1/gl1_sdl.o \
	src/client/refresh/gl1/gl1_md2.o \
	src/client/refresh/gl1/gl1_sp2.o \
	src/client/refresh/files/pcx.o \
	src/client/refresh/files/stb.o \
	src/client/refresh/files/wal.o \
	src/client/refresh/files/pvs.o \
	src/common/shared/shared.o \
	src/common/md4.o

ifeq ($(YQ2_OSTYPE), Windows)
REFGL1_OBJS_ += \
	src/backends/windows/shared/hunk.o
else # not Windows
REFGL1_OBJS_ += \
	src/backends/unix/shared/hunk.o
endif

# ----------


LOCAL_SRC_FILES :=  $(REFGL1_OBJS_:.o=.c) \


LOCAL_LDLIBS := -lEGL -ldl -llog -lGLESv3 -lz
LOCAL_STATIC_LIBRARIES := sigc libzip libpng
LOCAL_SHARED_LIBRARIES := gl4es SDL2 SDL2_mixer

include $(BUILD_SHARED_LIBRARY)



include 
