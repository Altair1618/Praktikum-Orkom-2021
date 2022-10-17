#include <stdio.h>

int gura(int x, int y) {
    // Hitung x | y hanya dengan ~ dan &
 
    // Tinggal De Morgan Aja
    return ~(~x & ~y);
}

int rushia(void) {
    // Berikan nilai terkecil dalam two`s complement

    // Membuat TMin = 0x80000000
    return 1 << 31;
}

unsigned int kobokan (unsigned int x, unsigned int n) {
    // Hitung sisa dari x jika dibagi 2 pangkat n
    // Atau x mod 2^n

    // Tinggal mengembalikan n digit dari belakang
    // Cara 1 : Cara yang kukumpulkan
    int a = x >> n;
    int b = a << n;
    return x & ~b; // ~b adalah kebalikan dari x namun n digit terbelakangnya adalah 1

    // Cara 2 :
    // x di and kan dengan 2^n - 1 (trailing one sebanyak n)
    // int a = (1 << n) + ~0;
    // return x & a;
}

int fauna(int x, int n) {
    // Mengembalikan byte ke-n dari word x

    // Caraku keknya agak rumit :D
    int a = n << 3;  // a = 8 * n
    int b = x >> a;  // x di right shift sebanyak 8 * n
    int c = (b >> 8) << 8; // Ngebuat 8 bit terakhir jadi 0
    return b ^ c;  // Mengembalikan bit yang berbeda antara b dan c
}

int yamada(int x) {
    // Periksa apakah x berada diantara 135 dan 182 inklusif

    // Inisiasi variabel
    int a = ~135 + 1;  // a = -135
    int b = ~182;  // b = -183

    // Pengecekan
    int c = (x + a) >> 31;  // Jika x >= 135 maka 0, x < 135 maka 1
    int d = (x + b) >> 31;  // Jika x > 182 maka 1, x <= 182 maka 0
    return ~c & d & 1;  // ~c dan d maka bit terakhirnya jadi 1 bila diantara 135 dan 182, di-and-kan dengan 1 agar dpt bit terakhir
}

int pekora(int x) {
    // Balik urutan byte pada x

    // Ngambil byte ke n dan membuat dia menjadi bit ke 3 - n
    int a = x >> 24 & 0xff;  // 3 ke 0
    int b = (x >> 16 & 0xff) << 8;  // 2 ke 1
    int c = (x >> 8 & 0xff) << 16;  // 1 ke 2
    int d = (x & 0xff) << 24;  // 0 ke 3
    return a + b + c + d;
    // Bisa juga ret a | b | c | d
}

int mumei(int x, int n) {
    // Geser x ke kanan dengan aturan logical shift
    
    int a = 1 << 31;  // Membuat 0x80000000 atau 1 diikuti 31 0
    int b = (a >> n) << 1;  // Membuat n angka 1 diikuti 32 - n angka 0
    int c = x >> n;  // Menggeser x sebanyak n dengan aturan arith shift
    return c & ~b;  // ~b kan jadinya n angka 0 dan 32 - n angka 1, kalau di and sama c jadinya x logical shift
}

int moona(int x) {
    // Hitung banyak trailing zero

    // Mendapat 2 pangkat terbesar yang habis membagi x
    int a = x & (~(x + ~0));

    // a - 1, hasilnya semua leading zero menjadi 1, sisanya jadi 0
    int b = a + ~0;

    // Divide and Conquer ngitung jumlah banyak 1 dalam bit
    int c = (0x55555555 & b) + (0x55555555 & (b >> 1));
    int d = (0x33333333 & c) + (0x33333333 & (c >> 2));
    int e = (0x0f0f0f0f & d) + (0x0f0f0f0f & (d >> 4));
    int f = (0x00ff00ff & e) + (0x00ff00ff & (e >> 8));
    int g = (0x0000ffff & f) + (0x0000ffff & (f >> 16));
    return g;
}

unsigned int ollie(unsigned int a) {
    // Hitung sisa dari a jika dibagi 30

    // Basically caraku adalah gini
    // a = 32x + y dimana x = a div 32 dan y = a mod 32
    // ini kongruen dengan (2x + y) mod 30
    // Karena 2x + y terkadang masih lebih dari 32, maka diulang (ini nyoba nyoba berapa kalinya)
    int e;
    int f;
    int z;

    // a = 2 * (a div 32) {ini x} + a mod 32 {ini y}
    a = ((a >> 5) << 1) + (a & 31);
    a = ((a >> 5) << 1) + (a & 31);
    a = ((a >> 5) << 1) + (a & 31);
    a = ((a >> 5) << 1) + (a & 31);
    a = ((a >> 5) << 1) + (a & 31);
    a = ((a >> 5) << 1) + (a & 31);
    a = ((a >> 5) << 1) + (a & 31);

    // Karena range a masih 0 - 31, padahal 30 dan 31 harusnya masing masing 0 dan 1 mod 30
    // Jadinya implementasi if a >= 30 then a -= 30

    // Mengubah a menjadi signed karena butuh arith shift
    z = a;  // Ini work karena z int

    // (z - 30) >> 31 akan membuat semua 0 jika >= 30 atau semua 1 jika < 30
    // Karena e itu negasinya maka 1 semua jika >= 30 atau 0 semua jika < 30
    e = ~((z + ~29) >> 31);

    // Mengurangi dengan 30 jika e nya 0 (a >= 30)
    // 30 & e akan menjadi 30 bila e nya 1 semua dan 0 bila e nya 0
    f = (a + ~((30 & e) + ~0));

    return f;
}

unsigned coco(unsigned uf) {
    // Hitung 2 * f untuk suatu bilangan floating point f
    int a = uf & 0x80000000;  // Mendapatkan s dari uf
    int b = uf & 0x78f00000;  // Mendapatkan exp dari uf

    if (!b) {  // Bila b == 0
        uf = a | (uf << 1);  // Left shift uf tanpa merubah signnya
    } else if (b != 0x7f800000) {  // Bila exp != 11111111
        uf += 0x00800000;  // Tinggal exp nya + 1
    }

    // Karena kalau f NaN lgsg kembalikan f maka tidak perlu diproses
    return uf;
}
