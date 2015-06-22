/*
 * dentaku.c
 *
 *  Created on: 2012/09/15
 *      Author: makoto
 */

#include <stdio.h>

//バッファとスタックの確保数
#define BUFFER_LENGTH	80
#define STACK_LENGTH		80

//デバッグの切り替え
//#define _Debug_enable
#define _Debug_diable

//モード定数
#define IN_MODE			1
#define RPN_MODE			2
#define EXIT_MODE			-1

//プロトタイプ宣言

//各種電卓関数
void calc(char*);
void in_calc(char*);
void rpn_calc(char*);
double calc_exec(char);
void convert_in_formula_to_rpn_formula(char*);

//スタック操作に関する関数
void stack_push(double);
double stack_pop(void);
void stack_clear(void);

//文字列配列に対する各種関数
void string_clear(char*,char,int);
void string_trim(char*);
int string_match(char*,char*);

//計算のラップ関数
//my_がつくのは、標準関数にdivというものがあるため
double my_add(double,double);
double my_sub(double,double);
double my_mul(double,double);
double my_div(double,double);

//標準ライブラリ関数を実装したもの。
//標準ライブラリ関数等を使用したときにどの範囲まで知っているか分からず、
//説明を書くのが大変なので自分で実装。
int my_atoi(char*);
double my_atof(char*);
double my_pow(double,double);
void my_strcpy(char*,const char*);

//スタックの宣言
double stack[STACK_LENGTH];
int stack_pointer = 0;

//実数フラグ
int double_flag = 0;
//エラーフラグ
int error_flag = 0;
//計算モード
int mode = IN_MODE;

int main(void)
{
	char string_buffer[BUFFER_LENGTH];

	//メインループ
	for(;;)
	{
		if(mode==IN_MODE)
		{
			printf("Calc (IN)  > ");
		}
		else
		{
			printf("Calc (RPN) > ");
		}
		gets(string_buffer);
		calc(string_buffer);
		if(mode==EXIT_MODE)
		{
			printf("\tCalc : Good bye!\n");
			return 0;
		}
	}

	return 0;
}

//電卓関数モードで中間か逆ポーランドか選択可能
void calc(char* formula)
{
	printf("\tCalc Exec : Start\n");

	//エラーフラグのクリア
	error_flag = 0;

	#ifdef _Debug_enable
		//デバッグ用
		printf("\t\tDebug : calc -> mode set search start\n");
	#endif

	char tmp_buffer[BUFFER_LENGTH];
	my_strcpy(tmp_buffer,formula);
	string_trim(tmp_buffer);

	//コマンド部分に関する記述
	if(string_match(tmp_buffer,"set"))
	{
		printf("\tCalc Exec : detected \"set\"\n");
		if(string_match(tmp_buffer,"mode=IN"))
		{
			mode = IN_MODE;
			printf("\tCalc Exec : set Calc mode = IN_MODE\n");
			return;
		}
		else if(string_match(tmp_buffer,"mode=RPN"))
		{
			mode = RPN_MODE;
			printf("\tCalc Exec : set Calc mode = RPN_MODE\n");
			return;
		}
		else
		{
			printf("\tCalc Exec : Please retry set mode.\n");
			return;
		}
	}
	else if(string_match(tmp_buffer,"quit")||string_match(tmp_buffer,"exit"))
	{
		mode = EXIT_MODE;
		return;
	}

	#ifdef _Debug_enable
		//デバッグ用
		printf("\t\tDebug : calc -> mode = %d, fromula = \"%s\"\n",mode,formula);
	#endif

	//計算関数呼び出し
	switch(mode)
	{
		case RPN_MODE : rpn_calc(formula); break;
		case IN_MODE	: in_calc(formula); break;
	}
}
//デバッグ用
//中間モードの関数（実際は逆ポーランドに変換）
void in_calc(char* formula)
{
	//中間置方だと空白があった場合に支障を来すことがあるので空白を削除
	printf("\tIN Calc Exec : formula = \"%s\"\n",formula);
	string_trim(formula);
	printf("\tIN Calc : trim formula \"%s\"\n",formula);

	//RPNの形式へ変換
	convert_in_formula_to_rpn_formula(formula);
	//RPNで計算実行
	rpn_calc(formula);
}

