# 42 Kocaeli So Long
## 2D Oyun Motoru - MiniLibX ile Platformer Oyunu

Bu proje, 42 Okulu'nun grafik programlama modülüdür. MiniLibX kütüphanesi kullanılarak geliştirilmiş bir 2D platformer oyunudur. Oyun motoru temelleri, olay yönetimi, sprite animasyonları ve oyun döngüsü konularını kapsar.

## 🎮 Oyun Hakkında

**So_long**, klasik 2D platformer tarzında bir koleksiyon oyunudur. Oyuncu karakteri haritada dolaşarak tüm madeni paraları toplamaya çalışır ve tamamlandıktan sonra çıkış kapısından ayrılır.

### Temel Mekanikler
- **Hareket**: WASD tuşları ile 4 yönlü hareket
- **Koleksiyon**: Haritadaki tüm madeni paraları toplama
- **Çıkış**: Tüm paralar toplandıktan sonra kapıdan çıkış
- **Skor Sistemi**: Her para için 500 puan
- **Adım Sayacı**: Her hareket konsolda gösterilir

### Bonus Özellikler
- **Düşman Sistemi**: Hareket eden zombie karakterler
- **Animasyonlar**: Karakter ve düşman sprite animasyonları
- **Gelişmiş Grafik**: Çoklu creeper türleri ve görsel efektler

## 📁 Proje Yapısı

### Ana Dosyalar
```
so_long.h              # Ana header dosyası
main.c                 # Program giriş noktası
so_long.c              # Rendering ve temel oyun mantığı
so_long_other.c        # Hareket kontrolleri
so_long_other2.c       # Tuş yönetimi ve olay işleyiciler
so_long_other3.c       # MLX materyal yükleme ve harita yaratma
so_long_other4.c       # Harita validasyonu ve oyuncu bulma
```

### Bonus Dosyalar
```
bonus/
├── so_long_bonus.h         # Bonus header dosyası
├── main_bonus.c            # Bonus program giriş noktası
├── so_long_bonus.c         # Bonus oyun mantığı
├── so_long_other_bonus.c   # Bonus hareket kontrolleri
├── so_long_other2_bonus.c  # Bonus tuş ve düşman yönetimi
├── so_long_other3_bonus.c  # Bonus MLX materyal yükleme
└── so_long_other4_bonus.c  # Bonus harita validasyonu
```

### Grafik Kaynakları
```
textures/
├── front.xpm      # Oyuncu ön sprite
├── back.xpm       # Oyuncu arka sprite
├── left.xpm       # Oyuncu sol sprite
├── right.xpm      # Oyuncu sağ sprite
├── grass.xpm      # Zemin texture
├── wall.xpm       # Duvar texture
├── coin.xpm       # Madeni para sprite
└── door.xpm       # Çıkış kapısı sprite

bonus/textures/
├── blue_creeper.xpm    # Mavi creeper
├── green_creeper.xpm   # Yeşil creeper
├── purple_creeper.xpm  # Mor creeper
├── red_creeper.xpm     # Kırmızı creeper
├── enemy_left.xpm      # Düşman sol sprite
└── enemy_right.xpm     # Düşman sağ sprite
```

### Harita Dosyaları
```
maps/
├── map1.ber       # Basit test haritası
├── map2.ber       # Orta seviye harita
├── map3.ber       # Karmaşık harita
├── map4.ber       # Büyük harita
├── map5.ber       # Zorlayıcı harita
└── emptymap.ber   # Boş test haritası
```

## 🔧 Kurulum ve Çalıştırma

### Gereksinimler
- **MacOS**: Xcode command line tools
- **Linux**: X11 development packages
- **MiniLibX**: Grafik kütüphanesi (proje ile birlikte gelir)
- **LibFT**: 42 standart kütüphanesi (proje ile birlikte gelir)

### Derleme
```bash
# Ana versiyon için
make

# Bonus versiyon için
make bonus

# Temizlik
make clean      # Object dosyalarını sil
make fclean     # Tüm üretilen dosyaları sil
make re         # Yeniden derle
make bonusre    # Bonus versiyonu yeniden derle
```

### Çalıştırma
```bash
# Ana versiyon
./so_long map1.ber

# Bonus versiyon (make bonus sonrası)
./so_long map1.ber

# Hata durumları
./so_long                    # Hata: Argüman eksik
./so_long map1.txt           # Hata: .ber uzantısı gerekli
./so_long nonexistent.ber    # Hata: Dosya bulunamadı
```

