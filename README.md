# 42 Kocaeli Common Core - Philosophers
## Dining Philosophers Problem (Yemek Yiyen Filozoflar Problemi)

Bu proje, 42 Okulu Common Core programının klasik eşzamanlılık (concurrency) ve senkronizasyon problemidir. Dijkstra'nın ünlü "Dining Philosophers Problem" algoritmasını pthread kütüphanesi ve mutex'ler kullanarak çözmektedir. Proje, thread yönetimi, race condition, deadlock önleme ve kaynak paylaşımı konularında derin bir anlayış kazandırmayı amaçlar.

## 📖 Problem Tanımı

Filozoflar bir yuvarlak masada otururlar. Her filozofun önünde bir tabak makarna ve sağında-solunda birer çatal vardır. Bir filozof düşünür, acıkınca yemek yer ve sonra uyur. Yemek yemek için iki çatala ihtiyacı vardır (sağındaki ve solundaki). Amaç, filozofların ölmeden (belirli bir süre yemek yemeden) yaşamalarını sağlamaktır.

### Kurallar:
- Filozoflar yemek yerken, uyurken veya düşünürken olabilirler
- İki çatal olmadan yemek yiyemezler
- Yemek bitince çatalları masaya bırakırlar
- Bir filozof belirli süre yemek yemezse ölür
- Filozoflar birbirleriyle konuşmazlar
- Data race olmamalıdır

## 📁 Dosya Yapısı

### philo.h
**Açıklama:** Tüm veri yapıları, fonksiyon prototipleri ve include direktifleri

**Veri Yapıları:**
- `t_fork`: Çatal yapısı (mutex ve durum bilgisi)
- `t_philo`: Filozof yapısı (ID, thread, başlangıç zamanı, yeme sayısı)
- `t_table`: Masa yapısı (tüm parametreler ve paylaşılan kaynaklar)

**Mutex'ler:**
- `fork`: Her çatal için mutex
- `thinking`: Düşünme durumu için mutex
- `die`: Ölüm kontrolü için mutex
- `starting_time`: Başlangıç zamanı için mutex
- `finish_optional`: Opsiyonel bitiş kontrolü için mutex

### main.c
**Açıklama:** Programın giriş noktası

**Fonksiyonlar:**
- `main()`: Argüman kontrolü, masa oluşturma, simülasyon başlatma ve temizleme

**İşlevler:**
- Komut satırı argümanlarını kontrol eder (4 veya 5 argüman)
- Masa yapısını oluşturur ve başlatır
- Filozof simülasyonunu çalıştırır
- Kaynakları temizler
- Ölüm durumunda bilgi verir

### philo1.c
**Açıklama:** Başlatma, doğrulama ve temizleme fonksiyonları

**Fonksiyonlar:**
- `print_invalid_arguments()`: Geçersiz argüman hatası mesajı
- `control()`: Argüman formatı kontrolü (sadece pozitif sayılar)
- `clear()`: Bellek ve mutex'lerin temizlenmesi
- `init_philos()`: Filozof yapılarının başlatılması
- `create_table()`: Masa yapısının oluşturulması ve çatalların başlatılması

**Özellikler:**
- Tek filozof durumu için özel kontrol
- Çift/tek filozof sayısına göre fork state optimizasyonu
- Dinamik bellek yönetimi

### philo2.c
**Açıklama:** Zamanlama, senkronizasyon ve çatal operasyonları

**Fonksiyonlar:**
- `current()`: Mevcut zamanı milisaniye cinsinden döndürür (gettimeofday kullanarak)
- `passing_time()`: Belirtilen süre kadar bekler (usleep ile)
- `check_die()`: Herhangi bir filozofun ölüp ölmediğini kontrol eder
- `waiting()`: Çatalların uygun duruma gelmesini bekler
- `fork_operation()`: Çatal alma işlemlerini yönetir

**Senkronizasyon Stratejisi:**
- Çift ID'li filozoflar önce sağdaki çatalı alır
- Tek ID'li filozoflar önce soldaki çatalı alır
- Deadlock önleme mekanizması
- Her işlemde ölüm kontrolü

### philo3.c
**Açıklama:** Filozof yaşam döngüsü ve kontrol thread'i

