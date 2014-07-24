ProjectName := ClockWorks
Modes := debug release
Platform := Win32
DisableExceptions := true
#Platform := Linux
#Platform := OSX

RootDir := $(dir $(lastword $(MAKEFILE_LIST)))

include $(RootDir)make/makefile_msvc

SourcePath    := $(wildcard $(RootDir)/src/*.cpp)
IncludePaths   := $(RootDir)include/
LibPath       := $(RootDir)lib/
IntermediatePath := $(RootDir)bin/o/
OutPath       := $(RootDir)bin/
CompilerFlags :=
LinkerFlags   = /NODEFAULTLIB /MACHINE:X86 /OUT:"$(RootDir)bin/$(ProjectName)-$@.exe"
Defines       :=
Libraries     :=

EchoNewline := @echo . >nul 2>&1 & echo.

all : $(Modes)

all-clean :
	$(EchoNewline)
	@echo # Cleaning all
	$(EchoNewline)
	$(RM) "$(OutPath)"
	
$(Modes:%=%):
	$(EchoNewline)
	@echo # Preparing $@
	$(EchoNewline)
	@echo mkdir "$(IntermediatePath)$@/"
	@mkdir "$(IntermediatePath)$@/" >nul 2>&1 & set %ERRORLEVEL% = 0
	$(EchoNewline)
	@echo # Compiling $@
	$(EchoNewline)
	@$(Compile) /MTd /Oy- /Gd /EHs-c- /Zc:forScope /analyze- /GS- /Od /W4 /Zc:wchar_t /ZI /Fa"$(IntermediatePath)$@/" /Fo"$(IntermediatePath)$@/main.o" /Fd"$(IntermediatePath)$@/" /fp:fast $(IncludePaths:%=$(IncludePathFlag)%) "$(RootDir)src/main.cpp"
	$(EchoNewline)
	@echo # Linking $@
	$(EchoNewline)
	@$(Link) $(LinkerFlags) "kernel32.lib" "user32.lib" "$(IntermediatePath)$@/main.o"
	
$(Modes:%=%-clean):
	$(EchoNewline)
	@echo # Cleaning $@
	$(EchoNewline)
	$(RM) "$(OutPath)$(subst -clean,,$@)/"

-clean: