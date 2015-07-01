include inc/wordpress-wordfence-falcon.inc;

location ~ .php$ {
  try_files $uri /index.php;
  include fastcgi_params;
  fastcgi_param PATH_TRANSLATED $document_root$fastcgi_script_name;
  fastcgi_pass   $fastcgi_host:$fastcgi_port;
}
