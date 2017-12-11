#include<iostream>
#include<sstream>
#include<fstream>
#include<algorithm>
#include<string>
#include<vector>
#include<map>
using namespace std;

/************** Symbol Table *************/
typedef struct st1{
	string symbol;
	string address;
	int linenumber;
} SymbolTable;

/*********** Global Variables ***********/
vector<SymbolTable> st;
vector<int> LabelTable;
bool error=0;
int model=0;
int LineCount=0;
int mod;
string LC;
map<string,string> eightbitreg;
map<string,string> sixteenbitreg;
map<string,string> thirtytwobitreg;
map<string,string> hex1;
map<char,string> disp;


/****************** Displacement ********************/
string Displacement(string str,int regsize){	
	string s="";
	char c;
	int l=str.length();
	if(regsize==16)
	{
		if(l==1)
		{
			s=s+disp['0'];
			c=str[0];
			s=s+disp[c];
			s=s+" ";
			s=s+disp['0'];
			s=s+disp['0'];
		}
		else if(l==2)
		{
			c=str[0];
			s=s+disp[c];
			c=str[1];
			s=s+disp[c];
			s=s+" ";
			s=s+disp['0'];
			s=s+disp['0'];
		}
		else if(l==3)
		{
			s=s+disp[str[1]];
			s=s+disp[str[2]];
			s=s+" ";
			s=s+disp['0'];
			s=s+disp[str[0]];
		}
		else if(l>=4)
		{
			s=s+disp[str[2]];
			s=s+disp[str[3]];
			s=s+" ";
			s=s+disp[str[0]];
			s=s+disp[str[1]];
		}
	}
	else if(regsize==32)
	{
		if(l==1)
		{
			s=s+disp['0'];
			c=str[0];
			s=s+disp[c];
			s=s+" ";
			s=s+disp['0'];
			s=s+disp['0'];
			s=s+" ";
			s=s+disp['0'];
			s=s+disp['0'];
			s=s+" ";
			s=s+disp['0'];
			s=s+disp['0'];
		}
		else if(l==2)
		{
			c=str[0];
			s=s+disp[c];
			c=str[1];
			s=s+disp[c];
			s=s+" ";
			s=s+disp['0'];
			s=s+disp['0'];
			s=s+" ";
			s=s+disp['0'];
			s=s+disp['0'];
			s=s+" ";
			s=s+disp['0'];
			s=s+disp['0'];
		}
		else if(l==3)
		{
			s=s+disp[str[1]];
			s=s+disp[str[2]];
			s=s+" ";
			s=s+disp['0'];
			s=s+disp[str[0]];
			s=s+" ";
			s=s+disp['0'];
			s=s+disp['0'];
			s=s+" ";
			s=s+disp['0'];
			s=s+disp['0'];
		}
		else if(l==4)
		{
			s=s+disp[str[2]];
			s=s+disp[str[3]];
			s=s+" ";
			s=s+disp[str[0]];
			s=s+disp[str[1]];
			s=s+" ";
			s=s+disp['0'];
			s=s+disp['0'];
			s=s+" ";
			s=s+disp['0'];
			s=s+disp['0'];
		}
		else if(l>=8)
		{
			s=s+disp[str[6]];
			s=s+disp[str[7]];
			s=s+" ";
			s=s+disp[str[4]];
			s=s+disp[str[5]];
			s=s+" ";
			s=s+disp[str[2]];
			s=s+disp[str[3]];
			s=s+" ";
			s=s+disp[str[0]];
			s=s+disp[str[1]];
		}
	}
	else if(regsize==8)
	{
		if(l==1)
		{
			s=s+disp['0'];
			s=s+disp[str[0]];
		}
		else if(l==2)
		{
			s=s+disp[str[0]];
			s=s+disp[str[1]];
		}
			else if(l==3)
		{
			s=s+disp['0'];
			s=s+disp[str[2]];
		}
		else if(l>=4)
		{
			s=s+disp[str[2]];
			s=s+disp[str[3]];
		}
	}
	return s;
}

/*************** Decimal to Binary ***************/
string binary(int num){
    int rem,sum=0,i=1;
    string s="";
    string temp;
    do{
        rem=num%2;
        temp=to_string(rem);
        s+=temp;
        sum=sum + (i*rem);
        num=num/2;
        i=i*10;
    }while(num>0); 
    return s;
}
 
