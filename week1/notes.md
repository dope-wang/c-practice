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

## 待解問題
- [ ] const char *prompt 的 * 是什麼意思？（預計 Lecture 4 指標）
- [ ] 編譯的四個階段分別在做什麼？（預計 Lecture 2）

## 參考
- 官方筆記：https://cs50.harvard.edu/x/notes/1/
- K&R 第 1 章 1.1–1.7
