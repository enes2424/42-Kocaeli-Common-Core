# 42 Kocaeli Common Core - Minishell
## Bash Shell Implementation (Bash Kabuğu Implementasyonu)

Bu proje, 42 Okulu Common Core programının kapsamlı sistem programlama projesidir. Bash shell'in temel işlevlerini yeniden implemente ederek bir Unix shell oluşturur. Proje, process yönetimi, pipe ve redirection mekanizmaları, signal handling, environment variable işlemleri ve parser geliştirme konularında derinlemesine bilgi kazandırır. MacOS üzerinde geliştirilmiş olup, readline kütüphanesi kullanılmıştır.

## 📖 Proje Tanımı

Minishell, Bash benzeri bir komut satırı yorumlayıcısıdır. Kullanıcıdan komut alır, parse eder, execute eder ve sonuçları gösterir. Built-in komutlar, pipe'lar, redirectionlar ve environment variable işlemlerini destekler.

### Temel Özellikler:
- **Built-in komutlar**: echo, cd, pwd, export, unset, env, exit
- **Executable komutlar**: PATH'ten komut arama ve çalıştırma
- **Pipe (|)**: Komutlar arası veri akışı
- **Redirections**: `<`, `>`, `>>`, `<<` (heredoc)
- **Environment variables**: `$VAR` ve `$?` desteği
- **Quote işleme**: Tek ('') ve çift ("") tırnak desteği
- **Signal handling**: Ctrl-C, Ctrl-D, Ctrl-\ işlemleri
- **History**: Readline ile komut geçmişi

### Bonus Özellikler:
- **Logical operators**: `&&` (AND) ve `||` (OR) operatörleri
- **Parentheses**: Komut gruplandırma `()` desteği
- **Wildcards**: `*` pattern matching desteği

## 📁 Dosya Yapısı

### Mandatory Bölüm

#### minishell.h
**Açıklama:** Tüm veri yapıları, enum tanımları ve fonksiyon prototipleri

**Enum Token Türleri:**
- `NONE`: Normal komut/argüman
- `PIPE`: Pipe operatörü (|)
- `INPUT`: Input redirection (<)
- `HEREDOC`: Heredoc (<<)
- `WRITE`: Append redirection (>>)
- `REWRITE`: Output redirection (>)
- `STD_IN`, `STD_OUT`: Standart input/output file descriptorları

**Veri Yapıları:**
- `t_env`: Environment variable linked list (key-value pairs)
- `t_cmd`: Command linked list (value ve token bilgisi)
- `t_ms`: Ana shell state yapısı (tüm global durumları tutar)

**Global Variable:**
- `g_sig_control`: Signal durumu kontrolü için global flag

#### minishell.c
**Açıklama:** Programın ana giriş noktası ve temel döngü

**Fonksiyonlar:**
- `main()`: Program başlangıcı, init ve ana döngü
- `process_cmd()`: Komut işleme ve yönlendirme
- `control_specifice_marks()`: Token syntax kontrolü
- `control_specifice_marks_and_exec_heredoc()`: Heredoc çalıştırma ve kontrol

**Ana Döngü:**
1. Prompt gösterimi (renkli, kullanıcı adı ve pwd)
2. Readline ile input alma
3. History'ye ekleme
4. Command parsing
5. Execution
6. Cleanup

#### cmd1.c & cmd2.c
**Açıklama:** Command parsing ve tokenization

**cmd1.c Fonksiyonlar:**
- `add_cmd()`: Yeni komut elemanı ekleme
- `operations_w_q()`: Quote işlemleri
- `end_edit_cmd()`: Command list sonlandırma
- `llist_cmd_to_cmd()`: Linked list'i array'e çevirme

**cmd2.c Fonksiyonlar:**
- `while_loop()`: Parser döngüsü
- `dolar_mark()`: `$` işareti ve variable expansion
- `edit_end_element()`: Son eleman düzenleme
- `edit_cmd()`: Command tokenization
- `create_cmd()`: Ana command oluşturma fonksiyonu

**Parsing Özellikleri:**
- Space-based tokenization
- Quote içi string birleştirme
- Special character detection (pipe, redirection)
- Environment variable expansion

#### env1.c, env2.c & env3.c
**Açıklama:** Environment variable yönetimi

