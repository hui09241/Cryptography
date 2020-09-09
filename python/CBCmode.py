from Crypto.Cipher import AES
from binascii import b2a_hex, a2b_hex
import random,string

class PrpCrypt(object):
 
    def __init__(self, key):
        self.key = key.encode('utf-8')
        self.mode = AES.MODE_CBC
        
    def encrypt(self, text):
        text = text.encode('utf-8')
        cryptor = AES.new(self.key, self.mode, b'0000000000000000')
        #三個參數key是祕鑰，中為加密方式，b'0000000000000000'是IV常常用key來代替也可以
        length = 16
        textlen = len(text)
        if textlen < length:#不足16補滿到16
            add = (length - textlen)
            text = text + ('\0' * add).encode('utf-8')
        elif textlen > length:#不足16的倍數，補滿到16的倍數
            add = (length - (textlen % length))
            text = text + ('\0' * add).encode('utf-8')
        ciphertext = cryptor.encrypt(text)
        return b2a_hex(ciphertext)
    
    def decrypt(self, text):
        cryptor = AES.new(self.key, self.mode, b'0000000000000000')
        plain_text = cryptor.decrypt(a2b_hex(text))
        return bytes.decode(plain_text).rstrip('\0')
    
def random_char(y):
       return ''.join(random.choice(string.ascii_letters) for x in range(y))#亂數生成
   
if __name__ == '__main__':
    
    pc = PrpCrypt(random_char(16))  # 使用亂數生成的初始化密鑰
    
    f =open('CBCplaintext.txt','r')#讀檔
    plaintext=f.read()
    
    enctext = pc.encrypt(plaintext)#加密
    dectext = pc.decrypt(enctext)  # 解密
    
    print("解密前明文：",plaintext)
    #print(len(plaintext))
    print("加密完密文：",bytes.decode(enctext)) #原本以byte表示，然後將byte轉回string
    #print(len(enctext))
    print("解密後明文：",dectext)
    
    f.close()#關檔

