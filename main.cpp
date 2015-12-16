#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include "Management.h"
#include "UI.h"


int main()
{
	while (1)
	{
		Mencu();
		unsigned int nChoise = 0;
		fflush(stdin);
		scanf("%d", &nChoise);
		if (nChoise >= 0 && nChoise <= 6)
		{
			switch (nChoise)
			{
			case 1:
				Add();
				break;
			case 2:
				Delete();
				break;
			case 3:
				Revisr();
				break;
			case 4:
				Find();
				break;
			case 5:
				Census();
				break;
			case 6:
				UIDefragment();
				break;
			default:
				break;
			}
		}
	}
	return 0;
}
