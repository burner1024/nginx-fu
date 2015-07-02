include inc/defaults.inc;
include inc/wordpress-w3tc.inc;

include inc/proxy.inc;
location ~ \.php$ {
  proxy_pass http://$apache_host:$apache_port;
}

include inc/static-cache.inc;
include inc/deny-dot-files.inc;
