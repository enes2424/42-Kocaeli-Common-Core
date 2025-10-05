FROM debian:bullseye

RUN apt-get update && \
	apt-get install -y nginx openssl && \
	apt-get clean

COPY conf/nginx.conf /etc/nginx/sites-enabled/default
COPY /tools/nginx.sh /nginx.sh
RUN chmod +x /nginx.sh

ENTRYPOINT ["/nginx.sh"]
