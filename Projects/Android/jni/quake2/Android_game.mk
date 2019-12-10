LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := yquake2_game

LOCAL_CFLAGS :=  -DUSE_GLES1 -DIOAPI_NO_64  -DYQ2OSTYPE=\"Linux\" -DYQ2ARCH=\"Arm\"


# BASE_DIR := engine

LOCAL_C_INCLUDES :=     $(SDL_INCLUDE_PATHS)  \
                        $(TOP_DIR) \
                        $(SUPPORT_LIBS)/jpeg8d

GAME_OBJS_ = \
	src/common/shared/flash.o \
	src/common/shared/rand.o \
	src/common/shared/shared.o \
	src/game/g_ai.o \
	src/game/g_chase.o \
	src/game/g_cmds.o \
	src/game/g_combat.o \
	src/game/g_func.o \
	src/game/g_items.o \
	src/game/g_main.o \
	src/game/g_misc.o \
	src/game/g_monster.o \
	src/game/g_phys.o \
	src/game/g_spawn.o \
	src/game/g_svcmds.o \
	src/game/g_target.o \
	src/game/g_trigger.o \
	src/game/g_turret.o \
	src/game/g_utils.o \
	src/game/g_weapon.o \
	src/game/monster/berserker/berserker.o \
	src/game/monster/boss2/boss2.o \
	src/game/monster/boss3/boss3.o \
	src/game/monster/boss3/boss31.o \
	src/game/monster/boss3/boss32.o \
	src/game/monster/brain/brain.o \
	src/game/monster/chick/chick.o \
	src/game/monster/flipper/flipper.o \
	src/game/monster/float/float.o \
	src/game/monster/flyer/flyer.o \
	src/game/monster/gladiator/gladiator.o \
	src/game/monster/gunner/gunner.o \
	src/game/monster/hover/hover.o \
	src/game/monster/infantry/infantry.o \
	src/game/monster/insane/insane.o \
	src/game/monster/medic/medic.o \
	src/game/monster/misc/move.o \
	src/game/monster/mutant/mutant.o \
	src/game/monster/parasite/parasite.o \
	src/game/monster/soldier/soldier.o \
	src/game/monster/supertank/supertank.o \
	src/game/monster/tank/tank.o \
	src/game/player/client.o \
	src/game/player/hud.o \
	src/game/player/trail.o \
	src/game/player/view.o \
	src/game/player/weapon.o \
	src/game/savegame/savegame.o


LOCAL_SRC_FILES :=  $(GAME_OBJS_:.o=.c) \


LOCAL_LDLIBS := -lEGL -ldl -llog -lGLESv3 -lz
LOCAL_STATIC_LIBRARIES := sigc libzip libpng libjpeg
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_mixer

include $(BUILD_SHARED_LIBRARY)


$(call import-module,VrApi/Projects/AndroidPrebuilt/jni)
