#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
#include <string>
#include <stdio.h>
#include <fstream>
#include <unistd.h>

using namespace std;

int asgn_acc();

class details
{
  protected:
	int acc_no;
	float bal;
	char s_ques[50], s_ans[20];
  public:
	char name[20];
	float ret_bal()
	{
		return bal;
	}
	int ret_acc()
	{
		return acc_no;
	}
	void display();
	void bal_change(float);
};
void details::bal_change(float x)
{
	bal += x;
}
void details::display()
{
	cout << name << "\t\t" << acc_no << "\t\t" << bal << '\n';
}

class user : public details
{
  private:
	int age;
	char email[40], add[50];
	long long int mob;
  protected:
	char pass[20];
  public:
  	char t[50];
  	char customer[10];
	user()
	{
		bal = 0;
		time_t rawtime;
		struct tm *timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strcpy(t, asctime(timeinfo));
	}
	void input();
	//void update();
	void all_display();
	int check(char[], char[]);
} u;

void user::all_display()
{
	cout << "Name: " << name;
	cout << "\nAccout Number: " << acc_no;
	cout << "\nBalance: " << bal;
	cout << "\nMobile No: " << mob;
	cout << "\nEmail: " << email;
	cout << "\nAddress: " << add;
	cout << "\nAccount Type: "<< customer << '\n';
}

int user::check(char s1[20], char s2[20])
{
	if (!strcmp(s1, name))
	{
		if (!strcmp(s2, pass))
			return 1;
	}
	else
		return 0;
}

void user::input()
{
	cout << "Name: ";
	cin.ignore();
	cin.getline(name, 20);
	cout << "Age: ";
	cin >> age;
	int flag = 0;
	do
	{
		cout << "Mobile Number: ";
		cin >> mob;
		if ((mob > 1000000000) && (mob < 10000000000))
		{
			flag = 1;
		}
		else
			cout << "Invalid mobile number. Please enter again\n";
	} while (flag != 1);
	flag = 0;
	int z = 0;
	do
	{
		cout << "Email: ";
		cin >> email;
		for (z = 0; email[z] != '\0'; z++);
		for (int i = 0; email[i] != '\0'; i++)
		{
			if ((email[i] == '@') && (i > 0))
			{
				for (int n = i + 1; email[n] != '\0'; n++)
				{
					if ((email[n] == '.')&&((n - i) > 1) && (z - n > 1))
					{
						flag = 1;
						break;
					}
				}
			}
		}
		if (flag != 1)
		{
			cout << "Invalid Email ID\n PLease enter again\n";
		}
	} while (flag != 1);
	cout << "Addess: ";
	cin.ignore();
	cin.getline(add, 50);
	char cpass[20];
	do
	{
		cout<<"Password: ";
		char *mypass=getpass("");
		strcpy(pass,mypass);
		cout<<"\nConfirm Password: ";
		mypass=getpass("");
		strcpy(cpass, mypass);
		if(strcmp(pass, cpass))
			cout<<"\nENTER PASSWORD AGAIN!!\n";
	}while(strcmp(pass, cpass));
	cout << "\nEnter security Question: ";
	cin.getline(s_ques, 50);
	cout << "Enter Answer: ";
	cin.getline(s_ans, 20);
	strcpy(customer, "NEW");
	acc_no = asgn_acc();
}

int asgn_acc()
{
	user acc;
	ifstream file;
	file.open("Account", ios::binary | ios::app);
	while (!file.eof())
	{
		file.read((char *)&acc, sizeof(user));
	}
	int x;
	x = acc.ret_acc();
	if (x < 1000 || x > 2000)
		x = 1000;
	return ++x;
}

void update()
{
	user u1;
	ifstream file1;
	file1.open("Account", ios::binary | ios::app);
	ofstream file;
	cout << endl;
	file.open("temp", ios::binary);
	while (file1.read((char *)&u1, sizeof(u1)))
	{
		if (u.ret_acc() == u1.ret_acc())
		{
			file.write((char *)&u, sizeof(user));
		}
		else
		{
			file.write((char *)&u1, sizeof(user));
		}
	}
	if(u.ret_bal()>100000)
		strcpy(u.customer, "CLASSIC");
	else
		strcpy(u.customer, "NEW");
	file.close();
	file1.close();
	remove("Account");
	rename("temp", "Account");
}

class trans
{
  private:
	char t[50], type[20], name[20];
	float bal, amt;
	int acc_no;

  public:
	trans(char str[], user temp, float a)
	{
		strcpy(name, temp.name);
		bal = temp.ret_bal();
		acc_no = temp.ret_acc();
		time_t rawtime;
		struct tm *timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strcpy(t, asctime(timeinfo));
		strcpy(type, str);
		amt = a;
	}
	void display();
} trans_save("NULL", u, 0);

