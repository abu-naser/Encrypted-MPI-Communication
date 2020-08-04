/***************************
 C wrapper file for cryptopp
 an16e@my.fsu.edu
****************************/

#include "cwrapper_by_an.h"
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

 //unsigned char key[32]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 //unsigned char iv[12]= {0,0,0,0,0,0,0,0,0,0,0,0}; 
const unsigned int TAG_SIZE = 12;
unsigned int nonce_size = 12;

#if 1
 GCM< AES >::Encryption  e;
 GCM< AES >::Decryption  d;

void init_my_cryptopp(unsigned long key_size, unsigned char * key, unsigned char * iv){

    try
    {
        e.SetKeyWithIV( key, key_size, iv, sizeof(iv) );
        d.SetKeyWithIV( key, key_size, iv, sizeof(iv) );
    }
     catch( CryptoPP::InvalidArgument& e )
    {
        cerr << "Caught InvalidArgument..." << endl;
        cerr << e.what() << endl;
        cerr << endl;
    }
    catch( CryptoPP::Exception& e )
    {
        cerr << "Caught Exception in init..." << endl;
        cerr << e.what() << endl;
        cerr << endl;
    }

    return;
}
#endif

int my_encrypt( unsigned char *buf ,  unsigned char *ciphertext , int count, unsigned long key_size,
                 unsigned char *key, unsigned char *nonce ){
	
    //string pdata;
    //pdata.assign(buf, count); 
     
    // Encrypted, with Tag
    string cipher, encoded;

    

    /*********************************\
    \*********************************/

    // Pretty print
   // encoded.clear();
   // StringSource( key, sizeof(key), true,
   //     new HexEncoder(
   //         new StringSink( encoded )
   //     ) // HexEncoder
   // ); // StringSource
   // cout << "key: " << encoded << endl;

    // Pretty print
  //  encoded.clear();
  //  StringSource( iv, sizeof(iv), true,
   //     new HexEncoder(
   //         new StringSink( encoded )
    //    ) // HexEncoder
    //); // StringSource
   // cout << " iv: " << encoded << endl;

   // cout << endl;

    /*********************************\
    \*********************************/

    try
    {
       // cout << "plain text: " << pdata << endl;

        //GCM< AES >::Encryption e;
        //e.SetKeyWithIV( key, key_size, nonce, nonce_size );
        // e.SpecifyDataLengths( 0, pdata.size(), 0 );

        e.Resynchronize(nonce, nonce_size);
        StringSource( buf, count, true,
            new AuthenticatedEncryptionFilter( e,
                new StringSink( cipher ), false, TAG_SIZE
            ) // AuthenticatedEncryptionFilter
        ); // StringSource
    }
    catch( CryptoPP::InvalidArgument& e )
    {
        cerr << "Caught InvalidArgument..." << endl;
        cerr << e.what() << endl;
        cerr << endl;
    }
    catch( CryptoPP::Exception& e )
    {
        cerr << "Caught Exception during encrypt..." << endl;
        cerr << e.what() << endl;
        cerr << endl;
    }

    /*********************************\
    \*********************************/

    // Pretty print
   // encoded.clear();
   // StringSource( cipher, true,
    //    new HexEncoder(
    //        new StringSink( encoded )
    //    ) // HexEncoder
   // ); // StringSource
   // cout << "cipher text: " << encoded << endl;

  
    memcpy (ciphertext, cipher.c_str(),count+12);
	return 0;
}

int my_decrypt( unsigned char *ciphertext ,  unsigned char *buf, int count, unsigned long key_size,
               unsigned char *key, unsigned char * nonce){

     // Encrypted, with Tag
    //string cipher, encoded;
    //cipher.assign(ciphertext,count);
    
    

    // Pretty print
   // encoded.clear();
   // StringSource( cipher, true,
   //     new HexEncoder(
    //        new StringSink( encoded )
    //    ) // HexEncoder
   // ); // StringSource
   // cout << "cipher text recv: " << encoded << endl;

    // Recovered plain text
    string rpdata;

   try
    {
        //GCM< AES >::Decryption d;
        //d.SetKeyWithIV( key, key_size, nonce, nonce_size );
         d.Resynchronize(nonce, nonce_size);
        //d.SpecifyDataLengths( 0, cipher.size()-TAG_SIZE, 0 );

        AuthenticatedDecryptionFilter df( d,
            new StringSink( rpdata ),
            AuthenticatedDecryptionFilter::DEFAULT_FLAGS,
            TAG_SIZE
        ); // AuthenticatedDecryptionFilter

        // The StringSource dtor will be called immediately
        //  after construction below. This will cause the
        //  destruction of objects it owns. To stop the
        //  behavior so we can get the decoding result from
        //  the DecryptionFilter, we must use a redirector
        //  or manually Put(...) into the filter without
        //  using a StringSource.
        StringSource( ciphertext, count, true,
            new Redirector( df /*, PASS_EVERYTHING */ )
        ); // StringSource

        // If the object does not throw, here's the only
        //  opportunity to check the data's integrity
        bool b = df.GetLastResult();
        assert( true == b );

     //   cout << "recovered text: " << rpdata << endl;
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
        cerr << "Caught Exception during decrypt..." << endl;
        cerr << e.what() << endl;
        cerr << endl;
    }

    /*********************************\
    \*********************************/	
    memcpy (buf, rpdata.c_str(),(count-12));

 return 0;
}

void my_nonce(unsigned char * nonce, unsigned long nonce_len){
    AutoSeededRandomPool prng;
    prng.GenerateBlock( nonce, nonce_len );  
    return;
}

extern "C" {

 /* count = plaintext size */  
 void  wrapper_encrypt( unsigned char *buf ,  unsigned char *ciphertext , int count, unsigned long key_size, 
                       unsigned char *key, unsigned char *nonce){

      int var = my_encrypt(buf, ciphertext, count, key_size, key, nonce);
     return;
   }

/* count = ciphertext size = plaintext+tag */
void wrapper_decrypt( unsigned char *ciphertext ,  unsigned char *buf, int count, unsigned long key_size,
                     unsigned char *key, unsigned char *nonce){
    
    int var = my_decrypt(ciphertext, buf, count, key_size, key, nonce);
    return;
  }

void wrapper_nonce(unsigned char * nonce, unsigned long nonce_len){
      my_nonce(nonce, nonce_len);
}  

#if 1
void wrapper_init_cryptopp(unsigned long key_size, unsigned char * key, unsigned char * iv){

    init_my_cryptopp( key_size,  key,  iv);
    return;
    }
#endif    

}
