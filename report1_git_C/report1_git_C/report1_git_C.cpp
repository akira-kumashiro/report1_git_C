// report1.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <random>

#define MAX_GENERATION 30000
#define MAX_GENOM_LIST 50
#define MAX_WEIGHT 60
#define ITEM_NUM 50

#define CROSSOVER_RATE 0.8//交叉率
#define INDIVIDUAL_MUTATION_RATE 0.3//個体突然変異率
#define GENOM_MUTATION_RATE 0.04//遺伝子突然変異率

#define COEFFICIENT 0.1//評価関数の係数

const double weight[ITEM_NUM] =  //品物の重さ
{
	9, //1
	7, //2
	8, //3
	2, //4
	10, //5
	7, //6
	7, //7
	8, //8
	5, //9
	4, //10
	7, //11
	5, //12
	7, //13
	5, //14
	9, //15
	9, //16
	9, //17
	8, //18
	8, //19
	2, //20
	7, //21
	7, //22
	9, //23
	8, //24
	4, //25
	7, //26
	3, //27
	9, //28
	7,   //29
	7,   //30
	9, //31
	5, //32
	10, //33
	7, //34
	10, //35
	10, //36
	7, //37
	10, //38
	10, //39
	10, //40
	3, //41
	8, //42
	3, //43
	4, //44
	2, //45
	2, //46
	5, //47
	3, //48
	9,   //49
	2   //50
};
const double prise[ITEM_NUM] = //品物の値段
{
	20, //1
	28, //2
	2, //3
	28, //4
	15, //5
	28, //6
	21, //7
	7, //8
	28, //9
	12, //10
	21, //11
	4, //12
	31, //13
	28, //14
	24, //15
	36, //16
	33, //17
	2, //18
	25, //19
	21, //20
	35, //21
	14, //22
	36, //23
	25, //24
	12, //25
	14, //26
	40, //27
	36, //28
	2,   //29
	28,   //30
	33, //31
	40, //32
	22, //33
	2, //34
	18, //35
	22, //36
	14, //37
	22, //38
	15, //39
	22, //40
	40, //41
	7, //42
	4, //43
	21, //44
	21, //45
	28, //46
	40, //47
	4, //48
	24,   //49
	21   //50
};

bool selection(bool isIncluded[][ITEM_NUM], double result[], double r_weight[], double r_value[], bool isIncluded_prev[][ITEM_NUM]);
bool uniformityCrossover(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM]);
bool onePointCrossover(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM]);
bool onePointCrossover(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM], int point1);
bool twoPointCrossover(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM]);
bool twoPointCrossover(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM], int point1, int point2);
bool mutation(bool isIncluded[][ITEM_NUM]);
bool calc(bool enableDisplay, bool isIncluded[][ITEM_NUM], double result[], double r_weight[], double r_value[]);
//bool prevDataToData(bool isIncluded[][ITEM_NUM], double result[], double r_weight[], double r_value[], bool isIncluded_prev[][ITEM_NUM]);
bool prevDataToData(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM]);
int random(int min, int max);
double random(int min, double max);
double random(double min, int  max);
double random(double min, double max);

int main()
{
	bool isIncluded[MAX_GENOM_LIST][ITEM_NUM];//品物を入れるかどうかの配列
	double result[MAX_GENOM_LIST];//評価関数の値
	double r_weight[MAX_GENOM_LIST];//その個体の合計重さ
	double r_value[MAX_GENOM_LIST];//その個体の合計価値

	bool isIncluded_prev[MAX_GENOM_LIST][ITEM_NUM];//品物を入れるかどうかの配列

	double resultSumValue = 0;//評価関数の合計

	for (int i = 0; i < MAX_GENOM_LIST; i++)//変数の初期化
	{
		r_value[i] = 0;
		r_weight[i] = 0;
		for (int j = 0; j < ITEM_NUM; j++)
		{
			isIncluded[i][j] = (random(0, 1) == 1 ? true : false);//遺伝子の初期設定
			//data[i].isIncluded[j] = false;//初期値全部0のとき
			printf_s("%d", isIncluded[i][j] ? 1 : 0);

			r_value[i] += prise[j] * isIncluded[i][j];
			r_weight[i] += weight[j] * isIncluded[i][j];
			//重さと値段の計算
		}
		if (r_weight[i] > MAX_WEIGHT)//最大重量を超えている時
		{
			if (r_weight[i] != 0)
				result[i] = COEFFICIENT / ((r_weight[i] - MAX_WEIGHT));//超えるほど評価関数の値が悪くなるように
			else
				result[i] = 0;
			//result = r_value * coefficient;//これだと超えるほど評価関数の値が良くなる
		}
		else//最大重量を超えなければそのまま
		{
			result[i] = r_value[i]*r_weight[i];
		}
		resultSumValue += result[i];//評価関数の合計を計算
		printf_s(" \t sumValue=%4.0lf\t sumWeight=%4.0lf\t Result=%7.4lf\n", r_value[i], r_weight[i], result[i]);
	}

	for (int i = 0; i <= MAX_GENERATION; i++)//メインのループ
	{
		bool change = selection(isIncluded, result, r_weight, r_value, isIncluded_prev);//選択
		//if (i < MAX_GENERATION / 2)
			//twoPointCrossover();
			onePointCrossover(isIncluded, isIncluded_prev);
		//else
		//	uniformityCrossover(isIncluded, isIncluded_prev);
		//onePointCrossover();//交叉
		//uniformityCrossover();

		mutation(isIncluded);//突然変異

		if (i % (MAX_GENERATION / 10) == 0)
			printf_s("i=%d\n", i);
		calc(false, isIncluded, result, r_weight, r_value);//評価関数の計算
		/*if (i % (MAX_GENERATION / 100) == 0)//デバッグ用
		{
			for (int j = 0; j < resultSumValue; j += MAX_GENOM_LIST * 3)
			{
				std::cout << ".";
			}
			std::cout << std::endl;
		}*/
	}
	calc(true, isIncluded, result, r_weight, r_value);//終了時の変数表示
	while (!_kbhit())
	{

	}
	return 0;
}

