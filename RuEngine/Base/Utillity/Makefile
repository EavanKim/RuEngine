CXX                             = g++
SRCS                            = $(wildcard *.cpp)
OBJS                            = $(SRCS:.cpp=.o)
SOBJS                           = $(SRCS:.cpp=.so)
LIBTARGET                       = libEngine
LIBFLAG                         = -fPIC -c
LIBSOFLAG                       = -shared -Wl,-soname,
INC                             = -I../99.Header
DMODE							= -D_DEBUG

all : $(TARGET)
	$(CXX) $(LIBSOFLAG)$(LIBTARGET).so -o $(LIBTARGET).so.1.0.0

.PHONY:debug
debug : 
	cd ./String; $(MAKE) debug
	cd ./File; $(MAKE) debug
	cp ./Headers/*.h ../headers
	cp ./lib/*.o ../lib

.PHONY:release
release : $(TARGET)
	$(CXX) $(DMODE) $(LIBFLAG) $(SRCS) $(INC)
	mv *.o ../Release
	cp *.h ../99.Header

clean :
	rm -f *.o
	rm -f *.so

$(TARGET) :
	$(CXX) $(LIBFLAG) $(SRC_DIRS) $(INC)