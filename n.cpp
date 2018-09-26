//star forming 6.0 //doesn't display all the combinations
				   //currently can omit the rotation, but cannot omit reflection
#include<iostream>
#include<algorithm>
#include<fstream>
#include<vector>
using namespace std;
int n,m,t;
int com=0;
int finalsum=0;
vector<int> line;
ofstream file;

struct board{
	int num;
 	board *ptr;
};
void find(int*);
void finding(int,int *,int,int);
void form(int *);
void process(board *,int,bool *);
void print(int *,int *);
int main()
{ 
	file.open("test");
	cout << "How many sides???" << endl;
    cin >> n;
	t=4*n-2;
	m=n*2;
	if(file.is_open())  //if the output file is opened?
	{ //the finding of the line combination
		int lines[4];
		find(&lines[0]);  //find all of the possibilities of the lines
	}
	for(int i=1;i<=com;i++)
	{
		for(vector<int>::iterator it=line.begin()+(i-1)*4;it!=line.begin()+4*i;it++)
		{
			cout << *it << " ";
		}
		cout <<endl;
	}
	board array[n][4];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<4;j++)
		{
			array[i][j].num=-1;
		}
	}
	//
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<4;j++)
		{
			array[i][j].ptr=NULL;
		}
	}
	array[n-2][3].ptr=&array[0][0];
	array[n-1][3].ptr=&array[1][0];
	array[n-1][2].ptr=&array[0][1];
	array[1][1].ptr=&array[0][2];
	for(int i=2;i<n;i++)
	{
		for(int j=0;j<2;j++)
		{
			if(j==0)
			{
				array[i][j].ptr=&array[i-2][3];
			}
			else if(j==1)
			{
				array[i][j].ptr=&array[i-1][2];
			}
		}
	}
	
	//finish checking
	//
	bool number[m];
	for(int i=0;i<m;i++)
	{
		number[i]=false;
	}
	process(&array[0][0],0,&number[0]);
	//finish the whole project!!!
	cout << "The total number of combinations is " << finalsum << endl;
	file << "The total number of combinations is " << finalsum << endl;
	file.close();
	
	return 0;
}

//
void find(int *lines)
{
	int sum=0;
	finding(sum,lines,0,-1);
	return;
}
//
void finding(int sum, int *num,int layer,int pre)  //temporary sum,temporary array to store(named alpha),which element currently is picked,previous picked item,the n star, the eventual sum of equivalent line sums
{
	if(layer==0)  //the first element
	{
		for(int i=0;i<=n;i++)
		{
			if(sum+i<t)
			{
				*(num+0)=i;
				finding(sum+i,num,1,i);
			}
		}
	}
	else if(layer==3)  //the last element
	{
		for(int i=pre+1;i<=(2*n-1);i++)
		{
			if(i<n+1)
			continue;
			if(sum+i==t)
			{
				*(num+3)=i;
				form(num);
			}
		}
	}
	else  //the second or third element
	{
		for(int i=pre+1;i<=(2*n-1);i++)
		{
			if(sum+i<t)
			{
				*(num+layer)=i;
				finding(sum+i,num,layer+1,i);
			}
		}
	}
	return;
}
//
void form(int *lines)
{
	for(int i=0;i<4;i++)
	{
		line.push_back(*(lines+i)); //entering the values of possibilities of lines into the vector
	}
	com+=1;
	return;
}
//finish finding lines

