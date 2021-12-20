LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := yquake2

LOCAL_CFLAGS :=  -DIOAPI_NO_64 -DUSE_GLES1 -DUSE_OPENAL -DYQUAKE2 -DENGINE_NAME=\"yquake2\" -DYQ2OSTYPE=\"Linux\" -DYQ2ARCH=\"Arm\"


LOCAL_C_INCLUDES :=     $(SUPPORT_LIBS)/openal/include/ \
                        $(GL4ES_PATH) 


# Used by the client
CLIENT_OBJS_ := \
	src/backends/generic/misc.o \
	src/client/cl_cin.o \
	src/client/cl_console.o \
	src/client/cl_download.o \
	src/client/cl_effects.o \
	src/client/cl_entities.o \
	src/client/cl_input.o \
	src/client/cl_inventory.o \
	src/client/cl_keyboard.o \
	src/client/cl_lights.o \
	src/client/cl_main.o \
	src/client/cl_network.o \
	src/client/cl_parse.o \
	src/client/cl_particles.o \
	src/client/cl_prediction.o \
	src/client/cl_screen.o \
	src/client/cl_tempentities.o \
	src/client/cl_view.o \
	src/client/menu/menu.o \
	src/client/menu/qmenu.o \
	src/client/menu/videomenu.o \
	src/client/sound/ogg.o \
	src/client/sound/openal.o \
	src/client/sound/qal.o \
	src/client/sound/sound.o \
	src/client/sound/wave.o \
	src/client/vid/glimp_android.o \
	src/client/vid/vid.o \
	src/client/curl/download.o \
	src/client/curl/qcurl.o \
	src/common/argproc.o \
	src/common/clientserver.o \
	src/common/collision.o \
	src/common/crc.o \
	src/common/cmdparser.o \
	src/common/cvar.o \
	src/common/filesystem.o \
	src/common/glob.o \
	src/common/md4.o \
	src/common/movemsg.o \
	src/common/frame.o \
	src/common/netchan.o \
	src/common/pmove.o \
	src/common/szone.o \
	src/common/zone.o \
	src/common/shared/flash.o \
	src/common/shared/rand.o \
	src/common/shared/shared.o \
	src/common/unzip/ioapi.o \
	src/common/unzip/miniz.o \
	src/common/unzip/unzip.o \
	src/server/sv_cmd.o \
	src/server/sv_conless.o \
	src/server/sv_entities.o \
	src/server/sv_game.o \
	src/server/sv_init.o \
	src/server/sv_main.o \
	src/server/sv_save.o \
	src/server/sv_send.o \
	src/server/sv_user.o \
	src/server/sv_world.o

ifeq ($(YQ2_OSTYPE), Windows)
CLIENT_OBJS_ += \
	src/backends/windows/main.o \
	src/backends/windows/network.o \
	src/backends/windows/system.o \
	src/backends/windows/shared/hunk.o
else
CLIENT_OBJS_ += \
	src/backends/unix/main.o \
	src/backends/unix/network.o \
	src/backends/unix/signalhandler.o \
	src/backends/unix/system.o \
	src/backends/unix/shared/hunk.o
endif



LOCAL_SRC_FILES :=  $(CLIENT_OBJS_:.o=.c) \
	   ../Quake2VR/Q2VR_SurfaceView.c \
       ../Quake2VR/VrCompositor.c \
       ../Quake2VR/VrInputCommon.c \
       ../Quake2VR/VrInputDefault.c \
       ../Quake2VR/mathlib.c \
       ../Quake2VR/matrixlib.c \
       ../Quake2VR/argtable3.c


LOCAL_LDLIBS :=  -lEGL -ldl -llog -landroid -lOpenSLES -lz
LOCAL_STATIC_LIBRARIES := gl4es sigc libzip libpng libjpeg
LOCAL_SHARED_LIBRARIES := openal vrapi
LOCAL_LDLIBS += -lGLESv3

include $(BUILD_SHARED_LIBRARY)


$(call import-module,VrApi/Projects/AndroidPrebuilt/jni)

