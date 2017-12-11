#include<iostream>
#include<string>
#include<map>
#include <utility>
#include <sstream>

using namespace std;

void PrintHexaDecimal(string ans)
{
	
	string s="";
	int c=0;
	map<string,string> pat;
	pat["0000"]="0";pat["0001"]="1";
	pat["0010"]="2";pat["0011"]="3";
	pat["0100"]="4";pat["0101"]="5";
	pat["0110"]="6";pat["0111"]="7";
	pat["1000"]="8";pat["1001"]="9";
	pat["1010"]="A";pat["1011"]="B";
	pat["1100"]="C";pat["1101"]="D";
	pat["1110"]="E";pat["1111"]="F";
	cout<<endl;
	for(int i=0;i<ans.length();i=i+4)
	{
		s="";
		int j=i;
		if(c==8 || c==17 || c==26 || c==35 || c==44 || c==53 || c==62 || c==71 || c==80)
		{
			j++;
			i++;
		}
		for(;j<=i+3;j++)
		{
			c++;
			s=s+ans[j];
		}
		cout<<pat[s];
	}
}

string PrintBinary(string str,int regsize)
{
	cout<<"Binary Value:- ";
	map<char,string> pat;
	pat['0']="0000";pat['1']="0001";
	pat['2']="0010";pat['3']="0011";
	pat['4']="0100";pat['5']="0101";
	pat['6']="0110";pat['7']="0111";
	pat['8']="1000";pat['9']="1001";
	pat['A']="1010";pat['B']="1011";
	pat['C']="1100";pat['D']="1101";
	pat['E']="1110";pat['F']="1111";
	
	string s="";
	char c;
	int l=str.length();
	if(regsize==16)
	{
		if(l==1)
		{
			s=s+pat['0'];
			s=s+pat['0'];
			s=s+" ";
			s=s+pat['0'];
			c=str[0];
			s=s+pat[c];
		}
		else if(l==2)
		{
			c=str[0];
			s=s+pat[c];
			c=str[1];
			s=s+pat[c];
			s=s+" ";
			s=s+pat['0'];
			s=s+pat['0'];
		}
		else if(l==3)
		{
			s=s+pat[str[1]];
			s=s+pat[str[2]];
			s=s+" ";
			s=s+pat['0'];
			s=s+pat[str[0]];
		}
		else if(l>=4)
		{
			s=s+pat[str[2]];
			s=s+pat[str[3]];
			s=s+" ";
			s=s+pat[str[0]];
			s=s+pat[str[1]];
		}
	}
	else if(regsize==32)
	{
		if(l==1)
		{
			s=s+pat['0'];
			s=s+pat['0'];
			s=s+" ";
			s=s+pat['0'];
			s=s+pat['0'];
			s=s+" ";
			s=s+pat['0'];
			s=s+pat['0'];
			s=s+" ";
			s=s+pat['0'];
			s=s+pat['0'];
			c=str[0];
			s=s+pat[c];
		}
		else if(l==2)
		{
			c=str[0];
			s=s+pat[c];
			c=str[1];
			s=s+pat[c];
			s=s+" ";
			s=s+pat['0'];
			s=s+pat['0'];
			s=s+" ";
			s=s+pat['0'];
			s=s+pat['0'];
			s=s+" ";
			s=s+pat['0'];
			s=s+pat['0'];
		}
		else if(l==3)
		{
			s=s+pat[str[1]];
			s=s+pat[str[2]];
			s=s+" ";
			s=s+pat['0'];
			s=s+pat[str[0]];
			s=s+" ";
			s=s+pat['0'];
			s=s+pat['0'];
			s=s+" ";
			s=s+pat['0'];
			s=s+pat['0'];
		}
		else if(l==4)
		{
			s=s+pat[str[2]];
			s=s+pat[str[3]];
			s=s+" ";
			s=s+pat[str[0]];
			s=s+pat[str[1]];
			s=s+" ";
			s=s+pat['0'];
			s=s+pat['0'];
			s=s+" ";
			s=s+pat['0'];
			s=s+pat['0'];
		}
		else if(l>=8)
		{
			s=s+pat[str[6]];
			s=s+pat[str[7]];
			s=s+" ";
			s=s+pat[str[4]];
			s=s+pat[str[5]];
			s=s+" ";
			s=s+pat[str[2]];
			s=s+pat[str[3]];
			s=s+" ";
			s=s+pat[str[0]];
			s=s+pat[str[1]];
		}
	}
	else if(regsize==8)
	{
		if(l==1)
		{
			s=s+pat['0'];
			s=s+pat[str[0]];
		}
		else if(l==2)
		{
			s=s+pat[str[0]];
			s=s+pat[str[1]];
		}
			else if(l==3)
		{
			s=s+pat['0'];
			s=s+pat[str[2]];
		}
		else if(l>=4)
		{
			s=s+pat[str[2]];
			s=s+pat[str[3]];
		}
	}
	return s;
}

