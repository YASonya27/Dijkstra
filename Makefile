TARGET = my_program								# название файла, куда скомпилится прога
SRCS = main.cpp mygraph.cpp mygraph.cpp			# файлы, которые нужно скомпилить
OBJS = $(SRCS:.cpp=.o) 							# заменяем .cpp на .o (создаем объектные файлы)
CXX = g++										# указали, что будем пользоваться компилятором g++

# Правило для сборки исполняемого файла
$(TARGET): $(OBJS)								# объединяем в файлы из OBJS в файл my_program
	$(CXX) -o $@ $^								# команда сборки

# Правило для сборки объектных файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Правило для очистки
clean:
	rm -f $(TARGET) $(OBJS)
