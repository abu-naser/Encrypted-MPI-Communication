#include "gcm3header.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <vector>
#include <sstream>
#include <utility>
#include <stdio.h>
#include <string.h>
#include "aes.h"
#include "gcm.h"
#include "assert.h"
#include "cryptlib.h"
#include "hex.h"
#include "filters.h"
#include "osrng.h"

//#define key_size 16


extern "C" {

using CryptoPP::Exception;
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;
using CryptoPP::StringSink;
using CryptoPP::StringSource;
using CryptoPP::AuthenticatedEncryptionFilter;
using CryptoPP::AuthenticatedDecryptionFilter;
using CryptoPP::AES;
using std::setw;
using namespace std;
using namespace CryptoPP;
using CryptoPP::AutoSeededRandomPool;


//static AutoSeededRandomPool prng;
//static byte key[ key_size ];
//static byte iv[ 16 ];
//static GCM< AES >::Encryption e;
//static GCM< AES >::Decryption d;
//static const byte key[key_size]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','a','b','c','d','e','f'};
const byte key[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 //const byte key[key_size]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const byte iv[12]= {0,0,0,0,0,0,0,0,0,0,0,0}; 

int cryptopp_init(){
	
	//prng.GenerateBlock( key, sizeof(key) );
    //prng.GenerateBlock( iv, sizeof(iv) ); 
	//e.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));
	//d.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));
// const byte iv[12]= {0,0,0,0,0,0,0,0,0,0,0,0}; 
	return 1;
}

static int key_size=16;

void key_cryptopp_128(){
	key_size = 16;
	//byte key[key_size];
	//memset( key, 0, sizeof(key) );

}


void key_cryptopp_256(){
	key_size = 32;
	//byte key[key_size];
	//memset( key, 0, sizeof(key) );

}

void my_print_recv(const void *print_buffer, int count,char s[])	//keep square brackets in signature
{ 
	printf("\n%s=\n",s);fflush(stdout);
	for (int i=0 ; i<count ; i++){
		printf("%2x ",*((unsigned char *)(print_buffer+i)));
		fflush(stdout);
	}
	printf("\n");fflush(stdout);
}

static const int TAG_SIZE = 12;

int encrypt(char *buf , char *ciphertext , int count){
	//printf("count ***= %d\n", count);
	string cipher, encoded;
	//string pdata=string(buf,count);
	//*((unsigned char *)buf+count)='\0';
	buf[count]='\0';
	//prng.GenerateBlock( key, sizeof(key) );
    //prng.GenerateBlock( iv, sizeof(iv) ); 
	//byte key[key_size];
	//memset( key, 0, sizeof(key) );
	//const byte iv[12]={0,0,0,0,0,0,0,0,0,0,0,0}; 
 
	try
	{
		GCM< AES >::Encryption e;
		//e.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));		
		e.SetKeyWithIV(key, key_size, iv, sizeof(iv));		
		StringSource( buf, true,
		//StringSource( pdata, true,
            new AuthenticatedEncryptionFilter( e,
                new StringSink( cipher ), false, TAG_SIZE
            ) // AuthenticatedEncryptionFilter
        ); // StringSource
			
		count=count+TAG_SIZE;
		//cout << "Enc cipher is " << cipher << "length is " << cipher.length() << " \n";
		cout << "cipher length is " << cipher.length() << " \n";
		//printf("\nThis ciphertext count: %d\n",count);
		//memcpy (ciphertext, cipher.c_str(),count);			
		memcpy (ciphertext, cipher.c_str(),strlen(cipher.c_str()));			
	
	}
		
		catch( CryptoPP::InvalidArgument& e )
		{
			cerr << "Caught InvalidArgument..." << endl;
			cerr << e.what() << endl;
			cerr << endl;
		}
		 catch( CryptoPP::Exception& e )
		{
			cerr << "Caught Exception..." << endl;
			cerr << e.what() << endl;
			cerr << endl;
		}
	return count;	
}

int decrypt(char *ciphertext , char *buf, int count){

string rpdata,encoded;
//string cipher=string(ciphertext,count);
//*((unsigned char *)ciphertext+count)='\0';
ciphertext[count]='\0';
 // prng.GenerateBlock( key, sizeof(key) );
 // prng.GenerateBlock( iv, sizeof(iv) ); 
 //byte key[key_size];
 //memset( key, 0, sizeof(key) );
 //const byte iv[12]= {0,0,0,0,0,0,0,0,0,0,0,0}; 
	
	try
	{
		GCM< AES >::Decryption d;
		//d.SetKeyWithIV(key, sizeof(key), iv, sizeof(iv));
		d.SetKeyWithIV(key, key_size, iv, sizeof(iv));
		
		AuthenticatedDecryptionFilter df( d,
            new StringSink( rpdata ),
            AuthenticatedDecryptionFilter::DEFAULT_FLAGS,
            TAG_SIZE
        );
		
			//printf("\nThis key: %s\n", (char)key);
		// my_print_recv(key,sizeof(key),"This is key:");
		// my_print_recv(iv,sizeof(iv),"This is iv:");
		// printf("\nThis is count @ decrypt:%d\n",count);
		
		
		StringSource( ciphertext, true,
		//StringSource( cipher, true,
            new Redirector( df /*, PASS_EVERYTHING */ )
        ); // StringSource
		cout << "rpdata length is " << rpdata.length() << " \n";
		bool b = false;
		b = df.GetLastResult();
		assert( true == b );
	
		count=count-TAG_SIZE;
		//cout << "Enc rpdata is " << rpdata << "length is " << rpdata.length() << " \n";
		
		//memcpy (buf, rpdata.c_str(),count);
		memcpy (buf, rpdata.c_str(),rpdata.length());
		//printf("Decryption was Succesful: %s\n", buf);
											
	}
	catch( CryptoPP::HashVerificationFilter::HashVerificationFailed& e )
	{
		cerr << "Caught HashVerificationFailed..." << endl;
		cerr << e.what() << endl;
		cerr << endl;
	}
	catch( CryptoPP::InvalidArgument& e )
	{
		cerr << "Caught InvalidArgument..." << endl;
		cerr << e.what() << endl;
		cerr << endl;
	}
	catch( CryptoPP::Exception& e )
	{
		cerr << "Caught Exception..." << endl;
		cerr << e.what() << endl;
		cerr << endl;
	}		
	return count;
	}
}