void RegisterToRegister(string ins)
{
	string final="";
	cout<<"Register To Register\n";
	map<string,string> eightbitreg;
	eightbitreg["AL"]="000";eightbitreg["CL"]="001";eightbitreg["DL"]="010";eightbitreg["BL"]="011";eightbitreg["AH"]="100";eightbitreg["CH"]="101";eightbitreg["DH"]="110";eightbitreg["BH"]="111";eightbitreg[","]="";eightbitreg[""]="";
	
	map<string,string> sixteenbitreg;
	sixteenbitreg["AX"]="000";sixteenbitreg["CX"]="001";sixteenbitreg["DX"]="010";sixteenbitreg["BX"]="011";sixteenbitreg["SP"]="100";sixteenbitreg["BP"]="101";sixteenbitreg["SI"]="110";sixteenbitreg["DI"]="111";sixteenbitreg[","]="";sixteenbitreg[""]="";
	
	map<string,string> thirtytwobitreg;
	thirtytwobitreg["EAX"]="000";thirtytwobitreg["ECX"]="001";thirtytwobitreg["EDX"]="010";thirtytwobitreg["EBX"]="011";thirtytwobitreg["ESP"]="100";thirtytwobitreg["EBP"]="101";thirtytwobitreg["ESI"]="110";thirtytwobitreg["EDI"]="111";thirtytwobitreg[","]="";thirtytwobitreg[""]="";
	
	string ans="";
	int flag=1;
	int c=0,modeop;
	string regbin,w,d;
	int mop=0;
	
	int regsize=0;
	cout<<"Mode of op"<<endl;
	cin>>modeop;

    istringstream iss(ins);

    do
    {
        string sub;
        iss >> sub;
        if(c==0)
        {
			d="1";
        	ans=ans+"100010";
			ans=ans+d;
        	c++;
        	continue;
		}
		
		if(eightbitreg.count(sub)>=1 && (regsize==0 || regsize==8))
		{
			if(c==1)
			{
				w="0";
				ans=ans+w;
				ans=ans+" 11";
			}
			regsize=8;
			regbin=eightbitreg[sub];
			ans=ans+regbin;
			c++;
		}
		else if(sixteenbitreg.count(sub)>=1 && (regsize==0 || regsize==16))
		{
			if(c==1)
			{
				w="1";
				if(modeop == 32)
				{
					mop=1;
				}
				ans=ans+w;
				ans=ans+" 11";
			}
			regsize=16;
			regbin=sixteenbitreg[sub];
			ans=ans+regbin;
			c++;
		}
		else if(thirtytwobitreg.count(sub)>=1 && (regsize==0 || regsize==32))
		{
			if(c==1)
			{
				w="1";
				if(modeop==16)
				{
					mop=1;
				}
				ans=ans+w;
				ans=ans+" 11";
			}
			regsize=32;
			regbin=thirtytwobitreg[sub];
			ans=ans+regbin;
			c++;
		}
		else
		{
			flag=0;
			break;
		}
    } while (iss);
    
    if(flag==1)
    {
    	if(mop==1)
    	{
    		cout<<"66 ";
		}
    	cout<<ans;
    	PrintHexaDecimal(ans);
    }
    else
    {
    	cout<<"Invalid instruction";
	}
}

void RegisterImmediate(string ins)
{
	string 	final="";
	cout<<"Register Immediate Mode\n";
	map<string,string> eightbitreg;
	eightbitreg["AL"]="000";eightbitreg["CL"]="001";eightbitreg["DL"]="010";eightbitreg["BL"]="011";eightbitreg["AH"]="100";eightbitreg["CH"]="101";eightbitreg["DH"]="110";eightbitreg["BH"]="111";eightbitreg[","]="";eightbitreg[""]="";
	
	map<string,string> sixteenbitreg;
	sixteenbitreg["AX"]="000";sixteenbitreg["CX"]="001";sixteenbitreg["DX"]="010";sixteenbitreg["BX"]="011";sixteenbitreg["SP"]="100";sixteenbitreg["BP"]="101";sixteenbitreg["SI"]="110";sixteenbitreg["DI"]="111";sixteenbitreg[","]="";sixteenbitreg[""]="";
	
	map<string,string> thirtytwobitreg;
	thirtytwobitreg["EAX"]="000";thirtytwobitreg["ECX"]="001";thirtytwobitreg["EDX"]="010";thirtytwobitreg["EBX"]="011";thirtytwobitreg["ESP"]="100";thirtytwobitreg["EBP"]="101";thirtytwobitreg["ESI"]="110";thirtytwobitreg["EDI"]="111";thirtytwobitreg[","]="";thirtytwobitreg[""]="";
	
	string ans="";
	string sa;
	int flag=1,u=0,du[20];
	int c=0,modeop;
	string regbin,w,d;
	int mop;
	
	int regsize=0;
	cout<<"Mode of op"<<endl;
	cin>>modeop;

    istringstream iss(ins);
    
	do
    {
        string sub;
        iss >> sub;
        if(c==0)
        {
        	ans=ans+"1011";
        	c++;
        	continue;
		}
		else
		{
			if(eightbitreg.count(sub)>=1 && (regsize==0 || regsize==8))
			{
				if(c==1)
				{
					w="0";
					ans=ans+w;
				}
				regsize=8;
				regbin=eightbitreg[sub];
				ans=ans+regbin;
				c++;
			}
			else if(sixteenbitreg.count(sub)>=1 && (regsize==0 || regsize==16))
			{
				if(c==1)
				{
					w="1";
					if(modeop == 32)
				{
					mop=1;
				}
					ans=ans+w;
				}
				regsize=16;
				regbin=sixteenbitreg[sub];
				ans=ans+regbin;
				c++;
			}
			else if(thirtytwobitreg.count(sub)>=1 && (regsize==0 || regsize==32))
			{
				if(c==1)
				{
					w="1";
					if(modeop == 16)
				{
					mop=1;
				}
					ans=ans+w;
				}
				regsize=32;
				regbin=thirtytwobitreg[sub];
				ans=ans+regbin;
				
				c++;
			}
			else
			{
				sa=PrintBinary(sub,regsize);
			}
			
			
		}
    } while (iss);
    
    if(flag==1)
    {
    	if(mop==1)
    	{
    		cout<<"66 ";
		}
    	ans=ans+" ";
    	ans=ans+sa;
    	cout<<ans;
    	PrintHexaDecimal(ans);
    }
    else
    {
    	cout<<"Invalid instruction";
	}
	
}

