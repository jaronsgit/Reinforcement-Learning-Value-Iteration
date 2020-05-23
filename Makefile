CC := g++ #Current Compiler
CFLAGS := -std=c++11 #-Wall #Special options for compiler

BIN		:= bin#Folder that contains the output executables
BUILD	:= build#Folder that contains all the object files - are removed on clean
SRC     := src#Contains the application and the application's source files
INCLUDE := include#Contains all the project header files
TARGET  := rlValIt#Name of the executable
SRCEXT := cpp

SOURCES := $(shell find $(SRC) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRC)/%,$(BUILD)/%,$(SOURCES:.$(SRCEXT)=.o))

#Linking Object Files
$(BIN)/$(TARGET): $(OBJECTS)
	@echo "🔗 Linking Object Files..."
	$(CC) $(OBJECTS) -o $(BIN)/$(TARGET) -std=c++11
#Compiling Object Files
$(BUILD)/%.o : $(SRC)/%.cpp   
	@echo "🚧 Building (Compiling Object Files)..."
	$(CC) -c $< -o $@ -std=c++11

run:
	clear
	@echo "🚀 Executing..."
	./$(BIN)/$(TARGET)

# deletes all the object code files as well as the previously generated outputs
clean:
	@echo "🧹 Cleaning..."
	@rm -f $(BUILD)/*.o
	@rm -f $(BIN)/$(TARGET)
	@echo "🏁 Cleaning Complete."