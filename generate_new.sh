echo 'paras:'$#

PRO_SRC='module_example/'

if [[ $# -eq 0 ]]; then
  echo 'please input target project_name'
  exit
elif [[ $# ]]; then
  cd $PRO_SRC && chmod +x operate.sh && ./operate.sh clean && cd ..
  cp $PRO_SRC $1 -rf
  echo 'generate project:'$1
  echo 'src project     :'$PRO_SRC
fi
