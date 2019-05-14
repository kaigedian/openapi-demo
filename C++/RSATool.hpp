#ifndef RSATOOL_H
#define RSATOOL_H

#include <openssl/evp.h>
#include <openssl/bio.h>  
#include <openssl/buffer.h>  
#include <openssl/rsa.h>  
#include <openssl/pem.h>  
#include <openssl/err.h> 

#include <string>
#include <sstream>

#define MAX_RSA_KEY_LEN				2048

class RSATool
{
public:
	/***********************************
	*函数名：base64
	*input ：字符串
	*length：字符串长度
	*result: 返回base64编码的字符串
	*size  ：result容纳的最大长度
	*返回  ：result的真实长度(0 调用失败)
	***********************************/
	static int base64(const char *input, size_t length, char *result, size_t size)  
	{  
		BIO * bmem = NULL;  
		BIO * b64 = NULL;  
		BUF_MEM * bptr = NULL; 
		int len = 0;

		if(input == NULL)
			return 0;
		b64 = BIO_new(BIO_f_base64());  
		bmem = BIO_new(BIO_s_mem());  
		if (NULL == b64 || NULL == bmem) {  
			perror("BIO_new");  
			return 0;  
		}  
		BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);  

		b64 = BIO_push(b64, bmem);  
		BIO_write(b64, input, length);  
		BIO_flush(b64);  
		BIO_get_mem_ptr(b64, &bptr);  

		if ((unsigned int)(bptr->length + 1) > size) {  
			BIO_free_all(b64);  
			return 0;  
		}  
		memcpy(result, bptr->data, bptr->length);  
		result[bptr->length] = 0;  
		len = bptr->length;

		BIO_free_all(b64);  

