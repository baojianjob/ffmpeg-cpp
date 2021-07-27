ifeq ($(debug), y)
	OPT = -g2
else
	OPT = -O2
endif

CPPFLAGS = -std=c++11 -I../ffmpeg-cpp $(OPT)
LDFLAGS = 
LDLIBS = ../ffmpeg-cpp/ffmpegcpp.a -lavcodec -lavformat -lavutil -lswscale -lswresample

SRC_FILES := $(wildcard ./*.cpp)

OBJ_FILES := $(SRC_FILES:.cpp=.o)

TARGET = ../../../encode_audio

$(TARGET): $(OBJ_FILES)
	$(CXX) -o $(TARGET) $(OBJ_FILES) $(LDLIBS)
test : $(TARGET) 
	$(TARGET)
clean:
	rm -f $(OBJ_FILES) $(TARGET)


