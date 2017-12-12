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

cd ../
rsync -avz --delete --exclude='.svn/' --exclude='*.log' --exclude='*.o' --exclude='*.a' --exclude='*.lib' --exclude='*.dll' --exclude='libboost_*' --exclude='Task.txt' --exclude='*.exe' --exclude='dbdata' GameWorld/ $dst_dir
cd $cur_dir