void trans::display()
{
	cout << bal << "\t\t";
	cout << amt << "\t\t";
	cout << type << "\t\t";
	cout << t << '\n';
}
class luser
{
  private:
	char pass[20];

  public:
	char name[20];
	int check();
	void input();
} lgn;

void luser::input()
{
	cout << "Name: ";
	cin.ignore();
	cin.getline(name, 20);
	cout<<"Password: ";
	char *mypass=getpass("");
	strcpy(pass, mypass);
	int i=0;
}
int luser::check()
{
	ifstream file;
	file.open("Account", ios::binary | ios::app);
	while (!file.eof())
	{
		file.read((char *)&u, sizeof(user));
		if (u.check(name, pass) == 1)
			return 1;
	}
	return 0;
}

class manager
{
  private:
	char name[20], pass[20], name_r[20], pass_r[20];

  public:
	manager()
	{
		ifstream file;
		file.open("manager", ios::app);
		file.getline(name_r, 20, ';');
		file.getline(pass_r, 20);
		file.close();
	}
	void input();
	int check();
};
int manager::check()
{
	if ((!strcmp(name, name_r)) && (!strcmp(pass, pass_r)))
	{
		return 1;
	}
	else
		return 0;
}
void manager::input()
{
	cout << "Name: ";
	cin.ignore();
	cin.getline(name, 20);
	cout<<"Pasword: ";
	char *mypass=getpass("");
	strcpy(pass, mypass);
}

class man_trans
{
  private:
	char t[50], type[20], name[20], name2[20];
	float amt;
	int acc_no, acc_no2;

  public:
	man_trans(char str[], user temp, float a)
	{
		strcpy(name, temp.name);
		amt = a;
		strcpy(name2, "");
		acc_no = temp.ret_acc();
		time_t rawtime;
		struct tm *timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strcpy(t, asctime(timeinfo));
		strcpy(type, str);
		acc_no2 = 0;
	}
	man_trans(char str[], user temp, float a, int x, char n[])
	{
		strcpy(name, temp.name);
		acc_no = temp.ret_acc();
		time_t rawtime;
		struct tm *timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		strcpy(t, asctime(timeinfo));
		strcpy(type, str);
		acc_no2 = x;
		amt = a;
		strcpy(name2, n);
	}
	void display();
} all_trans("NULL", u, 0);

void man_trans::display()
{

	cout << amt;

	cout << "\t" << type << "\t";
	if (acc_no2 == 0)
	{
		cout << acc_no << "\t\t" << name << "\t\t";
	}
	else
	{
		cout << acc_no << ',';
		cout << acc_no2 << "\t";
		cout << name << ',';
		cout << name2 << "\t";
	}
	cout << t << '\n';
}

void create()
{
	cout << "\n---CREATE ACCOUNT---\n";
	user crt;
	crt.input();
	ofstream file;
	file.open("Account", ios::binary | ios::app);
	file.write((char *)&crt, sizeof(user));
	cout << "\nAccount Number is :" << crt.ret_acc();
	cout << "\nAccount created!!\n";
}


void deposit()
{
	float amt;
	cout << "Curent Balance: " << u.ret_bal();
	cout << "\nEnter amount to deposit: ";
	cin >> amt;
	u.bal_change(amt);
	cout << "\nNew Balance: " << u.ret_bal();
	ofstream file;
	trans trans_save("DEPOSIT", u, amt);
	update();
	file.open(to_string(u.ret_acc()), ios::binary | ios::app);
	file.write((char *)&trans_save, sizeof(trans));
	ofstream out;
	man_trans all_trans("DEPO", u, amt);
	out.open("Trans", ios::binary | ios::app);
	out.write((char *)&all_trans, sizeof(all_trans));
	out.close();
	file.close();
}

void withdraw()
{
	float amt;
	cout << "\nCurent Balance: " << u.ret_bal();
	cout << "\nEnter amount to withdraw: ";
	cin >> amt;
	if(amt>u.ret_bal())
	{
		cout<<"Insufficient Balance\n";
		return;
	}
	u.bal_change(-amt);
	cout << "\nNew Balance: " << u.ret_bal();
	ofstream file;
	trans trans_save("WITHDRAWL", u, -amt);
	update();
	man_trans all_trans("WITH", u, -amt);
	ofstream out;
	out.open("Trans", ios::binary | ios::app);
	file.open(to_string(u.ret_acc()), ios::binary | ios::app);
	out.write((char *)&all_trans, sizeof(all_trans));
	file.write((char *)&trans_save, sizeof(trans));
	out.close();
	file.close();
}

