# Multi-platform makefile
# Hopefully BSDMake and GNUMake compatible

STANDARD:=-std=c++1z -nostdlib -nostdinc
WARNING:=-Wall
ERROR:=-pedantic-errors
DEBUG:=-g -fstandalone-debug
OPTIMIZATION:=
OPTIMIZATION_RELEASE:=-O3
OPTIMIZATION_DEBUG:=-O0

ifeq ($(OS),Windows_NT)
	ifndef PROCESSOR_ARCHITEW6432
		ARCH:=x86
	else
		ARCH:=x64
	endif
	PLAT:=nt
else
	ifeq ($(shell uname -s),Linux)
		PLAT:=linux
	else ifeq ($(shell uname -s),Darwin)
		PLAT:=darwin
	else ifeq ($(shell uname -s),FreeBSD)
		PLAT:=freebsd
	endif
	ifeq ($(shell uname -p),i686)
		ARCH:=x86
	else ifeq ($(shell uname -p),x86_64)
		ARCH:=x64
	endif
endif

ifeq ($(PLAT),)
	$(error Unknown platform.)
endif
ifeq ($(ARCH),)
	$(error Unknown architechure.)
endif

# WINDOWS
SUBSYSTEM:=CONSOLE
ENTRY:=CWMain

#INSTANT FAST SLOW
CRINKLER_COMP_DEBUG:=INSTANT
CRINKLER_COMP_RELEASE:=SLOW

# Paths
PROJECT_DIR:=$(dir $(lastword $(MAKEFILE_LIST)))
SRC_DIR:=$(PROJECT_DIR)src/
INC_DIR:=$(PROJECT_DIR)inc/
LIB_DIR:=$(PROJECT_DIR)lib/
BIN_DIR:=$(PROJECT_DIR)bin/
DOC_DIR:=$(PROJECT_DIR)doc/

BACKUP_DIR:=$(PROJECT_DIR)../backups/

THIRDPARTY_DIR=$(PROJECT_DIR)thirdparty/
THIRDPARTY_SRC_DIR:=$(THIRDPARTY_DIR)src/
THIRDPARTY_INC_DIR:=$(THIRDPARTY_DIR)inc/
THIRDPARTY_LIB_DIR:=$(THIRDPARTY_DIR)lib/
THIRDPARTY_BIN_DIR:=$(THIRDPARTY_DIR)bin/
THIRDPARTY_DOC_DIR:=$(THIRDPARTY_DIR)doc/

LIBS:=mssdk7.1a-$(ARCH)/kernel32.lib mssdk7.1a-$(ARCH)/user32.lib mssdk7.1a-$(ARCH)/opengl32.lib

CXX:=$(THIRDPARTY_BIN_DIR)clang/clang++.exe


OBJECT_FLAG:=-c
OUTPUT-FLAG:=-o
SYSTEM-INCLUDE-FLAG:=-isystem
INCLUDE-FLAG:=-I
EXCEPTIONS:=-fno-exceptions

ifeq ($(ARCH),x86)
	CLANG_ARCH:=i386
else
	CLANG_ARCH:=x86_64
endif

ifeq ($(PLAT),nt)
	CLANG_ABI:=msvc
else
	CLANG_ABI:=gnu
endif

ifeq ($(PLAT),nt)
	CLANG_SYS:=windows
else ifeq ($(PLAT),linux)
	CLANG_SYS:=linux
endif

CLANG_TARGET:=--target=$(CLANG_ARCH)-pc-$(CLANG_SYS)-$(CLANG_ABI)

DIAGNOSTICS:=-fshow-column -fshow-source-location -fcaret-diagnostics \
	-fcolor-diagnostics -fdiagnostics-format=clang -fdiagnostics-show-option \
	-fdiagnostics-show-category=name -fdiagnostics-fixit-info \
	-fdiagnostics-print-source-range-info -fdiagnostics-parseable-fixits \
	-fno-elide-type -fdiagnostics-show-template-tree

CRINKLER=$(THIRDPARTY_BIN_DIR)crinkler14/crinkler.exe

KKRUNCHY:=$(THIRDPARTY_BIN_DIR)kkrunchy023/kkrunchy.exe
KKRUNCHY_K7:=$(THIRDPARTY_BIN_DIR)kkrunchy023/kkrunchy_k7.exe

.PHONY: debug crinkle
all:
	@echo ARCH=$(ARCH) PLAT=$(PLAT)
	@echo PROJECT_DIR=$(PROJECT_DIR)
	@echo THIRDPARTY_DOC_DIR=$(THIRDPARTY_DOC_DIR)

.PHONY: kkrunch
kkrunch:

.PHONY: crinkle
crinkle:
	"$(CRINKLER)" /COMPMODE:$(CRINKLER_COMP_DEBUG) \
	/UNSAFEIMPORT /NOINITIALIZERS /SUBSYSTEM:$(SUBSYSTEM) /ENTRY:$(ENTRY) \
	"/out:$(BIN_DIR)x86-debug.exe" $(LIBS_x86_R) "$(BIN_DIR)x86-debug.obj"

.PHONY: version
version:
	@echo $(shell git rev-parse --short=8 HEAD)

.PHONY: git-graph
git-graph:
	git log --graph --full-history --all --date=short --pretty=format:"%h - %s (%an)"

.PHONY: debug
debug:
	"$(CXX)" $(STANDARD) $(WARNING) $(ERROR) $(CLANG_TARGET) $(EXCEPTIONS) $(DIAGNOSTICS) $(RTTI) $(DEBUG) $(OPTIMIZATION_DEBUG) $(INCLUDE-FLAG)"$(INC_DIR)" $(INCLUDE-FLAG)"$(THIRDPARTY_INC_DIR)" $(OBJECT_FLAG) $(OUTPUT-FLAG) "$(BIN_DIR)x64-debug.obj" "$(SRC_DIR)main.cpp"