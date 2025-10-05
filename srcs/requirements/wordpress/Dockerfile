FROM debian:bullseye

RUN apt-get update && \
	apt-get install -y \
	php7.4-fpm \
	php7.4-mysql \
	wget sendmail && \
	apt-get clean

RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
	&& chmod +x wp-cli.phar \
	&& mv wp-cli.phar /usr/local/bin/wp

COPY conf/wordpress.conf /etc/php/7.4/fpm/pool.d/www.conf

COPY tools/wordpress.sh /wordpress.sh
RUN chmod +x /wordpress.sh

WORKDIR /var/www/html

EXPOSE 9000

ENTRYPOINT ["/wordpress.sh"]
