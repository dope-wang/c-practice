# Week 2：編譯、除錯、陣列與字串

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
- 相關經驗：cs50作業中 substitution 的計數陣列 `int cArr[26];` 沒初始化，直接 `cArr[...]++` 會從垃圾值開始累加，正確的金鑰也可能被判為無效

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

## 字串（string）

### 字串以 \0 結尾
- C 的字串就是字元陣列，最後多一個 NUL 字元 '\0'（數值 0）當作結尾標記
- "HI!" 看起來 3 個字元，實際佔 4 個 byte：

| s[0] | s[1] | s[2] | s[3] |
|------|------|------|------|
| H | I | ! | \0 |
| 72 | 73 | 33 | 0 |

- \0 是編譯器在寫 "HI!" 時自動加上的，所以 s[3] 是合法存取，一定是 0
- 字串沒有記錄自己的長度，printf("%s") 和 strlen 都是一路往下讀，遇到 0 才停
- 自己實作 strlen：從 n = 0 開始，while (s[n] != '\0') n++;
- 單引號 'H' 是一個 char；雙引號 "H" 是字串，佔 2 個 byte（H 和 \0）
- 程式：hi.c、length.c

### strlen 回傳 size_t，不是 int
- 宣告：size_t strlen(const char *s);（需 #include <string.h>）
- size_t 是無號整數型別，在 64 位元 Linux 上等於 unsigned long
- printf 印 size_t 要用 %zu（跨平台正確）；%lu 在 64 位元 Linux 可用，但不保證其他平台
- sizeof 的結果也是 size_t，所以 Week 1 印 sizeof 用的就是 %zu
- 也可以先存進 int：int length = strlen(name); 再用 %i 印出（size_t 轉 int 的隱含轉換在 -Wall -Wextra 下不會警告）

## ctype.h：字元判斷與轉換
- 需 #include <ctype.h>，忘了引入會出現 implicit declaration 錯誤

| 函式 | 用途 |
|------|------|
| islower(c) / isupper(c) | 是否為小寫 / 大寫字母 |
| isalpha(c) | 是否為字母 |
| isdigit(c) | 是否為數字 0–9 |
| isalnum(c) | 是否為字母或數字 |
| isspace(c) | 是否為空白（空格、\t、\n 等） |
| ispunct(c) | 是否為標點符號 |
| tolower(c) / toupper(c) | 轉成小寫 / 大寫 |

- is 系列回傳「非 0」代表真，不保證是 1，判斷時寫 if (isdigit(c))，不要寫 == 1
- toupper 傳入非小寫字元會原樣回傳，所以不需要先用 islower 判斷

### 轉大寫的三個版本
1. 手動：if (s[i] >= 'a' && s[i] <= 'z') 印 s[i] - 32（要記 ASCII 範圍和大小寫差 32）
2. 函式判斷：if (islower(s[i])) 印 toupper(s[i])，else 原樣印
3. 只用 toupper：printf("%c", toupper(s[i]));（7 行變 1 行）
- 程式：uppercase.c

### 進階注意
- ctype 函式要求傳入值在 unsigned char 範圍（0–255）或 EOF
- Linux 的 char 預設有號，中文 UTF-8 的 byte 會變成負數，直接傳入是未定義行為
- 嚴謹寫法：toupper((unsigned char) s[i])

### 迴圈裡的 strlen
- for (int i = 0, n = strlen(s); i < n; i++)：strlen 只算一次
- 寫成 i < strlen(s) 會每圈都呼叫，strlen 每次都從頭數，總次數約 n × n
- 程式：string.c

## Command-line arguments（命令列參數）
- 寫法：`int main(int argc, string argv[])`（標準 C 寫法是 `char *argv[]`）
- argc：參數個數，「包含程式名稱本身」
- argv：參數陣列，argv[0] 是程式名稱，argv[1] 才是第一個參數
- 例：`./bin/greet David` → argc 為 2，argv[0] 是 "./bin/greet"，argv[1] 是 "David"
- 所有參數都是字串，要當數字用需轉換：`atoi(argv[1])`（需 #include <stdlib.h>）
- 一定要先檢查 argc 再讀 argv，否則讀到不存在的位置
- 參數錯誤時印出用法並 return 1，可用 `echo $?` 查看結束狀態
- argv[argc] 保證是 NULL
- 用引號可以讓含空格的內容變成同一個參數：./bin/args "David Malan" → argc 為 2

### argv[0] 的意義
- 是使用者「啟動程式時打的名稱」，不一定是原始檔名：在不同目錄執行，argv[0] 就不同
- 用途一：印出使用說明 printf("Usage: %s name\n", argv[0]);，名稱永遠和使用者實際打的一致
- 用途二：程式依名稱改變行為（例：BusyBox 一個執行檔扮演 ls、cp、mv 等上百個指令）
- Java 對照：Java 程式由 java ClassName 啟動，真正執行的是 java 本身，所以 args 只放使用者參數

## 密碼學基本觀念
- 明文 plaintext、密文 ciphertext、加密法 cipher、金鑰 key
- 密文 = 加密法(明文, 金鑰)；加密法通常公開，只有金鑰要保密
- 凱撒密碼：每個字母往後移 k 位，k 是金鑰；非字母不變；超過 Z 繞回 A
- 公式：密文字母編號 = (明文字母編號 + k) % 26（字母編號 A = 0 … Z = 25）
- 解密：往反方向移 k 位
- 不安全的原因：只有 25 種金鑰可暴力破解；英文字母頻率可做頻率分析
- 現代加密（如 AES）同樣是「公開演算法 + 秘密金鑰」，但金鑰空間大到無法暴力破解

