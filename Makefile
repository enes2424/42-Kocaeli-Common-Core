COMPOSE_FILE=srcs/docker-compose.yml

all:
	@(ls srcs/requirements/tools/original_hosts || (cp /etc/hosts srcs/requirements/tools/original_hosts && cp srcs/requirements/tools/hosts /etc/hosts)) 2>/dev/null || true
	@mkdir -p /home/eates/data/wordpress
	@mkdir -p /home/eates/data/mariadb
	@docker-compose -f $(COMPOSE_FILE) up --build

down:
	@(ls srcs/requirements/tools/original_hosts && cp srcs/requirements/tools/original_hosts /etc/hosts && rm srcs/requirements/tools/original_hosts) 2>/dev/null || true
	@docker-compose -f $(COMPOSE_FILE) down

reup: down all

re: clean all

clean:
	@(ls srcs/requirements/tools/original_hosts && cp srcs/requirements/tools/original_hosts /etc/hosts && rm srcs/requirements/tools/original_hosts) 2>/dev/null || true
	@docker-compose -f $(COMPOSE_FILE) down --volume
	@rm -rf /home/eates/data/wordpress
	@rm -rf /home/eates/data/mariadb
	@docker rmi srcs_nginx srcs_wordpress srcs_mariadb debian:bullseye 2>/dev/null || true
