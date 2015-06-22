#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_LENGTH  20
#define BUFFER_LENGTH 80

void stack_init(void);
int stack_pop(void);
void stack_push(int);

int calc(char*);

void convert_in_to_rpn(char*);

int stack[STACK_LENGTH];
int sp;

int main(void)
{
	int tmp;
	char buffer[BUFFER_LENGTH];

	printf("input > "); gets(buffer);
	printf("\tIN :%s\n",buffer);
	convert_in_to_rpn(buffer);
	printf("\tRPN:%s\n",buffer);
	tmp = calc(buffer);
	printf("output> %d\n",tmp);
}

int calc(char* form)
{
	int fp;
	int a,b;

	char buffer[BUFFER_LENGTH];
	int bp = 0;

	stack_init();

	for(fp=0;form[fp]!='\0';fp++)
	{
		if(form[fp]>='0'&&form[fp]<='9')
		{
			buffer[bp++] = form[fp];
		}
		else
		{
			switch(form[fp])
			{
				case '+':
					b = stack_pop();
					a = stack_pop();
					stack_push(a+b);
					break;

				case '-':
					b = stack_pop();
					a = stack_pop();
					stack_push(a-b);
					break;

				case '*':
					b = stack_pop();
					a = stack_pop();
					stack_push(a*b);
					break;

				case '/':
					b = stack_pop();
					a = stack_pop();
					stack_push(a/b);
					break;
				case ' ':
					if(bp!=0)
					{
						buffer[bp++] = '\0';
						bp = 0;
						stack_push(atoi(buffer));
					}
					break;
			}
		}
	}

	return stack_pop();
}

void convert_in_to_rpn(char* form)
{
	char buffer[BUFFER_LENGTH];
	int bp;
	int fp;

	int op;

	stack_init();

	for(fp=0,bp=0;form[fp]!='\0';fp++)
	{
		if(form[fp]>='0'&&form[fp]<='9')
		{
			buffer[bp++] = ' ';
			buffer[bp++] = form[fp];
		}
		else
		{
			switch(form[fp])
			{
				case '+':
					if(stack_check()!=0)
					{
						for(;;)
						{
							op = stack_pop();
							if(op!='+')
							{
								buffer[bp++] = ' ';
								buffer[bp++] = op;
							}
							else
							{
								stack_push(op);
								break;
							}
						}
					}

					stack_push(form[fp]);
					break;
				case '-':
					if(stack_check()!=0)
					{
						for(;;)
						{
							op = stack_pop();
							if(op!='+')
							{
								buffer[bp++] = ' ';
								buffer[bp++] = op;
							}
							else
							{
								stack_push(op);
								break;
							}
						}
					}

					stack_push(form[fp]);
					break;
				case '*':
					if(stack_check()!=0)
					{
						for(;;)
						{
							op = stack_pop();
							if(op!='+'&&op!='-')
							{
								buffer[bp++] = ' ';
								buffer[bp++] = op;
							}
							else
							{
								stack_push(op);
								break;
							}
						}
					}

					stack_push(form[fp]);

					break;
				case '/':
					if(stack_check()!=0)
					{
						for(;;)
						{
							op = stack_pop();
							if(op!='+'&&op!='-'&&op!='*')
							{
								buffer[bp++] = ' ';
								buffer[bp++] = op;
							}
							else
							{
								stack_push(op);
								break;
							}
						}
					}

					stack_push(form[fp]);

					break;
			}
		}
	}

	for(;stack_check()>0;)
	{
		buffer[bp++] = ' ';
		buffer[bp++] = stack_pop();
	}

	buffer[bp++] = '\0';

	strcpy(form,buffer);
}

int stack_check(void)
{
	return sp;
}

void stack_init(void)
{
	sp = 0;
	printf("\tSuccess: Stack Clear\n");
}

int stack_pop(void)
{
	if(sp<=0)
	{
		printf("\tError  : Stack Pop Failed\t: Stack is empty.\n");
		return 0;
	}

	printf("\tSuccess: Stack Poped\t: %d\n",stack[sp-1]);
	return stack[--sp];
}

void stack_push(int val)
{
	if(sp>=STACK_LENGTH)
	{
		printf("\tError  : Stack Push Failed\t: Stack overflow.\n");
		return;
	}

	printf("\tSuccess: Stack Pushed\t: %d\n",val);
	stack[sp++] = val;
}
