# MAKEFILE_LIST specifies the current used Makefiles, of which this is the last
# one. I use that to obtain the Application.mk dir then import the root
# Application.mk.
ROOT_DIR := $(dir $(lastword $(MAKEFILE_LIST)))../../../../..
NDK_MODULE_PATH := $(ROOT_DIR)

APP_PLATFORM := android-19

APP_CFLAGS += -Wl,--no-undefined

APPLICATIONMK_PATH = $(call my-dir)

GL4ES_PATH := $(APPLICATIONMK_PATH)/gl4es

APP_ALLOW_MISSING_DEPS=true

APP_MODULES := gl4es quake2
APP_STL := c++_shared


