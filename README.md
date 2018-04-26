# report1_git_C
アルゴリズム特論課題1(C)  
Cで書きました  
ソースは[ここ](https://github.com/akira-kumashiro/report1_git_C/blob/master/report1_git_C/report1_git_C/report1_git_C.cpp "report1_git_C.cpp")

## 交叉の種類
### 1. [`uniformityCrossover(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM])`](https://github.com/akira-kumashiro/report1_git_C/blob/master/report1_git_C/report1_git_C/report1_git_C.cpp#L261 "uniformityCrossover()")
一様交叉  
乱数生成が多くて遅い
### 2. [`onePointCrossover(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM])`](https://github.com/akira-kumashiro/report1_git_C/blob/master/report1_git_C/report1_git_C/report1_git_C.cpp#L278 "onePointCrossover()")
0~49の中でどれか1点を決めてそこを境にブロック分け  
ブロックごとに交叉率分交叉する
### 3. [`twoPointCrossover(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM])`](https://github.com/akira-kumashiro/report1_git_C/blob/master/report1_git_C/report1_git_C/report1_git_C.cpp#L307 "twoPointCrossover()")
`onePointCrossover(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM])`のブロックが3つになった版

## 突然変異について
突然変異を起こしたとき書き換えられるのは1点だけ
