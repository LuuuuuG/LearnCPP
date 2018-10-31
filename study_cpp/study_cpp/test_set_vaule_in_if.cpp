#include <cstdio>


void test_set_vaule_in_if()
{
	int rc = -1;
	bool return_vaule = true;
	while (rc = return_vaule)
	{
		if (true){
			printf("WTHWTHWTH=%d\n",rc);
			rc = 0;
			break;
		}
	}
	printf("WTFWTFWTF=%d\n", rc);
}


int main_vInIf()
{
	test_set_vaule_in_if();
	getchar();
	return 0;
}