//start forming array
void process(board *arr,int level,bool *num)
{
	bool number[m];
	for(int i=0;i<m;i++)
	{
		number[i]=*(num+i); //reset the boolean array to check out whether a number is used or not
	}
	board array[n][4];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<4;j++)
		{
			array[i][j].num=(arr+i*4+j)->num;
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<4;j++)
				{
					array[i][j].ptr=NULL;
				}
			}
			array[n-2][3].ptr=&array[0][0];
			array[n-1][3].ptr=&array[1][0];
			array[n-1][2].ptr=&array[0][1];
			array[1][1].ptr=&array[0][2];
			for(int i=2;i<n;i++)
			{
				for(int j=0;j<2;j++)
				{
					if(j==0)
					{
						array[i][j].ptr=&array[i-2][3];
					}
					else if(j==1)
					{
						array[i][j].ptr=&array[i-1][2];
					}
				}
			}
		}
	}
	//finish initializing pointer direction
	int temp[4]={-1};
	int tem=0;
	for(int i=0;i<4;i++)
	{
		if(array[level][i].ptr!=NULL)
		{
			temp[tem]=(*array[level][i].ptr).num;
			tem+=1;
		}
	}
	bool key;
	for(int p=1;p<=com;p++)
	{
		key=true;
		int candid[4];
		bool flagger=true,flag;
		for(int i=0;i<tem;i++)
		{
			flag=false;
			for(vector<int>::iterator it=line.begin()+(p-1)*4;it!=line.begin()+p*4;it++)
			{
				if(*it==temp[i])
				{
					flag=true;
					break;
				}
			}
			if(flag==false)
			{
				flagger=false;
				break;
			}
		}
		if(flagger==false)
		continue;
		for(vector<int>::iterator it=line.begin()+(p-1)*4;it!=line.begin()+p*4;it++)
		{
			bool flags=true;
			if(number[*it]==true)
			{
				flags=false;
				for(int i=0;i<tem;i++)
				{
					if(*it==temp[i])
					{
						flags=true;
						break;
					}
				}
			}
			if(flags==false)
			{
				flagger=false;
				break;
			}
		}
		if(flagger==false)
		continue;
		int let=0;
		for(vector<int>::iterator it=line.begin()+(p-1)*4;it!=line.begin()+p*4;it++)
		{
			flag=false;
			for(int i=0;i<tem;i++)
			{
				if(*it==temp[i])
				{
					flag=true;
					break;
				}
			}
			if(flag==false)
			{
				candid[let]=*it;
				let+=1;
			}
		}
		if(tem==0)
		{
			for(int i=0;i<4;i++)
			{
				array[0][0].num=candid[i];
				for(int j=0;j<4;j++)
				{
					if(j!=i)
					{
						array[0][1].num=candid[j];
						if(array[0][0].num!=0 && array[0][1].num!=0)//key difference
						{	
							key=false;
							break;
						}
						for(int k=0;k<4;k++)
						{
							if(k!=j && k!=i)
							{
								array[0][2].num=candid[k];
								for(int l=0;l<4;l++)
								{
									if(l!=i && l!=j && l!=k)
									{
										array[0][3].num=candid[l];
										for(int qwer=0;qwer<4;qwer++)
										{
											number[array[0][qwer].num]=true;
										}
										process(&array[0][0],1,&number[0]);
										for(int qwer=0;qwer<let;qwer++)
										{
											number[candid[qwer]]=false;
										}
									}
								}
							}
						}
					}
					if(key==false)
					break;
				}
			}
		}
		else if(tem==1)
		{
			for(int i=0;i<4;i++)
			{
				if(array[1][i].ptr!=NULL)
				{
					array[1][i].num=(*array[1][i].ptr).num;
				}
			}
			for(int i=0;i<3;i++)
			{
				array[1][0].num=candid[i];
				for(int j=0;j<3;j++)
				{
					if(j!=i)
					{
						array[1][2].num=candid[j];
						for(int k=0;k<3;k++)
						{
							if(k!=j && k!=i)
							{
								array[1][3].num=candid[k];
								for(int qwer=0;qwer<4;qwer++)
								{
									number[array[1][qwer].num]=true;
								}
								process(&array[0][0],2,&number[0]);
								for(int qwer=0;qwer<let;qwer++)
								{
									number[candid[qwer]]=false;
								}
							}
						}
					}				
				}
			}
		}
		else if(tem==3 && level==n-2)
		{
			for(int i=0;i<4;i++)
			{
				if(array[level][i].ptr!=NULL)
				{
					array[level][i].num=(*array[level][i].ptr).num;
				}
			}
			array[level][2].num=candid[0];
			for(int i=0;i<4;i++)
			{
				array[level+1][i].num=(*array[level+1][i].ptr).num;
			}
			//finished
			int out[n],in[n];
			for(int i=0;i<n;i++)
			{
				out[i]=array[i][0].num;
				if(i!=n-1)
				{
					in[i+1]=array[i][1].num;
				}
			}
			in[0]=array[n-1][1].num;
			print(&out[0],&in[0]);
		}
		else
		{
			for(int i=0;i<4;i++)
			{
				if(array[level][i].ptr!=NULL)
				{
					array[level][i].num=(*array[level][i].ptr).num;
				}
			}
			for(int i=0;i<2;i++)
			{
				array[level][2].num=candid[i];
				for(int j=0;j<2;j++)
				{
					if(i!=j)
					{
						array[level][3].num=candid[j];
						for(int qwer=0;qwer<4;qwer++)
						{
							number[array[level][qwer].num]=true;
						}
						process(&array[0][0],level+1,&number[0]);
						for(int qwer=0;qwer<let;qwer++)
						{
							number[candid[qwer]]=false;
						}
					}
				}
			}
		}
	}
	return;
}

//
void print(int *out,int *in)
{
	cout << "Outer cycle goes like: " << endl;
	for(int i=0;i<n;i++)
	{
		cout << *(out+i) << " ";
	}
	cout << endl;
	cout << "Inner cycle goes like: " << endl;
	for(int i=0;i<n;i++)
	{
		cout << *(in+i) << " ";
	}
	cout << endl;
	cout << "-----------------------------" << endl;
	file << "Outer cycle goes like: " << endl;
	for(int i=0;i<n;i++)
	{
		file << *(out+i) << " ";
	}
	file << endl;
	file << "Inner cycle goes like: " << endl;
	for(int i=0;i<n;i++)
	{
		file << *(in+i) << " ";
	}
	file << endl;
	file << "----------------------------" << endl;
	finalsum+=1;
	return;
}
