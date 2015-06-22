#include <stdio.h>

int partition(int a[],int l,int r);
int quick_sort_1(int a[],int l,int r);
int quick_sort(int a[],int n);

int main(void)
{
	int i;

	int a[] = {55,3,74,20,13,87,46,30};
	int n = 8;

	printf("Start : ");
	for(i=0;i<n;i++)
	{
		printf("%3d",a[i]);
	}
	printf("\n");

	quick_sort(a,n);

	printf("Finish: ");
	for(i=0;i<n;i++)
	{
		printf("%3d",a[i]);
	}
	printf("\n");

	return 0;
}

int partition(int a[],int l,int r)
{
	int i,j,pivot,t;

	i = l -1;
	j = r;

	printf("partition mov i : %d\n",i);
	printf("partition mov j : %d\n",j);

	pivot = a[r];

	for(;;)
	{
		while(a[++i] < pivot);

		while(i < --j&&pivot<a[j]);

		printf("partition now i : %d\n",i);
		printf("partition now j : %d\n",j);
		printf("\n");

		if(i>=j)
			break;
		
		t = a[i];
		a[i] = a[j];
		a[j] = t;
	}

	t = a[i];
	a[i] = a[r];
	a[r] = t;

	return i;
}

int quick_sort_1(int a[],int l,int r)
{
	int v;

	if(l >= r)
		return;

	v = partition(a,l,r);
	printf("quick_sort_1 v : %d\n",v);

	quick_sort_1(a,l,v-1);

	quick_sort_1(a,v+1,r);
}

int quick_sort(int a[],int n)
{
	quick_sort_1(a,0,n-1);
}
