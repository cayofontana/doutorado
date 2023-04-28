APP 		:= trabalhocg
CPP 		:= g++
CPPFLAGS	:= -Wall -lGL -lglut

SOURCE		:= $(shell find . -name "*.cpp")
OBJECTS		:= $(patsubst %.cpp, %.o, $(SOURCE))

all: $(APP)
	$(info PARA EXECUTAR O PROGRAMA, ENTRE COM A SEGUINTE INSTRUÇÃO: "./$(APP) <endereco_arquivo_xml> <posição_janela_x> <posição_janela_y>")

$(APP): $(OBJECTS)
	$(CPP) -o $(APP) $(OBJECTS) $(CPPFLAGS)

clean:
	rm -f $(OBJECTS) $(APP)