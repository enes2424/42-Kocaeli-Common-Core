FROM debian:bullseye

RUN apt-get update && \
	apt-get install -y mariadb-server && \
	apt-get clean

COPY conf/mariadb.conf /etc/mysql/mariadb.conf.d/50-server.cnf
RUN chmod 755 /etc/mysql/mariadb.conf.d/50-server.cnf

COPY tools/mariadb.sh /mariadb.sh
RUN chmod +x /mariadb.sh

EXPOSE 3306

ENTRYPOINT ["/mariadb.sh"]
