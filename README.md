### nginx-fu

A collection of snippets to use with Nginx

#### Installation
* `git clone https://github.com/burner1024/nginx-fu.git /opt/nginx-fu`
* `ln -s /opt/nginx-fu/inc /etc/nginx/inc`
* Set the required variables in the server block of your vhost (check defaults.inc for examples)
* Use the includes in your vhost

#### Example
Wordpress with W3 Total Cache (page enhanced)
```
server {
  listen     80;
  server_name  example1.com;
  access_log  /var/log/nginx/example1.com-access.log combined;
  error_log  /var/log/nginx/example1.com-error.log;
  root /var/www/html/example1.com;
  include inc/wordpress-w3tc-fastcgi.inc;
}
```
