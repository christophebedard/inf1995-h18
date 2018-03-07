####################################################
################### MAKEFILE LIB ###################
####################################################

#####      Details specifique a la cible       #####

# nom du projet
LIBNAME=librobot
# dossier source (.cpp et .c)
SRCDIR=src
# dossier include (.h)
INCDIR=include
# dossier build (output)
BUILDDIR=build

# tous les fichiers .cpp dans le dossier src/
PRJSRC=$(filter %.cpp, $(shell echo $(SRCDIR)/*))

# Inclusions additionnels (ex: -I/path/to/mydir)
# le dossier INCDIR avec les fichiers .h
INC=-I $(INCDIR)/

# Libraires a lier (ex: -lmylib)
LIBS=


####### Cible (Target) #######

# Nom des cibles par defaut
TRG=$(BUILDDIR)/$(LIBNAME).a


####### Creation des commandes du Makefile ####### 
.PHONY: all clean #debug

all: $(TRG)

include ../Makefile_common 

# target : librairie
$(TRG): $(BUILDDIR) $(OBJDEPS)
	@echo "\033[0;33mLibrairie!\033[0m"
	$(AR) -crs $(TRG) $(OBJDEPS)

debug:
	@echo "\033[0;33mPWD      : $(PWD)\033[0m"
	@echo "\033[0;33mCFILES   : $(CFILES)\033[0m"
	@echo "\033[0;33mCPPFILES : $(CPPFILES)\033[0m"
	@echo "\033[0;33mCFLAGS   : $(CFLAGS)\033[0m"
	@echo "\033[0;33mCXXFLAGS : $(CXXFLAGS)\033[0m"
	@echo "\033[0;33mPRJSRC   : $(PRJSRC)\033[0m"
	@echo "\033[0;33mOBJDEPS  : $(OBJDEPS)\033[0m"

