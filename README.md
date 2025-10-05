# 42 Kocaeli Inception
## System Administration & DevOps Infrastructure (Sistem Yönetimi & DevOps Altyapısı)

Bu proje, 42 Common Core'un en zorlu projelerinden biridir. Docker, Docker Compose, NGINX, MariaDB ve WordPress teknolojilerini kullanarak tam işlevli bir web altyapısı oluşturmayı hedefler. Proje, container'lar arası network iletişimi, SSL sertifikaları, veritabanı yönetimi ve web sunucusu konfigürasyonu konularında derin bilgi gerektirir.

## � Servisler

### MariaDB Service
**Dosyalar:** `srcs/requirements/mariadb/`

MySQL uyumlu veritabanı sunucusu.
- **Image:** Debian Bullseye üzerinde MariaDB
- **Port:** 3306 (internal network)
- **Volume:** `/home/eates/data/mariadb` → `/var/lib/mysql`
- **Özellikler:**
  - Otomatik veritabanı ve kullanıcı oluşturma
  - Bind-mount ile veri kalıcılığı
  - Network üzerinden erişim konfigürasyonu
- **Konfigürasyon:**
  ```properties
  bind-address = 0.0.0.0
  port = 3306
  character-set-server = utf8mb4
  ```

### WordPress Service
**Dosyalar:** `srcs/requirements/wordpress/`

PHP-FPM ile çalışan WordPress CMS.
- **Image:** Debian Bullseye + PHP 7.4-FPM
- **Port:** 9000 (FastCGI)
- **Volume:** `/home/eates/data/wordpress` → `/var/www/html`
- **Dependencies:** MariaDB servisi
- **Özellikler:**
  - WP-CLI ile otomatik kurulum
  - Admin ve normal kullanıcı oluşturma
  - PHP-FPM pool konfigürasyonu
  - FastCGI optimizasyonları
- **WP-CLI Komutları:**
  ```bash
  wp core download --allow-root
  wp config create --dbhost=mariadb
  wp core install --url=${DOMAIN_NAME}
  wp user create ${WORDPRESS_USER}
  ```

### NGINX Service
**Dosyalar:** `srcs/requirements/nginx/`

Reverse proxy ve SSL termination.
- **Image:** Debian Bullseye + NGINX + OpenSSL
- **Port:** 443 (HTTPS)
- **Dependencies:** WordPress servisi
- **Volume:** WordPress dosyalarına erişim
- **Özellikler:**
  - Self-signed SSL sertifikası oluşturma
  - TLS v1.2 ve v1.3 desteği
  - FastCGI proxy WordPress'e
  - Domain name routing
- **SSL Konfigürasyonu:**
  ```bash
  openssl req -x509 -nodes -days 365 -newkey rsa:4096
  ssl_protocols TLSv1.2 TLSv1.3
  ```

## 🔧 Kullanım

### Ön Gereksinimler
```bash
# Docker ve Docker Compose kurulumu
sudo apt-get update
sudo apt-get install docker.io docker-compose
sudo usermod -aG docker $USER
```

### Proje Kurulumu
```bash
# 1. Environment dosyasını hazırla
cp srcs/tmp_env srcs/.env
# .env dosyasını düzenle (zorunlu)

# 2. Projeyi başlat
make

# 3. Durumu kontrol et
docker ps
docker-compose -f srcs/docker-compose.yml logs
```

### Makefile Komutları
```bash
make        # Tüm servisleri build et ve başlat
make down   # Servisleri durdur
make reup   # Yeniden başlat (down + up)
make clean  # Tüm container, volume ve image'ları temizle
make re     # Temizle ve yeniden başlat
```

### Erişim
```bash
# WordPress'e erişim
https://eates.42.fr

# Container'lara erişim
docker exec -it nginx bash
docker exec -it wordpress bash
docker exec -it mariadb bash
```

## 📁 Proje Yapısı

