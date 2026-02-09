# 42 Kocaeli Common Core - ft_irc
## IRC Server Implementation (Internet Relay Chat Sunucu Implementasyonu)

Bu proje, 42 Okulu Common Core programının ağ programlama ve socket iletişimi projesidir. RFC 1459 standardına uygun bir IRC (Internet Relay Chat) sunucusu C++98 ile implemente edilmiştir. Proje, socket programlama, çoklu istemci yönetimi, poll() kullanımı, protokol implementasyonu ve network programming konularında derin bir anlayış kazandırmayı amaçlar. MacOS üzerinde geliştirilmiştir.

## 📖 Proje Tanımı

ft_irc, gerçek zamanlı metin tabanlı iletişim için bir IRC sunucusudur. Birden fazla istemci aynı anda bağlanabilir, kanallar oluşturabilir, mesajlaşabilir ve IRC komutlarını kullanabilir. Sunucu, HexChat ve nc (netcat) gibi IRC istemcileri ile uyumludur.

### Temel Özellikler:
- **Socket Programming**: TCP/IP socket iletişimi
- **Poll Mekanizması**: Non-blocking I/O ile çoklu istemci yönetimi
- **Channel Management**: Kanal oluşturma, katılma, ayrılma
- **User Authentication**: Password ile sunucu girişi
- **Private Messages**: Kullanıcılar arası ve kanal mesajları
- **Channel Modes**: +k (password), +l (limit), +n (outside messages)
- **Operator Commands**: KICK, MODE, TOPIC, INVITE
- **IRC Protocol**: RFC 1459 komut desteği
- **Signal Handling**: Graceful shutdown (Ctrl-C, SIGHUP)

## 📁 Dosya Yapısı

### Core Files

#### Server.hpp & Server.cpp
**Açıklama:** Ana sunucu sınıfı ve socket yönetimi

**Server Class:**
- **Private Members:**
  - `vector<Channel> channels`: Aktif kanallar listesi
  - `vector<Client> clients`: Bağlı istemciler (MAX_CLIENTS = 100)
  - `pollfd pollFds[MAX_CLIENTS + 1]`: Poll file descriptor array
  - `sockaddr_in serverAddr`: Server socket adresi
  - `int serverSocket`: Server dinleme socketi
  - `int port`: Server portu
  - `string password`: Server şifresi
  - `int num_of_client`: Aktif istemci sayısı
  - `bool is_open`: Server durum bayrağı

**Ana Fonksiyonlar:**
- `Server()`: Constructor - Socket oluşturma, bind, listen
  - `socket(AF_INET, SOCK_STREAM, 0)`: TCP socket
  - `setsockopt()`: SO_REUSEADDR ayarlama
  - `bind()`: Port bağlama
  - `listen()`: Dinleme moduna geçme
  
- `serverLoop()`: Ana event loop
  - `poll()`: File descriptor olaylarını bekleme
  - `acceptClient()`: Yeni bağlantıları kabul etme
  - `controlMSG()`: Mesaj okuma ve işleme
  
- `acceptClient()`: Yeni istemci kabul etme
  - `accept()`: Socket bağlantısını kabul etme
  - Boş pollfd slot bulma
  - "Server full" kontrolü

- `exec()`: Komut yönlendirme ve işleme
- `controlUsername()`: Unique username kontrolü
- `controlNickname()`: Unique nickname kontrolü
- `getChannel()`: İsme göre kanal bulma
- `getClient()`: Nickname'e göre istemci bulma

#### Client.hpp & Client.cpp
**Açıklama:** İstemci sınıfı ve kullanıcı bilgileri

**Client Class:**
- **Private Members:**
  - `string nickname`: Kullanıcı takma adı
  - `string username`: Kullanıcı adı
  - `string hostname`: Host bilgisi
  - `string servername`: Sunucu bilgisi
  - `string realname`: Gerçek ad
  - `vector<string> channels`: Kullanıcının bulunduğu kanallar
  - `Server *server`: Server referansı
  - `int clientSocket`: İstemci fd
  - `bool has_pass, has_nick, has_user`: Authentication flags
  - `bool connect`: Tam bağlantı durumu
  - `bool is_nc`: nc (netcat) istemcisi mi?

