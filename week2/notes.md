# Week 2：編譯、除錯、陣列與字串

## 一句話總結


## 編譯器 clang

### 基本用法
- `clang hello.c` → 預設輸出 a.out
- `clang -o hello hello.c` → 指定輸出檔名為 hello（寫成 `clang hello.c -o hello` 也一樣）
- `-o` 和檔名要相鄰；其他選項和來源檔的順序大多可互換

### 用 -l 連結函式庫
- `clang -o hello hello.c -lcs50`
- `-lxxx` 代表連結名為 libxxx 的函式庫：-lcs50 → libcs50，-lm → libm（數學，sqrt 等）
- -l 要放在來源檔「後面」：連結器由左往右處理，要先知道誰需要這個函式
- 用 `ldd bin/xxx` 可以查看執行檔連結了哪些共享函式庫

### 兩種錯誤要分清楚

| 缺了什麼 | 在哪個階段出錯 | 錯誤訊息關鍵字 |
|------|------|------|
| #include <cs50.h> | 編譯（第 2 階段） | implicit declaration / undeclared function 'get_string' |
| -lcs50 | 連結（第 4 階段） | undefined reference to `get_string' |

- 缺 #include：編譯器不認識這個函式長什麼樣
- 缺 -l：編譯器認識，但連結器找不到函式的實際程式碼

## 編譯的四個階段
平常說的「編譯」其實包含四個步驟：

| 階段 | 做什麼 | 可單獨執行 |
|------|------|------|
| 1. 前置處理 preprocessing | 處理 # 開頭的指令：#include 把標頭檔內容貼進來、#define 做文字替換 | clang -E hello.c |
| 2. 編譯 compiling | C 程式碼 → 組合語言（assembly） | clang -S hello.c → hello.s |
| 3. 組譯 assembling | 組合語言 → 機器碼（0 和 1） | clang -c hello.c → hello.o |
| 4. 連結 linking | 把自己的 .o 和函式庫（如 libcs50）合併成執行檔 | clang -o hello hello.o -lcs50 |

- #include 和 #define 都是 # 開頭，因為都由前置處理器處理（解開 Week 1 的待解問題）
- 第 3 階段產生的 .o 就是 .gitignore 裡擋掉的 *.o
- 連結進來的函式庫不只提供函式，它的初始化程式也會執行（例：libcs50 會把 stdout 設成無緩衝，見 Week 1 sleep_test）

## make 做了什麼、省略了什麼
- make 不是編譯器，它讀取規則後「組出完整的 clang 指令並執行」
- 我打 `make hello`，實際執行的是一長串：`clang -ferror-limit=1 -gdwarf-4 -ggdb3 -O0 -std=c11 -Wall -Werror -Wextra ... hello.c -o bin/hello -lcrypt -lcs50 -lm`
- 省略掉的部分：編譯器名稱、所有警告與除錯參數、輸出路徑、要連結的函式庫
- CS50 線上環境的 make 已預先設定好這些參數；我的 Ubuntu 則靠自己寫的 common.mk
- 一般 make 會比對檔案時間，原始碼沒改就不重新編譯（我的規則因為輸出到 bin/，每次都會重新編譯）

## 標頭檔與原型（prototype）的作用
- 標頭檔（.h）主要放的是「原型」：函式名稱、參數型別、回傳型別
  - 例：cs50.h 裡有類似 `string get_string(string prompt, ...);` 的宣告
- 函式的實際程式碼（實作）不在 .h 裡，而在函式庫（libcs50）或其他 .c 檔
- 原型的作用：讓編譯器在第 2 階段就能檢查呼叫是否正確（參數數量、型別），並知道回傳什麼型別
- #include 在第 1 階段把原型貼進來，效果等於自己在檔案開頭寫原型
- 分工：原型（宣告）給編譯器看，實作（定義）給連結器找
- Java 對照：Java 沒有標頭檔，編譯器直接讀其他類別的 .class 檔取得方法資訊

## Garbage value（垃圾值）
- 宣告變數但沒給初始值，值是那塊記憶體之前殘留的內容，無法預期
- 例：`int scores[3];` 沒賦值就印出，會看到奇怪的數字
- Java 對照：區域變數不初始化會編譯錯誤；陣列元素自動初始化為 0
- C 的例外：全域變數會自動初始化為 0，區域變數不會
- 好習慣：宣告時就初始化，`int x = 0;`、`int scores[3] = {0};`（全部設為 0）
- 相關經驗：Week 1 compare_scanf 印出的 -1519029308 就是垃圾值

## 陣列：C vs Java

| 項目 | Java | C |
|------|------|-----|
| 宣告 | `int[] a = new int[N];` | `int a[N];` |
| 本質 | heap 上的物件，變數存參考 | 一塊連續記憶體 |
| 預設值 | 全部為 0 | 區域陣列是垃圾值 |
| 長度 | `a.length` | 沒有，要自己記，參數要另外傳 |
| 參數寫法 | `int[] a` | `int length, int a[]` |
| 函式內修改 | 影響原陣列 | 影響原陣列（傳的是位置，原理見 Lecture 4 指標） |
| 超出範圍 | 丟出例外 | 不檢查，未定義行為（緩衝區溢位） |
| `b = a;` | 兩個變數指向同一陣列 | 編譯錯誤，只能逐一複製 |
| 回傳陣列 | 可以 | 不能回傳區域陣列 |

- 初始化：`int a[3] = {0};` 全部歸零；`int a[] = {72, 73, 33};` 大小由編譯器算出
- 參數寫 `int a[10]` 時，10 會被忽略，效果等同 `int a[]`
- 算長度的技巧 `sizeof(a) / sizeof(a[0])` 只在宣告陣列的地方有效，傳進函式後會失效（量到的是位置的大小 8 bytes）
- C 的 const 不是真正的編譯期常數，用 const int N 當陣列大小有時會出問題；最保險用 #define N 3
- 程式：scores_v3.c（固定大小）→ scores_v4.c（常數 N + 抽出 average 函式）

## Command-line arguments（命令列參數）
- 寫法：`int main(int argc, string argv[])`（標準 C 寫法是 `char *argv[]`）
- argc：參數個數，「包含程式名稱本身」
- argv：參數陣列，argv[0] 是程式名稱，argv[1] 才是第一個參數
- 例：`./bin/greet David` → argc 為 2，argv[0] 是 "./bin/greet"，argv[1] 是 "David"
- 所有參數都是字串，要當數字用需轉換：`atoi(argv[1])`（需 #include <stdlib.h>）
- 一定要先檢查 argc 再讀 argv，否則讀到不存在的位置
- 參數錯誤時印出用法並 return 1，可用 `echo $?` 查看結束狀態

## Java vs C 差異

| 項目 | Java | C |
|------|------|-----|
| 命令列參數 | String[] args，args[0] 是第一個參數 | argv[0] 是程式名稱，argv[1] 才是第一個參數 |
| 參數個數 | args.length | argc（包含程式名稱，所以至少是 1） |
| 陣列預設值 | 自動初始化為 0 | 區域陣列是垃圾值，需自己初始化 |
| 取得其他程式碼的資訊 | 讀 .class 檔 | 透過 #include 標頭檔取得原型 |
| 小數常值 | 3.0 是 double，3.0f 是 float | 相同：3.0 是 double，3.0f 是 float |

## 踩過的坑

### 同樣的平均，float 和 double 印出不同結果
- 現象：72、73、33 的平均，v3 印出 59.333333，v4 印出 59.333332
- 原因：v3 寫 / 3.0，帶小數點的常值預設是 double；v4 用 (float) length 且回傳 float，只有約 7 位有效數字
- 178 / 3 存成 float 最接近的值是 59.3333320617...，精確度在存入時就損失了，傳給 printf 時轉成 double 也救不回來
- 解法：函式回傳和轉型都改用 double
- 補充：3.0 是 double，3.0f 才是 float
- 程式：scores_v3.c、scores_v4.c

## 待解問題
- [ ] string 和 char * 是什麼關係？（預計 Lecture 4 指標）
- [ ] 陣列傳進函式時傳的「位置」是什麼？（預計 Lecture 4 指標）

## 參考
- 官方筆記：https://cs50.harvard.edu/x/notes/2/
- K&R 的內容依章節記在對應週數的筆記（第 1 章在 week1）
