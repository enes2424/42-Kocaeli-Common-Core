# 42 Kocaeli Common Core - Cub3D
## Raycasting 3D Game Engine (Raycasting 3D Oyun Motoru)

Bu proje, 42 Okulu Common Core programının grafik programlama ve raycasting projesidir. Wolfenstein 3D benzeri bir 3D oyun motoru, MinilibX kütüphanesi kullanılarak C dilinde implemente edilmiştir. Proje, raycasting algoritması, texture mapping, grafik optimizasyonu ve gerçek zamanlı rendering konularında derin bir anlayış kazandırmayı amaçlar. MacOS üzerinde geliştirilmiştir.

## 📖 Proje Tanımı

Cub3D, 2D haritadan 3D görünüm oluşturan bir raycasting motorudur. Oyuncu ilk şahıs perspektifinde hareket edebilir, dört yöne bakabilir ve duvarları gerçek zamanlı olarak render eder. Proje, .cub uzantılı harita dosyalarından sahne bilgilerini okur ve MinilibX ile ekrana çizer.

### Temel Özellikler:
- **Raycasting Engine**: 2D haritayı 3D perspektife dönüştürme
- **Texture Mapping**: XPM formatında duvar texture'ları
- **Real-time Rendering**: 60 FPS hedefi ile gerçek zamanlı görüntüleme
- **Player Movement**: W/A/S/D ile hareket, yön tuşları ile dönme
- **Map Parsing**: .cub dosyalarından harita okuma
- **Color Management**: RGB ile tavan ve zemin renklendirme
- **FOV (Field of View)**: 63 derece görüş açısı

### Bonus Özellikler:
- **Minimap**: Gerçek zamanlı mini harita gösterimi
- **Animated Sprites**: 12 frame animasyonlu karakterler
- **Doors**: Açılıp kapanabilen kapılar (SPACE tuşu)
- **Mouse Look**: Fare ile kamera kontrolü
- **Enhanced Graphics**: Ekstra görsel efektler

## 📁 Dosya Yapısı

### Mandatory Bölüm

#### cub3d.h
**Açıklama:** Tüm veri yapıları, macro tanımları ve fonksiyon prototipleri

**Macro Tanımları:**
- `W, S, A, D`: Hareket tuşları (13, 1, 0, 2)
- `L, R`: Sağa-sola dönüş (123, 124)
- `UP, DOWN`: Hız kontrol (126, 125)
- `SHIFT`: Sprint (257)
- `ESC`: Çıkış (53)
- `PIXEL`: Grid boyutu (150)
- `PI`: 3.14159265358979323846264338327950288

**Veri Yapıları:**

1. **t_map:**
   - `char **map`: 2D harita grid'i
   - `int height, width`: Harita boyutları

2. **t_wall:**
   - `char *no, *so, *we, *ea`: Duvar texture yolları (Kuzey, Güney, Batı, Doğu)

3. **t_colors:**
   - `char *f, *c`: Zemin ve tavan RGB string'leri
   - `int f_rpg, c_rpg`: RGB integer değerleri

4. **t_player:**
   - `int x, y`: Oyuncu pozisyonu (pixel)
   - `int new_x, new_y`: Hesaplanan yeni pozisyon
   - `int keys[6]`: Tuş durumları (W, S, A, D, L, R)

5. **t_mlx_image:**
   - `void *img`: MLX image pointer
   - `char *addr`: Image data adresi
   - `int bits_per_pixel, size_line`: Image özellikleri

6. **t_mlx:**
   - `void *ptr, *win`: MLX pencere ve pointer
   - `t_mlx_image *screen`: Ana ekran buffer
   - `t_mlx_image *walls[4]`: 4 yön duvar texture'ları

7. **t_linkedlist:**
   - Texture scaling için linked list yapısı
   - Image stretch algoritması için kullanılır

8. **t_program:**
   - Ana program state yapısı
   - Tüm alt yapıları toplar
   - `int angle`: Bakış açısı (0-360°)
   - `int speed`: Hareket hızı (pixel/step)
   - `int multipler`: Sprint çarpanı (1x veya 2x)

#### cub3d.c
**Açıklama:** Programın giriş noktası

**main() Fonksiyonu:**
1. `check_arg()`: Argüman kontrolü (.cub dosyası)
2. `init()`: Yapıların başlatılması
3. `create_map()`: Harita dosyası okuma ve parsing
4. `play_program()`: Oyun döngüsünü başlatma

