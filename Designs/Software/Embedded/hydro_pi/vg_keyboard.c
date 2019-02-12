#include "vg_keyboard.h"

#include <stdint.h>
#include <stdio.h>

// Graphics
#include <fcntl.h>
#include <shapes.h>
#include <fontinfo.h>

int isShiftOn = 0;
int isCapsOn = 0;

double units = 16.409;

typedef struct Key {
  struct Key *up;
  struct Key *down;
  struct Key *left;
  struct Key *right;
  char upper;
  char lower;
  int xPos;
  int yPos;
} Key;

Key key_a, key_b, key_c, key_d, key_e, key_f, key_g, key_h, key_i, key_j, key_k, key_l, key_m, key_n, key_o, key_p, key_q, key_r, key_s, key__t, key_u, key_v, key_w, key_x, key_y, key_z;
Key key_tilde, key_1, key_2, key_3, key_4, key_5, key_6, key_7, key_8, key_9, key_0, key_minus, key_equals, key_backspace;
Key key_tab, key_caps, key_lshift;
Key key_lbracket, key_rbracket, key_backslash, key_enter, key_rshift, key_comma, key_period, key_slash, key_semicolon, key_apostrophe;
Key key_space;
Key *selected_key;

void VG_KB_Init() {
  
  // Home row
  key_caps = (Key) {
    &key_tab, &key_lshift, &key_caps, &key_a,
    '\0','\0',1,7
  };
  key_a = (Key) {
    &key_q, &key_z, &key_caps, &key_s,
    'A','a',6,7
  };
  key_s = (Key) {
    &key_w, &key_x, &key_a, &key_d,
    'S','s',9,7
  };
  key_d = (Key) {
    &key_e, &key_c, &key_s, &key_f,
    'D','d',12,7
  };
  key_f = (Key) {
    &key_r, &key_v, &key_d, &key_g,
    'F','f',15,7
  };
  key_g = (Key) {
    &key__t, &key_b, &key_f, &key_h,
    'G','g',18,7
  };
  key_h = (Key) {
    &key_y, &key_n, &key_g, &key_j,
    'H','h',21,7
  };
  key_j = (Key) {
    &key_u, &key_m, &key_h, &key_k,
    'J','j',24,7
  };
  key_k = (Key) {
    &key_i, &key_comma, &key_j, &key_l,
    'K','k',27,7
  };
  key_l = (Key) {
    &key_o, &key_period, &key_k, &key_semicolon,
    'L','l',30,7
  };
  key_semicolon = (Key) {
    &key_p, &key_slash, &key_l, &key_apostrophe,
    ':',';',33,7
  };
  key_apostrophe = (Key) {
    &key_lbracket, &key_rshift, &key_semicolon, &key_enter,
    '"','\'',36,7
  };
  key_enter = (Key) {
    &key_backslash, &key_rshift, &key_apostrophe, &key_enter,
    '\0','\0',39,7
  };
  
  // Tab row
  key_tab = (Key) {
    &key_tilde, &key_caps, &key_tab, &key_q,
    '\t','\t',1,10
  };
  key_q = (Key) {
    &key_1, &key_a, &key_tab, &key_w,
    'Q','q',5,10
  };
  key_w = (Key) {
    &key_2, &key_s, &key_q, &key_e,
    'W','w',8,10
  };
  key_e = (Key) {
    &key_3, &key_d, &key_w, &key_r,
    'E','e',11,10
  };
  key_r = (Key) {
    &key_4, &key_f, &key_e, &key__t,
    'R','r',14,10
  };
  key__t = (Key) {
    &key_5, &key_g, &key_r, &key_y,
    'T','t',17,10
  };
  key_y = (Key) {
    &key_6, &key_h, &key__t, &key_u,
    'Y','y',20,10
  };
  key_u = (Key) {
    &key_7, &key_j, &key_y, &key_i,
    'U','u',23,10
  };
  key_i = (Key) {
    &key_8, &key_k, &key_u, &key_o,
    'I','i',26,10
  };
  key_o = (Key) {
    &key_9, &key_l, &key_i, &key_p,
    'O','o',29,10
  };
  key_p = (Key) {
    &key_0, &key_semicolon, &key_o, &key_lbracket,
    'P','p',32,10
  };
  key_lbracket = (Key) {
    &key_minus, &key_apostrophe, &key_p, &key_rbracket,
    '{','[',35,10
  };
  key_rbracket = (Key) {
    &key_equals, &key_enter, &key_lbracket, &key_backslash,
    '}',']',38,10
  };
  key_backslash = (Key) {
    &key_backspace, &key_enter, &key_rbracket, &key_backslash,
    '|','\\',41,10
  };
  
  // Number row
  key_tilde = (Key) {
    &key_tilde, &key_tab, &key_tilde, &key_1,
    '~','`',1,13
  };
  key_1 = (Key) {
    &key_1, &key_q, &key_tilde, &key_2,
    '!','1',4,13
  };
  key_2 = (Key) {
    &key_2, &key_w, &key_1, &key_3,
    '@','2',7,13
  };
  key_3 = (Key) {
    &key_3, &key_e, &key_2, &key_4,
    '#','3',10,13
  };
  key_4 = (Key) {
    &key_4, &key_r, &key_3, &key_5,
    '$','4',13,13
  };
  key_5 = (Key) {
    &key_5, &key__t, &key_4, &key_6,
    '%','5',16,13
  };
  key_6 = (Key) {
    &key_6, &key_y, &key_5, &key_7,
    '^','6',19,13
  };
  key_7 = (Key) {
    &key_7, &key_u, &key_6, &key_8,
    '&','7',22,13
  };
  key_8 = (Key) {
    &key_8, &key_i, &key_7, &key_9,
    '*','8',25,13
  };
  key_9 = (Key) {
    &key_9, &key_o, &key_8, &key_0,
    '(','9',28,13
  };
  key_0 = (Key) {
    &key_0, &key_p, &key_9, &key_minus,
    ')','0',31,13
  };
  key_minus = (Key) {
    &key_minus, &key_lbracket, &key_0, &key_equals,
    '_','-',34,13
  };
  key_equals = (Key) {
    &key_equals, &key_rbracket, &key_minus, &key_backspace,
    '+','=',37,13
  };
  key_backspace = (Key) {
    &key_backspace, &key_backslash, &key_equals, &key_backspace,
    '\b','\b',40,13
  };
  
  // Bottom row
  key_lshift = (Key) {
    &key_caps, &key_space, &key_lshift, &key_z,
    '\0','\0',1,4
  };
  key_z = (Key) {
    &key_a, &key_space, &key_lshift, &key_x,
    'Z','z',7,4
  };
  key_x = (Key) {
    &key_s, &key_space, &key_z, &key_c,
    'X','x',10,4
  };
  key_c = (Key) {
    &key_d, &key_space, &key_x, &key_v,
    'C','c',13,4
  };
  key_v = (Key) {
    &key_f, &key_space, &key_c, &key_b,
    'V','v',16,4
  };
  key_b = (Key) {
    &key_g, &key_space, &key_v, &key_n,
    'B','b',19,4
  };
  key_n = (Key) {
    &key_h, &key_space, &key_b, &key_m,
    'N','n',22,4
  };
  key_m = (Key) {
    &key_j, &key_space, &key_n, &key_comma,
    'M','m',25,4
  };
  key_comma = (Key) {
    &key_k, &key_space, &key_m, &key_period,
    '<',',',28,4
  };
  key_period = (Key) {
    &key_l, &key_space, &key_comma, &key_slash,
    '>','.',31,4
  };
  key_slash = (Key) {
    &key_semicolon, &key_space, &key_period, &key_rshift,
    '?','/',34,4
  };
  key_rshift = (Key) {
    &key_enter, &key_space, &key_slash, &key_rshift,
    '\0','\0',37,4
  };

  key_space = (Key) {
    &key_b, &key_space, &key_lshift, &key_rshift,
    ' ',' ',21,1
  };
    
  
  // TODO fill out the other keyboard rows
  
  
  selected_key = &key_a;
}

void VG_KB_Destroy() {
  
}

char VG_KB_KeyPress() {
  return 'a';
}

void VG_KB_Up() {
  selected_key = selected_key->up;
}
void VG_KB_Down() {
  selected_key = selected_key->down;
}
void VG_KB_Left() {
  selected_key = selected_key->left;
}
void VG_KB_Right() {
  selected_key = selected_key->right;
}

void VG_KB_Draw(int x, int y, int w, int h) {
  Image(x,y,1056,384,"images/keyboard_lower.jpg");
  Fill(255,255,255,0);
  Stroke(255,255,0,1); 
  StrokeWidth(5);
  Roundrect(x+(selected_key->xPos)*units, y+(selected_key->yPos)*units, 5*units/2, 5*units/2, 15, 15);
  StrokeWidth(0);
  
}