void fund_trans()
{
	int a, flag = 0;
	char n[20];
	float fund;
	cout << "\n---FUND TRANSFER---\n";
	cout << "Enter Account number to transfer funds: ";
	cin >> a;
	cout << "Enter name of Recipent: ";
	cin.ignore();
	cin.getline(n, 20);
	ifstream file;
	user u1;
	file.open("Account", ios::binary | ios::app);
	while (file.read((char *)&u1, sizeof(user)))
	{
		if (file.good())
		{
			if (!strcmp(n, u1.name))
			{
				if (a == u1.ret_acc())
				{
					flag = 1;
					break;
				}
			}
		}
	}

	if (flag != 1)
	{
		cout << "Error while processing!\nPlease try again\n";
		return;
	}
	cout << "Enter amount: ";
	cin >> fund;
	if (u.ret_bal() < fund)
	{
		cout << "Insufficient Funds\n";
		return;
	}
	if(fund<0)
	{
		cout<<"Amount <0,Cannot transfer Money\n";
		return;
	}
	if(((fund>1000000)&&(!strcmp(u.customer, "NEW")))||(fund>10000000)&&(!strcmp(u.customer, "CLASSIC")))
	{
		char pan[11];
		int count=0;
		cout<<"Large Transaction\nEnter PAN: ";
		cin>>pan;
		int i;
		for(i=0;pan[i]!='\0';i++)
		{
			if(i<5)
			{
				if(isalpha(pan[i]))
					count++;
			}
			else if((i>4)&&(i<9))
			{
				if(isdigit(pan[i]))
					count++;
			}
			else if(i==9)
			{
				if(isalpha(pan[i]))
					count++;
			}
		}
		if(i==10&&count==10)
		{
			cout<<"Valid PAN\n";
		}
		else
		{
			cout<<"Invalid PAN\n";
			return;
		}
	}
	u.bal_change(-fund);
	u1.bal_change(fund);
	cout << "Funds Transferred!!\n";
	file.close();
	user u2;
	ifstream files;
	files.open("Account", ios::binary | ios::app);
	ofstream file2;
	cout << endl;
	file2.open("temp", ios::binary);
	while (files.read((char *)&u2, sizeof(user)))
	{
		if (files.good())
		{
			if (a == u2.ret_acc())
			{
				file2.write((char *)&u1, sizeof(user));
			}
			else if (u.ret_acc() == u2.ret_acc())
			{
				file2.write((char *)&u, sizeof(user));
			}
			else
			{
				file2.write((char *)&u2, sizeof(user));
			}
		}
	}
	file2.close();
	files.close();
	remove("Account");
	rename("temp", "Account");

	ofstream file3, file4;
	char s1[30], s2[30];
	strcpy(s2, "TRANS,");
	strcat(s2, u.name);
	strcpy(s1, "TRANS,");
	strcat(s1, n);
	trans trans_save(s1, u, -fund);
	trans trans_save2(s2, u1, fund);
	file4.open(to_string(u1.ret_acc()), ios::binary | ios::app);
	file3.open(to_string(u.ret_acc()), ios::binary | ios::app);
	file3.write((char *)&trans_save, sizeof(trans));
	file4.write((char *)&trans_save2, sizeof(trans));
	file3.close();
	file4.close();
	man_trans all_trans("TRANS", u, fund, a, n);
	ofstream out;
	out.open("Trans", ios::binary | ios::app);
	out.write((char *)&all_trans, sizeof(man_trans));
	out.close();
}
void trans_his()
{
	ifstream file;
	file.open(to_string(u.ret_acc()), ios::binary | ios::app);
	cout << "\n---TRANSACTION HISTORY---\n";
	cout << "Balance\t\tAmount\t\tType\t\t\tDate\n";
	while (file.read((char *)&trans_save, sizeof(trans)))
	{
		if (file.good())
		{
			trans_save.display();
		}
	}
	cout << endl;
}

void mini_s()
{
	int i=0;
	ifstream file;
	file.open(to_string(u.ret_acc()), ios::binary | ios::app);
	cout << "\n---MINI STATEMENT---\n";
	cout << "Balance\t\tAmount\t\tType\t\t\tDate\n";
	while (file.read((char *)&trans_save, sizeof(trans)))
	{
		if(i>10)
			break;
		if (file.good())
		{
			trans_save.display();
		}
		i++;
	}
	cout << endl;
}


