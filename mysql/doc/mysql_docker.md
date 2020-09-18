

# launch_mysql_in_docker

```
[sxy@localhost ~]$ sudo systemctl start docker

[sxy@localhost ~]$ sudo docker ps
CONTAINER ID        IMAGE               COMMAND             CREATED             STATUS              PORTS               NAMES
[sxy@localhost ~]$ sudo docker ps -l
CONTAINER ID        IMAGE               COMMAND                  CREATED             STATUS                     PORTS               NAMES
dc83dafd5c42        mysql:5.6.48        "docker-entrypoint.s…"   4 weeks ago         Exited (255) 3 hours ago                       mysql-test
[sxy@localhost ~]$ sudo docker restart dc83dafd5c42
dc83dafd5c42


//LOGIN AS CLIENT
[sxy@localhost ~]$ mysql -h 127.0.0.1 -u root -p
//123456


<!-- Create Table: CREATE TABLE `tb_uvsslabel` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
  `dir` char(128) DEFAULT NULL,
  `big` char(128) DEFAULT NULL,
  `small` char(128) DEFAULT NULL, -->

  SELECT id,small
  FROM
  	tb_uvsslabel
  WHERE
  	id NOT IN (
  		SELECT
  			dt.minno
  		FROM
  			(
  				SELECT
  					MIN(id) AS minno
  				FROM
  					tb_uvsslabel
  				GROUP BY
  					small
  			) dt
  	)help

  ORDER BY
    small
```
