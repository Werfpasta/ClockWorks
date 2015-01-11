# Multi-platform makefile
# Hopefully BSDMake and GNUMake compatible

ifeq ($(OS),Windows_NT)
	ifndef PROCESSOR_ARCHITEW6432
		ARCH:=X86
	else
		ARCH:=X64
	endif
	PLATFORM:=NT
else
	ifeq ($(shell uname -s),Linux)
		PLATFORM:=LINUX
	else ifeq ($(shell uname -s),Darwin)
		PLATFORM:=DARWIN
	else ifeq ($(shell uname -s),FreeBSD)
		PLATFORM:=FREEBSD
	endif
	ifeq ($(shell uname -p),i686)
		ARCH:=X86
	else ifeq ($(shell uname -p),x86_64)
		ARCH:=X64
	endif
endif

ifeq ($(PLATFORM),)
	$(error Unknown platform.)
endif
ifeq ($(ARCH),)
	$(error Unknown architechure.)
endif

PROJECT_DIR:=$(dir $(lastword $(MAKEFILE_LIST)))
SRC_DIR:=$(PROJECT_DIR)src/
INC_DIR:=$(PROJECT_DIR)inc/
LIB_DIR:=$(PROJECT_DIR)lib/
BIN_DIR:=$(PROJECT_DIR)bin/
OBJ_DIR:=$(BIN_DIR)obj/
DOC_DIR:=$(PROJECT_DIR)doc/

THIRDPARTY_DIR=$(PROJECT_DIR)3rd/
THIRDPARTY_SRC_DIR:=$(THIRDPARTY_DIR)src/
THIRDPARTY_INC_DIR:=$(THIRDPARTY_DIR)inc/
THIRDPARTY_LIB_DIR:=$(THIRDPARTY_DIR)lib/
THIRDPARTY_BIN_DIR:=$(THIRDPARTY_DIR)bin/
THIRDPARTY_DOC_DIR:=$(THIRDPARTY_DIR)doc/


OBJECT_FLAG:=-c
OUTPUT-FLAG:=-o
SYSTEM-INCLUDE-FLAG:=-isystem
INCLUDE-FLAG:=-I
EXCEPTIONS:=-fno-exceptions

ifeq ($(ARCH),X86)
	CLANG_ARCH:=i386
else ifeq ($(ARCH),x86)
	CLANG_ARCH:=i386
else
	CLANG_ARCH:=x86_64
endif

ifeq ($(PLATFORM),NT)
	CLANG_ABI:=msvc
else
	CLANG_ABI:=gnu
endif

ifeq ($(PLATFORM),NT)
	CLANG_SYS:=windows
else ifeq ($(PLATFORM),LINUX)
	CLANG_SYS:=linux
endif

CLANG_TARGET:=--target=$(CLANG_ARCH)-pc-$(CLANG_SYS)-$(CLANG_ABI)

DIAGNOSTICS:=-fshow-column -fshow-source-location -fcaret-diagnostics \
	-fcolor-diagnostics -fdiagnostics-format=clang -fdiagnostics-show-option \
	-fdiagnostics-show-category=name -fdiagnostics-fixit-info \
	-fdiagnostics-print-source-range-info -fdiagnostics-parseable-fixits \
	-fno-elide-type -fdiagnostics-show-template-tree

CRINKLER:=$(THIRDPARTY_BIN_DIR)crinkler14/crinkler.exe

KKRUNCHY:=$(THIRDPARTY_BIN_DIR)kkrunchy023/kkrunchy.exe
KKRUNCHY_K7:=$(THIRDPARTY_BIN_DIR)kkrunchy023/kkrunchy_k7.exe

STANDARD:=-std=c++1z -nostdlib -nostdinc
WARNING:=-Wall
ERROR:=-pedantic-errors
DEBUG:=
compile-debug: DEBUG+=-g -fstandalone-debug
compile-release: DEBUG+=
OPTIMIZATION:=
compile-debug: OPTIMIZATION+=-O0
compile-release: OPTIMIZATION+=-O3
SUBSYSTEM:=CONSOLE
ENTRY:=CWMain
ifeq ($(PLATFORM),NT)
	CXX:=$(THIRDPARTY_BIN_DIR)clang/clang++.exe
