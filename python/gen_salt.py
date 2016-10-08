#-*- coding:utf-8 -*-
'''
简短地生成随机盐，也可以用来生成随机密码
'''

import random
import string

def gen_salt(length):
    chars = string.ascii_letters + string.digits + "@%&*$#"       # 不使用string.printable，里面有的字符我不喜欢
    return ''.join([random.choice(chars) for i in range(length)]) # 得出的结果中字符会有重复的
    # return ''.join(random.sample(chars, 15))                    # 得出的结果中字符不会有重复的

if __name__=="__main__":
    print gen_salt(16)