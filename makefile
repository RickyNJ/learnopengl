CXX = g++
CXXFLAGS = -Wall -Iinclude
LDFLAGS = -L/usr/local/lib -L. -lglfw -ldl
SRC = src/main.cpp src/glad.c src/shader.cpp src/std_image.cpp
TESTSRC = src/test.cpp src/glad.c
OUT = window
TESTOUT = test 

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(OUT)

clean:
	rm -f $(OUT)

test:
	$(CXX) $(CXXFLAGS) $(TESTSRC) $(LDFLAGS) -o $(TESTOUT)
