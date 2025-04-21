.PHONY: all test clean

all: stringMatchHorspool

stringMatchHorspool: stringMatchHorspool.cpp
	g++ ./stringMatchHorspool.cpp -Wall -std=c++11 -o stringMatchHorspool

test: all
	@echo "Running tests..." > output.txt
	@for number in 1 2 3; do \
		echo "\n--- Test $$number ---" >> output.txt; \
		cat text_$$number.txt > temp_input.txt; \
		cat pattern_$$number.txt >> temp_input.txt; \
		./stringMatchHorspool < temp_input.txt >> output.txt; \
	done
	@rm -f temp_input.txt
	@echo "Tests complete. Results saved to output.txt"

clean:
	rm -f stringMatchHorspool output.txt temp_input.txt
