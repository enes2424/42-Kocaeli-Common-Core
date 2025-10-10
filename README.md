# 42 Kocaeli Push Swap
## Sorting Algorithms with Stack Operations (Stack İşlemleri ile Sıralama Algoritmaları)

Bu proje, 42 Okulu Common Core müfredatının temel algoritmik projelerinden biridir. İki stack kullanarak sınırlı sayıda işlemle sayıları sıralamaya odaklanır. Algoritma optimizasyonu, veri yapıları ve sıralama stratejilerini geliştirmek için tasarlanmıştır.

## 📚 Ana Dosyalar

### push_swap.c
**Ana Program Dosyası**

Ana push_swap programının giriş noktası.
- **Fonksiyon:** `int main(int argc, char **argv)`
- **Açıklama:** Argümanları işler, stack oluşturur ve uygun sıralama algoritmasını seçer
- **Özellikler:**
  - Tek string argüman desteği (`"1 2 3"` formatında)
  - Çoklu argüman desteği (`1 2 3` formatında)
  - Eleman sayısına göre algoritma seçimi
- **Örnek:**
  ```bash
  ./push_swap 3 1 2          # Çoklu argüman
  ./push_swap "3 1 2"        # Tek string argüman
  ```

### push_swap.h
**Header Dosyası**

Tüm fonksiyon prototipleri ve yapı tanımları.
- **Yapı:** `t_push_swap` - Ana program yapısı
- **İçerik:**
  - Stack A ve B için linked list pointerları
  - Argüman işleme değişkenleri
  - Tüm fonksiyon prototipleri
- **Özellikler:**
  - Stack işlem fonksiyonları
  - Sıralama algoritma fonksiyonları
  - Yardımcı utility fonksiyonları

### stack_operations.c
**Temel Stack İşlemleri**

Temel stack manipülasyon fonksiyonları.
- **Fonksiyonlar:**
  - `push()` - Stack'e eleman ekleme
  - `pop()` - Stack'ten eleman çıkarma
  - `get()` - Belirli index'teki elemanı okuma
  - `set()` - Belirli index'teki elemanı değiştirme
- **Özellikler:**
  - Linked list tabanlı stack implementasyonu
  - Memory management ile güvenli işlemler
  - Index-based erişim desteği

### functions.c
**Push_Swap İşlem Fonksiyonları**

Push_swap kurallarına uygun temel stack işlemleri.
- **Fonksiyonlar:**
  - `s()` - Swap: İlk iki elemanı değiştir
  - `p()` - Push: Bir stack'ten diğerine eleman taşı
  - `r()` - Rotate: Stack'i yukarı kaydır
  - `rr()` - Reverse Rotate: Stack'i aşağı kaydır
  - `min()` - Minimum elemanın index'ini bul
- **Push_Swap Kuralları:**
  - sa/sb: Stack A/B'nin ilk iki elemanını değiştir
  - pa/pb: Stack B/A'dan A/B'ye eleman taşı
  - ra/rb: Stack A/B'yi yukarı kaydır
  - rra/rrb: Stack A/B'yi aşağı kaydır

### other_functions.c
**Yardımcı Utility Fonksiyonları**

Stack analizi ve validation fonksiyonları.
- **Fonksiyonlar:**
  - `max()` - Maximum elemanın index'ini bul
  - `is_it_in_order()` - Stack'in sıralı olup olmadığını kontrol et
  - `in_list()` - Elemanın stack'te olup olmadığını kontrol et
  - `has_error_and_create_stack()` - Hata kontrolü ve stack oluşturma
  - `function()` - Temel sıralama yardımcı fonksiyonu
- **Validation:**
  - Duplicate sayı kontrolü
  - Geçersiz karakter kontrolü
  - Integer overflow kontrolü

### other_other_functions.c
**İşlem Wrapper Fonksiyonları**

Push_swap işlemlerini output ile birleştiren wrapper'lar.
- **Fonksiyonlar:**
  - `p_operations()` - Push işlemi + output
  - `s_operations()` - Swap işlemi + output
  - `r_operations()` - Rotate işlemi + output
  - `rr_operations()` - Reverse rotate işlemi + output
  - `error()` - Hata durumu yönetimi
- **Özellikler:**
  - Her işlem için uygun output ("sa", "pb", "ra", vb.)
  - Memory cleanup işlemleri
  - Error handling ve program sonlandırma

### sort.c
**Sıralama Algoritmaları - Ana Fonksiyonlar**

