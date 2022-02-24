https://www.liaoxuefeng.com/wiki/896043488029600

# 集中式vs分布式

**集中式版本控制系统**

版本库是集中存放在中央服务器的。

最大的毛病就是必须联网才能工作，如果在局域网内还好，带宽够大，速度够快，可如果在互联网上，遇到网速慢的话，可能提交一个10M的文件就需要5分钟

**分布式版本控制系统**

没有“中央服务器”，每个人的电脑上都是一个完整的版本库

通常也有一台充当“中央服务器”的电脑，但这个服务器的作用仅仅是用来方便“交换”大家的修改，没有它大家也一样干活，只是交换修改不方便而已。



# 创建，配置

生成ssh公钥，默认路径在`~/.ssh` 目录下，复制 `.pub` 文件中的内容即可

```console
ssh-keygen
```

```bash
# 配置用户名，邮箱
$ git config --global user.name "Your Name"
$ git config --global user.email "email@example.com"
# 通过git init命令把这个目录变成Git可以管理的仓库：
$ git init
```



# 本地

添加文件到Git仓库，分两步：

1. 使用命令`git add <file>`，注意，可反复多次使用，添加多个文件；
2. 使用命令`git commit -m <message>`，完成。

```bash
# 1. 添加文件到Git仓库，分两步
# 将文件从工作区提交到暂存区
$ git add <file>
# 将文件从暂存区提交到本地仓库
$ git commit -m <message>
# 也可合并上述两个命令
$ git commit -a

# 2. 掌握仓库当前的状态
$ git status

# 3. 查看文件difference
$ git diff readme.txt

# 4. 将工作区文件撤销修改
$ git restore <file>

# 5. 将暂存区文件撤销修改
$ git restore --staged <file>

# 6. 删除文件并add
$ git rm <file>

# 7. 查看提交日志
# --pretty=oneline 输出为一条一行
# --abbrev-commit 简略commit id
# --graph 查看分支合并情况
$ git log

# 8. 查看命令历史
$ git reflog

# 9. 版本回退
# 上一个版本就是HEAD^，上n个版本为HEAD~n
$ git reset --hard HEAD^

# 10. 存储工作现场
$ git stash
# 查看存储的工作现场
$ git stash list
# 恢复并删除第一条工作现场
$ git stash pop
# 恢复工作现场，默认第一条
$ git stash apply stash@{0}
# 删除存储的工作现场，默认第一条
$ git stash drop stash@{0}
```



# 远程

```bash
# 1. 查看远程库信息
$ git remote -v

# 2. 把一个已有的本地仓库与远程仓库关联
$ git remote add origin git@github.com:sofice/md_note.git

# 3. 解除了本地和远程的绑定关系
$ git remote rm origin

# 4. 克隆远程仓库
$ git clone git@github.com:sofice/md_note.git

# 5. 推送到远程仓库
# 加上-u参数，会把本地的master分支和远程的master分支关联起来
$ git push origin master

# 6. 拉取到本地
$ git pull origin master

# 7. 克隆远程仓库到本地
$ git clone git@github.com:michaelliao/gitskills.git
```



# 分支

在实际开发中，我们应该按照几个基本原则进行分支管理：

首先，`master`分支应该是非常稳定的，也就是仅用来发布新版本，平时不能在上面干活；

那在哪干活呢？干活都在`dev`分支上，也就是说，`dev`分支是不稳定的，到某个时候，比如1.0版本发布时，再把`dev`分支合并到`master`上，在`master`分支发布1.0版本；

你和你的小伙伴们每个人都在`dev`分支上干活，每个人都有自己的分支，时不时地往`dev`分支上合并就可以了

```bash
# 1. 创建分支
# --set-upstream-to=origin/master 将远程分支与本地分支绑定
$ git branch dev
# 2. 切换分支
$ git switch dev
# 上述两个命令可合并，创建并切换
$ git switch -c dev

# 3. 查看分支
$ git branch

# 4. 将指定分支合并到当前分支
# --no-ff -m 'merged bug fix 101' 在merge时生成一个新的commit，从分支历史上就可以看出分支信息
$ git merge dev

# 5. 删除分支
# -d 改为 -D 可以强行删除一个没有被合并过的分支
$ git branch -d dev

# 6. 本地分支重命名
$ git branch -m oldbranch newbranch

# 7. 把其他分支上的提交合并到当前分支
$ git cherry-pick <commit>

# 8. 把本地未push的分叉提交历史整理成直线
$ git rebase
```

**BUG分支**

在需要解决bug时，可以用 `git stash` 先保存当前工作进度，切换到要修改bug的分支，创建解决bug编号为 n 的分支：`issue-n`，进行修改提交合并，然后切换回自己的工作分支，恢复工作现场。如果想要同步解决的bug，可用 `git cherry-pick`

**Feature分支**

开发一个新feature，最好新建一个分支，在上面开发，完成后，合并，最后删除该feature分支

如果要丢弃一个没有被合并过的分支，可以通过`git branch -D <name>`强行删除。



# 标签

```bash
# 1. 查看所有标签，按字母排序
$ git tag

# 2. 打标签到一个commit上，默认最新的commit
$ git tag v0.9 f52c633
# 创建带有说明的标签
$ git tag -a v0.1 -m "version 0.1 released" 1094adb

# 3. 推送标签到远程
# 创建的标签都只存储在本地，不会自动推送到远程
$ git push origin v1.0
# 一次性推送全部尚未推送到远程的本地标签
$ git push origin --tags

# 4. 删除标签
$ git tag -d v0.1
# 如果标签已经推送到远程，要删除远程标签：先从本地删除，再从远程删除
$ git tag -d v0.9
$ git push origin :refs/tags/v0.9
```



# 自定义Git

## .gitignore

```bash
# Windows:
Thumbs.db
ehthumbs.db
Desktop.ini

# Python:
*.py[cod]
*.so
*.egg
*.egg-info
dist
build

# My configurations:
db.ini
deploy_key_rsa

# 不排除.gitignore和App.class:
!.gitignore
!App.class
```

```bash
# 1. 忽略.gitignore，强制添加
$ git add -f App.class

# 2. 检查第几行规则生效
$ git check-ignore -v App.class
```

## 配置别名

```bash
# st表示status
$ git config --global alias.st status
# 便捷log
$ git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"
```