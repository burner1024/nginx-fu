### nginx-fu

A collection of snippets to use with Nginx

#### Installation
* `git clone https://github.com/burner1024/nginx-fu.git /opt/nginx-fu`
* `ln -s /opt/nginx-fu/inc /etc/nginx/inc`
* Set the required variables in the server block of your vhost (check defaults.inc for examples)
* Use the includes in your vhost

#### Example
Wordress with W3 Total Cache (page enhanced)
```
server {
  listen     80;
  server_name  example1.com;
  charset utf-8;
  access_log  /var/log/nginx/example1.com-access.log combined;
  error_log  /var/log/nginx/example1.com-error.log;
  root /var/www/html/example1.com;

  location / {
    try_files $uri $uri/ /index.php?$args;
  }
  location ~ \.php$ {
    include fastcgi_params;
    fastcgi_param SCRIPT_FILENAME $document_root/$fastcgi_script_name;
    fastcgi_pass   127.0.0.1:9000;
    try_files $uri =404;
  }
  include inc/deny-dot-files.inc;

}
```
