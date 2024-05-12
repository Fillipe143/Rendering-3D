.SILENT:

CMAKE_DIR = .cmake
P = cube

cmake:
	cmake $(CMAKE_DIR)

build:
	make -sC $(CMAKE_DIR) $(P)/fast

run: build
	./targets/$(P)
