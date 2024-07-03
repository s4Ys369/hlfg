BUILD_DIR=build
T3D_DIR=$(HOME)/t3d
T3D_INST=$(shell realpath $(T3D_DIR))

include $(N64_INST)/include/n64.mk
include $(T3D_INST)/t3d.mk

PROJECT_NAME=ibe

DEBUG=0

ifeq ($(DEBUG),0)
  N64_CFLAGS += -Ofast
else
  N64_CFLAGS += -g -ggdb
endif

N64_CFLAGS += -std=gnu2x \
	-mno-check-zero-division \
	-funsafe-math-optimizations \
	-fsingle-precision-constant \
	-fno-unroll-loops \
	-fno-peel-loops \
	-falign-functions=32 \
	-fno-merge-constants \
    -fno-strict-aliasing \
	-ffast-math \
    -mips3 \

src =   src/main.c \
		src/actors.c \
		src/camera.c \
		src/collision.c \
		src/debug.c \
		src/input.c \
		src/map.c \
		src/player.c \
		src/sound.c \
		src/ui.c \
		src/utils.c \
		src/wf_test.c
assets_png = $(wildcard assets/*.png)
assets_gltf = $(wildcard assets/*.glb)
assets_ttf = $(wildcard assets/*.ttf)
assets_xm = $(wildcard assets/*.xm)
assets_wav = $(wildcard assets/*.wav)

assets_conv = $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite))) \
			  $(addprefix filesystem/,$(notdir $(assets_ttf:%.ttf=%.font64))) \
			  $(addprefix filesystem/,$(notdir $(assets_gltf:%.glb=%.t3dm)))  \
			  $(addprefix filesystem/,$(notdir $(assets_xm:%.xm=%.xm64)))     \
			  $(addprefix filesystem/,$(notdir $(assets_wav:%.wav=%.wav64)))

all: $(PROJECT_NAME).z64

filesystem/%.sprite: assets/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o filesystem "$<"

filesystem/%.font64: assets/%.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	$(N64_MKFONT) $(MKFONT_FLAGS) -s 9 -o filesystem "$<"

filesystem/%.t3dm: assets/%.glb
	@mkdir -p $(dir $@)
	@echo "    [T3D-MODEL] $@"
	$(T3D_GLTF_TO_3D) "$<" $@
	$(N64_BINDIR)/mkasset -c 2 -w 256 -o filesystem $@

filesystem/%.xm64: assets/%.xm
	@mkdir -p $(dir $@)
	@echo "    [AUDIO] $@"
	@$(N64_AUDIOCONV) $(AUDIOCONV_FLAGS) -o filesystem "$<"

filesystem/%.wav64: assets/%.wav
	@mkdir -p $(dir $@)
	@echo "    [AUDIO] $@"
	@$(N64_AUDIOCONV) $(AUDIOCONV_FLAGS) -o filesystem "$<"

$(BUILD_DIR)/$(PROJECT_NAME).dfs: $(assets_conv)
$(BUILD_DIR)/$(PROJECT_NAME).elf: $(src:%.c=$(BUILD_DIR)/%.o)

$(PROJECT_NAME).z64: N64_ROM_TITLE="IBE Demo"
$(PROJECT_NAME).z64: $(BUILD_DIR)/$(PROJECT_NAME).dfs

clean:
	rm -rf $(BUILD_DIR) *.z64
	rm -rf filesystem

-include $(wildcard $(BUILD_DIR)/src/*.d) $(wildcard $(BUILD_DIR)/include/*.d)

.PHONY: all clean
