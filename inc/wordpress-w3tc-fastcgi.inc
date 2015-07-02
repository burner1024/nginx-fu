include inc/defaults.inc;
include inc/wordpress-w3tc.inc;

location ~ \.php$ {
  try_files $uri =404;
  include fastcgi_params;
  fastcgi_param SCRIPT_FILENAME $document_root/$fastcgi_script_name;
  fastcgi_pass $fastcgi_host:$fastcgi_port;
}

include inc/static-cache.inc;
include inc/deny-dot-files.inc;
