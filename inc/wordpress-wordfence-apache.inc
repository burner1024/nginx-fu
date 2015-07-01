include inc/wordpress-wordfence-falcon.inc;

include inc/proxy.inc;

location ~ .php$ {
  proxy_pass http://$apache_host:$apache_port;
}