		return len;  
	}  
	/***********************************
	*函数名：debase64
	*input ：base64字符串
	*length：字符串长度
	*result: 返回正常编码的字符串
	*size  ：result容纳的最大长度
	*返回  ：result的真实长度(0 调用失败)
	***********************************/
	static int debase64(const char *input, size_t length, char *result, size_t size)  
	{  
		BIO * b64 = NULL;  
		BIO * bmem = NULL;
		int len;

		if(input == NULL)
			return 0;
		if (length > size)  
			return 0;  
		memset(result, 0, size);  

		b64 = BIO_new(BIO_f_base64());  
		bmem = BIO_new_mem_buf((void *)input, length);  
		BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);  
		if (NULL == b64 || NULL == bmem) {  
			perror("BIO_new");  
			return 0;  
		}  
		bmem = BIO_push(b64, bmem);  
		len = BIO_read(bmem, result, length);  

		BIO_free_all(b64);  

		return len;  
	}
	/***********************************
	*RSASign : RSA签名
	*text  ：待签名字符串
	*signature：输出签名
	*size: signature的最大长度
	*private_key  ：私钥
	*返回  ：0 失败; 非0表示signature长度
	***********************************/
	static int RSASign(const char *text, char *signature, size_t size,const char *private_key)  
	{  
		RSA *rsa;  
		unsigned char *sig;  
		unsigned int len;
		unsigned int length = 0;
		BIO* in = NULL; 
        unsigned char sha1[32] = { '\0' };

		char tmpprivatekey[MAX_RSA_KEY_LEN] = {0};

		if(GetPEMKey(private_key, strlen(private_key), tmpprivatekey, MAX_RSA_KEY_LEN, 0) == 0)
			return 0;

		OpenSSL_add_all_algorithms(); 

		in = BIO_new_mem_buf((void*)tmpprivatekey, -1);
		if (in == NULL) {  
			perror("read private failed");  
			return 0;  
		}  

		rsa = PEM_read_bio_RSAPrivateKey(in, NULL, NULL, NULL);  
		if (in != NULL)  
			BIO_free(in);  
		if (rsa == NULL) {  
			perror("PEM_read_bio_RSAPrivateKey");  
			return 0;  
		}  
		if (NULL == (sig = (unsigned char*)malloc(RSA_size(rsa)))) {  
			RSA_free(rsa);  
			return 0;  
		}  

        SHA256((const unsigned char *)text, strlen(text), sha1);
        if (1 != RSA_sign(NID_sha256, sha1, 32, sig, &len, rsa)) {
			free(sig);  
			RSA_free(rsa);  
			printf("RSA_sign error.\n");  
			return 0;  
		}  

		if ((length= base64((char *)sig, 128, signature, size)) == 0) {  
			free(sig);  
			RSA_free(rsa);  
			printf("base64 error.\n");  
			return 0;  
		}  
		free(sig);  
		RSA_free(rsa);  

		return length;  
	}
	/***********************************
	*RSAVerify : RSA验签
	*text  ：待签名字符串
	*signature：输出签名
	*size: signature的最大长度
	*private_key  ：公钥
	*返回  ：0 失败; 1 成功
	***********************************/
	static int RSAVerify(const char *text,const char *signature, const char *public_key)  
	{  
		RSA *rsa;  
		BIO* in = NULL;  
		char * sig_debase = NULL;
        unsigned char sha1[32];

		char tmppublickey[MAX_RSA_KEY_LEN] = {0};

		if(GetPEMKey(public_key, strlen(public_key), tmppublickey, MAX_RSA_KEY_LEN, 1) == 0)
			return 0;
		
		in = BIO_new_mem_buf((void*)tmppublickey, -1);
		if (NULL == in) {  
			printf("BIO_read_filename error.\n");  
			return 0;  
		}  

		rsa = PEM_read_bio_RSA_PUBKEY(in, NULL, NULL, NULL);  

		if (in != NULL) BIO_free(in);  
		if (rsa == NULL) {  
			printf("PEM_read_bio_RSA_PUBKEY error.\n");  
			return 0;  
		}  

		sig_debase = (char *)malloc(250 * sizeof(char));  
		if (NULL == debase64(signature, strlen((char *)signature), sig_debase, 250)) {  
			RSA_free(rsa);  
			printf("debase64 error.\n");  
			return 0;  
		}  

        SHA256((const unsigned char *)text, strlen(text), sha1);
        if (1 != RSA_verify(NID_sha256, sha1, 32, (unsigned char *)sig_debase, 128, rsa)) {
			free(sig_debase);  
			RSA_free(rsa);  
			printf("RSA_verify error.\n");  
			return 0;  
		}  
		free(sig_debase);  
		RSA_free(rsa);  

		return 1;  
	}
	/***********************************
	*GetPEMKey : 将公钥或私钥转换为opelssl可加载的pem格式
	*key  ：原始秘钥
	*keylen: 原始秘钥长度
	*outpemkey：最大长度
	*outpemkeymaxlen：outpemkey最大长度
	*ispublickey: 0为私钥 1为公钥
	*返回  ：0 失败; 1 成功
	***********************************/
	static int GetPEMKey(const char *key, int keylen, char *outpemkey, int outpemkeymaxlen, int ispublickey)
	{
		std::stringstream sstm;
		std::string str(key, keylen);

		if (keylen > outpemkeymaxlen)
		{
			return 0;
		}
		
		if(ispublickey == 0)
		{
			int i = 0;


			sstm << "-----BEGIN RSA PRIVATE KEY-----\n";

			while(i + 64 < keylen)
			{
				sstm << str.substr(i, 64) << "\n";
				i += 64;
			}
			if(keylen - i > 0)
				sstm << str.substr(i, keylen - i) << "\n";
			sstm << "-----END RSA PRIVATE KEY-----\n";
		}
		else
		{
			int i = 0;
			sstm << "-----BEGIN PUBLIC KEY-----\n";

			while(i + 64 < keylen)
			{
				sstm << str.substr(i, 64) << "\n";
				i += 64;
			}
			if(keylen - i > 0)
				sstm << str.substr(i, keylen - i) << "\n";
			sstm << "-----END PUBLIC KEY-----\n";
		}

		if(strlen(sstm.str().c_str()) > outpemkeymaxlen)
			return 0;

		strcpy(outpemkey, sstm.str().c_str());
		return 1;
	}
};

#endif
