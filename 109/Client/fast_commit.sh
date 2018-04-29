svn add assets/ --no-ignore --force
svn add settings/ --no-ignore --force
for i in  $(svn st | grep \! | awk '{print $2}'); do svn delete $i; done
svn ci -m "push change by mac shell script"