endif
DEFINES:=CW_ARCH_$(ARCH) CW_PLATFORM_$(PLATFORM) CW_REV=$(shell git rev-parse --short=8 HEAD)
compile-debug: DEFINES+=CW_DEBUG
compile-release: DEFINES+=CW_RELEASE
LIBS:=mssdk7.1a-$(ARCH)/kernel32.lib mssdk7.1a-$(ARCH)/user32.lib mssdk7.1a-$(ARCH)/opengl32.lib
link-debug: LIBS+=
link-release: LIBS+=
CRINKLER_COMP:=
link-debug: CRINKLER_COMP:=INSTANT
link-release: CRINKLER_COMP:=SLOW

compile-debug: DEFINES:=$(addprefix -D , $(DEFINES))
compile-release: DEFINES:=$(addprefix -D , $(DEFINES))
link-debug: LIBS:=$(addprefix $(THIRDPARTY_LIB_DIR), $(LIBS))
link-release: LIBS:=$(addprefix $(THIRDPARTY_LIB_DIR), $(LIBS))

.PHONY: debug crinkle kkrunch
all: debug crinkle

kkrunch:
ifeq ($(ARCH),X64)
	echo ERROR: Kkrunchy only supports x86!
	exit 1
endif
	
debug: compile-debug link-debug
release: compile-release link-release
	
link-debug:
	echo $(THIRDPARTY_LIB_DIR)
ifeq ($(ARCH),X64)
	echo ERROR: Not implemented.
	exit 1
endif
	"$(CRINKLER)" /COMPMODE:$(CRINKLER_COMP) \
	/UNSAFEIMPORT /NOINITIALIZERS /SUBSYSTEM:$(SUBSYSTEM) /ENTRY:$(ENTRY) \
	"/out:$(BIN_DIR)$(ARCH)-debug.exe" $(LIBS) "$(OBJ_DIR)$(ARCH)-debug.obj"

link-release:
ifeq ($(ARCH),X64)
	echo ERROR: Not implemented.
	exit 1
endif
	"$(CRINKLER)" /COMPMODE:$(CRINKLER_COMP) \
	/UNSAFEIMPORT /NOINITIALIZERS /SUBSYSTEM:$(SUBSYSTEM) /ENTRY:$(ENTRY) \
	"/out:$(BIN_DIR)$(ARCH)-release.exe" $(LIBS) "$(OBJ_DIR)$(ARCH)-release.obj"

compile-debug:
	echo $(ARCH)
	"$(CXX)" $(STANDARD) $(WARNING) $(ERROR) $(CLANG_TARGET) $(EXCEPTIONS) \
	$(DEFINES) $(RTTI) $(DEBUG)  $(DIAGNOSTICS) $(OPTIMIZATION_DEBUG) \
	$(INCLUDE-FLAG)"$(INC_DIR)" $(INCLUDE-FLAG)"$(THIRDPARTY_INC_DIR)" \
	$(OBJECT_FLAG) $(OUTPUT-FLAG) "$(OBJ_DIR)$(ARCH)-debug.obj" -g -fstandalone-debug "$(SRC_DIR)main.cpp"

compile-release:
	"$(CXX)" $(STANDARD) $(WARNING) $(ERROR) $(CLANG_TARGET) $(EXCEPTIONS) \
	$(DEFINES) $(RTTI) $(DEBUG)  $(DIAGNOSTICS) $(OPTIMIZATION_DEBUG) \
	$(INCLUDE-FLAG)"$(INC_DIR)" $(INCLUDE-FLAG)"$(THIRDPARTY_INC_DIR)" \
	$(OBJECT_FLAG) $(OUTPUT-FLAG) "$(OBJ_DIR)$(ARCH)-release.obj" -g0 "$(SRC_DIR)main.cpp"