void MemoryImmediate(string ins)
{
	string 	final="";
	cout<<"Memory Immediate Mode\n";

	map<string,string> sixteenbitreg;
	sixteenbitreg["[BX+SI]"]="000";sixteenbitreg["[BX+DI]"]="001";sixteenbitreg["[BP+SI]"]="010";sixteenbitreg["[BP+DI]"]="011";sixteenbitreg["[SI+"]="100";sixteenbitreg["[DI+"]="101";sixteenbitreg["[BP+"]="110";sixteenbitreg["[BX+"]="111";sixteenbitreg[","]="";sixteenbitreg[""]="";sixteenbitreg["]"]="";sixteenbitreg["BYTE_PTR"]="";sixteenbitreg["WORD_PTR"]="";sixteenbitreg["DWORD_PTR"]="";sixteenbitreg["QWORD_PTR"]="";
	
	map<string,string> thirtytwobitreg;
	thirtytwobitreg["[EAX+"]="000";thirtytwobitreg["[ECX+"]="001";thirtytwobitreg["[EDX+"]="010";thirtytwobitreg["[EBX+"]="011";thirtytwobitreg["[ESP+"]="100";thirtytwobitreg["[EBP+"]="101";thirtytwobitreg["[ESI+"]="110";thirtytwobitreg["[EDI+"]="111";thirtytwobitreg[","]="";thirtytwobitreg[""]="";thirtytwobitreg["]"]="";thirtytwobitreg["BYTE_PTR"]="";thirtytwobitreg["WORD_PTR"]="";thirtytwobitreg["DWORD_PTR"]="";thirtytwobitreg["QWORD_PTR"]="";
	
	string ans="";
	string anstemp="";
	string sa;
	int flag=1,u=0,du[100],r=0,j;
	int c=0,modeop;
	string regbin,w,d,temp;
	int mop;
	int regsize=0;
	cout<<"Mode of op"<<endl;
	cin>>modeop;

    istringstream iss(ins);
    
	do
    {
        string sub;
        iss >> sub;
        if(c==0)
        {
        	ans=ans+"1100011";
        	c++;
        	continue;
		}
		else
		{
			if(c==1)
			{
				if(sub=="BYTE_PTR")
				{
					w="0";
					ans=ans+w;
					ans=ans+" ";
				}
				else if(sub=="WORD_PTR")
				{
					w="1";
					if(modeop == 32)
				{
					mop=1;
				}
					ans=ans+w;
					ans=ans+" ";
				}
				else if(sub=="DWORD_PTR")
				{
					w="1";
					if(modeop == 16)
				{
					mop=1;
				}
					ans=ans+w;
					ans=ans+" ";
				}
				else
				{
					w="1";
					ans=ans+w;
					ans=ans+" ";
				}
				c++;
			}
			if(sixteenbitreg.count(sub)>=1 && (regsize==0 || regsize==16))
			{
				regsize=16;
				regbin=sixteenbitreg[sub];
				anstemp=anstemp+regbin;
				c++;
			}
			else if(thirtytwobitreg.count(sub)>=1 && (regsize==0 || regsize==32))
			{
				regsize=32;
				regbin=thirtytwobitreg[sub];
				anstemp=anstemp+regbin;
				c++;
			}
			else
			{
				if(r==0)
				{
					if(sub.length()<=2)
					{
						j=0;
					}
					else
					{
						j=1;
					}
					sa=PrintBinary(sub,regsize);
				}
				else if(r==1)
				{
					sa=PrintBinary(sub,regsize);
				}
				anstemp=anstemp+" ";
				anstemp=anstemp+sa;
				r++;
			}
			
		}
    } while (iss);
    
    if(flag==1)
    {
    	if(mop==1)
    	{
    		cout<<"66 ";
		}
    	ans=ans+" ";
    	if(j==0)
    	{
    		ans=ans+"01";
		}
		else
		{
			ans=ans+"10";
		}
    	ans=ans+"000";
    	ans=ans+anstemp;
    	cout<<ans;
    	PrintHexaDecimal(ans);
    }
    else
    {
    	cout<<"Invalid instruction";
	}
}

