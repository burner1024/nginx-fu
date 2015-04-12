include inc/defaults.inc;

charset utf-8;

# Uncomment this if Nginx servers as SSL termination point
sub_filter 'http://$server_name' 'https://$server_name';
sub_filter_once off;

location /config {
  deny all;
}
location /data {
  deny all;
}
location ~.*\.(3gp|gif|jpg|jpeg|png|ico|wmv|avi|asf|asx|mpg|mpeg|mp4|pls|mp3|mid|wav|swf|flv|html|htm|txt|js|css|exe|zip|tar|rar|gz|tgz|bz2|uha|7z|doc|docx|xls|xlsx|pdf|iso|ico)$ {
  expires 7d;
  try_files $uri @apache;
}
location / {
  proxy_pass http://$apache_host:$apache_port;
}
location @apache {
  proxy_pass http://$apache_host:$apache_port;
}
