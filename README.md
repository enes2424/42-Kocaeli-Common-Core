# 42 Kocaeli Libft
## Standard C Library Recreation (Standart C Kütüphanesi Yeniden Oluşturma)

Bu proje, 42 Okulu Common Core eğitiminin ilk projesidir. C programlama dilinin standart kütüphanesindeki temel fonksiyonları yeniden implement ederek C dilinin derinliklerini öğrenmeyi ve güçlü bir temel oluşturmayı amaçlar. Ayrıca linked list veri yapısını da içerir.

## 📚 Fonksiyonlar

### Karakter Kontrolü Fonksiyonları

#### ft_isalpha
**Dosya:** `ft_isalpha.c`
**Prototip:** `int ft_isalpha(int c);`

Verilen karakterin alfabetik bir karakter olup olmadığını kontrol eder.
- **Açıklama:** Karakter a-z veya A-Z arasında ise 1, değilse 0 döndürür
- **Özellik:** Bit manipülasyonu ile optimize edilmiş implementasyon
- **Örnek:**
  ```c
  ft_isalpha('a');  // 1 döndürür
  ft_isalpha('Z');  // 1 döndürür
  ft_isalpha('1');  // 0 döndürür
  ```

#### ft_isdigit
**Dosya:** `ft_isdigit.c`
**Prototip:** `int ft_isdigit(int c);`

Verilen karakterin rakam olup olmadığını kontrol eder.
- **Açıklama:** Karakter 0-9 arasında ise 1, değilse 0 döndürür
- **Örnek:**
  ```c
  ft_isdigit('5');  // 1 döndürür
  ft_isdigit('a');  // 0 döndürür
  ```

#### ft_isalnum
**Dosya:** `ft_isalnum.c`
**Prototip:** `int ft_isalnum(int c);`

Verilen karakterin alfanümerik olup olmadığını kontrol eder.
- **Açıklama:** Karakter harf veya rakam ise 1, değilse 0 döndürür

#### ft_isascii
**Dosya:** `ft_isascii.c`
**Prototip:** `int ft_isascii(int c);`

Verilen karakterin ASCII karakter seti içinde olup olmadığını kontrol eder.
- **Açıklama:** Karakter 0-127 arasında ise 1, değilse 0 döndürür

#### ft_isprint
**Dosya:** `ft_isprint.c`
**Prototip:** `int ft_isprint(int c);`

Verilen karakterin yazdırılabilir olup olmadığını kontrol eder.
- **Açıklama:** Karakter yazdırılabilir ise 1, değilse 0 döndürür

### String Manipülasyonu Fonksiyonları

#### ft_strlen
**Dosya:** `ft_strlen.c`
**Prototip:** `size_t ft_strlen(const char *s);`

String'in uzunluğunu hesaplar.
- **Açıklama:** Null karakter görene kadar olan karakter sayısını döndürür
- **Örnek:**
  ```c
  ft_strlen("Hello");  // 5 döndürür
  ft_strlen("");       // 0 döndürür
  ```

#### ft_strchr
**Dosya:** `ft_strchr.c`
**Prototip:** `char *ft_strchr(const char *s, int c);`

String içinde belirtilen karakterin ilk konumunu bulur.
- **Açıklama:** Karakter bulunursa pointer döndürür, bulunamazsa NULL

#### ft_strrchr
**Dosya:** `ft_strrchr.c`
**Prototip:** `char *ft_strrchr(const char *s, int c);`

String içinde belirtilen karakterin son konumunu bulur.

#### ft_strncmp
**Dosya:** `ft_strncmp.c`
**Prototip:** `int ft_strncmp(const char *s1, const char *s2, size_t n);`

İki string'i belirtilen karakter sayısı kadar karşılaştırır.
- **Açıklama:** s1 < s2 ise negatif, s1 > s2 ise pozitif, eşit ise 0 döndürür

#### ft_strnstr
**Dosya:** `ft_strnstr.c`
**Prototip:** `char *ft_strnstr(const char *haystack, const char *needle, size_t len);`

Bir string içinde başka bir string'i arar (sınırlı uzunlukta).

#### ft_strlcpy
**Dosya:** `ft_strlcpy.c`
**Prototip:** `size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);`

Güvenli string kopyalama fonksiyonu.
- **Açıklama:** Buffer overflow'u önleyerek string kopyalar

#### ft_strlcat
**Dosya:** `ft_strlcat.c`
**Prototip:** `size_t ft_strlcat(char *dst, const char *src, size_t dstsize);`

Güvenli string birleştirme fonksiyonu.

#### ft_strdup
**Dosya:** `ft_strdup.c`
**Prototip:** `char *ft_strdup(const char *s1);`

String'in dinamik kopyasını oluşturur.
- **Açıklama:** Malloc kullanarak yeni string oluşturur

### Karakter Dönüşüm Fonksiyonları

#### ft_toupper
**Dosya:** `ft_toupper.c`
**Prototip:** `int ft_toupper(int c);`

