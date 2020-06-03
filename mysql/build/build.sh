# //https://cdn.mysql.com//Downloads/MySQL-8.0/mysql-boost-8.0.20.tar.gz
# tar -vxf mysql-boost-8.0.20.tar.gz
# useradd -s /sbin/nologin mysql
# sudo mkdir -p /data/mysql/data
#  sudo chown -R mysql:mysql /data/mysql
#  sudo mkdir /usr/local/mysql/ -p
#  sudo tar -zxvf mysql-boost-8.0.20.tar.gz -C /usr/local/mysql/
#
#  cd /usr/local/mysql/mysql-8.0.20/
#
#  sudo yum install centos-release-scl scl-utils-build
#  sudo yum  install devtoolset-7-gcc*
# export CC=/opt/rh/devtoolset-7/root/usr/bin/gcc
# export CPP=/opt/rh/devtoolset-7/root/usr/bin/cpp
# export CXX=/opt/rh/devtoolset-7/root/usr/bin/c++
# sudo ln -s /opt/rh/devtoolset-7/root/usr/bin/* /usr/local/bin/
# hash -r
# sudo yum install ncurses-devel
# sudo cmake3 -DDEFAULT_CHARSET=utf8 -DDEFAULT_COLLATION=utf8_general_ci -DWITH_BOOST=boost


wget http://repo.mysql.com/mysql-community-release-el7-5.noarch.rpm
sudo rpm -ivh mysql-community-release-el7-5.noarch.rpm
#sudo yum update
sudo groupadd mysql
sudo useradd -s /sbin/nologin -g mysql -M mysq
sudo yum install mysql-server
sudo chown mysql:mysql -R /var/lib/mysql
sudo mysqld --initialize --user=root #电脑重启了
sudo systemctl start mysqld
sudo systemctl status mysqld
mysql //start mysql-client
