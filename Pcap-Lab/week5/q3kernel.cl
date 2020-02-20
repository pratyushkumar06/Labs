__kernel void swap(__global int*A, __global int *B , __global int * length)
{
	//Get the index
	int i=get_global_id(0);
	int size = length[0];
	//Do the op
	if(i%2==0 && i<size-1)
	{
		int first = A[i];
		int second = A[i+1];
		B[i]=second ;
		B[i+1]=first;	
	}
	if(i==size-1)
	{
		B[i]=A[i];
	}
}