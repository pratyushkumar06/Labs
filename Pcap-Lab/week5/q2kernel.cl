__kernel void complement(__global int*A, __global int *B)
{
	//Get the index
	int i=get_global_id(0);
	//Do the op
	int res=0;
	int mult=1;
	while(A[i]>0)
	{
		int last=A[i]%10;
		if(last==1)
		{
			res+=mult*0;
		}
		else
		{
			res+=mult*1;
		}
		mult*=10;
		A[i]/=10;

	}
	B[i]=res;
}