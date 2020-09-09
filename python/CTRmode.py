from Crypto.Cipher import AES
from binascii import b2a_hex, a2b_hex
from Crypto.Util import Counter
from Crypto import Random
import random,string

class PrpCrypt(object):
 
    def __init__(self, key):
        self.key = key.encode('utf-8')
        self.mode = AES.MODE_CTR
        self.nonce = Random.get_random_bytes(4)
        self.ctr=Counter.new(64, prefix=self.nonce, suffix=b'ABCD',  initial_value=10,little_endian=True)
        #self.ctr=Counter.new(128)
        
    def encrypt(self, text):
        text = text.encode('utf-8')
        
        cryptor = AES.new(self.key, self.mode, counter=self.ctr)
        self.ciphertext = cryptor.encrypt(text)
        return bytes.decode(b2a_hex(self.ciphertext))
    
    def decrypt(self, text):
        cryptor = AES.new(self.key, self.mode, counter=self.ctr)
        plain_text  = cryptor.decrypt(a2b_hex(text))
        return bytes.decode(plain_text)
    
def random_char(y):
       return ''.join(random.choice(string.ascii_letters) for x in range(y)) #亂數生成
 
 
if __name__ == '__main__':
    pc = PrpCrypt(random_char(16))  # 使用亂數生成的初始化密鑰
    
    f =open('CTRplaintext.txt','r')#讀檔
    plaintext=f.read()
    
    enctext = pc.encrypt(plaintext)#加密
    dectext = pc.decrypt(enctext)  # 解密
    
    print("解密前明文：",plaintext)
    #print(len(plaintext))
    print("加密完密文：",enctext) #原本以byte表示，然後將byte轉回string
    #print(len(enctext))
    print("解密後明文：",dectext)