void acc_update()
{
	int opt;
	while (1)
	{
		cout << "\nChange:";
		cout << "\n1)Name";
		cout << "\n2)Go Back";
		cout << "\nChoose field to change: ";
		cin >> opt;
		switch (opt)
		{
		case 1:
			cout << "Enter new name: ";
			cin.ignore();
			cin.getline(u.name, 20);
			break;
		case 2:
			return;
		}
	}
}

void account()
{
	int opt;

	while (1)
	{
		cout << "\n1)Deposit";
		cout << "\n2)Withdrawl";
		cout << "\n3)Fund Transfer";
		cout << "\n4)Mini Statement";
		cout << "\n5)Transaction History";
		cout << "\n6)Account Details";
		cout << "\n7)Update Details";
		cout << "\n8)Logout";
		cout << "\nEnter Option: ";
		cin >> opt;
		switch (opt)
		{
			case 1:
				deposit();
				break;
			case 2:
				withdraw();
				break;
			case 3:
				fund_trans();
				break;
			case 4:
				mini_s();
				break;
			case 5:
				trans_his();
				break;
			case 6:
				cout << endl;
				u.all_display();
				break;
			case 7:
				acc_update();
				break;
			case 8:
				update();
				return;
			default:
				cout << "Enter appropriate Option:";
				break;
		}
	}
}

void login()
{
	cout << "\n---LOGIN---\n";
	lgn.input();
	if (lgn.check())
	{
		cout << "\n\nWelcome USER!!";
		cout << "\nLast Login Time: "<<u.t;
		account();
	}
	else
		cout << "Error Logging In!!\nPlease try again\n";
}

void mgr_menu()
{
	char inp[20];
	cout << "\nWelcome Manager";
	do
	{
		cout << "\n-->";
		cin>>inp;
		if (!strcmp(inp, "show"))
		{
			char str[5];
			cin>>str;
			if(!strcmp(str, "all"))
			{
				ifstream file;
				file.open("Account", ios::binary | ios::app);
				cout << "Name\t\tAcc No\t\tBalance\n";
				while (file.read((char *)&u, sizeof(u)))
				{
					if (file.good())
						u.display();
				}
				file.close();
			}
			if(!strcmp(str, "bal"))
			{
				int x;
				char op;
				cin>>op>>x;
				if(op=='<')
				{
					ifstream file;
					file.open("Account", ios::binary | ios::app);
					cout << "Name\t\tAcc No\t\tBalance\n";
					while (file.read((char *)&u, sizeof(u)))
					{
						if (file.good())
						{
							if(u.ret_bal()<=x)
								u.display();
						}
					}
					file.close();
				}
				if(op=='>')
				{
					ifstream file;
					file.open("Account", ios::binary | ios::app);
					cout << "Name\t\tAcc No\t\tBalance\n";
					while (file.read((char *)&u, sizeof(u)))
					{
						if (file.good())
						{
							if(u.ret_bal()>=x)
								u.display();
						}
					}
					file.close();
				}
			}
		}
		if (!strcmp(inp, "trans"))
		{
			ifstream file;
			file.open("Trans", ios::binary | ios::app);
			cout << "Amount\tType\tAcc No\t\tName\t\tTime\n";
			while (file.read((char *)&all_trans, sizeof(all_trans)))
			{
				if (file.good())
				{
					all_trans.display();
				}
			}
			file.close();
		}
		if (!strcmp(inp, "delete" ))
		{
			int x;
			cin>>x;
			ifstream file;
			ofstream file1;
			file1.open("temp", ios::binary|ios::app);
			file.open("Account", ios::binary | ios::app);

			while (file.read((char *)&u, sizeof(u)))
			{
				if (file.good())
				{
					if(u.ret_acc()!=x)
					{
						file1.write((char *)&u, sizeof(u));
					}
				}
			}

			file.close();
			file1.close();
			remove("Account");
			rename("temp", "Account");

			cout<<"Account No: "<<x<<" Removed";
		}
	} while (strcmp(inp, "exit"));
}

void mag_login()
{
	cout << "\n---Manager Login---\n";
	manager mgr;
	mgr.input();

	if (mgr.check() == 0)
	{
		cout << "Error Loging IN!!\nPlease try again";
		return;
	}

	mgr_menu();
}

int main()
{
	int opt;
	while (1)
	{
		cout << "\n\n1)Create Account";
		cout << "\n2)Login";
		cout << "\n3)Manager Login";
		cout << "\n4)Exit";
		cout << "\nChoose Correct Option: ";
		cin >> opt;
		switch (opt)
		{
			case 1:
				create();
				break;
			case 2:
				login();
				break;
			case 3:
				mag_login();
				break;
			case 4:
				exit(0);
				break;
			default:
				cout << "Enter appropriate option!!\n";
				break;
		}
	}
	return 0;
}
