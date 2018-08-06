EXENAME = testimage
OBJS = png.o image.o testimage.o rgbapixel.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi -lpthread

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

testimage.o : testimage.cpp image.h
	$(CXX) $(CXXFLAGS) testimage.cpp

testscene.o : testscene.cpp scene.h
	$(CXX) $(CXXFLAGS) testscene.cpp

image.o : image.cpp image.h
	$(CXX) $(CXXFLAGS) image.cpp

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

clean :
	-rm -f *.o $(EXENAME)
