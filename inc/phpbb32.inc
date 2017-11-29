include inc/defaults.inc;

location / {
  # phpBB uses index.htm
  index index.php index.html index.htm;
  try_files $uri $uri/ @rewriteapp;
}

location @rewriteapp {
  rewrite ^(.*)$ /app.php/$1 last;
}

# Deny access to internal phpbb files.
location ~ /(config\.php|common\.php|includes|cache|files|store|images/avatars/upload) {
  deny all;
  # deny was ignored before 0.8.40 for connections over IPv6.
  # Use internal directive to prohibit access on older versions.
  internal;
}

# Pass the php scripts to fastcgi server specified in upstream declaration.
location ~ \.php(/|$) {
  # Unmodified fastcgi_params from nginx distribution.
  include fastcgi_params;
  # Necessary for php.
  fastcgi_split_path_info ^(.+\.php)(/.*)$;
  fastcgi_param PATH_INFO $fastcgi_path_info;
  fastcgi_param SCRIPT_FILENAME $realpath_root$fastcgi_script_name;
  fastcgi_param DOCUMENT_ROOT $realpath_root;
  try_files $uri $uri/ /app.php$is_args$args;
  fastcgi_pass $fastcgi_host:$fastcgi_port;
}

# Correctly pass scripts for installer
location /install/ {
  # phpBB uses index.htm
  try_files $uri $uri/ @rewrite_installapp;

  # Pass the php scripts to fastcgi server specified in upstream declaration.
  location ~ \.php(/|$) {
    # Unmodified fastcgi_params from nginx distribution.
    include fastcgi_params;
    # Necessary for php.
    fastcgi_split_path_info ^(.+\.php)(/.*)$;
    fastcgi_param PATH_INFO $fastcgi_path_info;
    fastcgi_param SCRIPT_FILENAME $realpath_root$fastcgi_script_name;
    fastcgi_param DOCUMENT_ROOT $realpath_root;
    try_files $uri $uri/ /install/app.php$is_args$args;
    fastcgi_pass $fastcgi_host:$fastcgi_port;
  }
}

location @rewrite_installapp {
  rewrite ^(.*)$ /install/app.php/$1 last;
}

include inc/deny-dot-files.inc;
include inc/static-cache.inc;
