CC := g++
CCF := -O1 -std=c++17
CCLF := pkg-config --cflags --libs x11 xft fontconfig
SRC := text.cpp
OUT := font_shower

main:
	@$(CC) $(CCF) $(SRC) -o $(OUT) `$(CCLF)`