**Minimal Kod:**
- Sadece 26 satır
- Clean architecture yaklaşımı
- Her fonksiyon tek sorumluluk

#### utils.c
**Açıklama:** Başlatma ve harita okuma fonksiyonları

**Fonksiyonlar:**
- `check_arg()`: .cub dosya uzantısı kontrolü
- `init()`: Tüm yapıların NULL/0 ile başlatılması
- `init_mlx()`: MLX yapılarının başlatılması
- `create_map()`: Dosyadan harita okuma
  - 99 byte buffer ile okuma
  - `ft_strjoin` ile birleştirme
  - `\n` ile split
- `control()`: Harita geçerlilik kontrolü
  - NO, SO, WE, EA texture varlığı
  - F, C renk varlığı
  - Sıralı parsing

#### utils1.c
**Açıklama:** Harita parsing ve karakter kontrolleri

**Fonksiyonlar:**
- `control2()`: Texture ve renk satırlarını ayırma
- `equalize()`: Değerleri değişkenlere atama
  - RGB için ',' kontrolü (2 adet)
  - Path için whitespace kontrolü
- `close_map_control()`: Harita kapalılık kontrolü
  - 3x3 komşu kontrolü
  - Boşluk ve sınır kontrolü
- `character_control()`: Harita karakterleri doğrulama
  - NSWE oyuncu pozisyonu
  - Tek oyuncu kontrolü
  - Geçersiz karakter kontrolü
  - 1, 0, space ve oyuncu dışında karakter yasak

#### utils2.c
**Açıklama:** Path finding ve oyun döngüsü

**Fonksiyonlar:**
- `path_finder()`: Recursive flood fill algoritması
  - Oyuncu haritadan çıkabilir mi kontrolü
  - Boşluk ve sınır kontrolü
- `re_create()`: Harita kopyalama ve temizleme
- `control3()`, `control4()`: Ek kontrol fonksiyonları
- `play_program()`: Ana oyun başlatma
  - MLX window oluşturma
  - Texture'ları yükleme
  - Hook'ları kurma
  - Event loop başlatma

#### utils3.c
**Açıklama:** MLX başlatma ve rendering setup

**Fonksiyonlar:**
- `init_program()`: MLX ve texture başlatma
  - `mlx_init()`: MLX bağlantısı
  - `mlx_new_window()`: 1800x1000 pencere
  - 4 yön texture yükleme
  - 4000x4000 screen buffer oluşturma
  
- `mlx_image_init()`: XPM dosyasından image yükleme
  - `mlx_xpm_file_to_image()`
  - `mlx_get_data_addr()`
  
- `create_sky_and_floor()`: RGB parsing ve doğrulama
  - ',' ile split (3 parça)
  - 0-255 arası kontrol
  - Bit shifting ile RGB birleştirme:
    ```c
    color = (R << 16) + (G << 8) + B
    ```
  
- `render()`: Ana rendering fonksiyonu
  - Background temizleme
  - Raycasting
  - Screen'i window'a çizme
  - FPS gösterimi
  
- `mlx_put_background()`: Tavan ve zemin çizimi
  - Üst 500 pixel: Tavan (c_rpg)
  - Alt 500 pixel: Zemin (f_rpg)

#### utils4.c
**Açıklama:** Raycasting ana algoritması

**Fonksiyonlar:**
- `raycasting()`: Tüm ışınları atmak
  - 121.5° → 58.5° (63° FOV)
  - 0.035° artışla 1800 ışın
  - Her ışın için duvar mesafesi
  - Perspektif düzeltme:
    ```c
    height = 225000 / (distance * cos(angle_difference))
    ```
  
- `throwing_ray()`: Tek ışın hesaplama
  - Açıya göre direction vector
  - Grid intersection hesaplama
  - Düz ışın kontrolü
  - Diagonal ışın için DDA
  
- `throwing_straight_ray()`: Düz ışınlar (0°, 90°, 180°, 270°)
  - Horizontal (px = 0)
  - Vertical (py = 0)
  - Hızlı hesaplama
  
- `throwing_not_straight_ray()`: Diagonal ışınlar
  - X ve Y grid intersection'ları
  - En yakın intersection seçme
  - DDA (Digital Differential Analyzer) benzeri

#### utils5.c
**Açıklama:** Ray intersection ve texture rendering

