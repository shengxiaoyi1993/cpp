#!/usr/bin/bash
# this script is designed to check the environment os mysql
# docker/mysql-server

echo -e "\nusage: bash -e CheckEnv.sh\n"

read -s -p "please input password:" PASSWORD
echo -e "\nPASSWORD:"$PASSWORD

# check docker
echo -e "\n--------------------docker check--------------------\n"
docker_status=`bash -e checkrun.sh docker`
if [ ${docker_status} == "yes" ];then
  echo "docker is run"
else
  echo "docker is not run,try to launch ..."
  # launch docker
  echo ${PASSWORD} | sudo -S systemctl start docker
  echo -e "\n"
  echo "docker is run !"
fi
echo -e "\n------------------docker check end------------------\n"

# check mysql
echo -e "\n--------------------docker mysql--------------------\n"
mysql_count=`echo ${PASSWORD} | sudo -S docker ps |grep "mysql"|wc -l`
if [ $mysql_count -eq 0 ]; then
  echo "no mysql is running !"
else
  echo -e "${mysql_count} mysql is running!\n"
fi
echo "<all mysql in docker>"
echo ${PASSWORD} | sudo -S docker ps -l
echo -e "\n"
read -p "please input one CONTAINER ID of needed mysql or no :" mysql_conid
if [ ${mysql_conid} == "no" ]; then
  echo "no mysql launch !"
else
  echo ${PASSWORD} | sudo docker restart ${mysql_conid}
  echo -e "mysql ${mysql_conid} has been retart !\n"
fi

echo "<running mysql in docker>"
echo ${PASSWORD} | sudo -S docker ps
echo -e "\n"

echo -e "\n------------------docker mysql end------------------\n"
