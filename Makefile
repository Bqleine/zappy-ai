all: zappy_ai

build:
	cmake -B build -S .

zappy_ai: build
	cmake --build build -j

install:
	mkdir -p /usr/local/bin/
	cp zappy_ai /usr/local/bin/zappy_ai

clean:
	rm -r build/

.PHONY: all zappy_ai install