**Fonksiyonlar:**
- `throwing_ray1()`: X-axis intersection kontrolü
  - Duvar çarpışma tespiti
  - Köşe durumları
  - Which_wall belirleme (0: N, 1: E, 2: S, 3: W)
  
- `throwing_ray2()`: Y-axis intersection kontrolü
  - Benzer mantık, Y ekseni için
  
- `put_image()`: Texture column çizimi
  - Size ≤ PIXEL: Küçük texture (uzak duvar)
  - Size > PIXEL: Büyük texture (yakın duvar)
  - Linked list ile scaling
  - Vertical column çizimi
  
- `exe()`: Texture scaling algoritması
  - Bresenham benzeri piksel dağılımı
  - Linked list node oluşturma
  - Optimal upscaling/downscaling

#### utils6.c
**Açıklama:** Büyük texture rendering ve input handling

**Fonksiyonlar:**
- `put_image2()`: Büyük duvarlar için rendering
  - 1000 pixel üzeri için özel işlem
  - Ekran dışı kısımları atlama
  - Z-buffer benzeri optimizasyon
  
- `exit_x()`: Pencere kapatma event'i
- `handle()`: Tuş basma event'i
  - W/A/S/D: Hareket flagları
  - L/R: Dönüş flagları
  - UP/DOWN: Hız ayarlama (±5)
  - SHIFT: Sprint (2x)
  - ESC: Çıkış

#### utils7.c
**Açıklama:** Player movement ve cleanup

**Fonksiyonlar:**
- `handle2()`: Hareket hesaplama
  - Trigonometrik yön hesaplama
  - Collision detection
  - Ray-based wall check
  - Pozisyon güncelleme
  - Render tetikleme
  
- `release()`: Tuş bırakma event'i
  - Flag'leri 0'lama
  
- `free_program()`: Cleanup
  - Tüm malloc'ları free
  - MLX kaynakları temizleme
  - Exit
  
- `mlx_destroy()`: MLX temizleme
  - Window destroy
  - Image destroy
  - Pointer'ları free

#### utils8.c
**Açıklama:** Utility fonksiyonları

**Fonksiyonlar:**
- `linkedlistclear()`: Recursive list temizleme
- `special_free()`: Safe free (NULL set)
- `check_malloc()`: Malloc kontrolü ve hata
- `control_rgb()`: RGB string validation
  - Trim ve digit kontrolü
  - '+' işareti desteği

### Bonus Bölüm

#### cub3d_bonus.h
**Ek Özellikler:**

**t_door yapısı:**
- `int x, y`: Kapı pozisyonu
- `int is_open`: Açık/kapalı durum
- `struct s_door *next`: Linked list

**t_mlx eklentileri:**
- `void *player, *wall, *floor, *mdoor`: Minimap elemanları
- `t_mlx_image *door`: Kapı texture
- `t_mlx_image *animation[12]`: 12 frame karakter animasyonu

**t_map eklentileri:**
- `char **cropped_map`: Minimap için küçültülmüş harita
- `char **copy`: Path finding için kopya

**Yeni Macro:**
- `SPACE (49)`: Kapı açma tuşu
- `PIXEL2 (30)`: Minimap pixel boyutu

#### Bonus Fonksiyonlar
- **Minimap Rendering**: Gerçek zamanlı harita gösterimi
- **Door System**: Kapı açma/kapama mekanizması
- **Sprite Animation**: 12 frame smooth animation
- **Mouse Control**: Fare ile kamera dönüşü
- **Enhanced Movement**: Daha smooth hareket

### Map Format (.cub)