bool selection(bool isIncluded[][ITEM_NUM], double result[], double r_weight[], double r_value[], bool isIncluded_prev[][ITEM_NUM])
{
	int max_num = 0;//最も評価の良い個体の番号

	for (int i = 0; i < MAX_GENOM_LIST; i++)
	{
		for (int j = 0; j < ITEM_NUM; j++)
		{
			isIncluded_prev[i][j] = isIncluded[i][j];
		}
	}

	double resultSumValue = 0;
	for (int i = 0; i < MAX_GENOM_LIST; i++)//ルーレット選択用に評価関数の合計と一番評価の良い番号を取得
	{
		resultSumValue += result[i];
		if (result[i] > result[max_num])
			max_num = i;
	}

	for (int j = 0; j < ITEM_NUM; j++)//データの先頭は最も評価の良い個体
	{
		isIncluded[0][j] = isIncluded_prev[max_num][j];
	}

	for (int i = 1; i < MAX_GENOM_LIST; i++)
	{
		double selector = random(0.0, 1.0);//乱数を生成
		double needle = 0;//ルーレットの針を生成
		int j = 0;
		for (;; j++)
		{
			needle += result[j] / resultSumValue;//ルーレットの針を乱数の値まで進める
			if (needle > selector)
				break;
			if (j >= MAX_GENOM_LIST - 1)
				break;
		}

		for (int k = 0; k < ITEM_NUM; k++)
		{
			isIncluded[i][k] = isIncluded_prev[j][k];
		}
	}
	return false;
}

bool uniformityCrossover(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM])
{
	prevDataToData(isIncluded, isIncluded_prev);

	for (int i = 0; i < MAX_GENOM_LIST; i += 2)//2個ずつ交叉
	{
		for (int j = 0; j < ITEM_NUM; j++)
		{
			bool isCrossover = (random(0.0, 1.0) >= CROSSOVER_RATE ? true : false);//trueで交叉なし
			isIncluded[i + 1][j] = isCrossover ? isIncluded_prev[i + 1][j] : isIncluded_prev[i][j];
			if (i != 0)//先頭のデータは保護
				isIncluded[i][j] = isCrossover ? isIncluded_prev[i][j] : isIncluded_prev[i + 1][j];
		}
	}
	return true;
}

bool onePointCrossover(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM])
{
	return onePointCrossover(isIncluded, isIncluded_prev, random(0, ITEM_NUM));
}

bool onePointCrossover(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM], int point1)
{
	prevDataToData(isIncluded, isIncluded_prev);

	for (int i = 0; i < MAX_GENOM_LIST; i += 2)//2個ずつ交叉
	{
		if (random(0.0, 1.0) <= CROSSOVER_RATE)
		{
			for (int j = 0; j < point1; j++)
			{
				isIncluded[i + 1][j] = isIncluded_prev[i][j];
				if (i != 0)//先頭のデータは保護
					isIncluded[i][j] = isIncluded_prev[i + 1][j];
			}
		}
		if (random(0.0, 1.0) <= CROSSOVER_RATE)
		{
			for (int j = point1; j < ITEM_NUM; j++)
			{
				isIncluded[i + 1][j] = isIncluded_prev[i][j];
				if (i != 0)//先頭のデータは保護
					isIncluded[i][j] = isIncluded_prev[i + 1][j];
			}
		}
	}
	return true;
}