Farklı boyutlar için optimize edilmiş sıralama algoritmaları.
- **Fonksiyonlar:**
  - `basic_sort()` - 10'dan az eleman için temel sıralama
  - `sort_three_arg()` - Sadece 3 eleman için özel sıralama
  - `sort_array()` - Array sıralama (pivot hesabı için)
  - `get_middle()` - Pivot değeri hesaplama
  - `is_sorted()` - Stack'in sıralı olup olmadığını kontrol
- **Strateji:**
  - 3 eleman: Optimize edilmiş direkt çözüm
  - 4-10 eleman: Temel sıralama algoritması
  - 10+ eleman: Quicksort algoritması

### sort2.c
**Quicksort Algoritması İmplementasyonu**

Büyük veri setleri için optimize edilmiş quicksort algoritması.
- **Fonksiyonlar:**
  - `quicksort_a()` - Stack A için quicksort
  - `quicksort_b()` - Stack B için quicksort
  - `quicksort_3a()` - Stack A'da 3 elemanlı küçük gruplar
  - `quicksort_3b()` - Stack B'de 3 elemanlı küçük gruplar
- **Algoritma:**
  - Divide and conquer yaklaşımı
  - Pivot-based partitioning
  - Recursive çözüm
  - O(n log n) ortalama karmaşıklık

### ft_atoi.c
**String to Integer Dönüştürme**

Geliştirilmiş atoi fonksiyonu with error handling.
- **Fonksiyon:** `ft_atoi(const char *str, t_push_swap *p, void (*del)(void*))`
- **Özellikler:**
  - Integer overflow kontrolü
  - Whitespace handling
  - Pozitif/negatif sayı desteği
  - Error durumunda program sonlandırma
- **Sınırlar:**
  - INT_MIN ile INT_MAX arası değerler
  - Geçersiz format kontrolü

### checker.c
**Bonus: İşlem Doğrulayıcı**

Push_swap çıktısının doğruluğunu kontrol eden program.
- **Fonksiyonlar:**
  - `s_operation()` - Swap işlemlerini (sa, sb, ss) uygula
  - `r_operation()` - Rotate işlemlerini (ra, rb, rr) uygula
  - `cmp_operations()` - Tüm işlem türlerini karşılaştır ve uygula
  - `operations()` - Standard input'tan işlemleri okur ve uygular
- **Desteklenen İşlemler:**
  - `sa, sb, ss` - Swap operations
  - `pa, pb` - Push operations  
  - `ra, rb, rr` - Rotate operations
  - `rra, rrb, rrr` - Reverse rotate operations
- **Kullanım:**
  ```bash
  ./push_swap 3 1 2 | ./checker 3 1 2  # "OK" veya "KO"
  ```
- **Doğrulama:**
  - İşlem geçerliliği kontrolü
  - Final stack durumu kontrolü
  - "OK" (başarılı) veya "KO" (başarısız) çıktısı

### libft/
**42 Okulu Kütüphanesi**

Proje boyunca kullanılan temel C kütüphanesi.
- **Klasör:** `libft/` - 42 standardı utility fonksiyonları
- **İçerik:**
  - String işleme fonksiyonları (`ft_strlen`, `ft_strdup`, `ft_split` vb.)
  - Memory yönetimi (`ft_calloc`, `ft_memcpy`, `ft_memset` vb.)
  - Linked list işlemleri (`ft_lstnew`, `ft_lstadd_back`, `ft_lstclear` vb.)
  - I/O fonksiyonları (`ft_printf`, `get_next_line` vb.)
- **Özellikler:**
  - Push_swap için gerekli tüm yardımcı fonksiyonlar
  - Memory management fonksiyonları
  - Printf ve get_next_line implementasyonları

### pipex.c
**İlgisiz Dosya** 

Bu dosya push_swap projesiyle doğrudan ilgili değildir.
- **Açıklama:** Farklı bir 42 projesi (pipex) dosyası
- **İçerik:** Pipe ve process yönetimi
- **Push_swap İlişkisi:** Yok - workspace'te kalmış eski dosya

### Makefile
**Derleme Otomasyonu**

Projeyi derlemek için gerekli Makefile.
- **Hedefler:**
  - `make` / `make all` - push_swap ve checker programlarını derle
  - `make clean` - Object dosyalarını temizle  
  - `make fclean` - Tüm derleme dosyalarını temizle
  - `make re` - Yeniden derle
