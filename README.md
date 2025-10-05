# 42 Kocaeli Get Next Line
## Dosya Okuma ve Bellek Yönetimi (File Reading and Memory Management)

Bu proje, 42 Okulu Common Core müfredatının önemli projelerinden biridir. Dosyalardan satır satır okuma işlemi, statik değişkenler, bellek yönetimi ve buffer kullanımı konularında derinlemesine bilgi ve deneyim kazandırmak için tasarlanmıştır.

## 📚 Dosya Yapısı

### Temel Implementasyon
**Dosyalar:** `get_next_line.c`, `get_next_line.h`, `get_next_line_utils.c`

### Bonus Implementasyon
**Dosyalar:** `get_next_line_bonus.c`, `get_next_line_bonus.h`, `get_next_line_utils_bonus.c`

## 🔧 Ana Fonksiyon

### get_next_line
**Dosya:** `get_next_line.c` / `get_next_line_bonus.c`

Bir dosya tanımlayıcısından (file descriptor) bir seferde bir satır okuyan fonksiyon.
- **Fonksiyon:** `char *get_next_line(int fd)`
- **Parametre:** `fd` - Okunacak dosyanın file descriptor'ı
- **Dönüş Değeri:** 
  - Okunan satır (newline karakteri dahil)
  - `NULL` - Dosya sonu veya hata durumunda
- **Özellik:** Static değişken kullanarak dosya pozisyonunu hatırlar

char *get_next_line(int fd)
{
	static char	*stash = NULL;              // Temel versiyon
	// static char	*stash[10240];          // Bonus versiyon  
	char		buf[BUFFER_SIZE + 1];
	char		*line;
	char		*tmp;
	long		ret;
	
	// Ana okuma döngüsü
	ret = BUFFER_SIZE;
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1 || (ret == 0 && !stash))
			return (special_free(&stash, 0));
		buf[ret] = '\0';
		
		// Buffer'ı stash'e ekle ve newline kontrol et
		if (!ctrl(&stash, &line, -1, buf))
			continue ;
		if (!line)
			return (special_free(&stash, 0));
			
		// Kalan veriyi sakla
		tmp = NULL;
		if (stash[sl(line)])
			tmp = ft_strdup(stash + sl(line), sl(stash) - sl(line));
		return (special_free(&stash, 0), stash = tmp, line);
	}
	return (special_free(&stash, 1));
}
```

**Örnek Kullanım:**
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```
```

## 🎯 İmplementasyon Detayları

### Header Dosyası (get_next_line.h)
- **Buffer Size:** `#define BUFFER_SIZE` ile belirlenebilir
- **Güvenlik Kontrolleri:** 
  - BUFFER_SIZE tanımlanmamışsa 16'ya ayarlanır
  - BUFFER_SIZE ≤ 0 ise otomatik olarak 16'ya ayarlanır
  - BUFFER_SIZE > 5,000,000 ise otomatik olarak 1,000,000'a ayarlanır
- **Include'lar:** `<unistd.h>`, `<stdlib.h>`

### Yardımcı Fonksiyonlar

**Not:** `get_next_line_utils.c` ve `get_next_line_utils_bonus.c` dosyaları boş olup, tüm yardımcı fonksiyonlar ana dosyalarda `static` olarak tanımlanmıştır.

#### sl() - String Length
**Açıklama:** String uzunluğunu hesaplayan dahili fonksiyon
- **Fonksiyon:** `static size_t sl(const char *s)`
- **Özellik:** `strlen()` benzeri fakat dahili implementasyon
- **Konum:** Ana `.c` dosyalarında static fonksiyon olarak

#### ft_strdup() - String Duplicate with Limit
**Açıklama:** Belirtilen karakter sayısı kadar string kopyalayan fonksiyon
- **Fonksiyon:** `static char *ft_strdup(const char *s1, size_t limit)`
- **Özellik:** Sınırlı kopyalama ile bellek optimizasyonu
- **Döndürülen String:** Null-terminated ve heap'te allocated

#### special_free() - Özel Bellek Yönetimi
**Açıklama:** Farklı senaryolar için optimize edilmiş bellek temizleme fonksiyonu
- **Fonksiyon:** `static void *special_free(char **stash, int create_line)`
- **Parametreler:**
  - `create_line = 0`: Sadece belleği temizle, NULL döndür
  - `create_line = 1`: Stash'i kopyala, orijinali temizle ve kopyayı döndür
- **Dönüş:** Koşula göre NULL veya string pointer

#### ctrl() - Kontrol ve Buffer Yönetimi
**Açıklama:** Buffer'dan gelen yeni veriyi mevcut stash ile birleştiren ve satır kontrolü yapan fonksiyon
- **Fonksiyon:** `static int ctrl(char **stash, char **line, size_t i, char *tmp)`
- **Dönüş Değerleri:**
  - `0`: Henüz newline bulunamadı, okumaya devam et
  - `1`: Satır bulundu ve `*line`'a atandı
- **Görevler:**
  - Yeni okunan veriyi stash'e ekleme
  - Newline karakteri arama ve satır çıkarma
  - Memory allocation hata kontrolü

### Bonus Özellikleri

#### Çoklu File Descriptor Desteği
**Dosya:** `get_next_line_bonus.c`

Bonus versiyonu aynı anda birden fazla dosyayı okuyabilir.
- **Özellik:** `static char *stash[10240]` array'i ile 10240 dosyaya kadar destek
- **Avantaj:** Farklı dosyalar arasında geçiş yapabilme
- **Fark:** Temel versiyonda `static char *stash = NULL;`, bonus'ta `static char *stash[10240];`