## 結束狀態與錯誤處理
- return 1 表示錯誤結束，echo $? 查看（只顯示緊接著上一個指令的結果）
- 提前返回（early return / guard clause）：開頭先檢查，不符合就 return，主要邏輯不必包在 else 裡
- 用 printf("Usage: %s name\n", argv[0]); 印出用法
- 錯誤訊息慣例送到 stderr：fprintf(stderr, ...)，輸出導向檔案時錯誤訊息仍會顯示在螢幕上
- 程式：greet.c（缺參數用預設值）、status.c（缺參數報錯結束）

### stdout 與 stderr
| 名稱 | 編號 | 用途 | 預設連到 |
|------|------|------|------|
| stdin | 0 | 標準輸入 | 鍵盤 |
| stdout | 1 | 正常輸出 | 終端機 |
| stderr | 2 | 錯誤訊息 | 終端機 |

- printf(...) 等同 fprintf(stdout, ...)
- 兩者預設都連到終端機，所以看起來一樣；但可以分開重新導向
- `> file` 只導向 stdout；`2> file` 只導向 stderr；`2> /dev/null` 丟掉錯誤訊息；`> file 2>&1` 兩者都進檔案
- 管道 `|` 只傳遞 stdout
- 分開的意義：結果寫進檔案時，錯誤訊息不會混進去，而且仍即時顯示在畫面上
- 實驗：./bin/status > out.txt，Usage（stderr）留在畫面上，Missing CLI Argument（stdout）進了檔案

## Java vs C 差異

| 項目 | Java | C |
|------|------|-----|
| 命令列參數 | String[] args，args[0] 是第一個參數 | argv[0] 是程式名稱，argv[1] 才是第一個參數 |
| 參數個數 | args.length | argc（包含程式名稱，所以至少是 1） |
| 陣列預設值 | 自動初始化為 0 | 區域陣列是垃圾值，需自己初始化 |
| 取得其他程式碼的資訊 | 讀 .class 檔 | 透過 #include 標頭檔取得原型 |
| 小數常值 | 3.0 是 double，3.0f 是 float | 相同：3.0 是 double，3.0f 是 float |
| 字串長度 | 物件內部記錄，s.length() | 沒有記錄，靠結尾的 \0 判斷，strlen 要從頭數 |
| 字串越界 | charAt 丟出 StringIndexOutOfBoundsException | 不檢查，讀到相鄰記憶體的內容 |

## 踩過的坑

### 同樣的平均，float 和 double 印出不同結果
- 現象：72、73、33 的平均，v3 印出 59.333333，v4 印出 59.333332
- 原因：v3 寫 / 3.0，帶小數點的常值預設是 double；v4 用 (float) length 且回傳 float，只有約 7 位有效數字
- 178 / 3 存成 float 最接近的值是 59.3333320617...，精確度在存入時就損失了，傳給 printf 時轉成 double 也救不回來
- 解法：函式回傳和轉型都改用 double
- 補充：3.0 是 double，3.0f 才是 float
- 程式：scores_v3.c、scores_v4.c

### strlen 用 %i 印出，編譯失敗
- 現象：printf("%i\n", strlen(name)); 出現格式警告，因為 -Werror 變成編譯錯誤
- 原因：strlen 回傳 size_t（unsigned long），%i 要求 int，型別對不上
- 解法：改用 %zu；或先存進 int 變數再用 %i 印
- 程式：length.c

### s[4] 越界讀到隔壁字串的 %
- 現象：string s = "HI!"; 印 s[4] 得到 37（'%'），程式沒有出錯
- 原因：s[4] 已超出 "HI!\0" 的 4 個 byte；字串常值通常被編譯器緊密排放在同一區域，"HI!\0" 後面很可能緊接著某個 printf 格式字串，第一個字元剛好是 %
- 驗證方法：印出 s[4] 到 s[7]，看是否為格式字串的開頭（如 %d %）
- 這是未定義行為：換編譯器、換參數、多加一個字串，結果都可能不同，甚至崩潰
- 編譯器沒警告的原因：string 是 char * 的別名，編譯器只知道「位置」，不知道後面有幾個 byte 屬於這個字串
- 程式：hi.c

### 計數陣列忘記歸零（Java 習慣帶來的盲點）
- 現象：substitution 用 `int cArr[26];` 記錄每個字母出現次數，再檢查是否都等於 1
- 原因：Java 的 `new int[26]` 保證全部是 0，C 的區域陣列卻是垃圾值，`++` 會從未知的數字開始加
- 危險之處：結果不穩定，有時測試正常、有時不正常，很難追查
- 解法：宣告時就初始化，`int counts[26] = {0};`
- 教訓：從 Java 轉到 C，「預設值」是最容易被忽略的差異，用任何陣列或變數前先問自己「它的初始值是多少？」
- 程式：substitution.c

## 待解問題
- [ ] string 和 char * 是什麼關係？（預計 Lecture 4 指標）
- [ ] 陣列傳進函式時傳的「位置」是什麼？（預計 Lecture 4 指標）

## 參考
- 官方筆記：https://cs50.harvard.edu/x/notes/2/
- K&R 的內容依章節記在對應週數的筆記（第 1 章在 week1）
