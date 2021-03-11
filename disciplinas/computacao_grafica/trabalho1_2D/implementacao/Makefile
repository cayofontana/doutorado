APP 		:= trabalho1_2D
CPP 		:= g++
CPPFLAGS	:= -Wall -lGL -lglut -ltinyxml2

SOURCE		:= $(shell find . -name "*.cpp")
OBJECTS		:= $(patsubst %.cpp, %.o, $(SOURCE))

all: $(APP)
	$(info PARA EXECUTAR O PROGRAMA, ENTRE COM A SEGUINTE INSTRUÇÃO: "./trabalho2D <endereco_arquivo_xml> <posição_janela_x> <posição_janela_y>")

$(APP): $(OBJECTS)
	$(CPP) -o $(APP) $(OBJECTS) $(CPPFLAGS)

clean:
	rm -f $(OBJECTS) $(APP)