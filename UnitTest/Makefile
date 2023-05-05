TARGET = unittest

SRCFILES = ./Unittest.cpp
SRCFILES += ./TestMain.cpp

HEADFILES = -I ../

CFLAGS = -lgtest -lpthread -g -std=c++1z

$(TARGET) : $(SRCFILES)
	g++ -o $(TARGET) $(SRCFILES) $(HEADFILES) $(CFLAGS)

clean:
	rm -rf $(TARGET)
