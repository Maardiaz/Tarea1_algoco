CXX = g++
CXXFLAGS = -std=c++17 -Wall -O3

SRCS = matrix_multiplication.cpp algorithms/naive.cpp algorithms/strassen.cpp
TARGET = matrix_app

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

test: $(TARGET)
	@echo "Iniciando evaluacion de todos los escenarios generados..."
	@for file in data/matrix_input/*_1.txt; do \
		if [ -f "$$file" ]; then \
			echo "Procesando $$file"; \
			./$(TARGET) $$file; \
		fi \
	done
	@echo "Meticas guardadas en data/measurements/"

clean:
	rm -f $(TARGET)