# report1_git_C
アルゴリズム特論課題1(C)  
Cで書きました

## 交叉の種類
### 1. `uniformityCrossover()`
一様交叉  
乱数生成が多くて遅い
### 2. `onePointCrossover()`
0~49の中でどれか1点を決めてそこを境にブロック分け  
ブロックごとに交叉率分交叉する
### 3. `twoPointCrossover()`
`onePointCrossover()`のブロックが3つになった版
### 4. `tsunoPointCrossover()`
2点交叉だけど点を打つのは0~49の2点  
2点の間で交叉を行う  

## 突然変異について
突然変異を起こしたとき書き換えられるのは1点だけ
