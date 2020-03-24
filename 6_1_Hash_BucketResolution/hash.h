/*
author: user
date: 20200317
description: this is a hash function header file
*/

//Modulo hash function
int ModuloHash(int Key, int dataSize){
	//ret = key % dataSize;
	return Key%dataSize;
}
// Digital extraction hash function
int DigitExtractHash(int Key, int dataSize){
	//"123456789" -> extract {3, 6, 9} -> return 369%dataSize;
	int ret=0, seq[2]={1000,1000};
	ret+=Key%10; Key/=seq[0];
	ret+=(Key%10)*10; Key/=seq[1];
	ret+=(Key%10)*100;
	ret%=dataSize;
	return ret;
}
// Midsquare hash function
int MidSqrHash(int Key, int dataSize){
	//key="123456789" -> key="3456789"-> sqr: key=key*key -> "12345|678|91234" chose"567" -> return key%dataSize;
	unsigned long long int ret=Key%10000000;
	ret*=ret;
	ret/=100000;
	ret%=1000;
	ret%=dataSize;
	return (int)ret;
}
// folding hash function
int FoldHash(int Key, int dataSize){
	//"123456789" -> fold {123, 456, 789} -> return (123+456+789)%dataSize;
	int ret=0;
	ret+=Key%1000; Key/=1000;
	ret+=Key%1000; Key/=1000;
	ret+=Key%1000;
	ret%=dataSize;
	return ret;
}
// Rotation hase function
int RotateHash(int Key, int dataSize){
	//"123456789" -> rotate "891234567" -> return "891234567"%dataSize;
	int ret=0;
	ret=Key%100;
	Key/=100;
	Key+=ret*10000000;
	ret=Key;
	ret%=dataSize;
	return ret;
}
// Pseudorandom hase function
int PseuRandHash(int Key, int dataSize){
	// x = Key%10000000;
	// f(x)= ( 3*x*x + 173*x ) % dataSize;
	unsigned long long int ret=Key%10000000;
	int seq[2]={3,173};
	ret=seq[0]*ret*ret + seq[1]*ret;
	ret%=dataSize;
	return (int)ret;
}