**env1.c Fonksiyonlar:**
- `create_env()`: Başlangıç environment listesi oluşturma
- `edit_env()`: Environment variable düzenleme
- `convert_t_env_to_str_array()`: t_env'i string array'e çevirme

**env2.c Fonksiyonlar:**
- `get_env()`: Environment variable değeri alma
- `add_env()`: Yeni environment variable ekleme
- `set_env()`: Environment variable güncelleme/oluşturma
- `delete_env()`: Environment variable silme

**env3.c Fonksiyonlar:**
- `sort()`: Export için alfabetik sıralama
- `control()`: Key format kontrolü
- `write_error()`: Hata mesajı yazdırma

#### exec.c
**Açıklama:** Komut çalıştırma ve process yönetimi

**Fonksiyonlar:**
- `execute()`: Ana execution fonksiyonu
- `ft_exec()`: Single command execution
- `pipe2()`: Pipe implementation
- `ft_builtins()`: Built-in komut kontrolü ve çalıştırma

**Execution Flow:**
1. Redirection kontrolü
2. Built-in check
3. PATH'ten executable arama
4. Fork ve execve
5. Pipe management (multiple process)
6. Waitpid ile process bekleme

#### path.c
**Açıklama:** PATH ortam değişkeninden executable arama

**Fonksiyonlar:**
- `create_path()`: Komut için tam path oluşturma
- `pre_create_path()`: PATH'i parse etme

**Özellikler:**
- `/` içeren komutlar için direkt çalıştırma
- PATH içinde executable arama
- Access kontrolü ile permission check

#### heredoc.c
**Açıklama:** Heredoc (<<) implementasyonu

**Fonksiyonlar:**
- `heredoc()`: Heredoc okuma ve pipe'a yazma
- `heredocc()`: Readline ile heredoc input alma
- `ft_exec_heredoc()`: Tüm heredoc'ları önceden çalıştırma

**Çalışma Prensibi:**
1. Delimiter'a kadar readline ile input alma
2. Pipe'a yazma
3. Fork ile ayrı process
4. Ana process'te pipe read end'i saklama

#### redirection.c
**Açıklama:** Input/Output redirection yönetimi

**Fonksiyonlar:**
- `redirection()`: Ana redirection kontrolü
- `ft_input()`: `<` input redirection
- `ft_write()`: `>>` append redirection
- `ft_rewrite()`: `>` output redirection
- `ft_heredoc()`: Heredoc pipe'ı stdin'e yönlendirme
- `ft_control()`: Command list'ten redirection elemanlarını temizleme

**File Descriptor Yönetimi:**
- Dup2 ile stdin/stdout yönlendirme
- Geçici fd'leri kapatma
- Error handling

#### signal.c
**Açıklama:** Signal handling (Ctrl-C, Ctrl-D, Ctrl-\)

**Fonksiyonlar:**
- `sigcontrol()`: Signal handler kurulumu
- `ft_signal()`: Signal işleme fonksiyonu

**Signal Davranışları:**
- **SIGINT (Ctrl-C)**: Prompt'ta yeni satır, heredoc'ta exit, execution'da interrupt
- **SIGQUIT (Ctrl-\)**: Prompt'ta ignore, execution'da "Quit: 3" mesajı
- **EOF (Ctrl-D)**: Shell'den çıkış

#### Built-in Command Files

##### echo.c
- `-n` flag desteği (newline suppress)
- Multiple `-n` flag handling
- Argüman yazdırma