**Fonksiyonlar:**
- `setNickname()`: Nickname atama ve kanal güncelleme
- `setUser()`: User bilgilerini ayarlama
- `confirmPassword()`: Şifre onaylama
- `controlConnect()`: Bağlantı durumu kontrolü
- `addChannel()`: Kanala katılma
- `deleteChannel()`: Kanaldan ayrılma
- `allDeleteChannel()`: Tüm kanallardan çıkış
- `inChannel()`: Kanal üyeliği kontrolü
- `printInfo()`: Kullanıcı bilgilerini yazdırma

#### Channel.hpp & Channel.cpp
**Açıklama:** Kanal sınıfı ve kanal yönetimi

**Channel Class:**
- **Private Members:**
  - `string name`: Kanal adı (#channel)
  - `string topic`: Kanal konusu
  - `string password`: Kanal şifresi (+k mode)
  - `vector<string> clients`: Kanal üyeleri
  - `Client *moderator`: Kanal operatörü
  - `Server *server`: Server referansı
  - `bool isItClosedToOutside`: Dışarıdan mesaj (+n mode)
  - `int limit`: Kullanıcı limiti (+l mode)

**Fonksiyonlar:**
- `Channel()`: Constructor - Moderator ataması
- `addClient()`: Kullanıcı ekleme
- `deleteClient()`: Kullanıcı çıkarma ve yeni moderator atama
- `changeNameClient()`: Nickname değişikliği güncelleme
- `setLock()`: Kanal şifresi ayarlama (+k)
- `isMatchPassword()`: Şifre kontrolü
- `setIsItClosedToOutside()`: +n mode ayarlama
- `setLimit()`: Kullanıcı limiti (+l)
- `setTopic()`: Konu değiştirme
- `printTopic()`: Konu yazdırma
- `getUsers()`: Kullanıcı listesi (@moderator işaretiyle)
- `showTable()`: Kanal tablosunu gösterme
- `info()`: Kanal detaylarını yazdırma

#### Utils.hpp & Utils.cpp
**Açıklama:** Yardımcı fonksiyonlar ve macro tanımları

**Macro Tanımları (IRC Reply Codes):**
- `RPL_NICK`: Nickname değişikliği mesajı
- `RPL_JOIN`: Kanala katılım mesajı
- `RPL_INVITE`: Davet mesajı
- `RPL_PRIVMSG`: Özel mesaj formatı
- `RPL_PART`: Kanaldan ayrılma mesajı
- `RPL_KICK`: Kick mesajı
- `RPL_TOPIC`: Topic değişikliği mesajı
- `RPL_NAMREPLY`: Kanal kullanıcı listesi (353)
- `ERR_NEEDMOREPARAMS`: Eksik parametre hatası (461)
- `ERR_NICKNAMEINUSE`: Nickname kullanımda hatası (433)
- `ERR_NOSUCHCHANNEL`: Kanal bulunamadı (403)
- `ERR_BADCHANNELKEY`: Yanlış kanal şifresi (475)
- `ERR_CHANNELISFULL`: Kanal dolu (471)
- `ERR_ALREADYREGISTRED`: Zaten kayıtlı (462)

**Utility Fonksiyonlar:**
- `writeln()`: File descriptor'a string yazma
- `clearSpacesFromStartandEnd()`: String trimming
- `convertToUppercaseString()`: Uppercase dönüşüm (kanal adları için)
- `special_split()`: Özel split fonksiyonu

#### main.cpp
**Açıklama:** Programın giriş noktası

**Fonksiyonlar:**
- `main()`: Program başlangıcı
- `arg_control()`: Komut satırı argüman kontrolü
  - Port kontrolü (0-65535 arası)
  - Password kontrolü (space içermemeli)
- `signal_handle()`: Signal yakalama (SIGINT, SIGHUP)
  - Graceful shutdown
  - Server kaynakları temizleme

### Commands (IRC Komutları)

#### PASS.cpp
**Komut:** `PASS <password>`
**Açıklama:** Sunucuya bağlanmak için şifre girişi

**Kontroller:**
- Parametre sayısı
- Space karakteri kontrolü
- Şifre eşleşmesi
- Zaten bağlı mı kontrolü
- Şifre daha önce girilmiş mi kontrolü

#### NICK.cpp
**Komut:** `NICK <nickname>`
**Açıklama:** Kullanıcı nickname ayarlama/değiştirme

**Kontroller:**
- Nickname unique mi?
- '#' ile başlamıyor mu? (kanal için rezerve)
- Space içermiyor mu?
- Tüm kanallarda nickname güncelleme

**Özellikler:**
- İlk NICK: Kayıt işlemi
- Sonraki NICK: Değişiklik ve tüm kanallara bildirim

#### USER.cpp
**Komut:** `USER <username> <hostname> <servername> <realname>`
**Açıklama:** Kullanıcı bilgilerini ayarlama

**Kontroller:**
- Tüm parametrelerde '#' yok mu?
- Space içermiyor mu?
- Username unique mi?
- Zaten kayıtlı değil mi?

**Bağlantı Durumu:**
- NICK + USER = Tam bağlantı

#### JOIN.cpp
**Komut:** `JOIN #<channel> [password]`
**Açıklama:** Kanala katılma

**İşleyiş:**
1. Kanal yoksa oluştur (ilk kullanıcı moderator)
2. Password kontrolü (+k mode varsa)
3. Limit kontrolü (+l mode varsa)
4. Zaten üye değil mi kontrolü
5. Kullanıcıyı ekle
6. Tüm kanal üyelerine bildirim
7. Topic varsa göster

**Kanal İsimlendirme:**
- '#' ile başlamalı
- Uppercase'e çevrilir
- Minimum 2 karakter

#### PRIVMSG.cpp
**Komut:** `PRIVMSG <target> :<message>`
**Açıklama:** Mesaj gönderme (kanal veya kullanıcı)

**Hedef Türleri:**
1. **Kanal (#channel):**
   - Kanal üyesi mi kontrolü
   - +n mode: Sadece üyeler gönderebilir
   - Tüm kanal üyelerine yayınlama (gönderen hariç)

2. **Kullanıcı (nickname):**
   - Kullanıcı var mı kontrolü
   - Direct message

**Format:**
- IRC client: RPL_PRIVMSG formatı
- nc client: Basit format

#### PART.cpp
**Komut:** `PART #<channel>`
**Açıklama:** Kanaldan ayrılma

**İşleyiş:**
- Kanal var mı?
- Kullanıcı üye mi?
- Kanaldan çıkar
- Diğer üyelere bildirim
- Moderator ise yeni moderator ata

#### KICK.cpp
**Komut:** `KICK #<channel> <nickname> [:<reason>]`
**Açıklama:** Kullanıcıyı kanaldan atma

**Kontroller:**
- Sadece moderator kullanabilir
- Hedef kullanıcı kanalda mı?
- Kendini atamaz
- Reason opsiyonel

**İşleyiş:**
- Kullanıcıyı kanaldan çıkar
- Atılan kullanıcıya bildirim

#### MODE.cpp
**Komut:** `MODE #<channel> [mode] [parameters]`
**Açıklama:** Kanal modlarını yönetme (sadece moderator)

**Mod Türleri:**
1. **+k `<password>`**: Kanal şifresi ayarla
2. **-k**: Kanal şifresini kaldır
3. **+l `<limit>`**: Kullanıcı limiti ayarla
4. **-l**: Limiti kaldır
5. **+n**: Dışarıdan mesaj yasağı
6. **-n**: Dışarıdan mesaj izni

**Kontroller:**
- Moderator yetkisi
- Parametre doğruluğu
- Limit: pozitif sayı, MAX_CLIENTS'tan az

#### TOPIC.cpp
**Komut:** 
- `TOPIC #<channel>`: Topic görüntüleme
- `TOPIC #<channel> :<topic>`: Topic değiştirme

**Kontroller:**
- Kullanıcı kanalda mı?
- Topic değiştirme: Sadece moderator

**İşleyiş:**
- Tüm kanal üyelerine yeni topic bildirimi
- Topic history yok (sadece son topic)

#### INVITE.cpp
**Komut:** `INVITE <nickname> #<channel>`
**Açıklama:** Kullanıcıyı kanala davet etme

**Kontroller:**
- Davet eden kanalda mı?
- Hedef kullanıcı var mı?
- Hedef zaten kanalda değil mi?

**İşleyiş:**
- Hedef kullanıcıya davet mesajı
- JOIN komutu ile kanala giriş talimatı

#### WHO.cpp
**Komut:** `WHO #<channel>`
**Açıklama:** Kanal üyelerini listeleme

**Çıktı:**
- Kanal adı
- Moderator (@işareti ile)
- Tüm üyeler

#### INFO.cpp
**Komut:** `INFO`
**Açıklama:** Kullanıcının kendi bilgilerini görüntüleme

**Gösterilenler:**
- Nickname, Username
- Hostname, Servername, Realname
- Üye olunan kanallar

#### CHANNELINFO.cpp
**Komut:** `CHANNELINFO`
**Açıklama:** Tüm kanalları listeleme

**Çıktı:**
- Her kanal için:
  - Kanal adı
  - Moderator
  - Üye listesi

#### EXIT_AND_QUIT.cpp
**Komutlar:** `EXIT` / `QUIT`
**Açıklama:** Sunucudan çıkış

**İşleyiş:**
- Tüm kanallardan çıkış
- Connection temizleme
- Socket kapatma
- Console log

#### CAP.cpp
**Komut:** `CAP`
**Açıklama:** Client capability negotiation (HexChat için)

**İşleyiş:**
- Komut listesi gösterme
- IRC client başlangıç protokolü

### Makefile

**Derleme Ayarları:**
```makefile
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98
```

**Hedefler:**
- `all`: Executable oluşturma
- `clean`: Object dosyaları silme
- `fclean`: Executable silme
- `re`: Yeniden derleme

**Kaynak Dosyalar:**
- Core: main.cpp, Server.cpp, Client.cpp, Channel.cpp, Utils.cpp
- Commands: 15 komut dosyası

## 🔧 Kullanım

### Derleme
```bash
make
```

### Çalıştırma
```bash
./ircserv <port> <password>
```

**Parametreler:**
- `port`: 0-65535 arası port numarası
- `password`: Sunucu şifresi (space içermemeli)

### Örnek:
```bash
./ircserv 6667 mypassword
```

### İstemci Bağlantısı

#### HexChat ile:
1. HexChat'i aç
2. Network List → Add
3. Server: `127.0.0.1/6667`
4. Connect
5. Password gir: `mypassword`
6. Nickname ve username ayarla

#### nc (netcat) ile:
```bash
nc 127.0.0.1 6667
```

**Komut Dizisi:**
```
PASS mypassword
NICK johndoe
USER john localhost localhost :John Doe
JOIN #general
PRIVMSG #general :Hello everyone!
```

### Komut Örnekleri

#### Temel Bağlantı
```
PASS mypassword
NICK alice
USER alice localhost localhost :Alice Smith
```

#### Kanal İşlemleri
```
JOIN #general
JOIN #secret mypassword
PART #general
TOPIC #general :Welcome to general channel
```

#### Mesajlaşma
```
PRIVMSG #general :Hello everyone
PRIVMSG bob :Hi Bob, private message
```

#### Moderator Komutları
```
MODE #general +k secret123
MODE #general +l 50
MODE #general +n
KICK #general bob :Spamming
INVITE charlie #general
```

#### Bilgi Komutları
```
INFO
WHO #general
CHANNELINFO
```

#### Çıkış
```
EXIT
QUIT
```

## 🎯 Öğrenilen Kavramlar

1. **Socket Programming**: TCP/IP socket oluşturma ve yönetimi
2. **Network Protocols**: IRC protocol (RFC 1459) implementasyonu
3. **Poll Mechanism**: poll() ile non-blocking I/O
4. **Client-Server Architecture**: Çoklu istemci mimarisi
5. **File Descriptors**: fd yönetimi ve multiplexing
6. **C++ OOP**: Class design, encapsulation
7. **String Parsing**: Protocol message parsing
8. **State Management**: Client ve channel state tracking
9. **Error Handling**: Network ve protocol error handling
10. **Signal Handling**: Graceful shutdown
11. **Memory Management**: C++98 ile dynamic memory
12. **Vector Operations**: STL vector kullanımı
13. **Protocol Design**: Command-response pattern
14. **Authentication**: Password-based auth
15. **Authorization**: Role-based permissions (moderator)

## 🔍 Teknik Detaylar

### Socket Flow
```
socket() → setsockopt() → bind() → listen() → poll() → accept()
                                                 ↓
                                              recv() → parse() → execute() → send()
```

### Poll Mechanism
- **pollFds[0]**: Server socket (yeni bağlantılar)
- **pollFds[1-100]**: Client sockets
- **POLLIN**: Okunabilir veri var
- **Timeout**: 10000ms (istemci yoksa), -1 (var ise)

### Authentication Flow
```
Client → PASS → Server (verify) → NICK → USER → Connected
                    ↓
                  Fail → Disconnect
```

### Channel Lifecycle
```
JOIN (first user) → Create Channel + Set Moderator
                          ↓
                    Add Members → MODE/TOPIC/KICK operations
                          ↓
                    Last user PART → Delete Channel
```

### Message Broadcasting
- **Channel message**: Tüm üyelere (gönderen hariç)
- **Private message**: Tek kişiye
- **System message**: Belirli durumlarda (join, part, kick, topic)

### Moderator System
- **İlk kullanıcı**: Kanal oluşturan moderator olur
- **Moderator ayrılırsa**: İkinci sıradaki üye moderator olur
- **Yetkiler**: MODE, KICK, TOPIC, INVITE

### Client Types
- **IRC Client (HexChat)**: RFC formatında mesajlar
- **nc (netcat)**: Basit text formatında mesajlar
- `is_nc` flag ile ayrım yapılır

## 📋 Notlar

- Program C++98 standardına uygun yazılmıştır
- `-Wall -Wextra -Werror` ile derlenmiştir
- MacOS üzerinde geliştirilmiş ve test edilmiştir
- Poll() ile non-blocking I/O kullanılmıştır
- Maksimum 100 eş zamanlı istemci desteklenir
- Kanal isimleri case-insensitive (uppercase'e çevrilir)
- Password space karakteri içeremez
- Nickname ve username unique olmalıdır
- Her kanal bir moderator'a sahiptir
- HexChat ve nc ile test edilmiştir
- Signal handling ile graceful shutdown desteklenir

## ⚠️ UYARI

**ÖNEMLİ:** Bu proje maalesef aceleye gelmiş bir projedir ve 42 Kocaeli'nde tamamlanmıştır. Proje **MacOS** üzerinde geliştirilmiştir. Makefile'da bir hata yaptığımı fark ettim ve sadece derlenebilir hale getirmek için Makefile'ı düzelttim, başka bir değişiklik yapmadım. Projenin geri kalanı orijinal haliyle kalmıştır. Zamanında bazı kişisel kontrol standartlarına (null check, error handling, edge cases, vb.) yeterince dikkat edilmemiş olabilir. Bu proje zaman kısıtlaması altında tamamlandığı için kod kalitesi ve best practices açısından ideal olmayabilir. Ancak temel IRC protokolü ve socket programlama kavramlarını göstermektedir.

