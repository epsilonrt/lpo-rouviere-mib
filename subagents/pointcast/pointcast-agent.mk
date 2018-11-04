##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=pointcast-agent
ConfigurationName      :=Release
WorkspacePath          :=/home/pascal/src/lpo-rouviere-mib/subagents/pointcast
ProjectPath            :=/home/pascal/src/lpo-rouviere-mib/subagents/pointcast
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=epsilonrt
Date                   :=11/03/18
CodeLitePath           :=/home/pascal/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG $(PreprocessorSwitch)BACKGROUND=1 $(PreprocessorSwitch)SYSLOG=1 $(PreprocessorSwitch)RS485_RTS_LOW=1 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="pointcast-agent.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            := $(shell pkg-config --libs piduino) $(shell net-snmp-config --agent-libs) $(shell pkg-config --libs libmodbus) 
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS := -std=c++14 $(shell pkg-config --cflags piduino) $(shell pkg-config --cflags libmodbus) -O2 -Wall $(Preprocessors)
CFLAGS   := -std=c99 $(shell pkg-config --cflags piduino) $(shell pkg-config --cflags libmodbus) -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/lprPointCast.c$(ObjectSuffix) $(IntermediateDirectory)/main-daemon.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/lprPointCast.c$(ObjectSuffix): lprPointCast.c $(IntermediateDirectory)/lprPointCast.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/pascal/src/lpo-rouviere-mib/subagents/pointcast/lprPointCast.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lprPointCast.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lprPointCast.c$(DependSuffix): lprPointCast.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lprPointCast.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lprPointCast.c$(DependSuffix) -MM lprPointCast.c

$(IntermediateDirectory)/lprPointCast.c$(PreprocessSuffix): lprPointCast.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lprPointCast.c$(PreprocessSuffix) lprPointCast.c

$(IntermediateDirectory)/main-daemon.c$(ObjectSuffix): main-daemon.c $(IntermediateDirectory)/main-daemon.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/pascal/src/lpo-rouviere-mib/subagents/pointcast/main-daemon.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main-daemon.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main-daemon.c$(DependSuffix): main-daemon.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main-daemon.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main-daemon.c$(DependSuffix) -MM main-daemon.c

$(IntermediateDirectory)/main-daemon.c$(PreprocessSuffix): main-daemon.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main-daemon.c$(PreprocessSuffix) main-daemon.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


