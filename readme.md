hello world~
git add添加到上传缓存区
git commit给缓存区的内容添加备注，此时本地的commit修改啦，但是远程的commit和文件都没修改。
git push 修改远程文件和commit信息
而你下拉文件过程

git fetch 将数据拉下来，但是没修改本地的commit和文件
git merge 改变本地数据

$ git add +文件名.文件类型 ，将某个文件加到缓存区
$ git add +文件名.文件类型 ... 文件名.文件类型 ，将n个文件添加到缓存区
$ git add xx文件夹/*.html，将xx文件夹下的所有的html文件添加到缓存区。
$ git add *hhh ，将以hhh结尾的文件的所有修改添加到暂存区
$ git add Hello* ，将所有以Hello开头的文件的修改添加到暂存区
git add -u ，提交被修改(modified)和被删除(deleted)文件，不包括新文件(new)
git add .，提交新文件(new)和被修改(modified)文件，不包括被删除(deleted)文件
…
git add -A，提交所有变化。git add前几条都可以记不住，这个必须记住！！！


我们第一次推送master分支时，加上 –u参数才会把本地的master分支和远程的master分支关联起来，
就是告诉远程仓库的master分支，我的本地仓库和是对着你的哦，不是对着别的分支的哦。
只有第一次推的时候需要加上-u，以后的推送只输入：
$ git push 名称 分支

还记得git remote -v吗？用它看一下你下下来的本地仓库连接上那个远程仓库没。 