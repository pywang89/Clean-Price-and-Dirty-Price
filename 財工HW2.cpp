#include<iostream>
#include<math.h>
using namespace std;

//判斷是否為閏年
int isLeapYear(int y)
{
	if (y % 400 == 0)
		return 1;

	else
	{
		if (y % 100 == 0)
			return 0;

		else if (y % 4 == 0)
			return 1;

		else
			return 0;
	}
}

//計算實際天數
float Actual(int y1, int m1, int d1, int y2, int m2, int d2)
{
	int day_diff = 0;
	int day[12] = {31,28,31,30,31,30,31,31,30,31,30,31};


	if (y2 > y1) 
	{
		if (m1 == 2) 
		{
			if (isLeapYear(y1) == 1) 
			{
				day_diff += 29 - d1;
			}
			else {
				day_diff += 28 - d1;
			}
		}
		else 
		{
			day_diff = day[m1 - 1] - d1;
		}
		m1++;

		for (int i = m1; i <= 12; i++) 
		{
			if (i == 2) 
			{
				if (isLeapYear(y1) == 1) 
				{
					day_diff += 29;
				}
				else 
				{
					day_diff += 28;
				}
			}
			else 
			{
				day_diff += day[i - 1];
			}


		}
		y1++;

		for (int i = y1; i < y2; i++) 
		{
			if (isLeapYear(i) == 1)
			{
				day_diff += 366;
			}
			else 
			{
				day_diff += 365;
			}
		}

		for (int i = 1; i < m2; i++)
		{
			if (i == 2) 
			{
				if (isLeapYear(y2) == 1)
				{
					day_diff += 29;
				}
				else 
				{
					day_diff += 28;
				}
			}
			else 
			{
				day_diff += day[i - 1];
			}
		}

		day_diff += d2;
		return day_diff;
	}
	else if (y1 == y2) 
	{
		if (m2 > m1)
		{
			if (m1 == 2)
			{
				if (isLeapYear(y1) == 1) 
				{
					day_diff += 29 - d1;
				}
				else 
				{
					day_diff += 28 - d1;
				}
			}
			else 
			{
				day_diff = day[m1 - 1] - d1;
			}
			m1++;
			for (int i = m1; i < m2; i++)
			{
				if (i == 2) 
				{
					if (isLeapYear(y1) == 1) 
					{
						day_diff += 29;
					}
					else 
					{
						day_diff += 28;
					}
				}
				else 
				{
					day_diff += day[i - 1];
				}
			}

			day_diff += d2;
			return day_diff;
		}
		else if (m1 == m2) 
		{
			if (d2 > d1) 
			{
				return (d2 - d1);
			}
			else if (d1 == d2) 
			{
				return 0;
			}

		}

	}



}

//計算30/630的天數
float Thirty(int y1, int m1, int d1,int y2,int m2,int d2)
{
	return 360 * (y2 - y1) + 30 * abs((m2 - m1))+ abs((d2 - d1));
}

//計算 dirty_price 
double dirty_price(float r, float w, int n, float C)
{
	
	double Dirty = 0.00;
	
	for (int i = 0; i < n; i++)
	{
		double discount;
		
		discount = pow((1 + (0.01 * r)/2), -w - i);
		Dirty = Dirty + discount*C;

		if (i == n - 1)
		{
			Dirty = Dirty + 100 * discount;
		}
		
	}

	return Dirty;
}

int main()
{
	int n;
	float c, r, Value = 0, Dirty1 = 0, Dirty2 = 0;
	
	//1 = maturity 2 = settlement
	int y1, y2, d1, d2, m1, m2; 
	float month;//計算下一期會到月份
	int year;
	float w_actual, w_Thirty;
	cout << "Input Maturity Date (Year Month Date) :";
	cin >> y1 >> m1 >> d1;
	cout << "Input Settlement Date (Year Month Date) :";
	cin >> y2 >> m2 >> d2;
	
	cout << "Input bond yield:";
	cin >> r;
	cout << "Input coupon rate:";
	cin >> c;
	
	if (m1 > 6)
	{
		month = m1 - 6;
		year = y2 + 1;
	}
	if (m1 <= 6)
	{
		month = m1 + 6;
		year = y2;
	}
	
	n = (y1 - y2) * 2 ;
	c = c / 2;

	w_Thirty = Thirty(y2, m2, d2, year, month, d1)/180;
	w_actual = Actual(y2, m2, d2, year, month, d1)/180;

	

	cout << "==== Under actual/actual ===== " << endl;
	cout << "Dirty Price=" << dirty_price(r, w_actual, n, c) << endl;
	cout << "Accrued interest=" << c * (1 - w_actual)<< endl;
	cout << "Clean Price=" << dirty_price(r, w_actual, n, c) - c * (1 - w_actual)<<endl<<endl;
	
	cout << "====== Under 30/360 ====== " << endl;
	cout << "Dirty Price=" << dirty_price(r, w_Thirty, n, c) << endl;
	cout << "Accrued interest=" << c * (1 - w_Thirty)<<endl;
	cout << "Clean Price=" << dirty_price(r, w_Thirty, n, c)- c * (1 - w_Thirty) << endl;
	cout << "--------------\n\n";
	
	//Offering date=2010 08 03   Maturity date=2020 08 15  
	float n2 = 10, frequency = 2, Value2=0;
	float coupon = 4.250, offprice = 99.082, offyield = 4.36422, YTM;
	float cc = 4.250/2, y = 4.36422 /2;
	for (int i = 1; i <= n2 * 2; i++)
	{
		float discount;
		discount = pow((1 + y), (-i));
		Value2 = Value2 + cc * discount;

		if (i == n2 *2)
		{
			Value2 = Value2 + offprice * discount;
		}
	}

	cout << "YTM:"<<Value2*2<<endl;
	cout << "Offering yield:" << offyield << endl;
	

	return 0;
	

}
