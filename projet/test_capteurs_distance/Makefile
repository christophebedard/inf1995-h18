####################################################
################## MAKEFILE TEST ###################
####################################################

# nom du projet
PROJECTNAME=testcapteurdistance
# dossier include (.h)
INCDIR=include
# dossier build (output)
BUILDDIR=build

# Inclusions additionnels
INC=-I ../lib/$(INCDIR)/

# Libraires a lier
LIBS=-lrobot -L ../lib/$(BUILDDIR) -L ../lib/src


####### Cibles (target) #######

TRG=$(BUILDDIR)/$(PROJECTNAME).out
HEXROMTRG=$(BUILDDIR)/$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(BUILDDIR)/$(PROJECTNAME).ee.hex


####### Creation des commandes du Makefile #######

.PHONY: all install clean 

all: $(TRG)

include ../Makefile_common 

# target : programme pour le robot
$(TRG): $(BUILDDIR) $(OBJDEPS)
	@echo "\033[0;33mProgramme pour le robot!\033[0m"
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) \
	-lm \
	$(LIBS)

# install sur le microcontrolleur du robot
install: $(HEXROMTRG)
	@echo "\033[0;33mInstall!\033[0m"
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID) \
	-p $(MCU) -P -e -U flash:w:$(HEXROMTRG)

debug:
	@echo "\033[0;33mPWD      : $(PWD)\033[0m"
	@echo "\033[0;33mLIBS     : $(LIBS)\033[0m"
	@echo "\033[0;33mINC      : $(INC)\033[0m"
	@echo "\033[0;33mCFILES   : $(CFILES)\033[0m"
	@echo "\033[0;33mCPPFILES : $(CPPFILES)\033[0m"
	@echo "\033[0;33mCFLAGS   : $(CFLAGS)\033[0m"
	@echo "\033[0;33mCXXFLAGS : $(CXXFLAGS)\033[0m"
	@echo "\033[0;33mPRJSRC   : $(PRJSRC)\033[0m"
	@echo "\033[0;33mOBJDEPS  : $(OBJDEPS)\033[0m"
