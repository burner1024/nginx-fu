include inc/defaults.inc;

index  index.php index.html index.htm;

location ~ /(config\.php|common\.php|cache|files|images/avatars/upload|includes|store) {
  deny all;
  return 403;
}

location ~* \.(gif|jpe?g|png|css)$ {
  expires   30d;
}

location /app.php {
  try_files $uri $uri/ /app.php?$query_string;
}

location ~ \.php$ {
  try_files $uri =404;
  include fastcgi.conf;
  fastcgi_pass $fastcgi_host:$fastcgi_port;
}

include inc/deny-dot-files.inc;
