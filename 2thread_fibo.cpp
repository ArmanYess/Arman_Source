//Author: Arman Yessengaliyev
#include <iostream>
#include <thread>
#include<mutex>

using namespace std;
unsigned long const hardware_threads =std::thread::hardware_concurrency();
std::mutex mu;

class Fib{
	public: 
		Fib(): a0_(1), a1_(1) {}
		int operator () ();
	private:
		int a0_, a1_;

};
int Fib::operator()()
{
	int temp=a0_;
	a0_=a1_;
	a1_=temp+a0_;
	return temp;
}
void ThreadFunction(int number, int count)
{
	Fib fib;
	
	int * a;
	a= new int [count];

	for(int i=0; i<count; i++)
	{
		a[i]=fib();
	}

	
	if(number==2)//четные индексы
	{
		cout<<endl<<"Fibonacci numbers with even indices: "<<endl<<endl;
		for(int i=0; i<count; i++)
		{
			if(i%2==0)
			{
				cout<<a[i]<<", ";	
			}

			
		}
	 
	}
	else if(number==1){
		cout<<endl<<"Fibonacci numbers with odd indices: "<<endl<<endl;
		for(int i=0; i<count; i++)
		{
			if(i%2!=0)
			{
				cout<<a[i]<<", ";	
			}

			
		}
		
	}

}


int main()

{
	Fib fib;
	int count;
	cout<<"Enter a dimension for Fibonacci series :"<<endl;
	cin>>count;

	
	std::thread thFirst(ThreadFunction,1, count);
	mu.lock();
	cout<<"First thread id "<<thFirst.get_id()<<endl;
	mu.unlock();
	

	std::thread thSecond(ThreadFunction,2, count);
	
	mu.lock();
	cout<<"Second thread id "<<thSecond.get_id()<<endl;
	mu.unlock();
	
	thFirst.join();
	thSecond.join();
	
	
	return 0;
}
