# 與 CS50 線上環境相同的編譯設定
CC = clang
CFLAGS = -ferror-limit=1 -gdwarf-4 -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra \
         -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter \
         -Wno-unused-variable -Wno-unused-but-set-variable -Wshadow
LDLIBS = -lcrypt -lcs50 -lm

# 用法：make hello → 編譯 hello.c，輸出到 bin/hello
%: %.c
	@mkdir -p bin
	$(CC) $(CFLAGS) $< -o bin/$@ $(LDLIBS)

# 用法：make clean → 刪除所有編譯產物
clean:
	rm -rf bin

.PHONY: clean