Küçük harfi büyük harfe çevirir.
- **Örnek:**
  ```c
  ft_toupper('a');  // 'A' döndürür
  ft_toupper('Z');  // 'Z' döndürür (değişmez)
  ```

#### ft_tolower
**Dosya:** `ft_tolower.c`
**Prototip:** `int ft_tolower(int c);`

Büyük harfi küçük harfe çevirir.

### Bellek Yönetimi Fonksiyonları

#### ft_memset
**Dosya:** `ft_memset.c`
**Prototip:** `void *ft_memset(void *b, int c, size_t len);`

Bellek alanını belirtilen değerle doldurur.
- **Açıklama:** Belirtilen byte değerini belirtilen uzunluk kadar yazar
- **Örnek:**
  ```c
  char buffer[10];
  ft_memset(buffer, 'A', 5);  // İlk 5 byte'ı 'A' ile doldurur
  ```

#### ft_bzero
**Dosya:** `ft_bzero.c`
**Prototip:** `void ft_bzero(void *s, size_t n);`

Bellek alanını sıfırlar.
- **Açıklama:** ft_memset'in sıfır değeriyle çağrılması

#### ft_memcpy
**Dosya:** `ft_memcpy.c`
**Prototip:** `void *ft_memcpy(void *dst, const void *src, size_t n);`

Bellek alanını kopyalar (overlapping olmayan bölgeler için).

#### ft_memmove
**Dosya:** `ft_memmove.c`
**Prototip:** `void *ft_memmove(void *dst, const void *src, size_t len);`

Bellek alanını güvenli şekilde kopyalar (overlapping bölgeler için uygun).

#### ft_memchr
**Dosya:** `ft_memchr.c`
**Prototip:** `void *ft_memchr(const void *s, int c, size_t n);`

Bellek alanında belirtilen byte'ı arar.

#### ft_memcmp
**Dosya:** `ft_memcmp.c`
**Prototip:** `int ft_memcmp(const void *s1, const void *s2, size_t n);`

İki bellek alanını karşılaştırır.

#### ft_calloc
**Dosya:** `ft_calloc.c`
**Prototip:** `void *ft_calloc(size_t count, size_t size);`

Sıfırlanmış bellek alanı tahsis eder.
- **Açıklama:** malloc + bzero kombinasyonu

### Dönüşüm Fonksiyonları

#### ft_atoi
**Dosya:** `ft_atoi.c`
**Prototip:** `int ft_atoi(const char *str);`

String'i integer'a çevirir.
- **Açıklama:** Whitespace'leri atlar, işaret kontrol eder, sayısal değeri döndürür
- **Özellik:** Optimize edilmiş bit manipülasyonu implementasyonu
- **Örnek:**
  ```c
  ft_atoi("  -123");  // -123 döndürür
  ft_atoi("42abc");   // 42 döndürür
  ```

#### ft_itoa
**Dosya:** `ft_itoa.c`
**Prototip:** `char *ft_itoa(int n);`

Integer'ı string'e çevirir.
- **Açıklama:** Dinamik bellek kullanarak sayıyı string'e dönüştürür
- **Özellik:** Negatif sayılar ve INT_MIN için özel handling
- **Örnek:**
  ```c
  ft_itoa(-123);  // "-123" string'ini döndürür
  ft_itoa(0);     // "0" döndürür
  ```

### Gelişmiş String Fonksiyonları

#### ft_substr
**Dosya:** `ft_substr.c`
**Prototip:** `char *ft_substr(char const *s, unsigned int start, size_t len);`

String'in alt string'ini çıkarır.
- **Açıklama:** Belirtilen pozisyondan başlayarak belirtilen uzunlukta substring oluşturur

#### ft_strjoin
**Dosya:** `ft_strjoin.c`
**Prototip:** `char *ft_strjoin(char const *s1, char const *s2);`

İki string'i birleştirir.
- **Açıklama:** Yeni dinamik bellek alanında iki string'i birleştirir

#### ft_strtrim
**Dosya:** `ft_strtrim.c`
**Prototip:** `char *ft_strtrim(char const *s1, char const *set);`

String'in başındaki ve sonundaki belirtilen karakterleri kırpar.
- **Açıklama:** Set içindeki karakterleri baştan ve sondan temizler

#### ft_split
**Dosya:** `ft_split.c`
**Prototip:** `char **ft_split(char const *s, char c);`

String'i belirtilen karaktere göre böler.
- **Açıklama:** Delimiter karakterine göre string array'i oluşturur
- **Özellik:** Dynamic memory allocation ve error handling
- **Örnek:**
  ```c
  ft_split("hello,world,42", ',');  // ["hello", "world", "42", NULL]
  ```

#### ft_strmapi
**Dosya:** `ft_strmapi.c`
**Prototip:** `char *ft_strmapi(char const *s, char (*f)(unsigned int, char));`

String'in her karakterine fonksiyon uygular (index ile birlikte).
- **Açıklama:** Higher-order function - her karaktere index ve fonksiyon uygular