/************ Location Counter ******************/
string create_address(string temp){
	int l=temp.length();
	string s="";
	for(int i=l;i<16;i++){
		if(i%8==0)
		temp+=" ";
		temp+="0";
	}
	reverse(temp.begin(),temp.end());
//	cout<<temp;
	return temp;
}

/************** FORWARD REFERENCE **************/
string Forward(string s,string lc){
	int sum1=0,sum2=0;
	int j=16;
	while(j>=0){
		if(s[j]!=' '){
			int t=s[j]-'0';
			sum1+=t*pow(2,16-j);
			int t1=lc[j]-'0';
			sum2+=t1*pow(2,16-j);
		}
		j--;
	}
	sum1=sum1-sum2-3;
	string p=create_address(binary(sum1));
	return p;
}

/****************** PASS 2 ******************/
string Pass2(string temp){
	int l=temp.length();
	int j=0,i=l-1;
	bool done=0;
	string s="",tlc="";
	int z=0;
	while(temp[z]!=' '){
		z++;
	}
	z++;
	for(int zz=z;zz<17+z;zz++){
		tlc+=temp[zz];
	}
	while(temp[i]!=' '){
		s+=temp[i];
		i--;
	}
	reverse(s.begin(),s.end());
	temp.resize(i);
	while( j<st.size() && !done){
		if(s==st[j].symbol){
			done=1;
		}
		else
		j++;
	}
	if(done){
		return temp +" "+ Forward(st[j].address,tlc);
	}
	else{
		return "";
	}
}

/************** BACKWARD REFERENCE ************/
string Backward(string s){
	int sum1=0,sum2=0;
	int j=16;
	while(j>=0){
		if(s[j]!=' '){
			int t=s[j]-'0';
			sum1+=t*pow(2,16-j);
			int t1=LC[j]-'0';
			sum2+=t1*pow(2,16-j);
		}
		j--;
	}
	sum1=(sum2+3)-sum1;
	string p=create_address(binary(sum1));
	j=16;
	bool carry=1;
	while(j>=0){
		if(p[j]!=' '){
			if(p[j]=='0'){
				p[j]='1';
			}
			else{
				p[j]='0';
			}		
		}
		j--;
	}

	j=16;
	while(j>=0){
		if(p[j]!=' '){
			if(p[j]=='0'){
				if(carry){
					p[j]='1';
					carry=0;	
				}
			}
			else{
				if(carry)
				p[j]='0';
			}		
		}
		j--;
	}
	return p;
}

/****************** Jump *******************/
string Jmp(vector<string>& v){
	//for(int i=0;i<v.size();i++)
	//	cout<<v[i]<<" ";
	bool done=0;
	int i=0;
	while(i!=st.size() && !done){
		if(v[1]==st[i].symbol){
			done=1;
		}
		else
		i++;
	}
	if(done){
		return "11101001 "+Backward(st[i].address);
	}
	else{
		LabelTable.push_back(LineCount-1);
		return "11101001 "+v[1];
	}
		
}

/****************** Immediate Displacement **************/
string ImmediateAddition(vector<string>& v){
	string ans="";
	int l=v[2].length();
	if(eightbitreg.count(v[1])>=1){
		ans+="1000001";
		ans+="0 ";
		ans+="00000";
		ans+=eightbitreg[v[1]];
		ans+=" ";
		ans+=Displacement(v[2],8);
	}
	else if(sixteenbitreg.count(v[1])>=1){
		if(mod==2){
			ans="01100110 ";
		}
		ans+="1000001";
		ans+="1 ";
		ans+="00000";
		ans+=sixteenbitreg[v[1]];
		ans+=" ";
		ans+=Displacement(v[2],16);
	}
	else if(thirtytwobitreg.count(v[1])>=1){
		if(mod==1){
			ans="01100110 ";
		}
		ans+="1000001";
		ans+="1 ";
		ans+="00000";
		ans+=thirtytwobitreg[v[1]];
		ans+=" ";
		ans+=Displacement(v[2],32);
	}
	return ans;
}