void MemoryAccumulator(string ins)
{
	string 	final="";
	string ans="";
	string sa,anstemp="";
	int flag=1,u=0,du[100];
	int c=0,modeop;
	string regbin,w,d;
	int mop;
	int regsize=0;
	cout<<"Mode of op"<<endl;
	cin>>modeop;

    istringstream iss(ins);
    
	do
    {
        string sub;
        iss >> sub;
        if(c==0)
        {
        	ans=ans+"101000";
        	c++;
        	continue;
		}
		else if(c==1)
		{
			if(sub=="AL" || sub=="AH" || sub=="AX" || sub=="EAX")
			{
				d="1";
			}
			else
			{
				d="0";
			}
			ans=ans+d;
			c++;
		}
		if(sub=="AL" || sub=="AH")
		{
			w="0";
			regsize=8;
		}
		else if(sub=="AX")
		{
			w="1";
			if(modeop == 32)
				{
					mop=1;
				}
			regsize=16;
		}
		else if(sub=="EAX")
		{
			w="1";
			if(modeop == 16)
				{
					mop=1;
				}
			regsize=16;
		}
		ans=ans+w;
		ans=ans+" ";
		if(c==4)
		{
			sa=PrintBinary(sub,regsize);
		}
			
    } while (iss);
    
    if(flag==1)
    {
    	if(mop==1)
    	{
    		cout<<"66 ";
		}
    	ans=ans+sa;
    	cout<<ans;
    	PrintHexaDecimal(ans);
    }
    else
    {
    	cout<<"Invalid instruction";
	}
}


void RegisterIndirect(string ins)
{
	string 	final="";
	cout<<"Register Indirect Mode\n";
	map<string,string> sixteenbitreg;
	sixteenbitreg["AX"]="000";sixteenbitreg["CX"]="001";sixteenbitreg["DX"]="010";sixteenbitreg["BX"]="011";sixteenbitreg["SP"]="100";sixteenbitreg["BP"]="101";sixteenbitreg["SI"]="110";sixteenbitreg["DI"]="111";sixteenbitreg[","]="";sixteenbitreg[""]="";
	
	map<string,string> thirtytwobitreg;
	thirtytwobitreg["EAX"]="000";thirtytwobitreg["ECX"]="001";thirtytwobitreg["EDX"]="010";thirtytwobitreg["EBX"]="011";thirtytwobitreg["ESP"]="100";thirtytwobitreg["EBP"]="101";thirtytwobitreg["ESI"]="110";thirtytwobitreg["EDI"]="111";thirtytwobitreg[","]="";thirtytwobitreg[""]="";
	
	
	map<string,string> sixteenbitregbr;
	sixteenbitregbr["[BX+SI]"]="000";sixteenbitregbr["[BX+DI]"]="001";sixteenbitregbr["[BP+SI]"]="010";sixteenbitregbr["[BP+DI]"]="011";sixteenbitregbr["[SI]"]="100";sixteenbitregbr["[DI]"]="101";sixteenbitregbr["[BP]"]="110";sixteenbitregbr["[BX]"]="111";sixteenbitregbr[","]="";sixteenbitregbr[""]="";sixteenbitregbr["]"]="";
	
	map<string,string> thirtytwobitregbr;
	thirtytwobitregbr["[EAX]"]="000";thirtytwobitregbr["[ECX]"]="001";thirtytwobitregbr["[EDX]"]="010";thirtytwobitregbr["[EBX]"]="011";thirtytwobitregbr["[ESP]"]="100";thirtytwobitregbr["[EBP]"]="101";thirtytwobitregbr["[ESI]"]="110";thirtytwobitregbr["[EDI]"]="111";thirtytwobitregbr[","]="";thirtytwobitregbr[""]="";thirtytwobitregbr["]"]="";
	
	string ans="",ansreg,ansm;
	int flag=1;
	int c=0,modeop;
	string regbin,w,d;
	int mop;
	int regsize=0;
	cout<<"Mode of op"<<endl;
	cin>>modeop;
	
    istringstream iss(ins);

    do
    {
        string sub;
        iss >> sub;
        if(c==0)
        {
        	ans=ans+"100010";
        	c++;
        	continue;
		}
		if(c==1)
			{
				if(sixteenbitreg.count(sub)>=1 || thirtytwobitreg.count(sub)>=1)
				{
					d="1";
				}
				else
				{
					d="0";
				}
				ans=ans+d;
				c++;
			}
		if(sixteenbitreg.count(sub)>=1 && (regsize==0 || regsize==16))
		{
			if(c==2)
			{
				w="1";
				if(modeop == 32)
				{
					mop=1;
				}
				ans=ans+w;
				ans=ans+" 00";
			}
			regsize=16;
			regbin=sixteenbitreg[sub];
			ansreg=ansreg+regbin;
			c++;
		}
		else if(thirtytwobitreg.count(sub)>=1 && (regsize==0 || regsize==32))
		{
			if(c==2)
			{
				w="1";
				if(modeop == 16)
				{
					mop=1;
				}
				ans=ans+w;
				ans=ans+" 00";
			}
			regsize=32;
			regbin=thirtytwobitreg[sub];
			ansreg=ansreg+regbin;
			c++;
		}

		else if(sixteenbitregbr.count(sub)>=1 && (regsize==0 || regsize==16))
		{
			if(c==2)
			{
				w="1";
				if(modeop == 32)
				{
					mop=1;
				}
				ans=ans+w;
				ans=ans+" 00";
			}
			regsize=16;
			regbin=sixteenbitregbr[sub];
			ansm=ansm+regbin;
			c++;
		}
		else if(thirtytwobitregbr.count(sub)>=1 && (regsize==0 || regsize==32))
		{
			if(c==2)
			{
				w="1";
				if(modeop == 16)
				{
					mop=1;
				}
				ans=ans+w;
				ans=ans+" 00";
			}
			regsize=32;
			regbin=thirtytwobitregbr[sub];
			ansm=ansm+regbin;
			c++;
		}
		else
		{
			flag=0;
			break;
		}
    } while (iss);
    
    if(flag==1)
    {
    	if(mop==1)
    	{
    		cout<<"66 ";
		}
    	ans=ans+ansreg;
    	ans=ans+ansm;
    	cout<<ans;
    	PrintHexaDecimal(ans);
    }
    else
    {
    	cout<<"Invalid Instruction";
	}
}