//逆ポーランドモードの関数
void rpn_calc(char* formula)
{
	printf("\tRPN Calc Exec : formula = \"%s\"\n",formula);

	double answer = 0;
	double ret = 0;
	int i;

	char tmp_buffer[BUFFER_LENGTH];
	int tmp_buffer_pointer = 0;
	string_clear(tmp_buffer,'\0',BUFFER_LENGTH);

	//実数が含まれるか確認
	for(i=0;formula[i]!='\0';i++)
	{
		if(formula[i]=='.')
		{
			double_flag = 1;
			printf("\tRPN Calc Exec : double mode is true\n");
			break;
		}
	}

	//計算ループ
	for(i=0;formula[i]!='\0';i++)
	{
		//数値の場合
		if((formula[i]>='0'&&formula[i]<='9')||formula[i]=='.')
		{
			tmp_buffer[tmp_buffer_pointer++] = formula[i];
		}
		//演算子の場合
		else if(formula[i]=='+'||formula[i]=='-'||formula[i]=='*'||formula[i]=='/')
		{
			if(tmp_buffer[0]!='\0')
			{
				if(double_flag==1)
					ret = my_atof(tmp_buffer);
				else
					ret = my_atoi(tmp_buffer);

				stack_push(ret);
				string_clear(tmp_buffer,'\0',BUFFER_LENGTH);
				tmp_buffer_pointer = 0;
			}
			stack_push(calc_exec(formula[i]));
		}
		//スペースまたはコンマの場合
		else if(formula[i]==' '||formula[i]==',')
		{
			if(tmp_buffer[0]!='\0')
			{
				if(double_flag==1)
					ret = my_atof(tmp_buffer);
				else
					ret = my_atoi(tmp_buffer);

				stack_push(ret);
				string_clear(tmp_buffer,'\0',BUFFER_LENGTH);
				tmp_buffer_pointer = 0;
			}
		}
	}

	//解答を取り出す
	answer = stack_pop();

	//エラーフラグのチェック
	if(error_flag==0)
	{
		//実数フラグによって表示方法を変更
		if(double_flag==0)
		{
			printf("\tAnswer : %d\n",(int)answer);
		}
		else
		{
			printf("\tAnswer : %lf\n",answer);
			double_flag = 0;
		}
	}
	else
	{
		//エラーが起こったときに答えを表示せずにエラー件数を表示して終了
		printf("\tError : Total Error -> %d\n",error_flag);
		error_flag = 0;
	}
}

//各項ごとの計算関数
double calc_exec(char operator)
{
	double ret = 0;

	double a = 0;
	double b = 0;

	#ifdef _Debug_enable
		//デバッグ用
		printf("\t\tDebug : calc_exec -> operator = %c\n",operator);
	#endif

	//少なくとも二つ以上スタックに積んであるか確認する
	if(stack_pointer>=1)
	{
		switch(operator)
		{
			case '+' : b = stack_pop(); a = stack_pop(); ret = my_add(a,b); break;
			case '-' : b = stack_pop(); a = stack_pop(); ret = my_sub(a,b); break;
			case '*' : b = stack_pop(); a = stack_pop(); ret = my_mul(a,b); break;
			case '/' : b = stack_pop(); a = stack_pop(); ret = my_div(a,b); break;
		}
	}
	else
	{
		//エラー処理
		printf("\tError occured : calc_exec -> stack_pointer < 1 stack_pointer = %d\n",stack_pointer);
		error_flag++;
		ret = 0;
	}

	return ret;
}

