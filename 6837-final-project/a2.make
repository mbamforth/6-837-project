# GNU Make project makefile autogenerated by Premake
ifndef config
  config=debug
endif

ifndef verbose
  SILENT = @
endif

ifndef CC
  CC = gcc
endif

ifndef CXX
  CXX = g++
endif

ifndef AR
  AR = ar
endif

ifeq ($(config),debug)
  OBJDIR     = obj/Debug
  TARGETDIR  = debug
  TARGET     = $(TARGETDIR)/a2
  DEFINES   += -D_DEBUG -DDEBUG
  INCLUDES  += -Ivecmath/include
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -g -std=c++0x
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += `if [ "\`uname\`" = "Darwin" ]; then echo "-framework OpenGL -framework GLUT -framework Cocoa -framework AGL -framework Carbon -lfltk -lfltk_gl"; else echo "-lGL -lGLU -lglut "; fltk-config --use-gl --ldflags; fi;` -Ldebug
  LIBS      += -lvecmath
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += debug/libvecmath.a
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	cp debug/a2 a2
  endef
endif

ifeq ($(config),release)
  OBJDIR     = obj/Release
  TARGETDIR  = release
  TARGET     = $(TARGETDIR)/a2
  DEFINES   += -DNDEBUG
  INCLUDES  += -Ivecmath/include
  CPPFLAGS  += -MMD -MP $(DEFINES) $(INCLUDES)
  CFLAGS    += $(CPPFLAGS) $(ARCH) -O2 -std=c++0x
  CXXFLAGS  += $(CFLAGS) 
  LDFLAGS   += -s `if [ "\`uname\`" = "Darwin" ]; then echo "-framework OpenGL -framework GLUT -framework Cocoa -framework AGL -framework Carbon -lfltk -lfltk_gl"; else echo "-lGL -lGLU -lglut "; fltk-config --use-gl --ldflags; fi;` -Lrelease
  LIBS      += -lvecmath
  RESFLAGS  += $(DEFINES) $(INCLUDES) 
  LDDEPS    += release/libvecmath.a
  LINKCMD    = $(CXX) -o $(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(ARCH) $(LIBS)
  define PREBUILDCMDS
  endef
  define PRELINKCMDS
  endef
  define POSTBUILDCMDS
	@echo Running post-build commands
	cp release/a2 a2
  endef
endif

OBJECTS := \
	$(OBJDIR)/MatrixStack.o \
	$(OBJDIR)/bitmap.o \
	$(OBJDIR)/camera.o \
	$(OBJDIR)/Joint.o \
	$(OBJDIR)/main.o \
	$(OBJDIR)/modelerapp.o \
	$(OBJDIR)/modelerui.o \
	$(OBJDIR)/ModelerView.o \
	$(OBJDIR)/SkeletalModel.o \
	$(OBJDIR)/Mesh.o \
	$(OBJDIR)/SetDesign.o \

RESOURCES := \

SHELLTYPE := msdos
ifeq (,$(ComSpec)$(COMSPEC))
  SHELLTYPE := posix
endif
ifeq (/bin,$(findstring /bin,$(SHELL)))
  SHELLTYPE := posix
endif

.PHONY: clean prebuild prelink

all: $(TARGETDIR) $(OBJDIR) prebuild prelink $(TARGET)
	@:

$(TARGET): $(GCH) $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking a2
	$(SILENT) $(LINKCMD)
	$(POSTBUILDCMDS)

$(TARGETDIR):
	@echo Creating $(TARGETDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(TARGETDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(TARGETDIR))
endif

$(OBJDIR):
	@echo Creating $(OBJDIR)
ifeq (posix,$(SHELLTYPE))
	$(SILENT) mkdir -p $(OBJDIR)
else
	$(SILENT) mkdir $(subst /,\\,$(OBJDIR))
endif

clean:
	@echo Cleaning a2
ifeq (posix,$(SHELLTYPE))
	$(SILENT) rm -f  $(TARGET)
	$(SILENT) rm -rf $(OBJDIR)
else
	$(SILENT) if exist $(subst /,\\,$(TARGET)) del $(subst /,\\,$(TARGET))
	$(SILENT) if exist $(subst /,\\,$(OBJDIR)) rmdir /s /q $(subst /,\\,$(OBJDIR))
endif

prebuild:
	$(PREBUILDCMDS)

prelink:
	$(PRELINKCMDS)

ifneq (,$(PCH))
$(GCH): $(PCH)
	@echo $(notdir $<)
	-$(SILENT) cp $< $(OBJDIR)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
endif

$(OBJDIR)/MatrixStack.o: src/MatrixStack.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/bitmap.o: src/bitmap.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/camera.o: src/camera.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Joint.o: src/Joint.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/main.o: src/main.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/modelerapp.o: src/modelerapp.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/modelerui.o: src/modelerui.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/ModelerView.o: src/ModelerView.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/SkeletalModel.o: src/SkeletalModel.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/Mesh.o: src/Mesh.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"
$(OBJDIR)/SetDesign.o: src/SetDesign.cpp
	@echo $(notdir $<)
	$(SILENT) $(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)