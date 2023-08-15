all:
	g++ -w -o dictionary -Iinclude src/*.cpp *.cpp -Llib -lraylib -lopengl32 -lgdi32 -lwinmm && dictionary
clean:
	-del *.exe 