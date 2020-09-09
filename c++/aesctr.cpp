#include "Debug\check C++\aes.h"
#include "Debug\check C++\cryptlib.h"
#include "Debug\check C++\filters.h"
#include "Debug\check C++\osrng.h"
#include "Debug\check C++\hex.h"
#include "Debug\check C++\modes.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <string.h>
#include<fstream>
#include <cstdlib> 
#include <ctime> 
using namespace std;
using namespace CryptoPP;
using CryptoPP::AutoSeededRandomPool;
using CryptoPP::StringSink;
using CryptoPP::StreamTransformation;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::AES;
using CryptoPP::ECB_Mode;//�̪쬰ECB mode�A��²�檩��
//1.Initialization of key data
int K;
void InitKey(byte* key, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		K = rand();
		key[i] = (CryptoPP::byte)K;
	}
}
int main()
{
	string plainText = "";
	string encText1 = "";
	string decText = "";
	string encText2 = "";
	for (int i = 0; i < 2; i++)
	{
		//Initialize common key and IV with appropriate values
		byte key[CryptoPP::AES::DEFAULT_KEYLENGTH];
		byte iv[CryptoPP::AES::BLOCKSIZE];
		// Initialize common key and IV with appropriate values
		srand(time(NULL));
		InitKey(key, sizeof(key));
		InitKey(iv, sizeof(iv));
		cout << "�A�Q��ܭ��ؼҦ�?" << endl;//add
		cout << "�p�G�A�Q���CTR-mode�п�J�Ʀr1�A�p�G�A�Q���CBC-mode�п�J�Ʀr2" << endl;//add
		int choose;//add
		cin >> choose;//add
		cin.get();
		ifstream inFile("plaintext.txt");
		plainText = "";
		getline(inFile, plainText);
		if (choose == 1)//add
		{
			cout << "�ѱK�e������ :" << plainText << endl;//�ѱK�e������
			//Create an encrypted object
			CryptoPP::CTR_Mode<CryptoPP::AES>::Encryption enc;
			enc.SetKeyWithIV(key, sizeof(key), iv);
			encText1="";
			CryptoPP::StreamTransformationFilter encFilter(enc, new CryptoPP::StringSink(encText1));
			// encryption
			encFilter.Put(reinterpret_cast<const byte*>(plainText.c_str()), plainText.size());
			encFilter.MessageEnd();
			/*cout << sizeof(encText) << endl;
			cout << encText.size() << endl;*/
			cout << "�[�K�����K�� �G";
			for (int i = 0; i < encText1.size(); i++) {

				cout << "0x" << hex << (0xFF & static_cast<byte>(encText1[i])) << " ";
			}
			cout << endl;
			CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption dec;
			dec.SetKeyWithIV(key, sizeof(key), iv);

			//Creation of conversion filter for decryption
			decText="";
			CryptoPP::StreamTransformationFilter decFilter(dec, new CryptoPP::StringSink(decText));
			decFilter.Put(reinterpret_cast<const byte*>(encText1.c_str()), encText1.size());
			decFilter.MessageEnd();

			cout << "�ѱK�᪺���� �G" << decText << endl;//�ѱK�᪺����
		}
		else if (choose == 2)//add
		{
			cout << "�ѱK�e������ :" << plainText << endl;//�ѱK�e������
			CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption enc;
			enc.SetKeyWithIV(key, sizeof(key), iv);
			encText2="";
			CryptoPP::StreamTransformationFilter encFilter(enc, new CryptoPP::StringSink(encText2));
			// encryption
			encFilter.Put(reinterpret_cast<const byte*>(plainText.c_str()), plainText.size());
			encFilter.MessageEnd();
			//cout << encText2.size() << endl;
			cout << "�[�K�����K�� �G";
			for (int i = 0; i < encText2.size(); i++) {

				cout << "0x" << hex << (0xFF & static_cast<byte>(encText2[i])) << " ";
			}
			cout << endl;
			CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption dec;
			dec.SetKeyWithIV(key, sizeof(key), iv);

			//Creation of conversion filter for decryption
			decText="";
			CryptoPP::StreamTransformationFilter decFilter(dec, new CryptoPP::StringSink(decText));
			decFilter.Put(reinterpret_cast<const byte*>(encText2.c_str()), encText2.size());
			decFilter.MessageEnd();

			cout << "�ѱK�᪺���� �G" << decText << endl;//�ѱK�᪺����
		}
		inFile.close();
		cout << endl;
	}
		
	/*
	//Initialize common key and IV with appropriate values
	byte key[CryptoPP::AES::DEFAULT_KEYLENGTH];
	byte iv[CryptoPP::AES::BLOCKSIZE];

	// Initialize common key and IV with appropriate values
	InitKey(key, sizeof(key));
	InitKey(iv, sizeof(iv));
	cout << "which mode do you want to choose?" << endl;//add
	cout << "�p�G�A�Q���CTR-mode�п�J�Ʀr1.�p�G�A�Q���CBC-mode�п�J�Ʀr2." << endl;//add
	int choose;//add
	cin >> choose;//add
	if (choose == 1)//add
	{
		string plainText = "hello,i'm annie .this is the CTR-mode which you choose";//AES in Crypto++,Areej Qasrawi//CBC�h��峹�אּthis is AES-CBC
		cout << "�ѱK�e������ : " << plainText << endl;
		//Create an encrypted object
		CryptoPP::CTR_Mode<CryptoPP::AES>::Encryption enc;//CBC�Nmode�אּCBC_Mode
		enc.SetKeyWithIV(key, sizeof(key), iv);
		string encText;
		CryptoPP::StreamTransformationFilter encFilter(enc, new CryptoPP::StringSink(encText));

		// encryption
		encFilter.Put(reinterpret_cast<const byte*>(plainText.c_str()), plainText.size());
		encFilter.MessageEnd();

		cout << "�[�K�����K��G " << encText << endl;
		CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption dec;//CBC�Nmode�אּCBC_Mode
		dec.SetKeyWithIV(key, sizeof(key), iv);

		//Creation of conversion filter for decryption
		string decText;
		CryptoPP::StreamTransformationFilter decFilter(dec, new CryptoPP::StringSink(decText));
		decFilter.Put(reinterpret_cast<const byte*>(encText.c_str()), encText.size());
		decFilter.MessageEnd();

		cout << "�ѱK�᪺����G " << decText << endl;
	}
	else if (choose == 2)//add
	{
		string plainText = "hello,i'm annie .this is the CBC-mode that you choose";//AES in Crypto++,Areej Qasrawi//CBC�h��峹�אּthis is AES-CBC
		cout << "�ѱK�e������ : " << plainText << endl;
		//Create an encrypted object
		CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption enc;//CBC�Nmode�אּCBC_Mode
		enc.SetKeyWithIV(key, sizeof(key), iv);
		string encText;
		CryptoPP::StreamTransformationFilter encFilter(enc, new CryptoPP::StringSink(encText));

		// encryption
		encFilter.Put(reinterpret_cast<const byte*>(plainText.c_str()), plainText.size());
		encFilter.MessageEnd();

		cout << "�[�K�����K��G " << encText << endl;
		CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption dec;//CBC�Nmode�אּCBC_Mode
		dec.SetKeyWithIV(key, sizeof(key), iv);

		//Creation of conversion filter for decryption
		string decText;
		CryptoPP::StreamTransformationFilter decFilter(dec, new CryptoPP::StringSink(decText));
		decFilter.Put(reinterpret_cast<const byte*>(encText.c_str()), encText.size());
		decFilter.MessageEnd();

		cout << "�ѱK�᪺����G" << decText << endl;
	}*/
	/*string plainText = "hello,i'm annie .this is the mode which you choose";//AES in Crypto++,Areej Qasrawi//CBC�h��峹�אּthis is AES-CBC
	cout << "Plain Text : " << plainText << endl;
	//Create an encrypted object
	CryptoPP::CTR_Mode<CryptoPP::AES>::Encryption enc;//CBC�Nmode�אּCBC_Mode
	enc.SetKeyWithIV(key, sizeof(key), iv);
	string encText;
	CryptoPP::StreamTransformationFilter encFilter(enc, new CryptoPP::StringSink(encText));

	// encryption
	encFilter.Put(reinterpret_cast<const byte*>(plainText.c_str()), plainText.size());
	encFilter.MessageEnd();

	cout << "Encrypted Text : " << encText << endl;
	CryptoPP::CTR_Mode<CryptoPP::AES>::Decryption dec;//CBC�Nmode�אּCBC_Mode
	dec.SetKeyWithIV(key, sizeof(key), iv);

	//Creation of conversion filter for decryption
	string decText;
	CryptoPP::StreamTransformationFilter decFilter(dec, new CryptoPP::StringSink(decText));
	decFilter.Put(reinterpret_cast<const byte*>(encText.c_str()), encText.size());
	decFilter.MessageEnd();

	cout << "Decrypted Text : " << decText << endl;*/

	system("PAUSE");
}