#include "stdafx.h"
#include <iostream>
#include <istream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include "..\CryptoPP\cryptlib.h"
#include "..\CryptoPP\osrng.h"
#include "..\CryptoPP\filters.h"
#include "..\CryptoPP\sha.h"
#include "..\CryptoPP\md5.h"
#include "..\CryptoPP\files.h"
#include "..\CryptoPP\hex.h"
#include "..\CryptoPP\modes.h"
#include "..\CryptoPP\aes.h"
#include "..\CryptoPP\hmac.h"
#include "..\CryptoPP\secblock.h"
#include "..\CryptoPP\pwdbased.h"

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

using namespace std;
using namespace this_thread;
using namespace chrono;
using namespace CryptoPP;

// Function to generate a random string (0-9, A-Z, a-z) with user specified length
string generate_random_string(size_t length) {
	auto randchar = []() -> char
	{
		const char charset[] =
			"0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	string str(length, 0);
	generate_n(str.begin(), length, randchar);
	return str;
}

//Function to generate main menu of the program
void generate_menu() {
	cout << "------------------------------ AES Protocol Maker ------------------------------" << endl;
	cout << endl;
	cout << "What would you like to do? (Press x to exit)" << endl;
	cout << "\t1. Complex AES" << endl;
}

//Function to append mac code to key and use hmac prf to key
template<class T>
void hmac_append(const string& password, SecByteBlock& encKey, SecByteBlock& akey,
				 SecByteBlock& tb, SecByteBlock& tm, SecByteBlock& ts, PKCS5_PBKDF2_HMAC<T>& derive,
				 unsigned int iterations) {
	string master = "password";
	SecByteBlock master_AddBlock = SecByteBlock((const byte*)master.data(), master.size());
	tb = master_AddBlock + SecByteBlock((const byte*)password.data(), password.size());
	derive.DeriveKey(tm, tm.size(), 0, tb, tb.size(), ts, ts.size(), iterations);
	string encrypt = "encrypt_key";
	SecByteBlock encrypt_AddBlock = SecByteBlock((const byte*)encrypt.data(), encrypt.size());
	tb = encrypt_AddBlock + tm;
	derive.DeriveKey(encKey, encKey.size(), 0, tb, tb.size(), ts, ts.size(), iterations);
	string auth = "auth_key";
	SecByteBlock auth_AddBlock = SecByteBlock((const byte*)auth.data(), auth.size());
	tb = auth_AddBlock + tm;
	derive.DeriveKey(akey, akey.size(), 0, tb, tb.size(), ts, ts.size(), iterations);
}

// Function to generate encryption key and authentication key (based on user specified hashing) for AES
void generate_key(const string& password, const string& salt,
				  unsigned int iterations,
				  SecByteBlock& encKey, SecByteBlock& iv, SecByteBlock& akey,
				  const string& hashMode) {
	
	SecByteBlock x, y, z;
	
	if (hashMode == "1") {
		y = SecByteBlock(SHA1::DIGESTSIZE);
		z = SecByteBlock(SHA1::DIGESTSIZE);
		SHA1 hash;
		PKCS5_PBKDF2_HMAC<SHA1> derive;
		hash.CalculateDigest(y, (const byte*)salt.data(), salt.size());
		hmac_append(password, encKey, akey, x, z, y, derive, iterations);
	}
	else if (hashMode == "2") {
		y = SecByteBlock(SHA256::DIGESTSIZE);
		z = SecByteBlock(SHA256::DIGESTSIZE);
		SHA256 hash;
		PKCS5_PBKDF2_HMAC<SHA256> derive;
		hash.CalculateDigest(y, (const byte*)salt.data(), salt.size());
		hmac_append(password, encKey, akey, x, z, y, derive, iterations);
	}
	else if (hashMode == "3") {
		y = SecByteBlock(SHA512::DIGESTSIZE);
		z = SecByteBlock(SHA512::DIGESTSIZE);
		SHA512 hash;
		PKCS5_PBKDF2_HMAC<SHA512> derive;
		hash.CalculateDigest(y, (const byte*)salt.data(), salt.size());
		hmac_append(password, encKey, akey, x, z, y, derive, iterations);
	}
	else {
		y = SecByteBlock(MD5::DIGESTSIZE);
		z = SecByteBlock(MD5::DIGESTSIZE);
		MD5 hash;
		PKCS5_PBKDF2_HMAC<MD5> derive;
		hash.CalculateDigest(y, (const byte*)salt.data(), salt.size());
		hmac_append(password, encKey, akey, x, z, y, derive, iterations);
	}

}


int main()
{
	generate_menu();
	string flag = "1";
		string userInput;
		getline(cin, userInput);
		while (flag == "1") {
		if (userInput == "1") {
			string message, password, hashSelect, slength, blockSize;
			string userInput2 = "n";
			while (userInput2 == "n") {
				cout << "Alice wants to send a message to Bob. What should her message be?" << endl;
				getline(cin, message);
				cout << "Alice needs a password to authenticate the process, what should her password be?" << endl;
				getline(cin, password);
				cout << "Alice needs a random salt to apply to key. How long should the salt be?" << endl;
				getline(cin, slength);
				cout << "Alice needs to define the blocksize for the AES scheme. How large should the blocksize be? (16 byte/24 byte/32 byte)" << endl;
				getline(cin, blockSize);
				cout << "Please select a hashing method:" << endl;
				cout << "\t1. SHA-1" << endl;
				cout << "\t2. SHA-256" << endl;
				cout << "\t3. SHA-512" << endl;
				cout << "\t4. MD5" << endl;
				getline(cin, hashSelect);
				cout << "Confirm setting for the AES encryption scheme? (y/n)" << endl;
				getline(cin, userInput2);
			}
			cout << endl;
			cout << "Generating AES key and authentication key...." << endl;
			cout << endl;

			sleep_for(seconds(2));

			stringstream ss(slength);
			size_t saltLength;
			ss >> saltLength;

			string salt = generate_random_string(saltLength);
			SecByteBlock enc_key(stoi(blockSize)), iv(16), auth_key(stoi(blockSize));
			HexEncoder encoder(new FileSink(cout));
			AutoSeededRandomPool prng;

			prng.GenerateBlock(iv, iv.size());
			generate_key(password, salt, 4096, enc_key, iv, auth_key, hashSelect);

			CBC_Mode<AES>::Encryption encryptor;
			encryptor.SetKeyWithIV(enc_key, enc_key.size(), iv, iv.size());
			CBC_Mode<AES>::Decryption decryptor;
			decryptor.SetKeyWithIV(enc_key, enc_key.size(), iv, iv.size());
			HMAC< SHA256> hmac1;
			hmac1.SetKey(auth_key, auth_key.size());
			HMAC< SHA256> hmac2;
			hmac2.SetKey(auth_key, auth_key.size());


			cout << "Alice's Encryption Key: ";
			encoder.Put((byte*)enc_key.data(), enc_key.size());
			encoder.MessageEnd();
			cout << endl;

			cout << "Alice's Authentication Key: ";
			encoder.Put((byte*)auth_key.data(), auth_key.size());
			encoder.MessageEnd();
			cout << endl;

			cout << "Alice's IV: ";
			encoder.Put((byte*)iv.data(), iv.size());
			encoder.MessageEnd();
			cout << endl;

			cout << endl;
			sleep_for(seconds(1));

			cout << "Alice encrypts message with encryption key..." << endl;
			cout << "Alice authenticates encrypted text..." << endl;
			cout << endl;
			sleep_for(seconds(2));

			string cipherText, derivedText;
			static const word32 flags = CryptoPP::HashVerificationFilter::HASH_AT_END |
				CryptoPP::HashVerificationFilter::PUT_MESSAGE;

			StringSource ss1(message, true, new StreamTransformationFilter(encryptor, new HashFilter(hmac1, new StringSink(cipherText), true)));

			cout << "Alice's ciphertext: ";
			encoder.Put((byte*)cipherText.data(), cipherText.size());
			encoder.MessageEnd();
			cout << endl;

			cout << endl;
			sleep_for(seconds(2));

			cout << "Alice is sending the ciphertext to Bob..." << endl;
			cout << endl;
			sleep_for(seconds(2));
			cout << "Bob has recieved the ciphertext..." << endl;
			sleep_for(seconds(1));
			cout << "Bob authenticates and decrypt the ciphertext..." << endl;
			sleep_for(seconds(2));

			StringSource ss2(cipherText, true, new HashVerificationFilter(hmac2, new StreamTransformationFilter(decryptor, new StringSink(derivedText)), flags));
			cout << endl;
			cout << "Bob has decrypted Alice's message: " << derivedText << endl;
			cout << "Would you like to send another message? (y/n)" << endl;
			getline(cin, flag);
			if (flag == "y") {
				flag = "1";
			}
			else {
				flag = "0";
			}
		}
	}
}