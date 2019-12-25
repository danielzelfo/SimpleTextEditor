OBJS = TextEditorDriver.cpp

#Change compiler here if required
CC = g++

OBJ_NAME = TextEditorDriver

all :
	$(CC) $(OBJS) -std=c++11 -o $(OBJ_NAME)