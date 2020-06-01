# manuals

## build

```
cd executeAnotherExe/build
chmod +x build.sh
./build.sh

[sxy@localhost bin]$ tree
.
├── cycleapp
├── normalapp
├── withexec
├── withfork
└── withsystem

```
## test

```
cd executeAnotherExe/bin
```
###  测试system
- 循环程序:`./withsystem ./cycleapp`

```

Running ps with system
main pid=26956
------
cycleapp pid=26957
in cycleapp
cycleapp pid=26957
in cycleapp
...//持续运行

```
- 正常退出的程序:`./withsystem ./normalapp `

```
Running ps with system
main pid=27076
------
normalapp pid=27077
normalapp end!
------
ps Done

```


###  测试fork
- 循环程序:`./withfork ./cycleapp`

```
main pid=29442
Parent, ps Done
------
cycleapp pid=29443
in cycleapp
[sxy@localhost bin]$ cycleapp pid=29443
in cycleapp
cycleapp pid=29443
in cycleapp
cycleapp pid=29443
in cycleapp
...
//持续运行

```

- 正常退出的程序:`./withfork ./normalapp `

```
main pid=29576
Parent, ps Done
------
normalapp pid=29577
normalapp end!
```

###  测试exec
- 循环程序:` ./withexec ./cycleapp `

```
main pid=27527
Running ps with execlp
------
cycleapp pid=27527
in cycleapp
cycleapp pid=27527
in cycleapp
cycleapp pid=27527
in cycleapp
cycleapp pid=27527
in cycleapp
...
//持续运行

```

- 正常退出的程序:`./withexec ./normalapp `

```
main pid=27444
Running ps with execlp
------
normalapp pid=27444
normalapp end!

```

##  测试exec函数组
- `./testexec`
```
execut by execle
execut by execl
exec on execv
exec on execve
exec on execvp
exec by execlp

```