**Örnek:**
```c
int fd1 = open("file1.txt", O_RDONLY);
int fd2 = open("file2.txt", O_RDONLY);

char *line1 = get_next_line(fd1);  // file1'den oku
char *line2 = get_next_line(fd2);  // file2'den oku
char *line1_2 = get_next_line(fd1); // file1'den devam et
```

## 📋 Teknik Özellikler

### Buffer Yönetimi
- **BUFFER_SIZE:** Compile-time tanımlanabilir buffer boyutu
- **Dinamik Buffer:** `char buf[BUFFER_SIZE + 1]` ile esnek boyut
- **Null Termination:** Buffer'ın her zaman null-terminated olması

### Bellek Optimizasyonu
- **Static Variables:** Dosya pozisyonunu koruma
- **Dinamik Allocation:** Sadece gerekli kadar bellek kullanımı
- **Memory Leaks Prevention:** Özel free fonksiyonu ile bellek sızıntısı önleme

### Hata Yönetimi
- **Read Error:** `read()` fonksiyonundan -1 dönüşü kontrolü
- **Memory Allocation:** `malloc()` başarısızlığı kontrolü
- **Invalid FD:** Geçersiz file descriptor kontrolü

## 🔧 Derleme ve Kullanım

### Temel Derleme
```bash
# Temel versiyon
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c

# Test dosyası ile
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl_test
```

### Bonus Derleme
```bash
# Bonus versiyon
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c

# Test dosyası ile
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main_bonus.c -o gnl_bonus_test
```

### Buffer Size Testi
```bash
# Farklı buffer boyutları ile test
gcc -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c main.c -o gnl_1
gcc -D BUFFER_SIZE=1000 get_next_line.c get_next_line_utils.c main.c -o gnl_1000
gcc -D BUFFER_SIZE=10000000 get_next_line.c get_next_line_utils.c main.c -o gnl_big
```

## 🧪 Test Senaryoları

### Temel Testler
1. **Normal Dosya:** Standart text dosyası okuma
2. **Boş Dosya:** 0 byte dosya işleme
3. **Tek Satır:** Newline olmayan tek satır
4. **Büyük Dosya:** Megabyte seviyesinde dosyalar
5. **Binary Dosya:** Binary içerik ile test
6. **Çok Uzun Satırlar:** BUFFER_SIZE'dan büyük satırlar
7. **Sadece Newline:** Boş satırlar içeren dosyalar

### Buffer Size Testleri
1. **BUFFER_SIZE = 1:** Her karakter için read() çağrısı
2. **BUFFER_SIZE = 10000:** Büyük buffer ile performans
3. **BUFFER_SIZE = 0:** Geçersiz boyut kontrolü (otomatik 16'ya ayarlanır)
4. **BUFFER_SIZE tanımsız:** Default 16 değeri

### Bonus Testleri
1. **Çoklu FD:** Aynı anda 3+ dosya okuma
2. **FD Switching:** Dosyalar arası geçiş
3. **FD Close/Reopen:** Dosya kapatıp yeniden açma
4. **Maksimum FD:** 10240'a kadar dosya desteği

## 📊 Algoritma Analizi

### Zaman Karmaşıklığı
- **O(n):** n = okunan toplam karakter sayısı
- **Buffer Optimization:** Büyük buffer ile daha az system call

### Bellek Karmaşıklığı
- **O(m):** m = en uzun satır uzunluğu
- **Static Memory:** Her FD için constant space

### I/O Optimizasyonu
- **Buffered Reading:** Tek seferde BUFFER_SIZE kadar okuma
- **Minimal System Calls:** Mümkün olan en az read() çağrısı

## 🎯 Öğrenilen Kavramlar

1. **File Descriptors:** Unix dosya sistemi ile etkileşim
2. **Static Variables:** Fonksiyon çağrıları arası veri koruma
3. **Buffer Management:** Efficient I/O operations
4. **Memory Management:** Dinamik bellek yönetimi ve leak prevention
5. **System Calls:** `read()`, `open()`, `close()` kullanımı
6. **Error Handling:** Robust hata yönetimi teknikleri
7. **String Manipulation:** C string işlemleri
8. **Pointer Arithmetic:** Gelişmiş pointer kullanımı

## 📋 Proje Gereksinimleri

### Zorunlu Kısım
- ✅ Bir dosyadan satır satır okuma
- ✅ BUFFER_SIZE makrosu ile buffer boyutu kontrolü
- ✅ Static değişken kullanımı
- ✅ Memory leak olmaması
- ✅ Undefined behavior olmaması

### Bonus Kısım
- ✅ Çoklu file descriptor desteği
- ✅ Aynı anda farklı dosyaları okuyabilme
- ✅ Dosyalar arası geçiş yapabilme

### Kısıtlamalar
- ❌ Global değişken kullanımı yasak
- ❌ `libft` kullanımı yasak
- ❌ `lseek()` fonksiyonu yasak
- ❌ Buffer okuma dışında dosya manipülasyonu yasak

## 🔍 Dikkat Edilmesi Gerekenler

1. **Memory Leaks:** Her `malloc()` için karşılık gelen `free()`
2. **Buffer Overflow:** Buffer boyutu kontrolü
3. **Edge Cases:** Boş dosya, tek karakter, çok büyük satırlar
4. **File Descriptor Validation:** Geçersiz FD kontrolü
5. **Null Pointer Checks:** Pointer'ların geçerliliği
6. **Static Variable Cleanup:** Program sonunda bellek temizliği
7. **Return Value Check:** read() fonksiyonunun dönüş değeri kontrolü
8. **String Termination:** Tüm string'lerin null-terminated olması

Bu proje, sistem seviyesi programlama, bellek yönetimi ve dosya I/O işlemlerinde sağlam bir temel oluşturur ve daha ileri seviye C projelerine hazırlık sağlar.