bool twoPointCrossover(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM])
{
	int point1 = random(0, ITEM_NUM / 2);
	return twoPointCrossover(isIncluded, isIncluded_prev, point1, random(point1, ITEM_NUM - 1));
}

bool twoPointCrossover(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM], int point1, int point2)
{
	prevDataToData(isIncluded, isIncluded_prev);

	for (int i = 0; i < MAX_GENOM_LIST; i += 2)//2個ずつ交叉
	{
		if (random(0.0, 1.0) <= CROSSOVER_RATE)
		{
			for (int j = 0; j < point1; j++)
			{
				isIncluded[i + 1][j] = isIncluded_prev[i][j];
				if (i != 0)//先頭のデータは保護
					isIncluded[i][j] = isIncluded_prev[i + 1][j];
			}
		}
		if (random(0.0, 1.0) <= CROSSOVER_RATE)
		{
			for (int j = point1; j < point2; j++)
			{
				isIncluded[i + 1][j] = isIncluded_prev[i][j];
				if (i != 0)//先頭のデータは保護
					isIncluded[i][j] = isIncluded_prev[i + 1][j];
			}
		}

		if (random(0.0, 1.0) <= CROSSOVER_RATE)
		{
			for (int j = point2; j < ITEM_NUM; j++)
			{
				isIncluded[i + 1][j] = isIncluded_prev[i][j];
				if (i != 0)//先頭のデータは保護
					isIncluded[i][j] = isIncluded_prev[i + 1][j];
			}
		}
	}
	return true;
}

bool mutation(bool isIncluded[][ITEM_NUM])
{
	for (int i = 1; i < MAX_GENOM_LIST; i++)
	{
		if (random(0.0, 1.0) <= INDIVIDUAL_MUTATION_RATE)//個体突然変異率の計算
		{
			for (int j = 0; j < ITEM_NUM; j++)
			{
				isIncluded[i][j] = random(0.0, 1.0) <= GENOM_MUTATION_RATE ? !isIncluded[i][j] : isIncluded[i][j];//遺伝子突然変異率の計算　変化する場合はビット反転
			}
		}
	}
	return true;
}

bool calc(bool enableDisplay, bool isIncluded[][ITEM_NUM], double result[], double r_weight[], double r_value[])//, bool isIncluded_prev[][ITEM_NUM], double result_prev[], double r_weight_prev[], double r_value_prev[]
{
	for (int i = 0; i < MAX_GENOM_LIST; i++)
	{
		r_value[i] = 0;
		r_weight[i] = 0;

		for (int j = 0; j < ITEM_NUM; j++)
		{
			r_value[i] += prise[j] * (double)isIncluded[i][j];//個体の合計価値を計算
			r_weight[i] += weight[j] * (double)isIncluded[i][j];//個体の合計重さを計算

			if (enableDisplay)
				printf_s("%d", isIncluded[i][j] ? 1 : 0);//デバッグ用
		}
		if (r_weight[i] > MAX_WEIGHT)//最大重量を超えている時
		{
			if (r_weight[i] != 0)
				result[i] = COEFFICIENT / ((r_weight[i] - MAX_WEIGHT));//超えるほど評価関数の値が悪くなるように
			else
				result[i] = 0;
			//result = r_value * coefficient;//これだと超えるほど評価関数の値が良くなる
		}
		else//最大重量を超えなければそのまま
		{
			result[i] = r_value[i]*r_weight[i];
		}
		if (enableDisplay)//デバッグ用
			printf_s(" \t sumValue=%.0lf\t sumWeight=%.0lf\t Result=%.4lf\n", r_value[i], r_weight[i], result[i]);
	}

	if (enableDisplay)//デバッグ用
	{
		for (int i = 0; i < ITEM_NUM; i++)
		{
			if (isIncluded[0][i])
				printf_s("+%d", (int)prise[i]);
		}
		printf_s("=%lf\n", result[0]);
	}
	return true;
}

bool prevDataToData(bool isIncluded[][ITEM_NUM], bool isIncluded_prev[][ITEM_NUM])
{
	for (int i = 0; i < MAX_GENOM_LIST; i++)
	{
		for (int j = 0; j < ITEM_NUM; j++)
		{
			isIncluded_prev[i][j] = isIncluded[i][j];
		}
	}
	return true;
}

int random(int min, int max)
{
	//乱数の設定(int)
	std::random_device rnd;
	std::mt19937 engine(rnd());
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(engine);
}

double random(int min, double max)
{
	return random((double)min, max);
}

double random(double min, int max)
{
	return random(min, (double)max);
}

double random(double min, double max)
{
	//乱数の設定(double)
	std::random_device rnd;
	std::mt19937 engine(rnd());
	std::uniform_real_distribution<double> distribution(min, max);
	return distribution(engine);
}