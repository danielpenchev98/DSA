#include <iostream>
int max(int x, int y)
{
	return (x > y) ? x : y;
}
int KnapSack(int* arr1,int* arr2,int W,int n)
{
	int i, w;
	int** K = new int*[n+1];
	for (int z = 0; z <= n; z++)
	{
		K[z] = new int[W + 1];
	}
	for (int z = 0; z <= n; z++)
	{
		for (int x = 0; x <= W ; x++)
		{
			K[z][x] = 0;
		}
	}
	for (i = 0; i <= n ; i++)
	{
		for (w = 0; w <= W; w++)
		{
			if ((w == 0) || (i == 0))
			{
				K[i][w] = 0;
			}
			else if (arr2[i - 1] <= w)
			{
				K[i][w] = max(arr1[i - 1] + K[i - 1][w - arr2[i - 1]], K[i - 1][w]);
			}
			else
			{
				K[i][w] = K[i - 1][w];
			}
		}
	}
	int temp = K[n][W];
	for (int z = 0; z <= n; z++)
	{
		delete K[z];
	}
	delete[] K;
	return temp;
}
//------------------------------------------KanpSack-------------------------------
//0  0  0  0  0  0

//0  6  6  6  6  6

//0  6  10 16 16 16
//               ____
//0  6  10 16 18 |22|
//               ----
//
//
//
int main()
{
	int* arr1 = new int[3];
	arr1[0] = 6;
	arr1[1] = 10;
	arr1[2] = 12;
	int* arr2 = new int[3];
	arr2[0] = 1;
	arr2[1] = 2;
	arr2[2] = 3;
	int W = 5;
	std::cout << KnapSack(arr1, arr2, 5, 3) << std::endl;
	delete[] arr1;
	delete[] arr2;
	return 0;
}