void BasePlusIndex(string ins)
{
	string 	final="";
	cout<<"Base + Index Mode\n";
	map<string,string> eightbitreg;
	eightbitreg["AL"]="000";eightbitreg["CL"]="001";eightbitreg["DL"]="010";eightbitreg["BL"]="011";eightbitreg["AH"]="100";eightbitreg["CH"]="101";eightbitreg["DH"]="110";eightbitreg["BH"]="111";eightbitreg[","]="";eightbitreg[""]="";
	
	map<string,string> sixteenbitreg;
	sixteenbitreg["AX"]="000";sixteenbitreg["CX"]="001";sixteenbitreg["DX"]="010";sixteenbitreg["BX"]="011";sixteenbitreg["SP"]="100";sixteenbitreg["BP"]="101";sixteenbitreg["SI"]="110";sixteenbitreg["DI"]="111";sixteenbitreg[","]="";sixteenbitreg[""]="";
	
	map<string,string> thirtytwobitreg;
	thirtytwobitreg["EAX"]="000";thirtytwobitreg["ECX"]="001";thirtytwobitreg["EDX"]="010";thirtytwobitreg["EBX"]="011";thirtytwobitreg["ESP"]="100";thirtytwobitreg["EBP"]="101";thirtytwobitreg["ESI"]="110";thirtytwobitreg["EDI"]="111";thirtytwobitreg[","]="";thirtytwobitreg[""]="";
	
	map<string,string> sixteenbitregbr;
	sixteenbitregbr["[BX+SI]"]="000";sixteenbitregbr["[BX+DI]"]="001";sixteenbitregbr["[BP+SI]"]="010";sixteenbitregbr["[BP+DI]"]="011";sixteenbitregbr["[SI]"]="100";sixteenbitregbr["[DI]"]="101";sixteenbitregbr["[BP]"]="110";sixteenbitregbr["[BX]"]="111";sixteenbitregbr[","]="";sixteenbitregbr[""]="";sixteenbitregbr["]"]="";
	
	map<string,string> thirtytwobitregbr;
	thirtytwobitregbr["[EAX]"]="000";thirtytwobitregbr["[ECX]"]="001";thirtytwobitregbr["[EDX]"]="010";thirtytwobitregbr["[EBX]"]="011";thirtytwobitregbr["[ESP]"]="100";thirtytwobitregbr["[EBP]"]="101";thirtytwobitregbr["[ESI]"]="110";thirtytwobitregbr["[EDI]"]="111";thirtytwobitregbr[","]="";thirtytwobitregbr[""]="";thirtytwobitregbr["]"]="";
	
	string ans="",ansreg,ansm;
	int flag=1;
	int c=0,modeop;
	string regbin,w,d;
	int mop;
	int regsize=0;
	cout<<"Mode of op"<<endl;
	cin>>modeop;

    istringstream iss(ins);

    do
    {
        string sub;
        iss >> sub;
        if(c==0)
        {
        	ans=ans+"100010";
        	c++;
        	continue;
		}
		if(c==1)
			{
				if(eightbitreg.count(sub)>=1 || sixteenbitreg.count(sub)>=1 || thirtytwobitreg.count(sub)>=1)
				{
					d="1";
				}
				else
				{
					d="0";
				}
				ans=ans+d;
				c++;
			}
			if(eightbitreg.count(sub)>=1 && (regsize==0 || regsize==16))
		{
			if(c==2)
			{
				w="0";
				ans=ans+w;
				ans=ans+" 00";
			}
			regsize=16;
			regbin=eightbitreg[sub];
			ansreg=ansreg+regbin;
			c++;
		}
		else if(sixteenbitreg.count(sub)>=1 && (regsize==0 || regsize==16))
		{
			if(c==2)
			{
				w="1";
				if(modeop==32)
				{
					mop=1;
				}
				ans=ans+w;
				ans=ans+" 00";
			}
			regsize=16;
			regbin=sixteenbitreg[sub];
			ansreg=ansreg+regbin;
			c++;
		}
		else if(thirtytwobitreg.count(sub)>=1 && (regsize==0 || regsize==32))
		{
			if(c==2)
			{
				w="1";
				if(modeop==16)
				{
					mop=1;
				}
				ans=ans+w;
				ans=ans+" 00";
			}
			regsize=32;
			regbin=thirtytwobitreg[sub];
			ansreg=ansreg+regbin;
			c++;
		}

		else if(sixteenbitregbr.count(sub)>=1 && (regsize==0 || regsize==16))
		{
			if(c==2)
			{
				w="1";
				ans=ans+w;
				ans=ans+" 00";
			}
			regsize=16;
			regbin=sixteenbitregbr[sub];
			ansm=ansm+regbin;
			c++;
		}
		else if(thirtytwobitregbr.count(sub)>=1 && (regsize==0 || regsize==32))
		{
			if(c==2)
			{
				w="1";
				ans=ans+w;
				ans=ans+" 00";
			}
			regsize=32;
			regbin=thirtytwobitregbr[sub];
			ansm=ansm+regbin;
			c++;
		}
		else
		{
			flag=0;
			break;
		}
    } while (iss);
    
    if(flag==1)
    {
    	if(mop==1)
    	{
    		cout<<"66 ";
		}
    	ans=ans+ansreg;
    	ans=ans+ansm;
    	cout<<ans;
    	PrintHexaDecimal(ans);
    }
    else
    {
    	cout<<"Invalid Instruction";
	}
	
}


