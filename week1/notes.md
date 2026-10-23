# Week 1：C 語言基礎


## Java vs C 差異

| 項目 | Java | C |
|------|------|-----|
| int 大小 | 固定 32 位元 | 依平台而定，用 sizeof 確認 |
| char 大小 | 2 bytes (UTF-16) | 1 byte，本質是整數（'y' 就是 121） |
| boolean | 內建 boolean 型別 | C99 起需 #include <stdbool.h> 才有 bool（cs50.h 已幫忙引入） |
| 整數溢位 | 固定繞回變負數 | 有號整數溢位是未定義行為 |
| 區域變數未初始化 | 編譯錯誤 | 可以編譯，值是記憶體殘留的垃圾 |
| 常數 | final int n = 3; | const int n = 3;（傳統寫法 #define N 3，見 K&R 1.4） |
| main 回傳 | void，用 System.exit() | int，C99 起省略 return 視為 0 |
| 條件式 | 必須是 boolean | 整數即可，0 為假、非 0 為真 |
| 函式順序 | 不限，任何位置都能呼叫 | 使用前要先宣告；可把函式寫在 main 上方，或在檔案開頭寫原型（prototype） |
| 空括號 () | 代表沒有參數 | C23 以前代表「參數不指定」，編譯器不檢查；要寫 (void) 才是明確「沒有參數」 |
| 修改程式後 | IDE 通常自動重新編譯 | 必須自己重新 make，否則跑的是舊版 |
| 命名慣例 | camelCase | snake_case（檔名、變數、函式皆然） |
| 建置工具 | Maven / Gradle（含依賴管理） | make（只管編譯規則，不管依賴下載） |
| 整數除以零 | 丟出 ArithmeticException，可以捕捉 | 程式直接崩潰（Floating point exception） |
| 浮點數 | float / double，IEEE 754 | 同樣是 IEEE 754，不精確的問題完全相同；Java 處理金額用 BigDecimal |

## 踩過的坑

### scanf 讀取失敗，下一個輸入被跳過
- 現象：x 輸入 `ld`，程式沒讓我輸入 y 就直接印出結果，數值很怪
- 原因：scanf 失敗時不會清掉輸入，`ld\n` 留在緩衝區，下一個 scanf 直接讀到又失敗；怪數字是未初始化變數的垃圾值
- 解法：變數給初始值、檢查 scanf 回傳值、失敗時用 getchar 清空緩衝區
- 程式：compare_scanf.c

### 改了程式碼，執行結果卻沒變
- 現象：修改 .c 檔後直接 ./bin/xxx，跑出來還是舊的結果
- 原因：C 是編譯式語言，執行檔是編譯當下的「快照」，改了原始碼不會自動更新執行檔
- 解法：用 `make xxx && ./bin/xxx`，編譯成功才執行
- 補充：Java 其實也要重新編譯，只是 IDE 在背景幫忙做了

### 中文字的大小
- UTF-8 下一個中文字佔 3 bytes，strlen("你好") 是 6 不是 2
- cat -A 會把每個 byte 顯示成 M- 開頭的符號

### 整數除以零，程式直接崩潰
- 現象：division 程式輸入 y = 0，程式當場結束，顯示 Floating point exception
- 原因：整數除以零在 C 是未定義行為，Linux 會直接終止程式
- 對照：浮點數除以零不會崩潰，而是得到 inf；0.0 / 0.0 得到 nan
- 解法：除法前先檢查 if (y == 0)，用 return 1; 表示錯誤結束

### 轉型（casting）的位置
- (float) x / y 正確：x 先轉成 float，再做浮點除法
- (float) (x / y) 錯誤：括號內已先做完整數除法，小數已被捨去
- 程式：calculator_divide_casting.c

### 溢位不只發生在迴圈
- add 輸入 2000000000 + 2000000000、multiply 輸入 2000000000，都會溢位
- 任何運算都可能超出型別範圍


## 觀念補充

### #include 到底引入了什麼
- 標頭檔（如 stdio.h）裡主要放的是函式原型
- printf 的實際程式碼在標準函式庫裡，編譯器只需原型就知道怎麼呼叫
- 自己寫原型，和 #include 引入原型，是同一件事

### 魔術數字（magic number）
- 程式裡直接寫 i < 4，別人看不懂 4 代表什麼
- 取名成常數（const int width = 4;），意義清楚，要改也只改一處

### do-while
- 先執行一次，再檢查條件，適合「先問一次，不符合再重問」
- 語法結尾 while (條件); 的分號不能少

### 抽象化與函式命名
- 把細節藏進函式，main 只描述主流程，讀起來像一句話
- 函式名稱要準確描述行為：print_row 就只印一列，不印整個方塊

### 小技巧
- 大小寫都接受時，可用 <ctype.h> 的 tolower(c) == 'y' 簡化
- 寫 C 練習時只 #include 真正用到的標頭檔

### 整數溢位的防範
- 有號 int 溢位是未定義行為，無號整數溢位才保證繞回
- int 最大值 INT_MAX（2147483647）定義在 <limits.h>
- 檢查要在運算「之前」：if (dollars > INT_MAX / 2)，不能寫 dollars * 2 > INT_MAX（比較前就已溢位）
- 程式：dollars.c

### 整數除法
- 結果捨去小數，往零的方向：7 / 2 = 3，-7 / 2 = -3（和 Java 相同）

### 浮點數不精確
- 10.0 / 3 存成 float，印出 3.33333325386047363281250000...
- float 約 7 位有效數字，double 約 15～16 位，實務上預設用 double
- 後面全是 0，是因為存進去的是最接近的二進位小數，它換成十進位是有限位數；不精確發生在「存入」時，不是印出時
- 程式：calculator_divide_float.c

