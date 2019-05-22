from __future__ import print_function

def foo(a,b,c,d,e,f,g,h,i):
   print("key_%s = (Key) {\n  &key_%s, &key_%s, &key_%s, &key_%s,\n  '%s','%s',%d,%d\n};" % (a,b,c,d,e,f,g,h,i))
  # key_tilde = (Key) {
  #   &key_tilde, &key_tab, &key_tilde, &key_1,
  #   '~','`',1,13
  # };

# foo('tilde','tilde','tab','tilde','1','~','`',1,13)

# foo('4','4','r','3','5','$','4',1+3*3,13)
# foo('5','5','t','4','6','%','5',1+3*4,13)
# foo('6','6','y','5','7','^','6',1+3*5,13)
# foo('7','7','u','6','8','&','7',1+3*6,13)
# foo('8','8','i','7','9','*','8',1+3*7,13)
# foo('9','9','o','8','0','(','9',1+3*8,13)
# foo('0','0','p','9','minus',')','0',1+3*9,13)
# foo('minus','minus','lbrace','0','equals','_','-',1+3*10,13)
# foo('equals','equals','rbrace','minus','backspace','+','=',1+3*11,13)
# foo('backspace','backspace','backslash','equals','backspace','\\b','\\b',1+3*12,13)
# print("\n")

foo('lshift','caps','space','lshift','z','\\0','\\0',1,4)
foo('z','a','space','lshift','x','Z','z',7,4)
foo('x','s','space','z','c','X','x',7+3*1,4)
foo('c','d','space','x','v','C','c',7+3*2,4)
foo('v','f','space','c','b','V','v',7+3*3,4)
foo('b','g','space','v','n','B','b',7+3*4,4)
foo('n','h','space','b','m','N','n',7+3*5,4)
foo('m','j','space','n','comma','M','m',7+3*6,4)
foo('comma','k','space','m','period','<',',',7+3*7,4)
foo('period','l','space','comma','slash','>','.',7+3*8,4)
foo('slash','semicolon','space','period','rshift','\\0','\\0',7+3*9,4)