void RegisterRelative(string ins)
{
	string 	final="";
	cout<<"Register Relative Mode\n";
	map<string,string> eightbitreg;
	eightbitreg["AL"]="000";eightbitreg["CL"]="001";eightbitreg["DL"]="010";eightbitreg["BL"]="011";eightbitreg["AH"]="100";eightbitreg["CH"]="101";eightbitreg["DH"]="110";eightbitreg["BH"]="111";eightbitreg[","]="";eightbitreg[""]="";
	
	map<string,string> sixteenbitreg;
	sixteenbitreg["AX"]="000";sixteenbitreg["CX"]="001";sixteenbitreg["DX"]="010";sixteenbitreg["BX"]="011";sixteenbitreg["SP"]="100";sixteenbitreg["BP"]="101";sixteenbitreg["SI"]="110";sixteenbitreg["DI"]="111";sixteenbitreg[","]="";sixteenbitreg[""]="";
	
	map<string,string> thirtytwobitreg;
	thirtytwobitreg["EAX"]="000";thirtytwobitreg["ECX"]="001";thirtytwobitreg["EDX"]="010";thirtytwobitreg["EBX"]="011";thirtytwobitreg["ESP"]="100";thirtytwobitreg["EBP"]="101";thirtytwobitreg["ESI"]="110";thirtytwobitreg["EDI"]="111";thirtytwobitreg[","]="";thirtytwobitreg[""]="";
	
	map<string,string> sixteenbitregbr;
	sixteenbitregbr["[BX+SI+"]="000";sixteenbitregbr["[BX+DI+"]="001";sixteenbitregbr["[BP+SI+"]="010";sixteenbitregbr["[BP+DI+"]="011";sixteenbitregbr["[SI+"]="100";sixteenbitregbr["[DI+"]="101";sixteenbitregbr["[BP+"]="110";sixteenbitregbr["[BX+"]="111";sixteenbitregbr[","]="";sixteenbitregbr[""]="";sixteenbitregbr["]"]="";
	
	map<string,string> thirtytwobitregbr;
	thirtytwobitregbr["[EAX+"]="000";thirtytwobitregbr["[ECX+"]="001";thirtytwobitregbr["[EDX+"]="010";thirtytwobitregbr["[EBX+"]="011";thirtytwobitregbr["[ESP+"]="100";thirtytwobitregbr["[EBP+"]="101";thirtytwobitregbr["[ESI+"]="110";thirtytwobitregbr["[EDI+"]="111";thirtytwobitregbr[","]="";thirtytwobitregbr[""]="";thirtytwobitregbr["]"]="";
	
	string ans="",ansreg,ansm;
	int flag=1,j;
	int c=0,modeop;
	string regbin,w,d,sa;
	int mop;
	int regsize=0;
	cout<<"Mode of op"<<endl;
	cin>>modeop;

    istringstream iss(ins);

    do{
        string sub;
        iss >> sub;
        if(c==0){
        	ans=ans+"100010";
        	c++;
        	continue;
		}
		if(c==1){
			if(eightbitreg.count(sub)>=1 || sixteenbitreg.count(sub)>=1 || thirtytwobitreg.count(sub)>=1){
				d="1";
			}
			else{
				d="0";
			}
			ans=ans+d;
			c++;
		}
		if(eightbitreg.count(sub)>=1 && (regsize==0 || regsize==8)){
			if(c==2){
				w="0";
				ans=ans+w;
			}
			regsize=8;
			regbin=eightbitreg[sub];
			ansreg=ansreg+regbin;
			c++;
		}
		else if(sixteenbitreg.count(sub)>=1 && (regsize==0 || regsize==16)){
			if(c==2){
				w="1";
				if(modeop==32){
					mop=1;
				}
				ans=ans+w;
			}
			regsize=16;
			regbin=sixteenbitreg[sub];
			ansreg=ansreg+regbin;
			c++;
		}
		else if(thirtytwobitreg.count(sub)>=1 && (regsize==0 || regsize==32)){
			if(c==2){
				w="1";
				if(modeop==16){
					mop=1;
				}
				ans=ans+w;
			}
			regsize=32;
			regbin=thirtytwobitreg[sub];
			ansreg=ansreg+regbin;
			c++;
		}

		else if(sixteenbitregbr.count(sub)>=1){
			if(c==2){
				w="1";
				ans=ans+w;
			}
			regsize=16;
			regbin=sixteenbitregbr[sub];
			ansm=ansm+regbin;
			c++;
		}
		else if(thirtytwobitregbr.count(sub)>=1){
			if(c==2){
				w="1";
				ans=ans+w;
			}
			regsize=32;
			regbin=thirtytwobitregbr[sub];
			ansm=ansm+regbin;
			c++;
		}
		else{
			if(sub.length()<=2){
				j=0;
			}
			else{
				j=1;
			}
			sa=PrintBinary(sub,16);
		}
    } while (iss);
    
    if(flag==1){
    	if(mop==1){
    		cout<<"01100110 ";
		}
    	ans=ans+" ";
    	if(j==0){
    		ans=ans+"01";
		}
		else{
			ans=ans+"10";
		}
    	ans=ans+ansreg;
    	ans=ans+ansm;
    	ans=ans+" ";
    	ans=ans+sa;
    	cout<<ans;
    	PrintHexaDecimal(ans);
    }
    else{
    	cout<<"Invalid Instruction";
	}
}