- **Bağımlılıklar:**
  - Libft kütüphanesi otomatik derlenir
  - CC, CFLAGS (-Wall -Wextra -Werror) kullanılır
  - Tüm kaynak dosyalar tek static library'de birleştirilir

## 🔧 Kullanım

### Derleme
```bash
# Projeyi derle
make

# Sadece temizlik
make clean

# Tam temizlik
make fclean

# Yeniden derleme
make re
```

### Push_swap Çalıştırma
```bash
# Temel kullanım
./push_swap 3 1 4 5 9 2

# Tek string argüman
./push_swap "3 1 4 5 9 2"

# Negatif sayılarla
./push_swap -5 -2 0 1 3

# Büyük sayı seti
./push_swap 42 1 2 3 4 5 6 7 8 9 10
```

### Checker ile Doğrulama
```bash
# Pipeline kullanımı
./push_swap 3 1 2 | ./checker 3 1 2

# Manuel test
./checker 3 1 2
sa
ra
rra
^D

# Test dosyası ile
echo -e "sa\nrra\npb" | ./checker 3 1 2
```

### Test Senaryoları
```bash
# Küçük set (3-5 eleman)
./push_swap 2 1 3 | wc -l  # İşlem sayısını say

# Orta set (100 eleman)
ARG=$(seq 1 100 | shuf | tr '\n' ' ')
./push_swap $ARG | wc -l

# Büyük set (500 eleman)
ARG=$(seq 1 500 | shuf | tr '\n' ' ')
./push_swap $ARG | wc -l
```

## 🎯 Algoritma Stratejileri

### 1. **3 Eleman Sıralaması**
- **Yöntem:** Direkt optimizasyon
- **İşlem Sayısı:** Maximum 2 işlem
- **Strateji:** Tüm permütasyonlar için önceden hesaplanmış çözümler

### 2. **Küçük Setler (4-10 eleman)**
- **Yöntem:** Temel sıralama
- **Strateji:** Minimum elemanı bul → A'nın başına getir → B'ye taşı
- **Özellik:** Basit ama etkili yaklaşım

### 3. **Büyük Setler (11+ eleman)**
- **Yöntem:** Optimize edilmiş quicksort
- **Strateji:** Divide and conquer with pivot
- **Beklenen Performans:** 
  - 100 eleman: ~500-700 işlem (iyi implementasyon)
  - 500 eleman: ~5000-7000 işlem (iyi implementasyon)
  - Ortalama: O(n log n), en kötü: O(n²)

### 4. **Pivot Stratejisi**
- **Hesaplama:** Medyan bulma algoritması
- **Partitioning:** Pivot'tan küçükler B'ye, büyükler A'da kalır
- **Recursive:** Her iki stack için ayrı ayrı sıralama

## 📊 Performans Kriterleri

### Push_swap Puanlama (42 Evaluation)
- **3 eleman:** 3 işlemden az = 5 puan
- **5 eleman:** 12 işlemden az = 5 puan  
- **100 eleman:** 700 işlemden az = 5 puan (1500'den az = 4 puan, 1300'den az = 3 puan)
- **500 eleman:** 5500 işlemden az = 5 puan (11500'den az = 4 puan, 7000'den az = 3 puan)

### Algoritma Karmaşıklığı
- **Zaman:** O(n log n) ortalama, O(n²) en kötü
- **Alan:** O(n) - iki stack için
- **İşlem:** O(n log n) push_swap işlemi

## 🛠️ Öğrenilen Kavramlar

1. **Veri Yapıları**: Stack implementasyonu, linked list kullanımı
2. **Algoritma Tasarımı**: Divide and conquer, optimization strategies
3. **Sıralama Algoritmaları**: Quicksort, insertion sort, custom algorithms
4. **Memory Management**: Dynamic allocation, proper cleanup
5. **Error Handling**: Input validation, overflow detection
6. **Performance Optimization**: Algorithm selection, operation minimization
7. **Recursive Programming**: Quicksort implementation, stack operations
8. **C Programming**: Advanced pointer usage, modular design

## 📋 Önemli Notlar

- **Memory Leaks:** Tüm allocated memory düzgün şekilde free edilir
- **Error Handling:** Invalid input durumlarında "Error" mesajı ve program sonlandırma
- **Normalization:** 42 norm kurallarına uygun kod yazımı
- **Modularity:** Her dosya belirli bir sorumluluğu üstlenir
- **Efficiency:** Minimum işlem sayısı ile maksimum performans hedeflenir