**Fonksiyonlar:**
- `life()`: Yemek yeme, uyuma ve düşünme döngüsü
- `t_func()`: Her filozof thread'inin ana fonksiyonu
- `die()`: Filozof ölüm durumunu işler
- `die_control()`: Ölüm kontrolü thread'i (tüm filozofları sürekli kontrol eder)
- `philo()`: Ana simülasyon fonksiyonu (thread'leri oluşturur ve yönetir)

**Yaşam Döngüsü:**
1. Çatalları bekle
2. Çatalları al
3. Yemek ye (time_to_eat)
4. Çatalları bırak
5. Uyu (time_to_sleep)
6. Düşün
7. Tekrar et veya opsiyonel yeme sayısına ulaşınca bitir

### u_int64_atoi.c
**Açıklama:** String'i unsigned 64-bit integer'a çevirme fonksiyonu

**Fonksiyonlar:**
- `ft_uatoi()`: Pozitif sayı string'ini u_int64_t'ye dönüştürür

**Özellikler:**
- '+' işareti desteği
- Sadece rakamları işler
- Overflow kontrolü yok (42 normları gereği)

### Makefile
**Açıklama:** Proje derleme ve temizleme kuralları

**Hedefler:**
- `all`: Projeyi derler
- `clean`: Çalıştırılabilir dosyayı siler
- `fclean`: clean ile aynı
- `re`: Yeniden derleme (fclean + all)

**Derleme Bayrakları:**
- `-Wall -Wextra -Werror`: Tüm uyarıları hata olarak işle
- İsteğe bağlı: `-pthread -fsanitize=thread -g` (thread debugging)

## 🔧 Kullanım

### Derleme
```bash
cd philo
make
```

### Çalıştırma
```bash
./philo [1] [2] [3] [4] [5 (opsiyonel)]
```

**Parametreler:**
- `[1]` number_of_philosophers: Filozof sayısı
- `[2]` time_to_die: Ölüm süresi (ms)
- `[3]` time_to_eat: Yemek yeme süresi (ms)
- `[4]` time_to_sleep: Uyku süresi (ms)
- `[5]` number_of_times_each_philosopher_must_eat: Her filozofun yemesi gereken minimum sayı (opsiyonel)

### Örnekler
```bash
# Temel kullanım - 4 filozof, 410ms ölüm, 200ms yemek, 200ms uyku
./philo 4 410 200 200

# Opsiyonel parametre ile - her filozof 5 kez yemek yiyecek
./philo 5 800 200 200 5

# Tek filozof durumu
./philo 1 800 200 200

# Ölüm testi
./philo 4 310 200 100
```

### Beklenen Çıktı Formatı
```
[timestamp] [philo_id] has taken a fork
[timestamp] [philo_id] is eating
[timestamp] [philo_id] is sleeping
[timestamp] [philo_id] is thinking
[timestamp] [philo_id] died
```

**Renk Kodları:**
- 🔵 Cyan: Zaman damgası
- 🟢 Yeşil: Filozof aksiyonları
- 🔴 Kırmızı: Ölüm durumu

## 🎯 Öğrenilen Kavramlar

1. **Thread Yönetimi**: pthread_create, pthread_join kullanımı
2. **Mutex'ler**: pthread_mutex_lock, pthread_mutex_unlock ile senkronizasyon
3. **Race Condition**: Paylaşılan kaynakların güvenli kullanımı
4. **Deadlock Önleme**: Çatal alma sıralaması ile deadlock'tan kaçınma
5. **Zamanlama**: gettimeofday ile hassas zaman ölçümü
6. **Data Race**: Mutex'lerle veri yarışı (data race) önleme
7. **Eşzamanlılık**: Paralel çalışan thread'lerin koordinasyonu
8. **Kaynak Yönetimi**: Bellek ve mutex'lerin doğru şekilde temizlenmesi

## 🔍 Algoritma Detayları

### Deadlock Önleme Stratejisi
- **Çift ID'li filozoflar**: Önce sağ çatalı (fork_id2), sonra sol çatalı (fork_id1) alır
- **Tek ID'li filozoflar**: Önce sol çatalı (fork_id1), sonra sağ çatalı (fork_id2) alır
- **İstisna**: Tek sayıda filozof varsa, son filozof için özel durum

### State Machine
```
THINKING → WAITING → TAKING_FORKS → EATING → SLEEPING → THINKING
```

### Timing Kritik Noktalar
- Filozofun son yemek zamanı her yemek sonrası güncellenir
- Ölüm kontrolü thread'i sürekli tüm filozofları kontrol eder
- `current() - starting_time > time_to_die` kontrolü ile ölüm tespiti

### Fork State Sistemi
- `state = 0`: Çatal boş (fork_id % 2 == 0 için)
- `state = 1`: Çatal dolu (fork_id % 2 == 1 için)
- Tek filozof sayısında ilk çatal özel durum

## 📋 Notlar

- Program `-Wall -Wextra -Werror` ile derlenmiştir
- Norm kurallarına uygun yazılmıştır (42 coding standards)
- Data race ve memory leak bulunmamaktadır
- 10ms'den fazla gecikme olmaması için usleep(100) kullanılmıştır
- Bir filozofun ölümü 10ms içinde tespit edilir
- Valgrind ve Helgrind ile test edilmiştir

## ⚠️ UYARI

**ÖNEMLİ:** Bu proje 42 Kocaeli'nde tamamlanmış olup, **MacOS** üzerinde geliştirilmiştir. Zamanında bazı kişisel kontrol standartlarına (null check, malloc hata kontrolü, fonksiyon return değeri kontrolü, vb.) dikkat edilmemiştir. Önceki projelerimi bu doğrultuda düzelterek GitHub'a yüklememe rağmen, bu projeyi orijinal haliyle yüklemek ve sonradan düzeltme yapmak için zaman harcamamak istedim. Proje mantıksal olarak doğru çalışmaktadır ve temel kavramları göstermektedir, ancak production-level hata kontrolü için bazı ek kontroller eklenmelidir.

