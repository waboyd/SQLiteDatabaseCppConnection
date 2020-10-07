##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=SQLiteConnectionLibCompiler
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/Seeker/Documents/programming/SQLDatabaseCppConnection
ProjectPath            :=C:/Users/Seeker/Documents/programming/SQLDatabaseCppConnection/SQLiteConnection
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Seeker
Date                   :=06/10/2020
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/MinGW/bin/g++.exe
SharedObjectLinkerName :=C:/MinGW/bin/g++.exe -shared -fPIC
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
OutputFile             :=$(IntermediateDirectory)/SQLiteConnection.lib
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="SQLiteConnectionLibCompiler.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/MinGW/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch).\SQLite 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)..\SQLite 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/MinGW/bin/ar.exe rcu
CXX      := C:/MinGW/bin/g++.exe
CC       := C:/MinGW/bin/gcc.exe
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)
ASFLAGS  := 
AS       := C:/MinGW/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/SQLiteConnection.cpp$(ObjectSuffix) $(IntermediateDirectory)/SQLiteStatement.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "C:\Users\Seeker\Documents\programming\SQLDatabaseCppConnection/.build-debug"
	@echo rebuilt > "C:\Users\Seeker\Documents\programming\SQLDatabaseCppConnection/.build-debug/SQLiteConnectionLibCompiler"

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


./Debug:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/SQLiteConnection.cpp$(ObjectSuffix): SQLiteConnection.cpp $(IntermediateDirectory)/SQLiteConnection.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Seeker/Documents/programming/SQLDatabaseCppConnection/SQLiteConnection/SQLiteConnection.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SQLiteConnection.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SQLiteConnection.cpp$(DependSuffix): SQLiteConnection.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SQLiteConnection.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SQLiteConnection.cpp$(DependSuffix) -MM SQLiteConnection.cpp

$(IntermediateDirectory)/SQLiteConnection.cpp$(PreprocessSuffix): SQLiteConnection.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SQLiteConnection.cpp$(PreprocessSuffix) SQLiteConnection.cpp

$(IntermediateDirectory)/SQLiteStatement.cpp$(ObjectSuffix): SQLiteStatement.cpp $(IntermediateDirectory)/SQLiteStatement.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Seeker/Documents/programming/SQLDatabaseCppConnection/SQLiteConnection/SQLiteStatement.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SQLiteStatement.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SQLiteStatement.cpp$(DependSuffix): SQLiteStatement.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SQLiteStatement.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SQLiteStatement.cpp$(DependSuffix) -MM SQLiteStatement.cpp

$(IntermediateDirectory)/SQLiteStatement.cpp$(PreprocessSuffix): SQLiteStatement.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SQLiteStatement.cpp$(PreprocessSuffix) SQLiteStatement.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


