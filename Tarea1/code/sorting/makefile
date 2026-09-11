CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3

SRCS = sorting.cpp algorithms/mergesort.cpp algorithms/quicksort.cpp algorithms/patiencesort.cpp algorithms/sort.cpp
TARGET = sorting_app

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

test: $(TARGET)
	@echo "Iniciando evaluacion de arreglos..."
	@for file in data/array_input/*.txt; do \
		if [ -f "$$file" ]; then \
			echo "Procesando $$file"; \
			./$(TARGET) $$file; \
		fi \
	done
	@echo "Metricas de ordenamiento guardadas en data/measurements/"

clean:
	rm -f $(TARGET)