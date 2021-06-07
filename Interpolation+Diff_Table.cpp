//												NEWTONS DIFFERENCE TABLE
#include<iostream>
#include<iomanip>
#include<conio.h>
using namespace std;
	
	void Display_Diff_Table(float x[], float y[], float difference_values[][100], int n);
	
	float Interpolate(float x[], float y[], float difference_values[][100], float target, int n);
	
	int fact(int x) // Function to calculate factorial
	{
		if(x==0)
			return 1;
		else
			return x*fact(x-1);
	}
	
	void Restarter_Main(void)
	{
		
		float x[100],y[100],temp[100],difference_values[100][100], ans,target ;
		int n,i,j, choice ;
		
		cout << "\n\t\t\t NEWTONS DIFFERENCE TABLE";
		cout << "\n\n\t Enter the number of data set : ";
		cin >> n;
		
		cout << "\n\t Enter the corresponding x and y values,\n"<<endl;

		for(i=0;i<n;++i)
		{
			printf("\n\t x(%d) = ",i+1);
			cin >> x[i];
			
			printf("\t y(%d) = ",i+1);
			cin >> y[i];
			temp[i]=y[i];
		}
		cout << "\n\t Press Enter to continue : " ;
		getch();
		system("cls");

		// Calculating the values of difference table
		for(i=0 ; i<n-1 ; ++i )
			for(j=0 ; j<n-(i+1) ; ++j)
			{
				difference_values[i][j] = temp[j+1]-temp[j];
				temp[j] = difference_values[i][j];
			}
		do
		{
			cout<<"\n\t Press 1 to Generate the Difference Table "<<endl;
			cout<<"\n\t Press 2 to Interpolate a y-value "<<endl<<"\n\t -> ";
			cin >> choice;
			
			if(choice==1)
				Display_Diff_Table(x, y, difference_values, n);
			else if(choice==2)
			{
				system("cls");
				cout<<"\n\t Enter the target x-value : ";
				cin >> target;
				ans =  Interpolate( x, y, difference_values, target, n);
				cout<< "\n\n\t Interpolated y-value based on given target x-value("<<target<<") = "<<ans;
			}
			else
			{
				cout<<"\t Invalid input, please try again !!!";
				getch();
				system("cls");
			}
		}while(choice!=1 && choice!=2);
		
		
	}
	
	int main()
	{
		while(1)
		{
			Restarter_Main(); // looping the whole program for multiple use
			cout<<"\n\n\n   Press 'Space' to exit and 'Enter' to restart the program : ";
			if(getch()!=' ')
				system("cls");
			else
				break;
		}
	return 0;
	}
	
	float Interpolate(float x[], float y[], float difference_values[][100], float target, int n)
	{
		int i;
		float p, ans, product=1, h = x[2]-x[1], median = x[(n)/2] ;		// h is step interval
		
		// Forward Interpolation Formula
		if(target <= median)
		{
			p = (target -x[0])/h ;		// Forward p-value
			ans = y[0];
			for(i=0; i<n-1 ;++i)
			{
				product	*= p-i ;
				ans += (product/fact(i+1)) * difference_values[i][0]  ;
			}
		}
		// Backward Interpolation Formula
		else
		{
			p = (target -x[n-1])/h ;	// Backward p-value
			ans = y[n-1];
			for(i=0; i<n-1 ;++i)
			{
				product	*= p+i;
				ans += (product/fact(i+1)) * difference_values[i][n-2-i];
			}
		}
	return ans;	
	}
	
	void Display_Diff_Table(float x[], float y[], float difference_values[][100], int n)
	{
		int nrow,i,j,m,mr,t,ecl,ecm,ocl,ocm;
		
		ocl=ecl=0;
		ecm=ocm=0;
		
		nrow=2*n-1;
		m =n/2 ;
		mr=n-1;
		
		// Printing the table
		system("cls");
		cout << "\n\t\t\t FORWARD DIFFERENCE TABLE \n\n"<<endl;
		// Heading
		cout<<" ";
		// Top line
		for(i=0;i<n+1;++i)
			cout<<setw(7)<<setfill('_')<<"_";
		cout<<endl<<setfill(' ');
		// Variables
		cout<<" |   "<<"x"<<"  |   "<<"y"<<"  ";
		for(i=1;i<n;++i)
			cout<<"|"<<"D^"<<i<<"(y)";
		cout<<"|"<<endl;
		// Closing top box
		cout<<" |";
		for(i=0;i<n+1;++i)
			cout<<setw(7)<<setfill('_')<<"|";
		cout<<endl<<setfill(' ');
		
		// Main Table Data
		for(i=0 ; i<nrow ; ++i )
		{
			cout<<" |";
			if(!i)
			{
				cout<<setw(5)<< x[i] <<" |"<<setw(5)<< y[i] <<" |";
					for (j=1;j<n;++j)
						cout<<setw(7)<<"|";
				cout<<endl;
				continue;
			}
			else if(i==mr) 
			{
				t=ecl;
				if(mr%2!=0) //odd mr
				{
					t=ocl;
					cout<<setw(7)<<"|"<<setw(7)<<"|";
					for(j=0 ; j<i+1 ; j+=2,--t)
					{
						cout <<setw(5)<< difference_values[j][t] << " |";
						if(j!=i-1)
							cout<<setw(7)<<"|";
					}
					++ocl;
					
				}
						
				else // even mr
				{
					t=ecl;
					cout<<setw(5)<< x[i/2] <<" |"<<setw(5)<< y[i/2] <<" |"<<setw(7)<<"|";
					for(j=1 ; j<=i-1 ; j+=2,--t)
					{
						cout <<setw(5)<< difference_values[j][t] << " |";
						if(j!=i-1)
							cout<<setw(7)<<"|";
					}
					++ecl;
				}
				cout<<endl;
	
			}
			
			else if(i%2==0)		//for even case
			{
			cout<<setw(5)<< x[i/2] <<" |"<<setw(5)<< y[i/2] <<" |"<<setw(7)<<"|";
		
			if(i<mr)
				{
					t=ecl;
					for(j=1 ; j<=i-1 ; j+=2,--t)
						cout <<setw(5)<< difference_values[j][t] << " |"<<setw(7)<<"|";
					++ecl;
				}
				else if(i>mr && n!=3 && n!=2)
				{
					t=ecl;
					if(mr%2==0)
						for(j=1;j<=m-2*ecm ;j+=2,--t)
							cout <<setw(5)<< difference_values[j][t] << " |"<<setw(7)<<"|";	
					else
						for(j=1 ; j<m+1-2*ecm ; j+=2, --t)
							cout <<setw(5)<< difference_values[j][t] << " |"<<setw(7)<<"|";	
					++ecm;
					++ecl;
				}
				
			}
			
			else // odd case
			{
				for(j=0;j<2;++j)
					cout<<setw(7)<<"|";
				
				if(i<mr)
				{
					t=ocl;
					for(j=0 ; j<2*(i-ocl) ; j+=2, --t)
						cout <<setw(5)<< difference_values[j][t] << " |"<<setw(7)<<"|";	
					++ocl;
				}
				
				else if(i>mr)
				{
					t=ocl;
					if(mr%2==0)
						for(j=0; j<2*(m-ocm) ;j+=2,--t)
							cout <<setw(5)<< difference_values[j][t] << " |"<<setw(7)<<"|";	
					else
						for(j=0; j<2*(m-1-ocm) ;j+=2,--t)
							cout <<setw(5)<< difference_values[j][t] << " |"<<setw(7)<<"|";	
					++ocl;
					++ocm;
				}	
			}
			
			if(i<mr)
			{
				for (j=1;j<mr-i;++j)
						cout<<setw(7)<<"|";
				cout<<endl;
			}
				
			if(i>mr)
			{
				for (j=1;j<i-mr;++j)
						cout<<setw(7)<<"|";
				cout<<endl;
			}	
		}
		// Closing Bottom Line
		cout<<" |";
		for(i=0;i<n+1;++i)
			cout<<setw(7)<<setfill('_')<<"|";
		cout<<endl;
	}
	
