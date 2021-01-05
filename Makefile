## VARIABLES ##
CXX = g++
EXEC = App

## FUNCTION ##

COMPILE_RELEASE = $(SRC_CPP:$(SRC_CPP)=$(RELEASE_OBJS_DIR)/$(patsubst %.cpp,%.o,$(lastword $(subst /, ,$(SRC_CPP)))))
COMPILE_DEBUG = $(SRC_CPP:$(SRC_CPP)=$(DEBUG_OBJS_DIR)/$(patsubst %.cpp,%.o,$(lastword $(subst /, ,$(SRC_CPP)))))

# Configuration
RELEASE_DIR = release
RELEASE_EXEC = $(RELEASE_DIR)/$(EXEC)
DEBUG_DIR = debug
DEBUG_EXEC = $(DEBUG_DIR)/$(addsuffix -debug, $(EXEC))

# DIRECTORIES
ifndef SRC_CPP
	SRC_CPP = *.cpp 
	SRC_CPP += thing/*.cpp 
endif

RELEASE_OBJS_DIR = $(RELEASE_DIR)/OBJ
DEBUG_OBJS_DIR = $(DEBUG_DIR)/OBJ

DEBUG_FLAGS = -g
CXX_FLAGS = -std=c++17

## DEPENDENCIES ##


all: release
re: clean release

exe:
	@./$(RELEASE_EXEC)

# Release
release: $(RELEASE_EXEC)

$(RELEASE_EXEC):
	@for file in $(SRC_CPP) ; do \
        make --no-print-directory compile_release SRC_CPP=$$file ; \
    done
	$(CXX) $(CXX_FLAGS) -o $@ $(RELEASE_OBJS_DIR)/*.o

compile_release: $(COMPILE_RELEASE)

$(RELEASE_OBJS_DIR)/%.o:$(SRC_CPP)
	$(CXX) $(CXX_FLAGS) -o $@ -c $< $(INCLUDE_DIR)

# Debug
debug: $(DEBUG_EXEC)

$(DEBUG_EXEC):
	@for file in $(SRC_CPP) ; do \
        make --no-print-directory compile_debug SRC_CPP=$$file ; \
    done
	$(CXX) $(CXX_FLAGS) -o $@ $(DEBUG_OBJS_DIR)/*.o

compile_debug: $(COMPILE_DEBUG)

$(DEBUG_OBJS_DIR)/%.o:$(SRC_CPP)
	$(CXX) $(CXX_FLAGS) $(DEBUG_FLAGS) -o $@ -c $< $(INCLUDE_DIR)

# Delete directories
deleter:
	rm -r $(RELEASE_DIR)

deleted:
	rm -r $(DEBUG_DIR)

# Clean files
clean: cleanr cleand

cleanr:
	rm -rf $(RELEASE_DIR)/*.exe
	rm -rf $(RELEASE_OBJS_DIR)/*.o

cleand:
	rm -rf $(DEBUG_DIR)/*.exe
	rm -rf $(DEBUG_OBJS_DIR)/*.o

# Todo only once to make folders
prep:
	mkdir $(DEBUG_DIR) | mkdir $(RELEASE_DIR)
	mkdir $(DEBUG_DIR)/OBJ | mkdir $(RELEASE_DIR)/OBJ

.PHONY: exe clean
