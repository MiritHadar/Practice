INC_FOLDER = ./include
SRC_FOLDER = ./src
OBJ_FOLDER = ./objects

CXX = g++

# Debug
CXXFLAGS = -O0 -std=c++11 

INC = -I$(INC_FOLDER)

RM = rm -f

SOURCES = calculator.cpp calculator_test.cpp  

OBJECTS = $(patsubst %.cpp, $(OBJ_FOLDER)/%.o, $(SOURCES)) 

LIBRARY = 
EXECUTABLE = calculator.out

all: $(LIBRARY) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

$(LIBRARY): $(OBJECTS)
	$(AR) $(ARFLAGS) $(LIBRARY) $(OBJECTS)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.cpp | $(OBJ_FOLDER)
	$(CXX) $(CXXFLAGS) $(INC) -o $@ -c $< 

$(OBJ_FOLDER): 
	mkdir -p $(OBJ_FOLDER)

clean:
	$(RM) $(OBJ_FOLDER)/*.o $(LIBRARY) $(EXECUTABLE)
