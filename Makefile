# -*- Makefile -*-

TARGETS = \
    $(DIST_DIR)/dtra2 \
    $(DIST_DIR)/test-xlnt

COMMON_SOURCES = \
    sheet.cc record.cc \
    rjson.cc read-file.cc

STD = c++17
CXXFLAGS = -g -MMD $(OPTIMIZATION) $(PROFILE) -fPIC -std=$(STD) $(WARNINGS) -I$(XLNT_INCLUDE)

CXX_ROOT = /usr/local/opt/llvm
CXX = $(CXX_ROOT)/bin/clang++
CXX_TYPE = clang
CXX_NAME = "clang++-7.0.0   "
FS_LIB = -L$(CXX_ROOT)/lib -lc++fs
CXX_LIB = -L$(CXX_ROOT)/lib -lc++ -lomp $(FS_LIB)
WARNINGS = -Wno-weak-vtables -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-padded
OPTIMIZATION = -O3 -mavx -mtune=intel -DNDEBUG

OUT_DIR = out
DIST_DIR = dist
LDLIBS = $(XLNT_LIB) $(CXX_LIB)

# --------------------------------------------------

all: $(TARGETS)

test: $(TARGETS)
	time $(DIST_DIR)/test-xlnt ~/Shared/AC/Projects/Nicola-DTRA/master/DTRA-Prj.master.xlsx

# -------------------- xlnt --------------------

XLNT_RELEASE = 1.3.0
XLNT_LIB = xlnt-$(XLNT_RELEASE)/build/source/libxlnt.dylib
XLNT_INCLUDE = xlnt-$(XLNT_RELEASE)/include

xlnt: $(XLNT_LIB)

$(XLNT_LIB): | xlnt-$(XLNT_RELEASE) cmake-installed
	cd xlnt-$(XLNT_RELEASE) && mkdir -p build && ( cd build && cmake -D CMAKE_BUILD_TYPE=Release -D TESTS=OFF -D CMAKE_CXX_FLAGS_RELEASE="$(OPTIMIZATION)" -D CMAKE_CXX_COMPILER="$(CXX)" .. && $(MAKE) )
	test -x /usr/bin/install_name_tool && /usr/bin/install_name_tool -id $(abspath $(XLNT_LIB)) $(XLNT_LIB)

xlnt-$(XLNT_RELEASE):
	curl -OsL https://github.com/tfussell/xlnt/archive/v$(XLNT_RELEASE).tar.gz
	tar xzf v$(XLNT_RELEASE).tar.gz
	rm -f v$(XLNT_RELEASE).tar.gz

# -------------------- utils --------------------

.PHONY: cmake-installed
cmake-installed:
	@cmake --version >/dev/null || ( echo "ERROR: install cmake" >&2; false )

# -------------------- rules --------------------

-include $(OUT_DIR)/*.d

$(DIST_DIR)/%: $(OUT_DIR)/%.o $(patsubst %.cc,$(OUT_DIR)/%.o,$(COMMON_SOURCES)) | $(DIST_DIR) $(XLNT_LIB)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)

# abspath below is to show full file path by __FILE__ macro used in logging
$(OUT_DIR)/%.o: cc/%.cc | $(OUT_DIR)
	@echo $(CXX_NAME) $(OPTIMIZATION) $<
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
