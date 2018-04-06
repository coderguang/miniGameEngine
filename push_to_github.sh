#shell
#***********************************************
#
#      Filename: copy.sh
#
#      Author: royalchen 
#      Email: royalchen@royalchen.com
#      website: www.royalchen.com
#      Description: ----
#

#     Create: 2017-12-11 16:17:50
#     Last Modified: 2017-12-11 16:17:50
#***********************************************


dst_dir=/home/guang/github/GameWorld/
cur_dir=`pwd`

#first update code

svn update .

msg=$1

cd ../

rsync -avz --delete --exclude='lobby' --exclude='107_miniGame' --exclude='*.d' --exclude='runnable'  --exclude='.svn/' --exclude='.git' --exclude='*.log' --exclude='*.o' --exclude='*.a' --exclude='*.lib' --exclude='*.dll' --exclude='libboost_*' --exclude='Task.txt' --exclude='*.exe' --exclude='dbdata' GameWorld/ $dst_dir

cd $dst_dir

git add *
git commit -a -m "$1"
git push

cd $cur_dir

