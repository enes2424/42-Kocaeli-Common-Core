# 42 Kocaeli Pipex
## Unix Pipe Mekanizması ve Process İletişimi

Bu proje, 42 Okulu'nun sistem programlama müfredatının önemli bir parçasıdır. Unix sistemlerindeki pipe mekanizmasını, process yönetimini ve dosya manipülasyonunu öğrenmek için tasarlanmıştır. Bash shell'deki pipe operatörünün (|) çalışma prensibini C dilinde simüle eder.

## 📚 Proje Yapısı

### Ana Dosyalar (Mandatory)

#### pipex.c
**Ana Program Dosyası**

Shell komutunu simüle eden ana program.
- **Fonksiyon:** `main(int argc, char **argv, char **envp)`
- **Açıklama:** İki komut arasında pipe bağlantısı kurar
- **Kullanım:** `./pipex file1 cmd1 cmd2 file2`
- **Eşdeğer Shell:** `< file1 cmd1 | cmd2 > file2`
- **Örnek:**
  ```bash
  ./pipex infile "ls -l" "wc -l" outfile
  # Shell karşılığı: < infile ls -l | wc -l > outfile
  ```

#### pipex.h
**Header Dosyası (Mandatory)**

Mandatory version için gerekli struct ve fonksiyon tanımları.
- **Struct:** `t_pipex` - pipe işlemleri için gerekli veriler
- **Fonksiyonlar:** String işlemleri, hata kontrolü, process yönetimi
- **Includes:** Sistem kütüphaneleri

#### pipex_utils.c
**Yardımcı Fonksiyonlar**

String manipülasyonu ve bellek yönetimi fonksiyonları.
- **ft_strjoin:** İki string'i birleştirme
- **ft_strlen:** String uzunluğu hesaplama
- **ft_strlcpy:** Güvenli string kopyalama
- **ft_strncmp:** String karşılaştırma
- **finish:** Bellek temizleme

#### pipex_others.c
**Process ve Dosya İşlemleri**

Child process'ler ve dosya işlemleri için fonksiyonlar.
- **child1:** İlk komut için child process
- **child2:** İkinci komut için child process
- **create_path:** PATH çevre değişkeninden komut yolu bulma
- **has_error_of_arg:** Argüman doğrulama
- **has_error_of_pid:** Process ID hata kontrolü

#### ft_split.c
**String Ayırma Fonksiyonu**

Belirtilen ayraç karakterine göre string'i parçalara ayırma.
- **ft_split:** String'i char dizisine dönüştürme
- **free_string_array:** String dizisi bellek temizleme
- **ft_nb_words:** Kelime sayısı hesaplama

### Bonus Dosyaları

#### pipex_bonus.c
**Gelişmiş Ana Program**

Çoklu pipe ve here_doc desteği olan gelişmiş version.
- **Özellik:** Sınırsız sayıda komut desteği
- **Here_doc:** Bash'teki `<<` operatörü desteği
- **Kullanım:** `./pipex file1 cmd1 cmd2 cmd3 ... cmdN file2`
- **Here_doc Kullanım:** `./pipex here_doc LIMITER cmd1 cmd2 file`
- **Örnek:**
  ```bash
  ./pipex infile "grep a1" "wc -w" "cat -e" outfile
  ./pipex here_doc END "cat" "grep hello" outfile
  ```

#### pipex_bonus.h
**Bonus Header Dosyası**

Bonus özellikleri için genişletilmiş struct ve fonksiyon tanımları.
- **Gelişmiş t_pipex:** Çoklu pipe desteği
- **Here_doc:** Dinamik input desteği
- **Process Array:** Çoklu process yönetimi

#### pipex_child_bonus.c
**Gelişmiş Child Process Yönetimi**

Çoklu komut için child process yönetimi.
- **child1:** İlk komut (input handling)
- **child2:** Son komut (output handling)
- **child:** Ara komutlar için process yönetimi
- **here_doc_operation:** Here document işleme

#### pipex_others_bonus.c
**Bonus Yardımcı Fonksiyonlar**

Gelişmiş hata kontrolü ve dosya işlemleri.
- **has_error_of_arg:** Gelişmiş argüman doğrulama
- **create_path:** Optimize edilmiş path bulma
- **dup_input:** Input redirection yönetimi
- **here_doc_operation:** Here document implementasyonu

