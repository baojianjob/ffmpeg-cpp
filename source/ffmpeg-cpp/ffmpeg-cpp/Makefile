ifeq ($(debug), y)
	OPT = -g2
else
	OPT = -O2
endif

CPPFLAGS = -std=c++11 -I. $(OPT)
LDFLAGS = 

SRC_FILES := $(wildcard ./*.cpp) \
		$(wildcard ./Codecs/*.cpp) \
		$(wildcard ./Demuxing/*.cpp) \
		$(wildcard ./Muxing/*.cpp) \
		$(wildcard ./Sources/*.cpp) \
		$(wildcard ./FrameSinks/*.cpp) \

OBJ_FILES := $(SRC_FILES:.cpp=.o)

TARGET = ./ffmpegcpp.a

$(TARGET): $(OBJ_FILES)
	$(AR) -r $@ $^
test : $(TARGET)
	$(TARGET)
clean:
	rm -f $(OBJ_FILES) $(TARGET)