### printf 與 scanf 的格式符號
- printf 印 float 和 double 都用 %f（float 傳入時會自動轉成 double）
- scanf 讀 double 要用 %lf，讀 float 用 %f

### 檔案改名
- 用 git mv 舊名 新名，Git 才會記錄成改名，而不是刪除加新增
- 改名後用 make clean 清掉舊名稱的執行檔

### printf 格式符號

| 格式 | 意義 | 範例 | 輸出（[ ] 標示邊界） |
|------|------|------|------|
| %d | 整數 | printf("[%d]", 42) | [42] |
| %6d | 整數，至少 6 格寬，靠右補空格 | printf("[%6d]", 42) | [    42] |
| %f | 浮點數，預設小數 6 位 | printf("[%f]", 3.14159) | [3.141590] |
| %6f | 浮點數，至少 6 格寬（小數仍是 6 位） | printf("[%6f]", 3.14159) | [3.141590] |
| %.2f | 浮點數，小數 2 位 | printf("[%.2f]", 3.14159) | [3.14] |
| %6.2f | 浮點數，至少 6 格寬、小數 2 位 | printf("[%6.2f]", 3.14159) | [  3.14] |

- 寬度是「最少」寬度：內容比寬度長時不會被截掉，只是不補空格（所以 %3s 印 "Celsius" 沒有效果）
- 寬度包含小數點和負號：%6.2f 的 6 格 = 整數部分 + 小數點 + 2 位小數
- %.2f 是四捨五入：printf("%.2f", 2.678) 印出 2.68（和整數除法的「截斷」不同）
- 加負號改成靠左對齊：%-6d
- 表格對齊技巧：標題和資料用相同寬度，例如 %7s 對 %7d

### getchar / putchar / EOF（K&R 1.5）
- getchar() 每次從輸入取「一個」字元，putchar(c) 每次印出「一個」字元
- 迴圈 while (c != EOF) 中，「拿」永遠比「印」早一步：putchar 印的是上一次 getchar 拿到的字元
- 以輸入 AAA 加 Enter 為例：緩衝區是 A A A \n，迴圈跑 4 次，getchar 被呼叫 5 次，第 5 次緩衝區空了就停下來等
- \n 對 getchar 來說只是普通字元（數字 10），迴圈只有遇到 EOF 才結束
- EOF（End Of File）定義在 stdio.h，通常是 -1，不是真的字元，而是「沒有輸入了」的訊號
- 產生 EOF：鍵盤在一行開頭按 Ctrl + D（Windows 是 Ctrl + Z）；讀檔案則讀到結尾自然產生
- 輸入重新導向：./bin/xxx < notes.md 把檔案內容當作鍵盤輸入
- 程式：character_input_output.c

### 為什麼 getchar 要用 int 接收，不能用 char
- getchar 要回傳兩種東西：所有可能的字元（256 種）＋ EOF
- char 只有 1 byte，剛好只裝得下 256 種值，沒有空位留給 EOF
- 用 char 接收，EOF 會和某個真實字元撞在一起，可能提早結束或永遠停不下來
- 所以 getchar 回傳 int，接收的變數也必須是 int

### 緩衝區（buffer）
- 暫時存放資料的記憶體，讓資料累積後再一次搬運，減少和作業系統溝通的次數
- Java 對照：BufferedReader / BufferedWriter；flush 是「立刻送出緩衝區內容」

| 方式 | 英文 | 什麼時候送出 | 預設用在 |
|------|------|------|------|
| 行緩衝 | line buffered | 遇到 \n 或緩衝區滿 | 輸出到終端機（stdout） |
| 完全緩衝 | fully buffered | 緩衝區滿了才送 | 輸出到檔案 |
| 無緩衝 | unbuffered | 立刻送出 | 錯誤訊息（stderr） |

- 輸入緩衝區：沒被取走的資料會留在原處（scanf 讀 ld 失敗，ld\n 留著被下一個 scanf 讀到）
- 輸出緩衝區：printf("hello"); sleep(3); 會空白 3 秒才顯示，因為 hello 卡在緩衝區等 \n
- 強制送出：fflush(stdout);
- 程式要從鍵盤讀取前，標準函式庫會先清空 stdout，所以沒有 \n 的提示文字也能先顯示
- stderr 不緩衝，避免程式崩潰時錯誤訊息還卡在緩衝區裡跟著消失
- 除錯用的 printf 記得加 \n，否則程式崩潰時可能看不到訊息

### 終端機的行模式（canonical mode）
- 「等按 Enter 才把整行交給程式」是終端機的設定，不是 getchar 或 C 語言的規則
- 目的：讓使用者在送出前可以用 Backspace 修改
- stty -icanon 關閉行模式 → 每按一個鍵程式就立刻收到；stty icanon 恢復；出問題用 stty sane
- 關閉行模式後 Ctrl + D 會失效（變成普通字元，數字 4），因為 EOF 是行模式「翻譯」出來的；Ctrl + C 仍有效，因為它是另一套機制（中斷訊號 signal，由 isig 控制）
- vim、nano 會關閉行模式；輸入密碼時不顯示字元是關閉了回顯（stty -echo）
- 用 < 從檔案讀取時沒有終端機參與，也就沒有等 Enter 這回事

## 待解問題
- [ ] const char *prompt 的 * 是什麼意思？（預計 Lecture 4 指標）
- [x] 編譯的四個階段分別在做什麼？（預計 Lecture 2）

## 參考
- 官方筆記：https://cs50.harvard.edu/x/notes/1/
- K&R 第 1 章 1.1–1.7
