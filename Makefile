all: zappy_ai

build:
	cmake -B build -S .

zappy_ai: build
	cmake --build build -j

install: zappy_ai

clean:
	rm -r build/

.PHONY: all zappy_ai install