##### cd.c
- Home directory (`~`) desteği
- Argümansız cd (HOME'a git)
- Error handling (no such file, not a directory)
- PWD ve OLDPWD güncelleme

##### pwd.c
- Mevcut dizini yazdırma
- `create_pwd_and_name_and_home()`: Prompt oluşturma
- Renkli prompt (kullanıcı adı: yeşil, pwd: mavi)

##### exit.c
- Numeric argüman kontrolü
- Exit code desteği
- "Too many arguments" hatası

##### export.c
- Argümansız export: Declare formatında listeleme
- Argümanlı export: `add_export()` çağrısı
- Alfabetik sıralama

##### unset.c (env3.c içinde)
- Environment variable silme
- Multiple variable desteği

#### Utility Files

##### utils.c
- `add_char_to_str()`: String'e karakter ekleme
- Yardımcı fonksiyonlar

##### special_expressions.c
- `special_expression()`: Özel karakter işleme
- Quote içi variable expansion kontrolü

##### token_control.c
- Token validation
- Syntax error kontrolü

##### free1.c & free2.c
**Memory management:**
- `frees()`: Ana cleanup fonksiyonu
- `free_cmd()`: Command list temizleme
- `free_env()`: Environment list temizleme
- `free_heredocs()`: Heredoc pipe'ları kapatma
- `ft_free()`: Generic free wrapper
- `if_error_frees()`: Error durumunda cleanup ve exit

##### init.c
- Shell başlangıç durumu
- Environment kopyalama
- PWD, HOME, SHLVL ayarlama
- File descriptor kopyalama (stdin/stdout backup)

### Bonus Bölüm

#### minishell_bonus.h & minishell_bonus.c
**Ek Özellikler:**
- `AND`, `OR` token türleri
- `OP`, `CP` (Open/Close Parentheses)
- `WILCARD` token
- Logical operator execution flow

**Bonus Ana Döngü:**
1. Command parsing (with operators)
2. Wildcard expansion
3. Parentheses validation
4. Conditional execution (AND/OR logic)
5. Subshell simulation

#### wilcard_bonus.c
**Açıklama:** Wildcard (*) pattern matching implementasyonu

**Fonksiyonlar:**
- `is_wilcards()`: Pattern matching algoritması (recursive)
- `take_files_and_directories()`: ls çalıştırarak dosya listesi alma
- `wilcards_operations()`: Wildcard'ları gerçek dosya isimlerine çevirme

**Pattern Matching:**
- `*` ile any string matching
- Recursive algoritma
- Multiple wildcard desteği

#### control_bonus.c
**Açıklama:** Bonus özellik kontrolleri

**Fonksiyonlar:**
- `control_parantheses()`: Parantez dengesi kontrolü
- `token_error()`: Syntax error mesajları

#### clear_extra_parantheses_bonus.c
**Açıklama:** Gereksiz parantezleri temizleme

**Fonksiyonlar:**
- `clear_extra_parantheses()`: Ana temizleme
- Pipe etrafındaki gereksiz parantezleri kaldırma
- Nested parentheses depth kontrolü

### Makefile

**Hedefler:**
- `all`: Mandatory derleme
- `bonus`: Bonus derleme
- `clean`: Object dosyalarını silme
- `fclean`: Executable silme
- `re`: Yeniden derleme
- `run`: Derleme ve çalıştırma
- `brun`: Bonus derleme ve çalıştırma
- `v`: Valgrind ile test
- `n`: Norminette kontrolü

**Derleme:**
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lreadline
```

**Libft:**
- Projeye dahil edilmiş libft kütüphanesi
- Get_next_line dahil
- Ek utility fonksiyonlar

## 🔧 Kullanım

### Derleme
```bash
# Mandatory
make

# Bonus
make bonus
```

### Çalıştırma
```bash
./minishell
```

### Örnekler

#### Temel Komutlar
```bash
minishell$ echo Hello World
Hello World

minishell$ pwd
/Users/eates/Desktop/42-Kocaeli-Common-Core

minishell$ cd ..
minishell$ pwd
/Users/eates/Desktop

minishell$ export MY_VAR=hello
minishell$ echo $MY_VAR
hello

minishell$ env | grep MY_VAR
MY_VAR=hello

minishell$ unset MY_VAR
```

#### Redirections
```bash
minishell$ echo "test" > file.txt
minishell$ cat < file.txt
test

minishell$ echo "append" >> file.txt
minishell$ cat file.txt
test
append

minishell$ cat << EOF
> line1
> line2
> EOF
line1
line2
```

#### Pipes
```bash
minishell$ ls -l | grep .c | wc -l

minishell$ cat file.txt | grep "test" | wc -l

minishell$ echo "hello" | cat | cat | cat
hello
```

#### Quotes
```bash
minishell$ echo "Hello $USER"
Hello eates

minishell$ echo 'Hello $USER'
Hello $USER

minishell$ echo "test"'hello'"world"
testhelloworld
```

#### Exit Status
```bash
minishell$ ls
minishell$ echo $?
0

minishell$ ls nonexistent
ls: nonexistent: No such file or directory
minishell$ echo $?
1
```

#### Bonus: Logical Operators
```bash
minishell$ echo "first" && echo "second"
first
second

minishell$ false || echo "runs because previous failed"
runs because previous failed

minishell$ (echo "group1" && echo "group2") || echo "group3"
group1
group2
```

#### Bonus: Wildcards
```bash
minishell$ echo *.c
minishell.c cd.c cmd1.c cmd2.c echo.c env1.c ...

minishell$ ls *.h
minishell.h

minishell$ echo test*.txt
test1.txt test2.txt test.txt
```

## 🎯 Öğrenilen Kavramlar

1. **Process Management**: Fork, execve, waitpid kullanımı
2. **Pipe Mekanizması**: Inter-process communication
3. **File Descriptors**: Open, close, dup2 ile fd yönetimi
4. **Redirections**: Input/output yönlendirmeleri
5. **Signal Handling**: SIGINT, SIGQUIT, SIGTERM işlemleri
6. **Parser Development**: Tokenization, lexical analysis
7. **Environment Variables**: Ortam değişkeni yönetimi
8. **Memory Management**: Malloc, free, memory leak önleme
9. **Readline Library**: Input handling, history management
10. **Error Handling**: Perror, errno, error messages
11. **Shell Behavior**: Bash clone geliştirme
12. **Linked Lists**: Dynamic data structure kullanımı
13. **Pattern Matching**: Wildcard algoritması (bonus)
14. **Boolean Logic**: AND/OR operators (bonus)
15. **Parentheses Parsing**: Expression grouping (bonus)

## 🔍 Teknik Detaylar

### Parser Algoritması
```
Input → Tokenization → Token Validation → Command List → Execution
```

**Tokenization Adımları:**
1. Space-based splitting
2. Quote içeriğini birleştirme
3. Special character detection (`|`, `<`, `>`, `<<`, `>>`)
4. Environment variable expansion (`$VAR`, `$?`)
5. Wildcard detection (bonus: `*`)

### Execution Flow
```
Command List → Built-in Check → PATH Search → Fork → Execve
                                               ↓
                                           Pipe Setup → Next Command
```

**Pipe Implementation:**
- Her pipe için ayrı process
- File descriptor chaining
- Parent process waitpid
- Exit status propagation

### Memory Management Strategy
- Malloc için null check
- Her malloc sonrası `if_error_frees` kontrolü
- Exit öncesi tüm kaynakları temizleme
- Linked list'leri recursive free
- Pipe fd'lerini kapatma

### Signal Handling Strategy
- Global variable ile state tracking
- Readline signal integration
- Heredoc ve execution'da farklı davranış
- Child process'lerde signal inheritance

## 📋 Notlar

- Program `-Wall -Wextra -Werror` ile derlenmiştir
- MacOS üzerinde geliştirilmiş ve test edilmiştir
- Readline kütüphanesi kullanılmıştır (`-lreadline`)
- Norm kurallarına uygun yazılmıştır (42 coding standards)
- Valgrind ile memory leak test edilmiştir
- Bash referans alınarak davranışlar implemente edilmiştir
- Libft kütüphanesi projeye dahil edilmiştir (ft_* fonksiyonlar)
- History özelliği readline ile entegre edilmiştir
- Renkli prompt desteği (ANSI color codes)

## ⚠️ UYARI

**ÖNEMLİ:** Bu proje 42 Kocaeli'nde tamamlanmış olup, **MacOS** üzerinde geliştirilmiştir. Zamanında bazı kişisel kontrol standartlarına (null check, malloc hata kontrolü, fonksiyon return değeri kontrolü, vb.) dikkat edilmemiş olabilir. Ancak bu proje, Philosophers projesine göre daha az hata kontrolü eksikliği içermektedir ve daha temiz bir kod yapısına sahiptir. Önceki projelerimi bu doğrultuda düzelterek GitHub'a yüklememe rağmen, bu projeyi orijinal haliyle yüklemek ve sonradan düzeltme yapmak için zaman harcamamak istedim. Proje mantıksal olarak doğru çalışmaktadır ve temel kavramları göstermektedir, ancak production-level hata kontrolü için bazı ek kontroller eklenmelidir.