int main()
{
	map<string,string> eightbitreg;
	eightbitreg["AL"]="000";eightbitreg["CL"]="001";eightbitreg["DL"]="010";eightbitreg["BL"]="011";eightbitreg["AH"]="100";eightbitreg["CH"]="101";eightbitreg["DH"]="110";eightbitreg["BH"]="111";eightbitreg[","]="";eightbitreg[""]="";
	
	map<string,string> sixteenbitreg;
	sixteenbitreg["AX"]="000";sixteenbitreg["CX"]="001";sixteenbitreg["DX"]="010";sixteenbitreg["BX"]="011";sixteenbitreg["SP"]="100";sixteenbitreg["BP"]="101";sixteenbitreg["SI"]="110";sixteenbitreg["DI"]="111";sixteenbitreg[","]="";sixteenbitreg[""]="";
	
	map<string,string> thirtytwobitreg;
	thirtytwobitreg["EAX"]="000";thirtytwobitreg["ECX"]="001";thirtytwobitreg["EDX"]="010";thirtytwobitreg["EBX"]="011";thirtytwobitreg["ESP"]="100";thirtytwobitreg["EBP"]="101";thirtytwobitreg["ESI"]="110";thirtytwobitreg["EDI"]="111";thirtytwobitreg[","]="";thirtytwobitreg[""]="";
	
	map<string,string> sixteenbitregbr;
	sixteenbitregbr["[BX+SI]"]="000";sixteenbitregbr["[BX+DI]"]="001";sixteenbitregbr["[BP+SI]"]="010";sixteenbitregbr["[BP+DI]"]="011";sixteenbitregbr["[SI+"]="100";sixteenbitregbr["[DI+"]="101";sixteenbitregbr["[BP+"]="110";sixteenbitregbr["[BX+"]="111";sixteenbitregbr[","]="";sixteenbitregbr[""]="";sixteenbitregbr["]"]="";sixteenbitregbr["BYTE_PTR"]="";sixteenbitregbr["WORD_PTR"]="";sixteenbitregbr["DWORD_PTR"]="";sixteenbitregbr["QWORD_PTR"]="";
	
	map<string,string> thirtytwobitregbr;
	thirtytwobitregbr["[EAX+"]="000";thirtytwobitregbr["[ECX+"]="001";thirtytwobitregbr["[EDX+"]="010";thirtytwobitregbr["[EBX+"]="011";thirtytwobitregbr["[ESP+"]="100";thirtytwobitregbr["[EBP+"]="101";thirtytwobitregbr["[ESI+"]="110";thirtytwobitregbr["[EDI+"]="111";thirtytwobitregbr[","]="";thirtytwobitregbr[""]="";thirtytwobitregbr["]"]="";thirtytwobitregbr["BYTE_PTR"]="";thirtytwobitregbr["WORD_PTR"]="";thirtytwobitregbr["DWORD_PTR"]="";thirtytwobitregbr["QWORD_PTR"]="";
	
	map<string,string> sixteenbitregbrr;
	sixteenbitregbrr["[BX+SI+"]="000";sixteenbitregbrr["[BX+DI+"]="001";sixteenbitregbrr["[BP+SI+"]="010";sixteenbitregbrr["[BP+DI+"]="011";sixteenbitregbrr["[SI+"]="100";sixteenbitregbrr["[DI+"]="101";sixteenbitregbrr["[BP+"]="110";sixteenbitregbrr["[BX+"]="111";sixteenbitregbrr[","]="";sixteenbitregbrr[""]="";sixteenbitregbrr["]"]="";
	
	map<string,string> sixteenbitregb;
	sixteenbitregb["[BX+SI]"]="000";sixteenbitregb["[BX+DI]"]="001";sixteenbitregb["[BP+SI]"]="010";sixteenbitregb["[BP+DI]"]="011";sixteenbitregb["[SI]"]="100";sixteenbitregb["[DI]"]="101";sixteenbitregb["[BP]"]="110";sixteenbitregb["[BX]"]="111";sixteenbitregb[","]="";sixteenbitregb[""]="";sixteenbitregb["]"]="";
	
	map<string,string> thirtytwobitregb;
	thirtytwobitregb["[EAX]"]="000";thirtytwobitregb["[ECX]"]="001";thirtytwobitregb["[EDX]"]="010";thirtytwobitregb["[EBX]"]="011";thirtytwobitregb["[ESP]"]="100";thirtytwobitregb["[EBP]"]="101";thirtytwobitregb["[ESI]"]="110";thirtytwobitregb["[EDI]"]="111";thirtytwobitregb[","]="";thirtytwobitregb[""]="";thirtytwobitregb["]"]="";
	
	int modeop,c=0,fl=1;
	string ins;
	
	cout<<"Enter an Instruction :- "<<endl;
	getline(cin,ins);
	int f=-1;
	istringstream iss(ins);
	
    do
    {
    	string sub;
        iss >> sub;
        if((c==1 || c==3) && (f==-1 || f==9 || f==10 || f==1 || f==7 || f==2)){
        	if(eightbitreg.count(sub)>=1 || sixteenbitreg.count(sub)>=1 || thirtytwobitreg.count(sub)>=1){
        		f=1;
        		c++;
        		continue;
			}
			cout<<"In the loop f = "<<f<<endl;
        }
        if((c==1 || c==3) && (f==-1 || f==9 || f==10 || f==1 || f==7 || f==2)){
        	if(c==1){
        		if(eightbitreg.count(sub)>=1 || sixteenbitreg.count(sub)>=1 || thirtytwobitreg.count(sub)>=1){
        			f=2;
        			c++;
        			continue;
				}
			}
			if(c==3){
				for(int z=0;z<sub.length();z++){
					if(!(((sub[z]>='0' && sub[z]<='9') || (sub[z]>='A' && sub[z]<='F')))){
						fl=0;
					}
				}
				if(fl==1){
					f=3;
				}
			}
			cout<<"In the loop f = "<<f<<endl;
        }
        if((c==1 || c==3)&& (f==-1 || f==4)){
        	if(c==1){
        		if(sixteenbitregbr.count(sub)>=1 || thirtytwobitregbr.count(sub)>=1){
        			f=4;
				}
			}
        	if(c==3){
				for(int z=0;z<sub.length();z++){
					if(((sub[z]>='0' && sub[z]<='9') || (sub[z]>='A' && sub[z]<='F')) && f==4){
						f=5;
					}
				}
			}
			cout<<"In the loop f = "<<f<<endl;
		}
		if((c==1 || c==3)&& (f==-1 || f==6)){
			if(sixteenbitregb.count(sub)>=1 || thirtytwobitregb.count(sub)>=1){
				f=6;
			}
			cout<<"In the loop f = "<<f<<endl;
		}
		if(((c==1 || c==3)) && (f==-1 || f==9 || f==10 || f==1 || f==7 || f==2)){
			if(eightbitreg.count(sub)>=1 || sixteenbitreg.count(sub)>=1 || thirtytwobitreg.count(sub)>=1){
        		f=7;
        		c++;
        		continue;
			}
			if(sixteenbitregb.count(sub)>=1 || thirtytwobitregb.count(sub)>=1){
				f=8;
				break;
			}
			cout<<"In the loop f = "<<f<<endl;
		}
		if((c==1 || c==3) && (f==-1 || f==9 || f==10 || f==1 || f==7 || f==2)){
			if(eightbitreg.count(sub)>=1 || sixteenbitreg.count(sub)>=1 || thirtytwobitreg.count(sub)>=1){
        		f=9;
        		c++;
        		continue;
			}
			if(sixteenbitregbrr.count(sub)>=1 || thirtytwobitregbr.count(sub)>=1){
				f=10;
				break;
			}
			cout<<"In the loop f = "<<f<<endl;
		}
    	c++;
    	
    }while(iss);
	
	
	
	
	
	cout<<"\nAddresing Mode:- ";
	
	// We are checking here value of 'f' to know which operation has to perform
	
	cout<<"After loop f = "<<f<<endl;
	
	if(f==1){
		RegisterToRegister(ins);
	}
	else if(f==3){
		RegisterImmediate(ins);
	}
	else if(f==5){
		MemoryImmediate(ins);
	}
	else if(f==6){
		RegisterIndirect(ins);
	}
	else if(f==7 || f==8){
		BasePlusIndex(ins);
	}
	else if(f==9 || f==10){
		RegisterRelative(ins);
	}
    return 0;
}