//中間の数式を逆ポーランドに変換する関数
void convert_in_formula_to_rpn_formula(char* formula)
{
	printf("\tConvert IN Formula to RPN Formula : start IN Formula = \"%s\"\n",formula);

	char tmp_buffer[BUFFER_LENGTH];
	int tmp_buffer_pointer = 0;
	string_clear(tmp_buffer,'\0',BUFFER_LENGTH);

	int i;

	//メインループ
	for(i=0;formula[i]!='\0';i++)
	{
		//数字の処理
		if((formula[i]>='0'&&formula[i]<='9')||formula[i]=='.')
		{
			tmp_buffer[tmp_buffer_pointer++] = formula[i];
		}
		//各演算子の処理
		else if(formula[i]=='+')
		{
			for(;;)
			{
				//自分の優先順位より低くなるまでスタックをポップ
				if((int)(stack_pointer-1)>=0)
				{
					if((int)stack[stack_pointer-1]!='(')
					{
						tmp_buffer[tmp_buffer_pointer++] = ' ';
						tmp_buffer[tmp_buffer_pointer++] = (int)stack_pop();
					}
					else
					{
						stack_push(formula[i]);
						break;
					}
				}
				else
				{
					stack_push(formula[i]);
					break;
				}
			}
			tmp_buffer[tmp_buffer_pointer++] = ' ';
		}
		else if(formula[i]=='-')
		{
			//式の最初にマイナスがあったときのための処理
			if(i==0)
			{
				tmp_buffer[tmp_buffer_pointer++] = '0';
				tmp_buffer[tmp_buffer_pointer++] = ' ';
			}
			else if(formula[i-1]=='(')
			{
				tmp_buffer[tmp_buffer_pointer++] = '0';
				tmp_buffer[tmp_buffer_pointer++] = ' ';
			}

			for(;;)
			{
				//自分の優先順位より低くなるまでスタックをポップ
				if((stack_pointer-1)>=0)
				{
					if((int)stack[stack_pointer-1]!='+'&&(int)stack[stack_pointer-1]!='(')
					{
						tmp_buffer[tmp_buffer_pointer++] = ' ';
						tmp_buffer[tmp_buffer_pointer++] = (int)stack_pop();
					}
					else
					{
						stack_push(formula[i]);
						break;
					}
				}
				else
				{
					stack_push(formula[i]);
					break;
				}
			}
			tmp_buffer[tmp_buffer_pointer++] = ' ';
		}
		else if(formula[i]=='*')
		{
			for(;;)
			{
				//自分の優先順位より低くなるまでスタックをポップ
				if((stack_pointer-1)>=0)
				{
					if((int)stack[stack_pointer-1]!='+'&&(int)stack[stack_pointer-1]!='-'&&(int)stack[stack_pointer-1]!='(')
					{
						tmp_buffer[tmp_buffer_pointer++] = ' ';
						tmp_buffer[tmp_buffer_pointer++] = (int)stack_pop();
					}
					else
					{
						stack_push(formula[i]);
						break;
					}
				}
				else
				{
					stack_push(formula[i]);
					break;
				}
			}
			tmp_buffer[tmp_buffer_pointer++] = ' ';
		}
		else if(formula[i]=='/')
		{
			for(;;)
			{
				//自分の優先順位より低くなるまでスタックをポップ
				if((stack_pointer-1)>=0)
				{
					if((int)stack[stack_pointer-1]!='+'&&(int)stack[stack_pointer-1]!='-'&&(int)stack[stack_pointer-1]!='*'&&(int)stack[stack_pointer-1]!='(')
					{
						tmp_buffer[tmp_buffer_pointer++] = ' ';
						tmp_buffer[tmp_buffer_pointer++] = (int)stack_pop();
					}
					else
					{
						stack_push(formula[i]);
						break;
					}
				}
				else
				{
					stack_push(formula[i]);
					break;
				}
			}
			tmp_buffer[tmp_buffer_pointer++] = ' ';
		}
		//括弧開きがあったとき
		else if(formula[i]=='(')
		{
			stack_push(formula[i]);
			tmp_buffer[tmp_buffer_pointer++] = ' ';
		}
		//括弧閉じがあったとき
		else if(formula[i]==')')
		{
			for(;;)
			{
				//括弧開きが出るまでスタックをポップ
				if(stack[stack_pointer-1]!='(')
				{
					tmp_buffer[tmp_buffer_pointer++] = ' ';
					tmp_buffer[tmp_buffer_pointer++] = (int)stack_pop();
				}
				//括弧開きは読み捨てる
				else
				{
					stack_pop();
					break;
				}
			}
		}
	}

	//スタックに残っている演算子をすべてポップ
	for(i=stack_pointer-1;i>=0;i--)
	{
		tmp_buffer[tmp_buffer_pointer++] = ' ';
		tmp_buffer[tmp_buffer_pointer++] = (int)stack_pop();
	}
	tmp_buffer[tmp_buffer_pointer++] = '\0';

	my_strcpy(formula,tmp_buffer);

	string_clear(tmp_buffer,'\0',BUFFER_LENGTH);
	tmp_buffer_pointer = 0;
	stack_clear();

	printf("\tConvert IN Formula to RPN Formula : done  RPN Formula = \"%s\"\n",formula);
}