## 🗺️ Harita Formatı (.ber)

### Karakter Seti
- `1`: Duvar
- `0`: Boş alan (zemin)
- `P`: Oyuncu başlangıç pozisyonu
- `C`: Toplanabilir madeni para
- `E`: Çıkış kapısı
- `X`: Düşman (sadece bonus)

### Harita Kuralları
1. **Dikdörtgen**: Harita tam dikdörtgen olmalı
2. **Duvarlarla Çevrili**: Kenarlar `1` karakteri ile çevrili
3. **Tek Oyuncu**: Haritada sadece bir `P` olmalı
4. **Tek Çıkış**: Haritada sadece bir `E` olmalı
5. **En Az Bir Para**: Haritada en az bir `C` olmalı
6. **Erişilebilirlik**: Tüm paralar ve çıkış erişilebilir olmalı

### Örnek Harita
```
1111111111111
10010000000C1
1000011110001
1P0011E000001
1111111111111
```

## 🎯 Teknik Detaylar

### Veri Yapıları

#### t_so_long (Ana Oyun Yapısı)
```c
typedef struct s_so_long
{
    void        *ptr;           // MLX pointer
    void        *win;           // Window pointer
    void        *wall;          // Duvar sprite
    void        *coin;          // Para sprite
    void        *grass;         // Zemin sprite
    void        *front;         // Oyuncu ön sprite
    void        *right;         // Oyuncu sağ sprite
    void        *left;          // Oyuncu sol sprite
    void        *back;          // Oyuncu arka sprite
    void        *door;          // Kapı sprite
    t_player    p;              // Oyuncu bilgileri
    char        **map;          // Harita verileri
    int         keys[4];        // Tuş durumları
    int         num_of_steps;   // Adım sayısı
    int         num_of_coin;    // Para sayısı
    int         num_of_exit;    // Çıkış sayısı
    int         width;          // Harita genişliği
    int         height;         // Harita yüksekliği
} t_so_long;
```

#### t_player (Oyuncu Yapısı)
```c
typedef struct s_player
{
    int x;      // X koordinatı
    int y;      // Y koordinatı
    int score;  // Oyuncu skoru
} t_player;
```

### Temel Fonksiyonlar

#### `render()`: Ekran Rendering
- Tüm ekranı temizler
- Harita elementlerini çizer
- Skor bilgisini gösterir
- 60 FPS ile güncellenir

#### `handle_key()`: Tuş Yönetimi
- WASD tuşlarına yanıt verir
- ESC tuşu ile çıkış
- Hareket validasyonu
- Sprite yönlendirmesi

#### `preliminary_so_long()`: Oyun Başlatma
- Harita dosyasını yükler
- Validasyon kontrolleri
- MLX materyallerini başlatır
- Pencere oluşturur

### Validasyon Sistemi

#### Harita Validasyonu
```c
// Harita formatı kontrolü
if (!ft_strchr(argv[1], '.') || 
    ft_strncmp(ft_strchr(argv[1], '.'), ".ber", 5))
    return error_message();

// Dikdörtgen kontrolü
if (j != s->width)
    return error_message();

// Duvar kontrolü
if (i == 0 || i == s->height - 1 || 
    j == 0 || j == s->width - 1)
{
    if (s->map[i][j] != '1')
        return error_message();
}
```

#### Erişilebilirlik Kontrolü
- Flood-fill algoritması kullanır
- Oyuncu pozisyonundan başlar
- Tüm paraları ve çıkışı kontrol eder
- Erişilemeyen alanları tespit eder

## 🎮 Kontroller

### Temel Kontroller
- **W**: Yukarı hareket
- **A**: Sola hareket  
- **S**: Aşağı hareket
- **D**: Sağa hareket
- **ESC**: Oyundan çıkış
- **Pencere X**: Oyundan çıkış

### Hareket Mekaniği
- **Pixel Tabanlı**: 10 pixel artışlarla hareket
- **Grid Snapping**: Duvarlarla temas halinde grid'e yaslanma
- **Smooth Movement**: Akıcı hareket animasyonları
- **Collision Detection**: Duvar ve engel tespiti

## 🏆 Bonus Özellikler