#### pipex_utils_bonus.c
**Bonus Utility Fonksiyonları**

Gelişmiş bellek yönetimi ve string işlemleri.
- **finish:** Gelişmiş cleanup fonksiyonu
- **free_double_array:** 2D array bellek temizleme
- **İyileştirilmiş fonksiyonlar:** Optimize edilmiş string fonksiyonları

#### ft_split_bonus.c
**Bonus Split Fonksiyonu**

Bonus özellikler için optimize edilmiş split fonksiyonu.
- **free_double_array:** Genel 2D array temizleme
- **Gelişmiş hata yönetimi:** İyileştirilmiş error handling

### Get Next Line Entegrasyonu

#### getnextline/get_next_line.h
**Get Next Line Header**

Here document özelliği için satır okuma desteği.

#### getnextline/get_next_line.c
**Satır Okuma Fonksiyonu**

Dosya veya stdin'den satır satır okuma.

#### getnextline/get_next_line_utils.c
**GNL Utility Fonksiyonları**

Get Next Line için yardımcı fonksiyonlar.

## 🔧 Derleme ve Kullanım

### Makefile Komutları
```bash
# Mandatory version
make

# Bonus version
make bonus

# Temizlik
make clean
make fclean

# Yeniden derleme
make re
```

### Mandatory Kullanım
```bash
# Temel kullanım
./pipex infile "cmd1" "cmd2" outfile

# Örnekler
./pipex input.txt "cat" "wc -l" output.txt
./pipex /etc/passwd "grep root" "cut -d: -f1" result.txt
./pipex data.txt "sort" "uniq" sorted_unique.txt
```

### Bonus Kullanım
```bash
# Çoklu komut
./pipex infile "cmd1" "cmd2" "cmd3" "cmd4" outfile

# Here document
./pipex here_doc LIMITER "cmd1" "cmd2" outfile

# Örnekler
./pipex input.txt "cat" "grep error" "wc -l" "cat" output.txt
./pipex here_doc EOF "cat" "sort" result.txt
./pipex here_doc STOP "grep hello" "wc -w" count.txt
```

## 🎯 Öğrenilen Kavramlar

### 1. **Process Yönetimi**
- **fork():** Child process oluşturma
- **execve():** Program çalıştırma
- **waitpid():** Process bekleme
- **Process ID:** PID yönetimi

### 2. **Pipe Mekanizması**
- **pipe():** Pipe oluşturma
- **dup2():** File descriptor redirection
- **IPC:** Inter-Process Communication
- **Data Flow:** Process'ler arası veri akışı

### 3. **Dosya İşlemleri**
- **open():** Dosya açma (O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC, O_APPEND)
- **close():** Dosya kapatma
- **File Descriptors:** 0(stdin), 1(stdout), 2(stderr)
- **Permission:** Dosya izinleri (0644)

### 4. **Sistem Programlama**
- **Environment Variables:** Çevre değişkenleri (PATH)
- **Command Parsing:** Komut ayrıştırma
- **Error Handling:** Sistem hata yönetimi
- **Memory Management:** Dinamik bellek yönetimi

### 5. **Here Document**
- **Stdin Reading:** Standart giriş okuma
- **Dynamic Input:** Dinamik veri girişi
- **Delimiter Matching:** Sınırlayıcı eşleştirme
- **Temporary Storage:** Geçici veri saklama

## 📋 Teknik Detaylar

### Mandatory Version
```c
typedef struct s_pipex
{
    pid_t   pid1;        // İlk child process ID
    pid_t   pid2;        // İkinci child process ID
    char    **cmd;       // Komut argümanları
    int     filefd1;     // Input dosya descriptor
    int     filefd2;     // Output dosya descriptor
    char    **cmd_paths; // PATH directories
    char    *path;       // Komut tam yolu
} t_pipex;
```