#### ft_striteri
**Dosya:** `ft_striteri.c`
**Prototip:** `void ft_striteri(char *s, void (*f)(unsigned int, char*));`

String'in her karakterine fonksiyon uygular (mutable versiyon).

### Dosya Descriptor Fonksiyonları

#### ft_putchar_fd
**Dosya:** `ft_putchar_fd.c`
**Prototip:** `void ft_putchar_fd(char c, int fd);`

Belirtilen dosya descriptor'a karakter yazar.

#### ft_putstr_fd
**Dosya:** `ft_putstr_fd.c`
**Prototip:** `void ft_putstr_fd(char *s, int fd);`

Belirtilen dosya descriptor'a string yazar.

#### ft_putendl_fd
**Dosya:** `ft_putendl_fd.c`
**Prototip:** `void ft_putendl_fd(char *s, int fd);`

Belirtilen dosya descriptor'a string + newline yazar.

#### ft_putnbr_fd
**Dosya:** `ft_putnbr_fd.c`
**Prototip:** `void ft_putnbr_fd(int n, int fd);`

Belirtilen dosya descriptor'a sayı yazar.

### Bonus: Linked List Fonksiyonları

#### t_list Yapısı
```c
typedef struct s_list
{
    void            *content;
    struct s_list   *next;
} t_list;
```

#### ft_lstnew
**Dosya:** `ft_lstnew.c`
**Prototip:** `t_list *ft_lstnew(void *content);`

Yeni liste node'u oluşturur.
- **Açıklama:** Content ile yeni liste elemanı yaratır

#### ft_lstadd_front
**Dosya:** `ft_lstadd_front.c`
**Prototip:** `void ft_lstadd_front(t_list **lst, t_list *new);`

Listenin başına eleman ekler.

#### ft_lstsize
**Dosya:** `ft_lstsize.c`
**Prototip:** `int ft_lstsize(t_list *lst);`

Liste boyutunu hesaplar.

#### ft_lstlast
**Dosya:** `ft_lstlast.c`
**Prototip:** `t_list *ft_lstlast(t_list *lst);`

Listenin son elemanını döndürür.

#### ft_lstadd_back
**Dosya:** `ft_lstadd_back.c`
**Prototip:** `void ft_lstadd_back(t_list **lst, t_list *new);`

Listenin sonuna eleman ekler.

#### ft_lstdelone
**Dosya:** `ft_lstdelone.c`
**Prototip:** `void ft_lstdelone(t_list *lst, void (*del)(void *));`

Tek liste elemanını siler.

#### ft_lstclear
**Dosya:** `ft_lstclear.c`
**Prototip:** `void ft_lstclear(t_list **lst, void (*del)(void*));`

Tüm listeyi temizler.

#### ft_lstiter
**Dosya:** `ft_lstiter.c`
**Prototip:** `void ft_lstiter(t_list *lst, void (*f)(void *));`

Liste elemanlarının her birine fonksiyon uygular.

#### ft_lstmap
**Dosya:** `ft_lstmap.c`
**Prototip:** `t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));`

Liste elemanlarına fonksiyon uygulayarak yeni liste oluşturur.

## 🔧 Kullanım

### Derleme
```bash
# Temel fonksiyonları derle
make

# Bonus fonksiyonları da dahil et
make bonus

# Temizlik
make clean      # Object dosyalarını sil
make fclean     # Kütüphane dosyasını da sil
make re         # Temizle ve yeniden derle
```

### Kullanım
```c
#include "libft.h"

int main()
{
    char *str = ft_strdup("Hello World");
    char **words = ft_split(str, ' ');
    
    ft_putstr_fd(words[0], 1);  // "Hello" yazdırır
    ft_putchar_fd('\n', 1);
    
    // Bellek temizliği
    free(str);
    // words array'ini de temizle...
    
    return 0;
}
```

### Linkleme
```bash
# Derleme
gcc -Wall -Wextra -Werror -c your_file.c
gcc your_file.o -L. -lft -o your_program
```

## 🎯 Öğrenilen Kavramlar

1. **Pointer Manipülasyonu**: C dilinde pointer kullanımı ve bellek yönetimi
2. **Dynamic Memory Allocation**: malloc, free kullanımı ve memory leak'lerin önlenmesi
3. **String Handling**: C'de string işlemleri ve buffer overflow koruması
4. **Bit Manipulation**: Performans optimizasyonu için bit işlemleri
5. **Data Structures**: Linked list implementasyonu ve operations
6. **Function Pointers**: Higher-order functions ve callback implementasyonu
7. **Error Handling**: Null pointer checks ve edge case handling
8. **Makefile**: Automated build system ve compilation rules

## 📋 Notlar

- Tüm fonksiyonlar norminette uyumlu olarak yazılmıştır
- Memory leak'ler valgrind ile test edilmiştir
- Error handling her fonksiyonda titizlikle implement edilmiştir
- Standart kütüphane fonksiyonlarıyla tam uyumluluk sağlanmıştır
- Bonus bölümü gelişmiş veri yapısı kullanımını gösterir