/*****************REGISTER ADDITION*****************/
string RegisterAddition(vector<string>& v){
	string ans="0000001";
	if(eightbitreg.count(v[1])>=1 && (eightbitreg.count(v[2])>=1)){
		ans+="0";
		ans+=" 00";		
		ans+=eightbitreg[v[1]];
		ans+=eightbitreg[v[2]];
	}
	else if(sixteenbitreg.count(v[1])>=1 && sixteenbitreg.count(v[2])>=1){
	 	ans+="1";
	 	if(mod==1){
	 		ans+=" 00";
			ans+=sixteenbitreg[v[1]];
			ans+=sixteenbitreg[v[2]];	
		}
		else{
			string s="01100110 ";
			s+=ans;
			ans=s;
			ans+=" 00";
			ans+=sixteenbitreg[v[1]];
			ans+=sixteenbitreg[v[2]];
		}
	}
	else if(thirtytwobitreg.count(v[1])>=1 && thirtytwobitreg.count(v[2])>=1){
	 	ans+="1";
	 	if(mod==2){
	 		ans+=" 00";
			ans+=thirtytwobitreg[v[1]];
			ans+=thirtytwobitreg[v[2]];	
		}
		else{
			string s="01100110 ";
			s+=ans;
			ans=s;
			ans+=" 00";
			ans+=thirtytwobitreg[v[1]];
			ans+=thirtytwobitreg[v[2]];
		}
	}
	return ans;
}

/**************** ADDITION ****************/
string Add(vector<string> &v){
	string ans="";
	//for(int i=0;i<v.size();i++)
	//cout<<v[i]<<" ";	
	if((eightbitreg.count(v[1])>=1 && eightbitreg.count(v[2])>=1) || (sixteenbitreg.count(v[1])>=1 && sixteenbitreg.count(v[2])>=1) || (thirtytwobitreg.count(v[1])>=1 && thirtytwobitreg.count(v[2])>=1))
	{		
		ans=RegisterAddition(v);
	}
	else{
		ans=ImmediateAddition(v);
	}
	return ans;
}

/******************* RegisterImmediate ******************/
string RegisterImmediate(vector<string>& v){
	string ans="";
	int l=v[2].length();
	if(eightbitreg.count(v[1])>=1){
		ans+="1011";
		ans+=eightbitreg[v[1]];
		ans+="0 ";
		ans+=Displacement(v[2],8);
	}
	else if(sixteenbitreg.count(v[1])>=1){
		if(mod==2){
			ans="01100110 ";
		}
		ans+="1011";
		ans+=sixteenbitreg[v[1]];
		ans+="1 ";
		ans+=Displacement(v[2],16);
	}
	else if(thirtytwobitreg.count(v[1])>=1){
		if(mod==1){
			ans="01100110 ";
		}
		ans+="1011";
		ans+=thirtytwobitreg[v[1]];
		ans+="1 ";
		ans+=Displacement(v[2],32);
	}
	return ans;
}

/************** RegisterToRegister ***************/
string RegisterToRegister(vector<string>& v){
	string ans="1000101";
	if(eightbitreg.count(v[1])>=1 && (eightbitreg.count(v[2])>=1)){
		ans+="0";
		ans+=" 11";		
		ans+=eightbitreg[v[1]];
		ans+=eightbitreg[v[2]];
	}
	else if(sixteenbitreg.count(v[1])>=1 && sixteenbitreg.count(v[2])>=1){
	 	ans+="1";
	 	if(mod==1){
	 		ans+=" 11";
			ans+=sixteenbitreg[v[1]];
			ans+=sixteenbitreg[v[2]];	
		}
		else{
			string s="01100110 ";
			s+=ans;
			ans=s;
			ans+=" 11";
			ans+=sixteenbitreg[v[1]];
			ans+=sixteenbitreg[v[2]];
		}
	}
	else if(thirtytwobitreg.count(v[1])>=1 && thirtytwobitreg.count(v[2])>=1){
	 	ans+="1";
	 	if(mod==2){
	 		ans+=" 11";
			ans+=thirtytwobitreg[v[1]];
			ans+=thirtytwobitreg[v[2]];	
		}
		else{
			string s="01100110 ";
			s+=ans;
			ans=s;
			ans+=" 11";
			ans+=thirtytwobitreg[v[1]];
			ans+=thirtytwobitreg[v[2]];
		}
	}
	return ans;
}

