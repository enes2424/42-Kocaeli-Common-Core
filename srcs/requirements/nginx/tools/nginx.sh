#!/bin/bash

openssl req -x509 \
			-nodes \
			-days 365 \
			-newkey rsa:4096 \
			-keyout $PRIVATE_KEY \
			-out $CERTIFICATE \
			-subj "/CN=$DOMAIN_NAME";

sed -i "s|!DOMAIN_NAME!|$DOMAIN_NAME|g" /etc/nginx/sites-enabled/default
sed -i "s|!CERTIFICATE!|$CERTIFICATE|g" /etc/nginx/sites-enabled/default
sed -i "s|!PRIVATE_KEY!|$PRIVATE_KEY|g" /etc/nginx/sites-enabled/default

exec nginx -g 'daemon off;'