### Bonus Version
```c
typedef struct s_pipex
{
    int     argc;                // Argüman sayısı
    char    **argv;              // Argüman dizisi
    char    **envp;              // Environment variables
    int     control;             // Here_doc kontrolü
    pid_t   *pid;                // Process ID dizisi
    int     **pipefd;            // Pipe file descriptor'ları
    int     pipefd_limiter[2];   // Here_doc pipe
    char    **str;               // Komut string'leri
    int     filefd1;             // Input file descriptor
    int     filefd2;             // Output file descriptor
    char    **cmd_paths;         // PATH dizinleri
    char    *cmd;                // Aktif komut
} t_pipex;
```

### Algoritma Akışı

#### Mandatory Version:
1. **Argument Validation:** Argüman sayısı ve dosya kontrolü
2. **Pipe Creation:** pipe() ile veri kanalı oluşturma
3. **PATH Parsing:** Environment'tan PATH bulma ve parse etme
4. **Fork Process 1:** İlk komut için child process
5. **Fork Process 2:** İkinci komut için child process
6. **Wait Processes:** Child process'lerin tamamlanmasını bekleme
7. **Cleanup:** Bellek ve file descriptor temizliği

#### Bonus Version:
1. **Extended Validation:** Here_doc ve çoklu komut kontrolü
2. **Dynamic Allocation:** Komut sayısına göre dinamik alan tahsisi
3. **Here_doc Handling:** Stdin'den veri okuma ve geçici saklama
4. **Sequential Processing:** Komutları sırayla işleme
5. **Chain Management:** Pipe zinciri yönetimi

## 🚨 Hata Yönetimi

### Kontrol Edilen Hatalar:
- **Argüman Hataları:** Eksik veya fazla argüman
- **Dosya Hataları:** Dosya bulunamama, izin hataları
- **Fork Hataları:** Process oluşturma başarısızlığı
- **Pipe Hataları:** Pipe oluşturma başarısızlığı
- **Execve Hataları:** Komut çalıştırma başarısızlığı
- **Memory Hataları:** Malloc başarısızlığı
- **PATH Hataları:** Komut bulunamama

### Hata Mesajları:
```bash
"missing argument or excess argument!"
"no such file or directory: filename"
"command not found: command"
"fork did not work!"
"could not create pipe!"
"couldn't take space with malloc"
"Path not found!"
```

## 🧪 Test Örnekleri

### Mandatory Test:
```bash
# Test 1: Basit komutlar
./pipex input.txt "cat" "wc -l" output.txt
echo "test" | wc -l  # Karşılaştırma

# Test 2: Dosya işlemleri
./pipex /etc/passwd "grep root" "cut -d: -f1" result.txt
grep root /etc/passwd | cut -d: -f1  # Karşılaştırma

# Test 3: Hata durumları
./pipex nonexistent.txt "cat" "wc -l" output.txt
./pipex input.txt "nonexistent_cmd" "wc -l" output.txt
```

### Bonus Test:
```bash
# Test 1: Çoklu komut
./pipex input.txt "cat" "grep a" "sort" "uniq" "wc -l" output.txt

# Test 2: Here document
./pipex here_doc EOF "cat" "sort" result.txt
# INPUT:
# line1
# line3
# line2
# EOF

# Test 3: Karmaşık pipeline
./pipex input.txt "cat" "tr a-z A-Z" "sort" "uniq -c" "sort -nr" output.txt
```

## 📝 Notlar

- **Norm Uyumluluğu:** 42 kodlama standartlarına uygun
- **Bellek Güvenliği:** Bellek sızıntısı olmayan kod
- **Hata Dayanıklılığı:** Güçlü hata yönetimi
- **Taşınabilirlik:** Unix sistemlerde çalışır
- **Verimlilik:** Optimize edilmiş pipe implementasyonu
- **Eğitici:** Sistem programlama kavramlarını öğretir

## 🔍 Debugging İpuçları

```bash
# Valgrind ile bellek kontrolü
valgrind --leak-check=full ./pipex input.txt "cat" "wc -l" output.txt

# Strace ile sistem çağrısı takibi
strace -f ./pipex input.txt "ls -l" "wc -l" output.txt

# GDB ile debugging
gdb ./pipex
(gdb) run input.txt "cat" "wc -l" output.txt
```

Bu proje, Unix sistemlerinin temel mekanizmalarını anlamak ve sistem programlama becerilerini geliştirmek için mükemmel bir öğrenme aracıdır.