/************** MOVE Operation **************/
string Move(vector<string>& v){
	string ans="";
//	for(int i=0;i<v.size();i++)
//	cout<<v[i]<<" ";	
	if((eightbitreg.count(v[1])>=1 && eightbitreg.count(v[2])>=1) || (sixteenbitreg.count(v[1])>=1 && sixteenbitreg.count(v[2])>=1) || (thirtytwobitreg.count(v[1])>=1 && thirtytwobitreg.count(v[2])>=1))
	{		
		ans=RegisterToRegister(v);
	}
	else{
		ans=RegisterImmediate(v);
	}
	return ans;
}

/*************** Machine Operations ***************/
string Machine_ops(string check,vector<string>& v){
	string s;
	if(check=="MOV"){
		s=Move(v);
		return s;
	}
	else if(check=="ADD"){
		s=Add(v);
		return s;
	}
	else if(check=="JMP"){
		s=Jmp(v);
		return s;
	}
	else{
		return "";
	}	
}

/**************** Convert_to_Machine ***************/
string Convert_to_Machine(vector<string>& ins){
	string s=Machine_ops(ins[0],ins);
	if(s==""){
		error=1;
		return "";
	}	
	else{
		model=0;
		return s;	
	}
}

/**************** Split Function *****************/
vector<string> Split(string line){
	vector<string> temp;
	string s="";
	int i=0,j=0;
	while(line[i]==' '){
		i++;
	}
	if(i==0){
		while(line[i]!=':'){
			s+=line[i];
			i++;
		}
		SymbolTable s1;
		s1.symbol=s;
		s1.address=LC;
		s1.linenumber=LineCount;
		st.push_back(s1);
		s="";
		i++;
	}
	while(line[i]!='\0'){
		if(line[i]==' '||line[i]==','){
			temp.push_back(s);j++;s="";
		}
		else
		s+=line[i];
		i++;
	}
	if(!s.empty()){
		temp.push_back(s);j++;
	}
	return temp;
}

/****************  Print  ***************/
string pri(string ans){
	string s="",final="";
	int i=0,c=0;
	while(ans[i]!=' ')
		i++;
	for(;i<ans.length();i=i+4){
		c++;
		s="";
		while(ans[i]==' '){
			i++;
		}
		for(int j=i;j<=i+3;j++){
			s=s+ans[j];
		}
		final+=hex1[s];
		if(c%2==0 && c!=2){
			final+=" ";
		}
	}
	return final;
}

/***************** MAIN FUNCTION *****************/
int main(){
	vector<string> temp;
	/********* Initializing Maps   **************/
	{
		eightbitreg["AL"]="000";eightbitreg["CL"]="001";eightbitreg["DL"]="010";eightbitreg["BL"]="011";eightbitreg["AH"]="100";eightbitreg["CH"]="101";eightbitreg["DH"]="110";eightbitreg["BH"]="111";eightbitreg[","]="";eightbitreg[""]="";
		sixteenbitreg["AX"]="000";sixteenbitreg["CX"]="001";sixteenbitreg["DX"]="010";sixteenbitreg["BX"]="011";sixteenbitreg["SP"]="100";sixteenbitreg["BP"]="101";sixteenbitreg["SI"]="110";sixteenbitreg["DI"]="111";sixteenbitreg[","]="";sixteenbitreg[""]="";
		thirtytwobitreg["EAX"]="000";thirtytwobitreg["ECX"]="001";thirtytwobitreg["EDX"]="010";thirtytwobitreg["EBX"]="011";thirtytwobitreg["ESP"]="100";thirtytwobitreg["EBP"]="101";thirtytwobitreg["ESI"]="110";thirtytwobitreg["EDI"]="111";thirtytwobitreg[","]="";thirtytwobitreg[""]="";
		hex1["0000"]="0";hex1["0001"]="1";hex1["0010"]="2";hex1["0011"]="3";hex1["0100"]="4";hex1["0101"]="5";hex1["0110"]="6";hex1["0111"]="7";hex1["1000"]="8";hex1["1001"]="9";hex1["1010"]="A";hex1["1011"]="B";hex1["1100"]="C";hex1["1101"]="D";hex1["1110"]="E";hex1["1111"]="F";
		disp['0']="0000";disp['1']="0001";disp['2']="0010";disp['3']="0011";disp['4']="0100";disp['5']="0101";disp['6']="0110";disp['7']="0111";disp['8']="1000";disp['9']="1001";disp['A']="1010";disp['B']="1011";disp['C']="1100";disp['D']="1101";disp['E']="1110";disp['F']="1111";
	}
	
	//     main function    //
	string nextline,ans,address;
	int countbyte=0;
	mod=1;
	ifstream imp( "main.txt" );
	ofstream opt1;
	opt1.open("output1.txt");
	
	if(imp.is_open()){
		while(getline(imp,nextline) && !error){	
			address=create_address(binary(countbyte));
			LC=address;
			LineCount++;
			cout<<" ";
			temp=Split(nextline);
			
			if(temp[0]==".EXIT" || temp[0]=="END"){
				break;
			}		
			if(temp[0]==".MODEL"){
				LineCount--;
				continue;
			}
			
			// FOR .DATA SECTION //
			
			if(temp[0]==".DATA"){
				while(getline(imp,nextline) && !error){
					int i=0,j=0;
					string s="";
					while(nextline[i]==' '){
						i++;
					}
					if(i!=0){
						temp=Split(nextline);
						break;
					}
					while(nextline[i]!=':'){
						s+=nextline[i];
						i++;
					}
					vector<string> temp1;
					SymbolTable s1;
					s1.symbol=s;
					s="";
					while(nextline[i]!='\0'){
						if(nextline[i]==' '){
							temp1.push_back(s);s="";
						}
						else
						s+=nextline[i];
						i++;
					}
					if(!s.empty()){
						temp1.push_back(s);
					}
					string diss;
					if(temp1.size()==2){
						if(temp1[0]==":DB"){
							countbyte+=1;
							diss=Displacement(temp1[1],8);
						}
						if(temp1[0]==":DW"){
							countbyte+=2;
							diss=Displacement(temp1[1],16);
						}
						if(temp1[0]==":DD"){
							countbyte+=4;
							diss=Displacement(temp1[1],32);
						}
						if(temp1[0]==":DQ"){
							countbyte+=8;
							diss=Displacement(temp1[1],32);
						}
					}		
					opt1<<LineCount;
					opt1<<" ";
					opt1<<address;
					opt1<<" ";
			//		cout<<endl;
					opt1<<diss;
					opt1<<"\n";
					s1.address=LC;
					s1.linenumber=LineCount;
					st.push_back(s1);
					LineCount++;
					address=create_address(binary(countbyte));
					LC=address;
				}	
			}
			if(temp[0]==".CODE" || temp[0]==".STARTUP"){
				LineCount--;
				countbyte=0;
				continue;
			}
		
			// FOR .CODE SECTION //
		
			ans=Convert_to_Machine(temp);
			opt1<<LineCount;
			opt1<<" ";
			opt1<<address;
			opt1<<" ";
		//	cout<<endl;
			countbyte+=(ans.length()+1)/9;
			opt1<<ans;
			opt1<<"\n";
		
		}
		imp.close();
		opt1.close();
		
		
	
		// pass 2 //
		
		
		if(!error){
			ifstream opt11( "output1.txt" );
			ofstream opt2;
			opt2.open("output2.txt");
			ofstream opt3;
			opt3.open("output21.txt");
			int k=0,m=0;
			while(getline(opt11,nextline)){
				if(m==LabelTable.size()){
					break;
				}
				if(m<LabelTable.size() && k<LabelTable[m]){
					opt2<<nextline;
					opt3<<pri(nextline);
					k++;
				}
				else{
					string s;
					s=Pass2(nextline);
					opt2<<s;
					opt3<<pri(s);
					m++;
					k++;
				}
				opt2<<"\n";
				opt3<<"\n";
			}
			do{
				opt2<<nextline;
				opt3<<pri(nextline);
				opt2<<"\n";
				opt3<<"\n";
			}while(getline(opt11,nextline));
			opt11.close();
			opt2.close();
			opt3.close();
		}	
		if(error){
			cout<<"Error at Line "<<LineCount<<".\nCan not Process furthur! :(";
		}
		if(!error){
			cout<<"\n\nSymbol Table :\n"<<"\n    Line Number\t"<<"      Address"<<"\t   "<<"    Symbol"<<endl;
			for(int i=0;i<st.size();i++){
				cout<<"\t"<<st[i].linenumber<<"\t\t"<<pri(st[i].address)<<"\t\t"<<st[i].symbol<<endl;
			}		
		}
	}
	else
	cout<<"\n\n\tTry Again...\n\n";
	return 0;
}