//スタックにプッシュする
void stack_push(double val)
{
	if((stack_pointer+1)<=STACK_LENGTH)
	{
		stack[stack_pointer++] = val;

		#ifdef _Debug_enable
			printf("\t\tDebug : stack_push -> stack[%d] = %lf\n",stack_pointer-1,val);
		#endif
	}
	else
	{
		printf("\Error occured : stack_push -> stack is full. stack_pointer = %d\n",stack_pointer);
		error_flag++;
	}
}

//スタックからポップする
double stack_pop(void)
{
	double ret = 0;
	if((stack_pointer-1)>=0)
	{
		ret = stack[--stack_pointer];
		#ifdef _Debug_enable
			printf("\t\tDebug : stack_pop -> stack[%d] = %lf\n",stack_pointer,ret);
		#endif
	}
	else
	{
		printf("\tError occured : stack_pop -> stack is empty. stack_pointer = %d\n",stack_pointer);
		ret = 0;
		error_flag++;
	}

	return ret;
}

//スタックをクリアする（スタックポインタ＝0）
void stack_clear(void)
{
	stack_pointer = 0;

	#ifdef _Debug_enable
		printf("\t\tDebug : stack_clear -> stack_pointer = %d\n",stack_pointer);
	#endif
}

//任意の配列を指定した数値で初期化する（文字列用）
void string_clear(char* string,char ch,int length)
{
	int i;
	for(i=0;i<length;i++)
		string[i] = ch;

	#ifdef _Debug_enable
		printf("\t\tDebug : string_clear -> string[0...%d] = %d\n",length-1,ch);
	#endif
}

//任意の文字列の空白を削除する。注:RPN式に使用しないこと
void string_trim(char* string)
{
	char tmp_buffer[BUFFER_LENGTH];
	int tmp_buffer_pointer = 0;
	int i;

	for(i=0;string[i]!='\0';i++)
	{
		if(string[i]!=' ')
		{
			tmp_buffer[tmp_buffer_pointer++] = string[i];
		}
	}

	tmp_buffer[tmp_buffer_pointer++] = '\0';

	#ifdef _Debug_enable
		printf("\t\tDebug : string_trim -> trim \"%s\" to \"%s\"\n",string,tmp_buffer);
	#endif

	my_strcpy(string,tmp_buffer);
}

//文字が含まれているかチェックする
int string_match(char* string1,char* string2)
{
	int string1_i = 0;
	int string2_i = 0;

	int string2_length = 0;
	int match_length = 0;

	int match_flag = 0;

	for(string2_length=0;string2[string2_length]!='\0';string2_length++);

	for(string1_i=0,string2_i=0;string1[string1_i]!='\0';string1_i++)
	{
		if(string1[string1_i]==string2[0])
		{
			match_length = 0;
			for(string2_i=0;string2[string2_i]!='\0';string2_i++)
			{
				if(string1[string1_i+string2_i]==string2[string2_i])
					match_length++;
				else
					break;
			}
			if(match_length==string2_length)
			{
				match_flag = 1;
				break;
			}
		}
	}

	return match_flag;
}

//足し算
double my_add(double val1,double val2)
{
	double ret = 0;
	ret = val1 + val2;

	#ifdef _Debug_enable
		printf("\t\tDebug : my_add -> %lf + %lf = %lf\n",val1,val2,ret);
	#endif

	return ret;
}