```
NO ./mandatory/xpm_file/north.xpm
SO ./mandatory/xpm_file/south.xpm
WE ./mandatory/xpm_file/west.xpm
EA ./mandatory/xpm_file/east.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

**Format Kuralları:**
- İlk 6 satır: Texture ve renk tanımları
- Boş satırlardan sonra: Harita
- 1: Duvar
- 0: Boş alan
- N/S/E/W: Oyuncu başlangıç (yön ile)
- Space: Harita dışı alan
- Harita kapalı olmalı (flood fill testi)

## 🔧 Kullanım

### Derleme
```bash
make
```

### Bonus Derleme
```bash
make bonus
```

### Çalıştırma
```bash
./cub3d <map.cub>
```

### Örnek:
```bash
./cub3d mandatory/cub_file/map.cub
```

### Kontroller

**Mandatory:**
- `W`: İleri
- `S`: Geri
- `A`: Sola
- `D`: Sağa
- `←`: Sola dön
- `→`: Sağa dön
- `↑`: Hız artır (+5)
- `↓`: Hız azalt (-5)
- `SHIFT`: Sprint (2x hız)
- `ESC`: Çıkış

**Bonus:**
- `SPACE`: Kapı aç/kapa
- `Mouse`: Kamera kontrolü
- Tüm mandatory kontroller

## 🎯 Öğrenilen Kavramlar

1. **Raycasting Algorithm**: 2D→3D dönüşüm algoritması
2. **Trigonometry**: Sin, cos, tan kullanımı
3. **DDA Algorithm**: Digital Differential Analyzer
4. **Texture Mapping**: UV mapping ve texture projection
5. **MinilibX**: Low-level grafik kütüphanesi
6. **Image Manipulation**: Pixel-level operations
7. **Real-time Rendering**: 60 FPS optimizasyonu
8. **Field of View**: Perspektif hesaplamaları
9. **Collision Detection**: Ray-based wall checking
10. **Map Parsing**: File parsing ve validation
11. **Flood Fill**: Recursive path finding
12. **Bit Manipulation**: RGB color packing
13. **Linked Lists**: Dynamic scaling algoritması
14. **Event Handling**: Keyboard ve mouse events
15. **Memory Management**: MLX image cleanup

## 🔍 Teknik Detaylar

### Raycasting Algorithm
```
For each screen column (1800 columns):
    1. Calculate ray angle
    2. Cast ray from player position
    3. Find first wall intersection
    4. Calculate distance to wall
    5. Apply perspective correction: height = 225000 / (dist * cos(angle))
    6. Draw vertical texture column
```

### DDA-like Intersection
```
Start from player position
Calculate direction vector (cos, sin)
Step to next grid line (X or Y)
Check which grid line is closer
Test for wall at that position
Repeat until wall found
```

### Texture Mapping
```
1. Determine which wall face hit (N/S/E/W)
2. Calculate texture X coordinate:
   - For N/S walls: X = player_x % PIXEL
   - For E/W walls: X = player_y % PIXEL
3. Scale texture column to wall height
4. Draw scaled column to screen buffer
```

### Perspective Correction
- **Fish-eye düzeltme**: `distance * cos(angle_diff)`
- Merkez ışın referans alınır
- Yan ışınlar merkeze göre düzeltilir

### Scaling Algorithm
- Bresenham benzeri pixel dağılım
- Linked list ile dinamik scale factor
- Upscaling ve downscaling optimizasyonu

### Performance Optimization
- 4000x4000 screen buffer (off-screen rendering)
- Single `mlx_put_image_to_window` call
- Minimal texture lookups
- Integer-only calculations (where possible)

## 📋 Notlar

- Program C dilinde yazılmıştır
- `-Wall -Wextra -Werror` ile derlenmiştir
- MacOS üzerinde geliştirilmiş ve test edilmiştir
- MinilibX kütüphanesi kullanılmıştır
- 1800x1000 çözünürlük
- 63° FOV (Field of View)
- 0.035° ray step (1800 rays)
- PIXEL = 150 (grid size)
- Libft kütüphanesi projeye dahildir
- XPM texture formatı desteklenir
- MLX framework kullanılır (MacOS OpenGL/AppKit)

## ⚠️ UYARI

**ÖNEMLİ:** Bu proje 42 Kocaeli'nde tamamlanmış olup, **MacOS** üzerinde geliştirilmiştir. Vaktiyle bu projeyi yaparken basit düşünüp çözebilecekken **komplike bir yaklaşım** benimsedim. Özellikle duvarları çizdirirken farklı bir algoritma kullanmayı tercih ettim ve bu durum bazı durumlarda **duvarların dalgalanıyormuş hissi vermesine** neden oldu. Standart raycasting implementasyonuna göre daha karmaşık bir hesaplama yöntemi kullanıldığı için rendering'de ince tutarsızlıklar oluşabilmektedir. Zamanında bazı kişisel kontrol standartlarına (null check, edge case handling, vb.) dikkat edilmemiş olabilir. Proje temel raycasting kavramlarını göstermektedir ancak production-level bir oyun motoru için daha fazla optimizasyon ve standart algoritma implementasyonu gereklidir.
