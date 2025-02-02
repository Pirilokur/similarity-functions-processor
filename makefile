all: similarity dictionary cosin

TARGET_EXEC ?= similarity dictionary cosin

INTM_FILES ?= postings.txt dictionary.txt  size.txt

SRC_DIRS ?= ./src
BUILD_DIR ?= ./BUILD


SRCS := $(shell find $(SRC_DIRS) -name *.cpp -o -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)


DICT_EXEC ?= dictionary



DICT_SRC_DIRS ?= ./dict/src
DICT_BUILD_DIR ?= ./DICTIONARY_BUILD

DICT_SRCS := $(shell find $(DICT_SRC_DIRS) -name *.cpp -o -name *.c)
DICT_OBJS := $(DICT_SRCS:%=$(DICT_BUILD_DIR)/%.o)

DICT_INC_DIRS := $(shell find $(DICT_SRC_DIRS) -type d)


COS_EXEC ?= cosine


COS_SRC_DIRS ?= ./cosine/src
COS_BUILD_DIR ?= ./COSINE_BUILD

COS_SRCS := $(shell find $(COS_SRC_DIRS) -name *.cpp -o -name *.c)
COS_OBJS := $(COS_SRCS:%=$(COS_BUILD_DIR)/%.o)

COS_INC_DIRS := $(shell find $(COS_SRC_DIRS) -type d)


CC = g++



similarity: $(OBJS)
	$(CC) $(OBJS) -o $@ 

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -w  -c $< -o $@

$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@



dictionary: $(DICT_OBJS)
	$(CC) $(DICT_OBJS) -o $@ 

$(DICT_BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -w  -c $< -o $@

$(DICT_BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

cosin: $(COS_OBJS)
	$(CC) $(COS_OBJS) -o $@ 

$(COS_BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -w  -c $< -o $@

$(COS_BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(DICT_BUILD_DIR)
	$(RM) -r $(COS_BUILD_DIR)
	$(RM) $(TARGET_EXEC)
	$(RM) $(INTM_FILES)

-include $(DEPS)

MKDIR_P ?= mkdir -p


