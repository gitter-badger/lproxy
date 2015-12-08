/*************************************************************************
	> File Name:    test.cpp
	> Author:       D_L
	> Mail:         deel@d-l.top
	> Created Time: 2015/11/6 7:31:20
 ************************************************************************/

#include <iostream>
#include <cstring>
#include <assert.h>
#include "crypto/xor_crypto.h"
#include "crypto/rc4_crypto.h"
#include "crypto/aes_crypto.h"

void print(const uint8_t* buffer, size_t size) {
    assert(buffer);
    for (size_t i = 0; i < size; ++i) {
        std::cout << (char)(*(buffer + i));
    }
    std::cout << std::endl;
}
void print(const char* buffer, size_t size) {
    print((const uint8_t*)buffer, size);
}
void print(const std::vector<uint8_t>& buffer, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        if (i >= buffer.size()-1) break;
        std::cout << (char)(buffer[i]);
    }
    std::cout << std::endl;
}

void test_xor(void) {
    using namespace crypto;
    const char* key = "hello crypto!";
    uint8_t buffer[1024] = "This is a test ...";
    /*
    uint8_t res1[1024] = {0}, res2[1024] = {0};
    uint8_t res3[1024] = {0}, res4[1024] = {0};
    */
    std::vector<uint8_t> res1, res2;
    std::vector<uint8_t> res3, res4;

    std::cout << buffer << std::endl;
    std::cout << "---" << std::endl; 

    // 默认可以交叉加解密
    Encryptor encryptor(new Xor((const uint8_t*)key, strlen(key))); 
    
    // encrypt
    encryptor.encrypt(res1, buffer, 1024);
    print(res1, 1024);
    std::cout << "---" << std::endl; 

    // decrypt
    encryptor.decrypt(res2, &res1[0], 1024);
    print(res2, 1024);
    std::cout << "---" << std::endl; 

    // encrypt
    encryptor.encrypt(res3, buffer, 1024);
    print(res3, 1024);
    std::cout << "---" << std::endl; 

    // decrypt
    encryptor.decrypt(res4, &res3[0], 1024);
    print(res4, 1024);
    std::cout << "---" << std::endl; 

}

void test_rc4(void) {
    using namespace crypto;
    const char* key = "hello crypto!";
    uint8_t buffer[1024] = "This is a test ...";
    /*
    uint8_t res1[1024] = {0}, res2[1024] = {0};
    uint8_t res3[1024] = {0}, res4[1024] = {0};
    */
    std::vector<uint8_t> res1, res2;
    std::vector<uint8_t> res3, res4;

    
    std::cout << buffer << std::endl;
    std::cout << "---" << std::endl; 

    Encryptor encryptor(new Rc4((const uint8_t*)key, strlen(key))); 
    // encrypt
    encryptor.encrypt(res1, buffer, 1024);
    print(res1, 1024);
    std::cout << "---" << std::endl; 

    // decrypt
    encryptor.decrypt(res2, &res1[0], 1024);
    print(res2, 1024);
    std::cout << "---" << std::endl; 

    // 内置同步机制，无法交叉加解密

    // encrypt
    encryptor.encrypt(res3, buffer, 1024);
    print(res3, 1024);
    std::cout << "---" << std::endl; 

    // decrypt
    encryptor.decrypt(res4, &res3[0], 1024);
    print(res4, 1024);
    std::cout << "---" << std::endl; 

}

void test_aes(void) {
    using namespace crypto;
    const char* key = "hello crypto!";
    const size_t buffer_size = 1024;
    //uint8_t buffer[buffer_size] = "This is a test ...";
    uint8_t buffer[buffer_size] = {0};
    for (std::size_t i = 0; i < buffer_size; ++i) {
        static char flag = 'A';
        if ((i % 10) == 0) {
            buffer[i] = flag++;
            if (flag >= 'Z') flag = 'A';
        }
        else {
            buffer[i] = i % 10 + '0';
        }
    }
    /*
    uint8_t res1[buffer_size] = {0}, res2[buffer_size] = {0};
    uint8_t res3[buffer_size] = {0}, res4[buffer_size] = {0};
    */

    std::vector<uint8_t> res1, res2;
    std::vector<uint8_t> res3, res4;

    print(buffer, buffer_size);
    std::cout << "---" << std::endl; 


    Encryptor encryptor(new Aes(std::string(key))); 
    //Encryptor encryptor(new Aes((const uint8_t*)key, strlen(key))); 
    // encrypt
    encryptor.encrypt(res1, buffer, buffer_size);
    print(res1, buffer_size);
    std::cout << "---" << std::endl; 

    // 交叉加解密开始
    // encrypt
    encryptor.encrypt(res3, buffer, buffer_size);
    print(res3, buffer_size);
    std::cout << "---" << std::endl; 

    // decrypt
    encryptor.decrypt(res4, &res3[0], buffer_size);
    print(res4, buffer_size);
    std::cout << "---" << std::endl; 
    // 交叉加解密结束

    // decrypt
    encryptor.decrypt(res2, &res1[0], buffer_size);
    print(res2, buffer_size);
    std::cout << "---" << std::endl; 

}

int main() {
    using namespace std;
    cout << "\n/*--------test xor--------*/" << endl;
    test_xor();

    cout << "\n/*--------test rc4--------*/" << endl;
    test_rc4();

    cout << "\n/*--------test aes--------*/" << endl;
    test_aes();
    return 0;
}