//引き算
double my_sub(double val1,double val2)
{
	double ret = 0;
	ret = val1 - val2;

	#ifdef _Debug_enable
		printf("\t\tDebug : my_sub -> %lf + %lf = %lf\n",val1,val2,ret);
	#endif

	return ret;
}

//掛け算
double my_mul(double val1,double val2)
{
	double ret = 0;
	ret = val1 * val2;

	#ifdef _Debug_enable
		printf("\t\tDebug : my_mul -> %lf * %lf = %lf\n",val1,val2,ret);
	#endif

	return ret;
}

//割り算
double my_div(double val1,double val2)
{
	double ret = 0;

	if(val2==0)
	{
		printf("\tError occuured : my_div -> can't divide by zero.");
		ret = 0;
		error_flag++;
		return 0;
	}

	ret = val1 / val2;

	#ifdef _Debug_enable
		printf("\t\tDebug : my_div -> %lf / %lf = %lf\n",val1,val2,ret);
	#endif

	return ret;
}

//文字列を整数に変換
int my_atoi(char* string)
{
	int ret = 0;
	int i,length;

	for(length=0;string[length]!='\0';length++);

	for(i=0;string[i]!='\0';i++)
	{
		ret += (string[i] - '0') * my_pow(10,length-1-i);

		#ifdef _Debug_enable
			printf("\t\tDebug : my_atoi -> ret = %d string[%d] = %c\n",ret,i,string[i]);
		#endif
	}

	#ifdef _Debug_enable
		printf("\t\tDebug : my_atoi -> \"%s\" to %d\n",string,ret);
	#endif

	return ret;
}

//文字列を実数に変換
double my_atof(char* string)
{
	double ret = 0;
	int int_length = 0;
	int float_length = 0;
	int i;

	for(i=0;string[i]!='\0';i++);

	//整数部の文字数を取得
	for(int_length=0;string[int_length]!='\0';)
	{
		if(string[int_length]>='0'&&string[int_length]<='9')
		{
			int_length++;
		}
		else
		{
			break;
		}
	}

	//小数部のスタートを求める
	if(string[int_length]=='.')
	{
		float_length = i - int_length - 1;
	}

	#ifdef _Debug_enable
		//デバッグ用
		printf("\t\tDebug : my_atof -> i = %d,int_length = %d,float_length = %d\n",i,int_length,float_length);
	#endif

	//整数部の処理
	for(i=0;i<int_length;i++)
	{
		ret += (string[i] - '0') * my_pow(10,int_length-i-1);
		#ifdef _Debug_enable
			//デバッグ用
			printf("\t\tDebug : my_atof -> ret = %lf\n",ret);
		#endif
	}

	//小数部の処理
	for(i=0;i<float_length;i++)
	{
		ret += (string[int_length+i+1] - '0') * my_pow(10,-i-1);
		#ifdef _Debug_enable
			//デバッグ用
			printf("\t\tDebug : my_atof -> ret = %lf\n",ret);
		#endif
	}

	#ifdef _Debug_enable
		//デバッグ用
		printf("\t\tDebug : my_atof -> \"%s\" to %lf\n",string,ret);
	#endif

	return ret;
}

//累乗を求める
double my_pow(double e,double x)
{
	double ret = e;
	int i;

	if(x==0)
	{
		ret = 1;
	}
	//乗数がプラスだったとき
	else if(x>0)
	{
		for(i=0;i<x-1;i++)
		{
			ret *= e;
		}
	}
	//乗数がマイナスだったとき
	else if(x<0)
	{
		ret = 1/e;
		for(i=(x+1)*-1;i>0;i--)
		{
			ret *= 1/e;
		}
	}

	#ifdef _Debug_enable
		//デバッグ用
		printf("\t\tDebug : my_pow -> %lf^%lf = %lf\n",e,x,ret);
	#endif

	return ret;
}

//文字列をコピー
void my_strcpy(char* string1,const char* string2)
{
	int i;

	#ifdef _Debug_enable
		//デバッグ用
		printf("\t\tDebug : my_strcpy -> copy string \"%s\"\n",string2);
	#endif

	for(i=0;string2[i]!='\0';i++)
		string1[i] = string2[i];

	string1[i] = '\0';
}