```
├── Makefile                          # Build ve deploy komutları
├── srcs/
│   ├── docker-compose.yml           # Multi-container orchestration
│   ├── .env                         # Environment değişkenleri
│   └── requirements/
│       ├── mariadb/
│       │   ├── Dockerfile           # MariaDB container tanımı
│       │   ├── conf/mariadb.conf    # MySQL konfigürasyonu
│       │   └── tools/mariadb.sh     # Database initialization script
│       ├── nginx/
│       │   ├── Dockerfile           # NGINX container tanımı
│       │   ├── conf/nginx.conf      # Server blocks ve SSL config
│       │   └── tools/nginx.sh       # SSL cert generation script
│       ├── wordpress/
│       │   ├── Dockerfile           # WordPress container tanımı
│       │   ├── conf/wordpress.conf  # PHP-FPM pool configuration
│       │   └── tools/wordpress.sh   # WP installation script
│       └── tools/
│           ├── hosts                # Local DNS override
│           └── original_hosts       # Backup of original hosts
```

## 🌐 Network Mimarisi

```
┌─────────────────┐
│   Host Machine  │
│  eates.42.fr    │
└─────────┬───────┘
          │ :443 (HTTPS)
┌─────────▼───────┐
│     NGINX       │
│   (SSL Term.)   │
└─────────┬───────┘
          │ :9000 (FastCGI)
┌─────────▼───────┐
│   WordPress     │
│   (PHP-FPM)     │
└─────────┬───────┘
          │ :3306 (MySQL)
┌─────────▼───────┐
│    MariaDB      │
│  (Database)     │
└─────────────────┘
```

## 🎯 Öğrenilen Kavramlar

1. **Container Orchestration**: Docker Compose ile multi-service uygulamalar
2. **Network Isolation**: Docker networks ile servis izolasyonu
3. **Volume Management**: Bind mounts ile veri kalıcılığı
4. **SSL/TLS Security**: Self-signed sertifikalar ve HTTPS konfigürasyonu
5. **Reverse Proxy**: NGINX ile yük dağıtımı ve SSL termination
6. **Database Administration**: MariaDB kurulumu ve kullanıcı yönetimi
7. **PHP-FPM**: FastCGI Process Manager konfigürasyonu
8. **Environment Configuration**: .env dosyaları ile güvenli konfigürasyon
9. **Service Dependencies**: Container başlatma sırası ve bağımlılık yönetimi
10. **Host File Management**: Local DNS override teknikleri

## 🔐 Güvenlik Özellikleri

- **HTTPS Only**: HTTP trafiği kabul edilmez
- **TLS 1.2/1.3**: Modern SSL/TLS protokolleri
- **Network Isolation**: Container'lar arası güvenli iletişim
- **Environment Variables**: Hassas bilgilerin güvenli saklanması
- **Non-Root Users**: Container'larda privilege escalation önleme
- **Volume Permissions**: Dosya sistem izinleri optimizasyonu

## � Environment Değişkenleri

```bash
# Domain ve SSL
DOMAIN_NAME=eates.42.fr
PRIVATE_KEY=/etc/ssl/private/nginx.key
CERTIFICATE=/etc/ssl/certs/nginx.crt

# MariaDB Ayarları
MYSQL_DATABASE=wordpress
MYSQL_USER=wpuser
MYSQL_PASSWORD=secure_password

# WordPress Ayarları
WORDPRESS_USER=normaluser
WORDPRESS_EMAIL=user@example.com
WORDPRESS_ADMIN_USER=admin
WORDPRESS_ADMIN_PASSWORD=admin_password
WORDPRESS_ADMIN_EMAIL=admin@example.com
```

## 🔧 Troubleshooting

### Container Logları
```bash
docker-compose -f srcs/docker-compose.yml logs nginx
docker-compose -f srcs/docker-compose.yml logs wordpress
docker-compose -f srcs/docker-compose.yml logs mariadb
```

### Network Kontrol
```bash
docker network ls
docker network inspect inception
```

### Volume Kontrol
```bash
docker volume ls
ls -la /home/eates/data/
```

### SSL Sertifika Kontrol
```bash
openssl x509 -in /path/to/cert -text -noout
curl -k -v https://eates.42.fr
```

## 📝 Notlar

- Tüm container'lar Debian Bullseye base image kullanır
- Volume mount'lar host makinesinde veri kalıcılığı sağlar
- SSL sertifikaları her container restart'ında yeniden oluşturulur
- WordPress kurulumu otomatik olarak gerçekleşir
- Hosts dosyası otomatik olarak backup'lanır ve geri yüklenir
- Container'lar restart policy ile otomatik yeniden başlatılır