### Düşman Sistemi
- **Hareket Eden Düşmanlar**: Otomatik hareket eden zombie karakterler
- **Collision Detection**: Oyuncu-düşman çarpışma tespiti
- **Game Over**: Düşmana temas halinde oyun sonu
- **Sprite Animations**: Sağ-sol hareket animasyonları

### Gelişmiş Grafikler
- **Multiple Sprites**: Farklı renkli creeper karakterler
- **Animation System**: Sprite değiştirme sistemi
- **Visual Effects**: Gelişmiş görsel efektler

### Ek Mekanikler
```c
typedef struct s_enemy
{
    int x;          // Düşman X koordinatı
    int y;          // Düşman Y koordinatı  
    int is_right;   // Sağa hareket durumu
    int is_left;    // Sola hareket durumu
} t_enemy;
```

## 🛠️ Kullanılan Teknolojiler

### MiniLibX Grafik Kütüphanesi
- **Window Management**: Pencere oluşturma ve yönetimi
- **Image Handling**: XPM dosya formatı desteği
- **Event System**: Klavye ve mouse olayları
- **Pixel Manipulation**: Pixel seviyesinde grafik kontrolü

### LibFT Standart Kütüphanesi
- **String Functions**: String işlemleri
- **Memory Management**: Bellek yönetimi
- **File I/O**: Dosya okuma işlemleri
- **Get Next Line**: Satır bazlı dosya okuma

### Dosya Yönetimi
- **Get Next Line**: `.ber` dosyalarını okuma
- **String Split**: Harita parse etme
- **Memory Allocation**: Dinamik bellek yönetimi
- **Error Handling**: Hata yakalama ve yönetimi

## 🎯 Öğrenilen Kavramlar

### Grafik Programlama
1. **2D Rendering**: İki boyutlu grafik çizimi
2. **Sprite Management**: Sprite yükleme ve yönetimi
3. **Animation Systems**: Animasyon döngüleri
4. **Event-Driven Programming**: Olay tabanlı programlama

### Oyun Geliştirme
1. **Game Loop**: Ana oyun döngüsü
2. **State Management**: Oyun durumu yönetimi
3. **Collision Detection**: Çarpışma tespiti
4. **Scene Management**: Sahne yönetimi

### Algoritma ve Veri Yapıları
1. **Flood Fill**: Erişilebilirlik algoritması
2. **Path Finding**: Yol bulma algoritmaları
3. **Grid-Based Movement**: Grid tabanlı hareket
4. **Memory Management**: Bellek yönetimi

### Sistem Programlama
1. **File I/O**: Dosya giriş/çıkış işlemleri
2. **Error Handling**: Hata yönetimi
3. **Memory Leaks**: Bellek sızıntısı önleme
4. **Resource Management**: Kaynak yönetimi

## 📋 Hata Durumları ve Çözümleri

### Yaygın Hatalar
```bash
# Dosya bulunamadı
Error
File not found!!!

# Geçersiz harita formatı
Error
Map is not rectangular!!!

# Oyuncu bulunamadı
Error
Player not found!!!

# Erişilemeyen para
Error
Some coins have a barrier!!!

# Erişilemeyen çıkış
Error
Door have a barrier!!!
```

### Debug İpuçları
1. **Harita Kontrolü**: `.ber` dosyası formatını kontrol edin
2. **Duvar Kontrolü**: Harita kenarlarının `1` ile çevrili olduğundan emin olun
3. **Element Kontrolü**: P, E, C elementlerinin doğru sayıda olduğunu kontrol edin
4. **Memory Leaks**: Valgrind ile bellek sızıntılarını kontrol edin

## � Geliştirilme Potansiyeli

### Ek Özellikler
- **Multiple Levels**: Çoklu seviye sistemi
- **Power-ups**: Güç artırıcı öğeler
- **Sound Effects**: Ses efektleri
- **High Score**: Yüksek skor sistemi
- **Multiplayer**: Çok oyunculu mod

### Performans Optimizasyonları
- **Dirty Rectangle**: Sadece değişen alanları güncelleme
- **Sprite Caching**: Sprite önbellekleme
- **Level Streaming**: Seviye akışı
- **Memory Pooling**: Bellek havuzu

Bu proje, grafik programlama ve oyun geliştirme alanında sağlam bir temel oluşturur ve MiniLibX kütüphanesi ile 2D oyun motoru geliştirme konusunda kapsamlı deneyim sağlar.
