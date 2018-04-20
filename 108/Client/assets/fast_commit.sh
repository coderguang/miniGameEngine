svn add . --no-ignore --force
for i in  $(svn st | grep \! | awk '{print $2}'); do svn delete $i; done
svn ci -m $1 
