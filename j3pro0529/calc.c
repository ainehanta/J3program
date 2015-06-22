/*
 * dentaku.c
 *
 *  Created on: 2012/09/15
 *      Author: makoto
 */

#include <stdio.h>

//�Хåե��ȥ����å��γ��ݿ�
#define BUFFER_LENGTH	80
#define STACK_LENGTH		80

//�ǥХå����ڤ��ؤ�
//#define _Debug_enable
#define _Debug_diable

//�⡼�����
#define IN_MODE			1
#define RPN_MODE			2
#define EXIT_MODE			-1

//�ץ�ȥ��������

//�Ƽ�����ؿ�
void calc(char*);
void in_calc(char*);
void rpn_calc(char*);
double calc_exec(char);
void convert_in_formula_to_rpn_formula(char*);

//�����å����˴ؤ���ؿ�
void stack_push(double);
double stack_pop(void);
void stack_clear(void);

//ʸ����������Ф���Ƽ�ؿ�
void string_clear(char*,char,int);
void string_trim(char*);
int string_match(char*,char*);

//�׻��Υ�å״ؿ�
//my_���Ĥ��Τϡ�ɸ��ؿ���div�Ȥ�����Τ����뤿��
double my_add(double,double);
double my_sub(double,double);
double my_mul(double,double);
double my_div(double,double);

//ɸ��饤�֥��ؿ������������Ρ�
//ɸ��饤�֥��ؿ�������Ѥ����Ȥ��ˤɤ��ϰϤޤ��ΤäƤ��뤫ʬ���餺��
//������񤯤Τ����ѤʤΤǼ�ʬ�Ǽ�����
int my_atoi(char*);
double my_atof(char*);
double my_pow(double,double);
void my_strcpy(char*,const char*);

//�����å������
double stack[STACK_LENGTH];
int stack_pointer = 0;

//�¿��ե饰
int double_flag = 0;
//���顼�ե饰
int error_flag = 0;
//�׻��⡼��
int mode = IN_MODE;

