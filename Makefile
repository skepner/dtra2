# -*- Makefile -*-

TARGETS = \
    $(DIST_DIR)/dtra2 \
    $(DIST_DIR)/dtra2-csv \
    $(DIST_DIR)/dtra2-ceirs
#    $(DIST_DIR)/test-xlnt

COMMON_SOURCES = \
    sheet.cc record.cc directories.cc \
    field.cc date.cc \
    rjson.cc read-file.cc

STD = c++2a
CXXFLAGS = -g -MMD $(OPTIMIZATION) $(PROFILE) -fPIC -std=$(STD) $(WARNINGS) -I$(XLNT_INCLUDE)

CXX_ROOT = /usr/local/opt/llvm
CXX = $(CXX_ROOT)/bin/clang++
CXX_TYPE = clang
CXX_NAME = $(shell $(CXX) --version | grep version | cut -d ' ' -f 3)
# FS_LIB = -L$(CXX_ROOT)/lib -lc++fs
CXX_LIB = -L$(CXX_ROOT)/lib -lc++ -lomp
WARNINGS = -Wno-weak-vtables -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded

ifeq ($(DEBUG),1)
  OPTIMIZATION = -O0 -fsanitize=address -fno-inline-functions
  CXX_NAME += DEBUG
else
  OPTIMIZATION = -O3 -mavx -mtune=intel -DNDEBUG
  CXX_NAME += OPT
endif


OUT_DIR = out
DIST_DIR = dist
LDLIBS = $(XLNT_LIB) $(CXX_LIB)
LDFLAGS = $(CXXFLAGS)

# --------------------------------------------------

all: $(TARGETS)

test: $(TARGETS)
	time $(DIST_DIR)/test-xlnt ~/Shared/AC/Projects/Nicola-DTRA/master/DTRA-Prj.master.xlsx

# -------------------- xlnt --------------------

XLNT_RELEASE = 1.5.0
XLNT_LIB = xlnt-$(XLNT_RELEASE)/build/source/libxlnt.dylib
XLNT_INCLUDE = xlnt-$(XLNT_RELEASE)/include
XLNT_CXX_FLAGS = $(OPTIMIZATION)
XLNT_CMAKE_CMD = cmake -D CMAKE_COLOR_MAKEFILE=OFF -D CMAKE_BUILD_TYPE=Release -D TESTS=OFF -D CMAKE_CXX_FLAGS_RELEASE="$(XLNT_CXX_FLAGS)" -D CMAKE_CXX_COMPILER="$(CXX)" ..

xlnt: $(XLNT_LIB)

$(XLNT_LIB): | xlnt-$(XLNT_RELEASE) cmake-installed
	cd xlnt-$(XLNT_RELEASE) && mkdir -p build && cd build && $(XLNT_CMAKE_CMD) && $(MAKE)
	test -x /usr/bin/install_name_tool && /usr/bin/install_name_tool -id $(abspath $(XLNT_LIB)) $(XLNT_LIB)

xlnt-$(XLNT_RELEASE):
	curl -OsL https://github.com/tfussell/xlnt/archive/v$(XLNT_RELEASE).tar.gz
	tar xzf v$(XLNT_RELEASE).tar.gz
	rm -f v$(XLNT_RELEASE).tar.gz
	if [ -f xlnt-$(XLNT_RELEASE)/third-party/libstudxml/version ]; then mv xlnt-$(XLNT_RELEASE)/third-party/libstudxml/version xlnt-$(XLNT_RELEASE)/third-party/libstudxml/version.orig; fi

# -------------------- utils --------------------

.PHONY: cmake-installed
cmake-installed:
	@cmake --version >/dev/null || ( echo "ERROR: install cmake" >&2; false )

# -------------------- rules --------------------

-include $(OUT_DIR)/*.d

$(DIST_DIR)/%: $(OUT_DIR)/%.o $(patsubst %.cc,$(OUT_DIR)/%.o,$(COMMON_SOURCES)) | $(DIST_DIR) $(XLNT_LIB)
	@echo $(LDFLAGS) -o $@ $(LDLIBS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# abspath below is to show full file path by __FILE__ macro used in logging
$(OUT_DIR)/%.o: cc/%.cc | $(OUT_DIR) $(XLNT_LIB)
	@echo $(CXX_NAME) $(CXXFLAGS) $<
	@$(CXX) $(CXXFLAGS) -c -o $@ $(abspath $<)

clean:
	rm -rf $(OUT_DIR) $(DIST_DIR)

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(DIST_DIR):
	mkdir -p $(DIST_DIR)

# ======================================================================
### Local Variables:
### eval: (if (fboundp 'eu-rename-buffer) (eu-rename-buffer))
### End:
