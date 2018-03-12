#include<iostream>
#include<cstring>
using namespace std;
int P10[]={3,5,2,7,4,10,1,9,8,6};
int P8[] ={6,3,7,4,8,5,10,9};
int P4[] ={2,4,3,1};
int IP[] ={2,6,3,1,4,8,5,7};
int IPI[]={4,1,3,5,7,2,8,6};
int EP[] ={4,1,2,3,2,3,4,1};
int S0[][4]={
	{1,0,3,2},
	{3,2,1,0},
	{0,2,1,3},
	{3,1,3,2},
};
int S1[][4]={
	{0,1,2,3},
	{2,0,1,3},
	{3,0,1,0},
	{2,1,0,3},
};
string ciphertext="11010100"; 
string key="0111111101";
string k1,k2;//定义两个子密钥 
int getNum(string str){
	if(str=="11")
		return 3;
	else if(str=="10")
		return 2;
	else if(str=="01")
		return 1;
	else
		return 0;
}
string getBinary(int num){
	switch(num){
		case 3:
			return "11";
		case 2:
			return "10";
		case 1:
			return "01";
		case 0:
			return "00"; 
	}
}
string P10Swap(string key){//P10置换 
	string t;
	for(int i=0;i<10;i++)
		t+=key[P10[i]-1];
	return t;
}
string P8Swap(string key){//P8置换 
	string t;
	for(int i=0;i<8;i++)
		t+=key[P8[i]-1];
	return t;
}
string P4Swap(string key){//P4置换 
	string t;
	for(int i=0;i<4;i++)
		t+=key[P4[i]-1];
	return t;
}
string rsl(string s,int offset){//循环左移
	string t;
	t=s.substr(offset)+s.substr(0,offset);
	return t;
}
string IPSwap(string key){//IP置换 
	string t;
	for(int i=0;i<8;i++)
		t+=key[IP[i]-1];
	return t;
}
string IPISwap(string key){//IP逆置换 
	string t;
	for(int i=0;i<8;i++)
		t+=key[IPI[i]-1];
	return t;
}
string EPSwap(string key){//EP置换 
	string t;
	for(int i=0;i<8;i++)
		t+=key[EP[i]-1];
	return t;
}
string XOR(string key1,string key2){//异或
	string t;
	for(int i=0;i<key1.length();i++){
		if(key1[i]!=key2[i])
			t+='1';
		else
			t+='0';
	}
	return t;
}
string S0Swap(string key){
	string row,col;
	row+=key[0];
	row+=key[3];
	col+=key[1];
	col+=key[2];
	return getBinary(S0[getNum(row)][getNum(col)]);
}
string S1Swap(string key){
	string row,col;
	row+=key[0];
	row+=key[3];
	col+=key[1];
	col+=key[2];
	return getBinary(S1[getNum(row)][getNum(col)]);
}
string Swap(string key){
	return key.substr(4)+key.substr(0,4);
}
string fk(string m,string subkey){//fk函数 
	string epR=EPSwap(m.substr(4));
	string xorResult=XOR(epR,subkey);
	string result=S0Swap(xorResult.substr(0,4))+S1Swap(xorResult.substr(4));//得到的四位输出
	return XOR(P4Swap(result),m.substr(0,4))+m.substr(4);
}
int main(){
	//步骤1、获取子密钥 
    string t0=P10Swap(key);
    string t1=rsl(t0.substr(0,5),1)+rsl(t0.substr(5),1);//高低位循环左移一位并合并 
	k1=P8Swap(t1);//子密钥K1
	string t2=rsl(t1.substr(0,5),2)+rsl(t1.substr(5),2); //高低位循环左移两位并合并
	k2=P8Swap(t2);//子密钥K2
	cout<<"子密钥k1："<<k1<<endl<<"子密钥k2："<<k2<<endl;
	//步骤2、第一轮fk函数
	string m=IPSwap(ciphertext);
	string fk1Result=fk(m,k2);
	cout<<"第一轮fk函数结果："<<fk1Result<<endl;
	string afterSwap=Swap(fk1Result);
	string fk2Result=fk(afterSwap,k1);
	cout<<"第二轮fk函数结果："<<fk2Result<<endl;
	cout<<"最终得到的密文为："<<IPISwap(fk2Result)<<endl;
}
