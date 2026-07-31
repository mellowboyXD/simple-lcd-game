CXX := avr-g++
OBJCOPY := avr-objcopy
TARGET_EXEC := droid
DEVICE := atmega328p
FREQ := 16000000UL
DUDE := avrdude
DUDE_DEVICE := arduino
DUDE_BAUD := 115200
USB_PORT := COM3

BUILD_DIR := ./build
SRC_DIRS := ./src

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
SRCS := $(shell find $(SRC_DIRS) -name '*.cpp')

# Prepends BUILD_DIR and appends .o to every src file
# As an example, ./your_dir/hello.cpp turns into ./build/./your_dir/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# String substitution (suffix version without %).
# As an example, ./build/hello.cpp.o turns into ./build/hello.cpp.d
DEPS := $(OBJS:.o=.d)

# Every folder in ./src will need to be passed to GCC so that it can find header files
INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# The -MMD and -MP flags together generate Makefiles for us!
# These files will have .d instead of .o as the output.
CPPFLAGS := $(INC_FLAGS) -Os -MMD -MP -DF_CPU=$(FREQ) -mmcu=$(DEVICE) -I./include/

$(BUILD_DIR)/$(TARGET_EXEC).hex: $(BUILD_DIR)/$(TARGET_EXEC)
	$(OBJCOPY) -O ihex -R .eeprom $< $@

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) -mmcu=$(DEVICE) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean flash

flash: $(BUILD_DIR)/$(TARGET_EXEC).hex
	$(DUDE) -F -V -c $(DUDE_DEVICE) -p $(DEVICE) -P $(USB_PORT) \
		-b $(DUDE_BAUD) -U flash:w:$<:i

clean:
	rm -r $(BUILD_DIR)

# Include the .d makefiles. The - at the front suppresses the errors of missing
# Makefiles. Initially, all the .d files will be missing, and we don't want those
# errors to show up.
-include $(DEPS)