int main(void)
{
	char string_buffer[BUFFER_LENGTH];

	//�ᥤ��롼��
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

//����ؿ��⡼�ɤ���֤��եݡ����ɤ������ǽ
void calc(char* formula)
{
	printf("\tCalc Exec : Start\n");

	//���顼�ե饰�Υ��ꥢ
	error_flag = 0;

	#ifdef _Debug_enable
		//�ǥХå���
		printf("\t\tDebug : calc -> mode set search start\n");
	#endif

	char tmp_buffer[BUFFER_LENGTH];
	my_strcpy(tmp_buffer,formula);
	string_trim(tmp_buffer);

	//���ޥ����ʬ�˴ؤ��뵭��
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
		//�ǥХå���
		printf("\t\tDebug : calc -> mode = %d, fromula = \"%s\"\n",mode,formula);
	#endif

	//�׻��ؿ��ƤӽФ�
	switch(mode)
	{
		case RPN_MODE : rpn_calc(formula); break;
		case IN_MODE	: in_calc(formula); break;
	}
}
//�ǥХå���
//��֥⡼�ɤδؿ��ʼºݤϵեݡ����ɤ��Ѵ���
void in_calc(char* formula)
{
	//����������ȶ��򤬤��ä����˻پ���褹���Ȥ�����ΤǶ������
	printf("\tIN Calc Exec : formula = \"%s\"\n",formula);
	string_trim(formula);
	printf("\tIN Calc : trim formula \"%s\"\n",formula);

	//RPN�η������Ѵ�
	convert_in_formula_to_rpn_formula(formula);
	//RPN�Ƿ׻��¹�
	rpn_calc(formula);
}

//�եݡ����ɥ⡼�ɤδؿ�
void rpn_calc(char* formula)
{
	printf("\tRPN Calc Exec : formula = \"%s\"\n",formula);

	double answer = 0;
	double ret = 0;
	int i;

	char tmp_buffer[BUFFER_LENGTH];
	int tmp_buffer_pointer = 0;
	string_clear(tmp_buffer,'\0',BUFFER_LENGTH);

	//�¿����ޤޤ�뤫��ǧ
	for(i=0;formula[i]!='\0';i++)
	{
		if(formula[i]=='.')
		{
			double_flag = 1;
			printf("\tRPN Calc Exec : double mode is true\n");
			break;
		}
	}

	//�׻��롼��
	for(i=0;formula[i]!='\0';i++)
	{
		//���ͤξ��
		if((formula[i]>='0'&&formula[i]<='9')||formula[i]=='.')
		{
			tmp_buffer[tmp_buffer_pointer++] = formula[i];
		}
		//�黻�Ҥξ��
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
		//���ڡ����ޤ��ϥ���ޤξ��
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

	//��������Ф�
	answer = stack_pop();

	//���顼�ե饰�Υ����å�
	if(error_flag==0)
	{
		//�¿��ե饰�ˤ�ä�ɽ����ˡ���ѹ�
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
		//���顼�������ä��Ȥ���������ɽ�������˥��顼�����ɽ�����ƽ�λ
		printf("\tError : Total Error -> %d\n",error_flag);
		error_flag = 0;
	}
}

//�ƹऴ�Ȥη׻��ؿ�
double calc_exec(char operator)
{
	double ret = 0;

	double a = 0;
	double b = 0;

	#ifdef _Debug_enable
		//�ǥХå���
		printf("\t\tDebug : calc_exec -> operator = %c\n",operator);
	#endif

	//���ʤ��Ȥ���İʾ她���å����Ѥ�Ǥ��뤫��ǧ����
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
		//���顼����
		printf("\tError occured : calc_exec -> stack_pointer < 1 stack_pointer = %d\n",stack_pointer);
		error_flag++;
		ret = 0;
	}

	return ret;
}

//��֤ο�����եݡ����ɤ��Ѵ�����ؿ�
void convert_in_formula_to_rpn_formula(char* formula)
{
	printf("\tConvert IN Formula to RPN Formula : start IN Formula = \"%s\"\n",formula);

	char tmp_buffer[BUFFER_LENGTH];
	int tmp_buffer_pointer = 0;
	string_clear(tmp_buffer,'\0',BUFFER_LENGTH);

	int i;

	//�ᥤ��롼��
	for(i=0;formula[i]!='\0';i++)
	{
		//�����ν���
		if((formula[i]>='0'&&formula[i]<='9')||formula[i]=='.')
		{
			tmp_buffer[tmp_buffer_pointer++] = formula[i];
		}
		//�Ʊ黻�Ҥν���
		else if(formula[i]=='+')
		{
			for(;;)
			{
				//��ʬ��ͥ���̤���㤯�ʤ�ޤǥ����å���ݥå�
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
			//���κǽ�˥ޥ��ʥ������ä��Ȥ��Τ���ν���
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
				//��ʬ��ͥ���̤���㤯�ʤ�ޤǥ����å���ݥå�
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
				//��ʬ��ͥ���̤���㤯�ʤ�ޤǥ����å���ݥå�
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
				//��ʬ��ͥ���̤���㤯�ʤ�ޤǥ����å���ݥå�
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
		//��̳��������ä��Ȥ�
		else if(formula[i]=='(')
		{
			stack_push(formula[i]);
			tmp_buffer[tmp_buffer_pointer++] = ' ';
		}
		//����Ĥ������ä��Ȥ�
		else if(formula[i]==')')
		{
			for(;;)
			{
				//��̳������Ф�ޤǥ����å���ݥå�
				if(stack[stack_pointer-1]!='(')
				{
					tmp_buffer[tmp_buffer_pointer++] = ' ';
					tmp_buffer[tmp_buffer_pointer++] = (int)stack_pop();
				}
				//��̳������ɤ߼ΤƤ�
				else
				{
					stack_pop();
					break;
				}
			}
		}
	}

	//�����å��˻ĤäƤ���黻�Ҥ򤹤٤ƥݥå�
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

//�����å��˥ץå��夹��
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

//�����å�����ݥåפ���
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

//�����å��򥯥ꥢ����ʥ����å��ݥ��󥿡�0��
void stack_clear(void)
{
	stack_pointer = 0;

	#ifdef _Debug_enable
		printf("\t\tDebug : stack_clear -> stack_pointer = %d\n",stack_pointer);
	#endif
}

//Ǥ�դ��������ꤷ�����ͤǽ���������ʸ�����ѡ�
void string_clear(char* string,char ch,int length)
{
	int i;
	for(i=0;i<length;i++)
		string[i] = ch;

	#ifdef _Debug_enable
		printf("\t\tDebug : string_clear -> string[0...%d] = %d\n",length-1,ch);
	#endif
}

//Ǥ�դ�ʸ����ζ���������롣��:RPN���˻��Ѥ��ʤ�����
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

//ʸ�����ޤޤ�Ƥ��뤫�����å�����
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

//­����
double my_add(double val1,double val2)
{
	double ret = 0;
	ret = val1 + val2;

	#ifdef _Debug_enable
		printf("\t\tDebug : my_add -> %lf + %lf = %lf\n",val1,val2,ret);
	#endif

	return ret;
}

//������
double my_sub(double val1,double val2)
{
	double ret = 0;
	ret = val1 - val2;

	#ifdef _Debug_enable
		printf("\t\tDebug : my_sub -> %lf + %lf = %lf\n",val1,val2,ret);
	#endif

	return ret;
}

//�ݤ���
double my_mul(double val1,double val2)
{
	double ret = 0;
	ret = val1 * val2;

	#ifdef _Debug_enable
		printf("\t\tDebug : my_mul -> %lf * %lf = %lf\n",val1,val2,ret);
	#endif

	return ret;
}

//��껻
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

//ʸ������������Ѵ�
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

//ʸ�����¿����Ѵ�
double my_atof(char* string)
{
	double ret = 0;
	int int_length = 0;
	int float_length = 0;
	int i;

	for(i=0;string[i]!='\0';i++);

	//��������ʸ���������
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

	//�������Υ������Ȥ����
	if(string[int_length]=='.')
	{
		float_length = i - int_length - 1;
	}

	#ifdef _Debug_enable
		//�ǥХå���
		printf("\t\tDebug : my_atof -> i = %d,int_length = %d,float_length = %d\n",i,int_length,float_length);
	#endif

	//�������ν���
	for(i=0;i<int_length;i++)
	{
		ret += (string[i] - '0') * my_pow(10,int_length-i-1);
		#ifdef _Debug_enable
			//�ǥХå���
			printf("\t\tDebug : my_atof -> ret = %lf\n",ret);
		#endif
	}

	//�������ν���
	for(i=0;i<float_length;i++)
	{
		ret += (string[int_length+i+1] - '0') * my_pow(10,-i-1);
		#ifdef _Debug_enable
			//�ǥХå���
			printf("\t\tDebug : my_atof -> ret = %lf\n",ret);
		#endif
	}

	#ifdef _Debug_enable
		//�ǥХå���
		printf("\t\tDebug : my_atof -> \"%s\" to %lf\n",string,ret);
	#endif

	return ret;
}

//�߾�����
double my_pow(double e,double x)
{
	double ret = e;
	int i;

	if(x==0)
	{
		ret = 1;
	}
	//������ץ饹���ä��Ȥ�
	else if(x>0)
	{
		for(i=0;i<x-1;i++)
		{
			ret *= e;
		}
	}
	//������ޥ��ʥ����ä��Ȥ�
	else if(x<0)
	{
		ret = 1/e;
		for(i=(x+1)*-1;i>0;i--)
		{
			ret *= 1/e;
		}
	}

	#ifdef _Debug_enable
		//�ǥХå���
		printf("\t\tDebug : my_pow -> %lf^%lf = %lf\n",e,x,ret);
	#endif

	return ret;
}

//ʸ����򥳥ԡ�
void my_strcpy(char* string1,const char* string2)
{
	int i;

	#ifdef _Debug_enable
		//�ǥХå���
		printf("\t\tDebug : my_strcpy -> copy string \"%s\"\n",string2);
	#endif

	for(i=0;string2[i]!='\0';i++)
		string1[i] = string2[i];

	string1[i] = '\0';
}
