BUILD_DIR=build
T3D_DIR=$(HOME)/t3d
T3D_INST=$(shell realpath $(T3D_DIR))

include $(N64_INST)/include/n64.mk
include $(T3D_INST)/t3d.mk

PROJECT_NAME=ibe

DEBUG=0

ifeq ($(DEBUG),0)
  N64_CFLAGS += -O2
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
		src/test_level.c \
		src/ui.c \
		src/utils.c
assets_debug_font = $(wildcard assets/*.png)
assets_png = $(wildcard assets/models/*.png)
assets_gltf = $(wildcard assets/models/*.glb)
assets_ttf = $(wildcard assets/fonts/*.ttf)
assets_xm = $(wildcard assets/sound/*.xm)
assets_wav = $(wildcard assets/sound/*.wav)

assets_conv = $(addprefix filesystem/,$(notdir $(assets_debug_font:%.png=%.sprite))) \
			  $(addprefix filesystem/models/,$(notdir $(assets_png:%.png=%.sprite))) \
			  $(addprefix filesystem/fonts/,$(notdir $(assets_ttf:%.ttf=%.font64))) \
			  $(addprefix filesystem/models/,$(notdir $(assets_gltf:%.glb=%.t3dm)))  \
			  $(addprefix filesystem/sound/,$(notdir $(assets_xm:%.xm=%.xm64)))     \
			  $(addprefix filesystem/sound/,$(notdir $(assets_wav:%.wav=%.wav64)))

all: $(PROJECT_NAME).z64

filesystem/%.sprite: assets/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o filesystem "$<"

filesystem/BG0.rgba16.sprite: MKSPRITE_FLAGS=-f RGBA16 -c 1

filesystem/models/%.t3dm: assets/models/%.glb
	@mkdir -p $(dir $@)
	@echo "    [T3D-MODEL] $@"
	$(T3D_GLTF_TO_3D) "$<" $@
	$(N64_BINDIR)/mkasset -c 2 -w 256 -o filesystem $@

filesystem/models/%.sprite: assets/models/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o $(dir $@) "$<"

filesystem/fonts/%.font64: assets/fonts/%.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	$(N64_MKFONT) $(MKFONT_FLAGS) -s 9 -o $(dir $@) "$<"

filesystem/sound/%.xm64: assets/sound/%.xm
	@mkdir -p $(dir $@)
	@echo "    [AUDIO] $@"
	@$(N64_AUDIOCONV) $(AUDIOCONV_FLAGS) -o $(dir $@) "$<"

filesystem/sound/%.wav64: assets/sound/%.wav
	@mkdir -p $(dir $@)
	@echo "    [AUDIO] $@"
	@$(N64_AUDIOCONV) $(AUDIOCONV_FLAGS) -o $(dir $@) "$<"

filesystem/sound/ene.wav64: AUDIOCONV_FLAGS=--wav-compress 3

$(BUILD_DIR)/$(PROJECT_NAME).dfs: $(assets_conv)
$(BUILD_DIR)/$(PROJECT_NAME).elf: $(src:%.c=$(BUILD_DIR)/%.o)

$(PROJECT_NAME).z64: N64_ROM_TITLE="IBE Demo"
$(PROJECT_NAME).z64: $(BUILD_DIR)/$(PROJECT_NAME).dfs

clean:
	rm -rf $(BUILD_DIR) *.z64
	rm -rf filesystem

-include $(wildcard $(BUILD_DIR)/src/*.d) $(wildcard $(BUILD_DIR)/include/*.d)

.PHONY: all clean
